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
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>


#include "gnumake.h"

/*
 Convert to signed integer and increment
*/

GMK_EXPORT int plugin_is_GPL_compatible=1;

/*
 * $(mkdir apath)
 *
 * Returns the path if successful
 * empty string if there was an error.
 *
 * example use: $(mkdir /home/fred/test)
 */


/* Should be enough even up to 128 bits */
#define MAX_LENGTH_OCTETS 40


/* It is perhaps a bit inflexible to have 
 * only one path separator allowed  because it will 
 * make things difficult when dealing with cygwin.
 * I think it's best to cross that bridge when we come 
 * to it, however.
 */
#define PATH_SEPARATOR '/'

GMK_EXPORT char *
func_mkdir (const char *func_name, unsigned int argc, char **argv)
{
    char *result = NULL;
    unsigned long long len;

    len = strlen(argv[0]);
    char *modifiable = gmk_alloc(len + 1);
    strcpy(modifyable, argv[0]);

    char *end = NULL;
    char *start = modifiable;

    if (*start != '\0') {
        if (mkdir(modifiable) == -1) {
            if (errno == EEXIST) {
                return modifiable;
            }

            if (errno == ENOENT) { 
                do {
                    errno = 0;
                    end = strchr(start, PATH_SEPARATOR);
                    if (end) {
                        *end = '\0';
                        mkdir(modifiable);
                        *end = PATH_SEPARATOR;
                        start = modifiable + 1;
                    } else {
                        break;
                    }

                    if (errno != EEXIST) {
                        gmk_free(modifiable);
                        return NULL;
                    }
                } while (*start == '\0');
            }
        }
    }
    

    return modifiable;
}

GMK_EXPORT
int
strlen_gmk_setup (const gmk_floc *flocp)
{
    gmk_add_function ("strlen", func_strlen, 1, 1, GMK_FUNC_DEFAULT);
    return 1;
}
