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
 * $(mul a b c ... )
 *
 * Returns the result of treating all the parameters
 * as integers and multiplying them.  Negative numbers are
 * permitted such that $(mul 10 -1) returns -1.
 * Non numeric parameters will cause the empty string
 * to be returned.
 *
 * Overflow is possible.
 */

/* Should be enough even up to 128 bits */
#define MAX_LENGTH_OCTETS 40

GMK_EXPORT char *func_mul(const char *func_name, unsigned int argc,
                          char **argv) {
  char *result = NULL;
  long long answer = 1L;

  char *startptr = argv[0];
  char *endptr = NULL;

  NOTUSED(func_name);
  NOTUSED(argc);

  while (*startptr != '\0') {
    while (*startptr == ' ' || *startptr == '\t') {
      startptr++;
    }

    /* Non numeric characters are not allowed.
     * signal this by returning the empty string
     * if we spot them */
    if (!isdigit(*startptr) && *startptr != '-') {
      return NULL;
    }
    answer *= strtoll(startptr, &endptr, 10);

    startptr = endptr;
  }

  /* We have not seen any numbers at all so this is an
   * invalid call and the only way to indicate that is
   * to return an empty string. */
  if (endptr == NULL) {
    return NULL;
  }

  result = gmk_alloc(MAX_LENGTH_OCTETS);
  (void)snprintf(result, MAX_LENGTH_OCTETS - 1, "%lld", answer);
  result[MAX_LENGTH_OCTETS - 1] = '\0';

  return result;
}

GMK_EXPORT
int mul_gmk_setup(const gmk_floc *flocp) {
  NOTUSED(flocp);
  gmk_add_function("mul", func_mul, 1, 1, GMK_FUNC_DEFAULT);
  return 1;
}
