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

/*
 Convert to signed integer and increment
*/

GMK_EXPORT int plugin_is_GPL_compatible = 1;

/*
 * $(equals a,b)
 *
 * Returns the first string if the two
 * parameters match. The comparison is string based.
 *
 * If they don't match, returns the empty string
 * example use: FLAGS:=$(if $(equals $(DEBUG),full),-g -O0,-O2)
 */
GMK_EXPORT char *func_equals(const char *func_name, unsigned int argc,
                             char **argv) {
  char *result = NULL;

  NOTUSED(func_name);
  NOTUSED(argc);

  if (strcmp(argv[0], argv[1]) == 0) {
    int arglen = strlen(argv[0]);
    if (arglen == 0) {
        result = gmk_alloc(2);
	result[0] = '1';
	result[1] = '\0';
	return result;
    } 
    result = gmk_alloc( arglen + 1 );
    /* If the allocation fails we will crash but that is presumably
       better than allowing a build to be incorrect.  An error message
       would be nicer. Nicest would be if GNU make gave us an error
       reporting mechanism.
    */
    strcpy(result, argv[0]);
  }

  return result;
}

GMK_EXPORT
int equals_gmk_setup(const gmk_floc *flocp) {
  NOTUSED(flocp);
  gmk_add_function("equals", func_equals, 2, 2, GMK_FUNC_DEFAULT);
  return 1;
}
