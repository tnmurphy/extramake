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

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

#include "gnumake.h"

GMK_EXPORT int plugin_is_GPL_compatible=1;

/*
 * $(sum a b c ... )
 *
 * Returns the result of treating all the parameters
 * as integers and adding them.  Negative numbers are
 * permitted such that $(add 1 -1) returns 0.
 * Non numeric parameters will cause the empty string
 * to be returned.
 */


/* Should be enough even up to 128 bits */
#define MAX_LENGTH_OCTETS 40


GMK_EXPORT char *
func_sum (const char *func_name, unsigned int argc, char **argv)
{
    char *result = NULL;
    long long sum = 0L;

    char *startptr = argv[0];
    char *endptr;

    while (*startptr != '\0') {
        while (*startptr == ' ' || *startptr == '\t') {
            startptr ++;
        }

        if (!isdigit(*startptr) && *startptr != '-') {
            return NULL;
        }
        sum += strtoll(startptr, &endptr, 10);

        startptr = endptr;

    }

    result = gmk_alloc(MAX_LENGTH_OCTETS);
    snprintf(result, MAX_LENGTH_OCTETS - 1, "%lld", sum);
    result[MAX_LENGTH_OCTETS - 1] = '\0';

    return result;
}

GMK_EXPORT
int
sum_gmk_setup (const gmk_floc *flocp)
{
    gmk_add_function ("sum", func_sum, 1, 1, GMK_FUNC_DEFAULT);
    return 1;
}
