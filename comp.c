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

#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "gnumake.h"

#include "extramake.h"

GMK_EXPORT int plugin_is_GPL_compatible = 1;

/*
 * $(lt a,b)
 * $(lte a,b)
 * $(gt a,b)
 * $(gte a,b)
 *
 * Returns the result of treating all the parameters
 * as integers and comparing them numerically. Returns
 * the 1 "true" or the empty string
 * if false.
 * e.g. $(lt 1,0) meaning 1 < 0 would return ""
 * Non numeric parameters will cause the empty string
 * to be returned.
 */

/* Should be enough even up to 128 bits */
#define MAX_LENGTH_OCTETS 40

GMK_EXPORT char *func_comp(const char *func_name, unsigned int argc,
                           char **argv) {
  char *result = NULL;
  long long left, right, answer = 0;

  char *endptr = NULL;
  char *startptr = NULL;

  NOTUSED(argc);

  startptr = argv[0];
  while (*startptr == ' ' || *startptr == '\t') {
    startptr++;
  }
  left = strtoll(startptr, &endptr, 10);
  if (endptr - startptr < 1) {
    /* it's really an error to compare
     * empty strings numerically */
    return NULL;
  }
  /* Non numeric characters are not allowed.
   * signal this by returning the empty string
   * if we spot them. Whitespace IS allowed.
   */
  while (*endptr != '\0') {
    if (*endptr != ' ' && *endptr != '\t') {
      return NULL;
    }
    endptr++;
  }

  startptr = argv[1];
  while (*startptr == ' ' || *startptr == '\t') {
    startptr++;
  }
  right = strtoll(startptr, &endptr, 10);
  if (endptr - startptr < 1) {
    /* it's really an error to compare
     * empty strings numerically */
    return NULL;
  }
  /* Non numeric characters are not allowed.
   * signal this by returning the empty string
   * if we spot them */
  while (*endptr != '\0') {
    if (*endptr != ' ' && *endptr != '\t') {
      return NULL;
    }
    endptr++;
  }

  if (func_name[2] == '\0') {
    /* lt or gt */
    if (func_name[0] == 'l') {
      if (left < right) {
        answer = 1;
      }
    } else {
      if (left > right) {
        answer = 1;
      }
    }
  } else {
    /* lte or gte */
    if (func_name[0] == 'l') {
      if (left <= right) {
        answer = 1;
      }
    } else {
      if (left >= right) {
        answer = 1;
      }
    }
  }

  if (answer == 0) {
    return NULL;
  }

  result = gmk_alloc(MAX_LENGTH_OCTETS);
  (void)snprintf(result, MAX_LENGTH_OCTETS - 1, "%lld", answer);
  result[MAX_LENGTH_OCTETS - 1] = '\0';

  return result;
}

GMK_EXPORT
int comp_gmk_setup(const gmk_floc *flocp) {
  NOTUSED(flocp);
  gmk_add_function("gt", func_comp, 2, 2, GMK_FUNC_DEFAULT);
  gmk_add_function("lt", func_comp, 2, 2, GMK_FUNC_DEFAULT);
  gmk_add_function("gte", func_comp, 2, 2, GMK_FUNC_DEFAULT);
  gmk_add_function("lte", func_comp, 2, 2, GMK_FUNC_DEFAULT);
  return 1;
}
