/*
Copyright (C) 2015 Timothy Norman Murphy <tnmurphy@gmail.com>

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

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "gnumake.h"

#include "extramake.h"

GMK_EXPORT int plugin_is_GPL_compatible = 1;

/*
 * $(reverse ab cd ef ... )
 *
 * returns ef cd ab
 */

/* Should be enough even up to 128 bits */
#define MAX_LENGTH_OCTETS 40

GMK_EXPORT char *func_reverse(const char *func_name, unsigned int argc,
                              char **argv) {
  char *result = NULL;

  char *startptr = argv[0];
  char *endptr = NULL;
  int result_index = 0;

  NOTUSED(func_name);
  NOTUSED(argc);

  /* Work out how long the result string has to be which may be less than the
   * length if the input has multiple spaces in it since the output won't have
   * multiple spaces.
   */
  result_index = 0;
  char *c = startptr;
  int inspace = 1;
  while (*c != '\0') {
    if (*c == ' ' || *c == '\t') {
      if (inspace == 0) {
        result_index++; /* transition from word to space - will need a separator
                           in the result */
      }
      inspace = 1;
    } else {
      result_index++; /* will need room for this character in the result */
      inspace = 0;
    }
    c++;
  }
  if (inspace)
    result_index--; /* We don't need a separator for the last item or if there's
                       only one item  */

  if (result_index <= 0) {
    return NULL;
  }
  result = gmk_alloc(result_index + 1);
  result[result_index] = '\0';

  /* fill the result string starting from the end coming back towards the
   * beginning placing one token at a time from the source. A single space is
   * inserted between each token.
   */
  while (*startptr != '\0') {
    while (*startptr == ' ' || *startptr == '\t') {
      startptr++;
    }
    endptr = startptr;

    while (*endptr != ' ' && *endptr != '\t' && *endptr != '\0') {
      endptr++;
    }

    int gap = endptr - startptr;
    if (gap > 0) {
      result_index -= gap;
      memcpy(result + result_index, startptr, gap);
      if (result_index > 0) {
        result[--result_index] = ' ';
      }
    }

    startptr = endptr;
  }
  return result;
}

GMK_EXPORT
int reverse_gmk_setup(const gmk_floc *flocp) {
  NOTUSED(flocp);
  gmk_add_function("reverse", func_reverse, 1, 1, GMK_FUNC_DEFAULT);
  return 1;
}
