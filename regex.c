/*
Copyright (C) 2025 Timothy Norman Murphy <tnmurphy@gmail.com>

Extramake is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 3 of the License, or (at your option) any later
version.

Extramake is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <regex.h>

#include "gnumake.h"
#include "makeint.h"

#include "extramake.h"

GMK_EXPORT int plugin_is_GPL_compatible = 1;

/*
 * $(regcomp pattern)
 * Returns a handle that identifies the pattern or blank if compilation failed.
 *
 * $(regexec handle,string)
 * Returns empty if there is no match, otherwise the match.
 *
 */

/* Should be enough even up to 128 bits */
#define MAX_LENGTH_OCTETS 40
/*
 *       #include <regex.h>

       int regcomp(regex_t *restrict preg, const char *restrict regex,
                   int cflags);
       int regexec(const regex_t *restrict preg, const char *restrict string,
                   size_t nmatch, regmatch_t pmatch[_Nullable restrict nmatch],
                   int eflags);

       size_t regerror(size_t errbuf_size;
                   int errcode, const regex_t *_Nullable restrict preg,
                   char errbuf[_Nullable restrict errbuf_size],
                   size_t errbuf_size);

       void regfree(regex_t *preg);

       typedef struct {
           size_t    re_nsub;
       } regex_t;

       typedef struct {
           regoff_t  rm_so;
           regoff_t  rm_eo;
       } regmatch_t;

       typedef regoff_t;
*/

#define MAX_NREGEXPS 50
regex_t regs[MAX_NREGEXPS];
int reglast = -1;

/* turn a list of flags in a string into an integer */
int get_compile_flags(char *flag_str) {

  int flags = REG_EXTENDED; /* always extended - to keep life simple */

  /*
         Use POSIX Extended Regular Expression syntax when
         interpreting regex.  If not set, POSIX Basic Regular
         Expression syntax is used.

         For the time being it's an enforced default to make things
         simple.

  if (strcasestr(flag_str, "REG_EXTENDED") != NULL) {
      flags |= REG_EXTENDED;
  }
  */

  /*
   *    Do not differentiate case.  Subsequent regexec() searches using this
   * pattern buffer will be case insensitive.
   */
  if (strcasestr(flag_str, "REG_ICASE") != NULL) {
    flags |= REG_ICASE;
  }

  /*
    Report only overall success.  regexec() will use only pmatch for
    REG_STARTEND, ignoring nmatch.
    
    This is problematic for make because there's no match to return and one may
    ask what the great purpose is. The value would be if the match was absolutely
    huge.
   
    if (strcasestr(flag_str, "REG_NOSUB") != NULL) { flags |= REG_NOSUB; }
   */

  /*
   *    Match-any-character operators don't match a newline.
   */
  if (strcasestr(flag_str, "REG_NEWLINE") != NULL) {
    flags |= REG_NEWLINE;
  }

  return flags;
}

GMK_EXPORT char *func_regcomp(const char *func_name, unsigned int argc,
                              char **argv) {
  char *result = NULL;
  long handle = 1L;

  char *startptr = argv[0];
  int compresult = 0;

  NOTUSED(func_name);
  int flags = REG_EXTENDED;

  if (argc == 2) {
    flags = get_compile_flags(argv[1]);
  }

  while (*startptr == ' ' || *startptr == '\t') {
    startptr++;
  }

  /* Non numeric characters are not allowed.
   * signal this by returning the empty string
   * if we spot them */

  reglast += 1;
  regs[reglast].re_nsub = 0;
  handle = reglast;

  compresult = regcomp(&regs[reglast], startptr, flags);

  /* fprintf(stderr, "compile result nsubs=%ld\n", regs[reglast].re_nsub); */
  if (compresult != 0) {
    fprintf(stderr, "regcomp: failure to compile '%s'\n", startptr);
    return NULL;
  }

  result = gmk_alloc(MAX_LENGTH_OCTETS);
  (void)snprintf(result, MAX_LENGTH_OCTETS - 1, "%ld", handle);
  result[MAX_LENGTH_OCTETS - 1] = '\0';

  return result;
}

GMK_EXPORT char *func_regexec(const char *func_name, unsigned int argc,
                              char **argv) {
  char *result = NULL;
  long handle = -1L;

  char *startptr = argv[0];
  char *source_string = NULL;
  int reg_result = 0;

  NOTUSED(func_name);
  NOTUSED(argc);

  while (*startptr == ' ' || *startptr == '\t') {
    startptr++;
  }

  /* Non numeric characters are not allowed.
   * signal this by returning the empty string
   * if we spot them */

  if (!isdigit(*startptr)) {
    fprintf(stderr, "Non numeric regex handle\n");
    return NULL;
  }
  handle = atol(startptr);

  if (handle < 0 || handle > reglast) {
    fprintf(stderr, "Invalid regex handle %ld %d\n", handle, reglast);
    return NULL;
  }

  source_string = argv[1];

  if (source_string == NULL) {
    fprintf(stderr, "Invalid source string\n");
    return NULL;
  }

  {

    int nmatches = regs[reglast].re_nsub + 1;

    regmatch_t pmatch[nmatches];

    /* initialise the results in case there's a REG_NOSUB
     * flag on the compiled regexp and we don't
     * get the matches we expect */
    for (int i = 0; i < nmatches; i++) {
      pmatch[i].rm_so = -1;
    }

    reg_result = regexec(&regs[reglast], source_string, nmatches, pmatch, 0);

    if (reg_result != 0) {
      return NULL;
    }
    /* fprintf(stderr, "MATCHED: %d\n", nmatches); */

    /* guess that the result string can't be bigger than the source
     * which is not strictly true */
    int result_size = strlen(source_string + nmatches + 1);
    result = gmk_alloc(result_size);

    /* fprintf(stderr, "Result size guess: %d\n", result_size); */
    int pos = -1;
    int i;
    for (i = 0; i < nmatches; i++) {
      pos++;
      int len = pmatch[i].rm_eo - pmatch[i].rm_so;

      /* REG_NOSUB could prevent the full set of matches: */
      if (pmatch[i].rm_so < 0) {
        break;
      }

      /* Check if the output string is large enough to add on the next match and
       * realloc if not. */
      if (len + pos + 1 > result_size) {
        result_size *= 2;
        result = xrealloc(result, result_size);
        /* fprintf(stderr, "Result size realloc to: %d\n", result_size); */
      }

      strncpy(result + pos, source_string + pmatch[i].rm_so, len);
      pos += len;
      *(result + pos) = ' ';
    }
    if (pos > 0) {
      result[pos] = '\0';
    } else {
      result[0] = '\0';
    }

    return result;
  }
}

GMK_EXPORT
int regex_gmk_setup(const gmk_floc *flocp) {
  NOTUSED(flocp);
  gmk_add_function("regcomp", func_regcomp, 1, 2, GMK_FUNC_DEFAULT);
  gmk_add_function("regexec", func_regexec, 2, 2, GMK_FUNC_DEFAULT);
  return 1;
}
