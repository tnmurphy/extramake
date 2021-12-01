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

#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include "gnumake.h"

/*
 Convert to signed integer and increment
*/

GMK_EXPORT int plugin_is_GPL_compatible=1;

/*
 * $(strlen astring)
 *
 * Returns the length of the parameter in 
 * characters.  
 *
 * example use: $(strlen $(commandline))
 */


/* Should be enough even up to 128 bits */
#define MAX_LENGTH_OCTETS 40


GMK_EXPORT char *
func_strlen (const char *func_name, unsigned int argc, char **argv)
{
    char *result = NULL;
    unsigned long long len;

    len = strlen(argv[0]);

    result = gmk_alloc(MAX_LENGTH_OCTETS);
    snprintf(result, MAX_LENGTH_OCTETS - 1, "%llu", len);
    result[MAX_LENGTH_OCTETS - 1] = '\0';

    return result;
}

GMK_EXPORT
int
strlen_gmk_setup (const gmk_floc *flocp)
{
    gmk_add_function ("strlen", func_strlen, 1, 1, GMK_FUNC_DEFAULT);
    return 1;
}
