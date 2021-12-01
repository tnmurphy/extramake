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
#include "siphash24.h"

/*
 Convert to signed integer and increment
*/

#define HASH_OCTETS 8
#define HASH_STRING_SIZE 16

#define UNUSED(symbol) (void)(symbol)

GMK_EXPORT int plugin_is_GPL_compatible=1;

/*
 * siphash24 - returns a 16 character hexadecimal hash value of the input string.
 * An optional key value may be supplied as a second parameter and it must be 16
 * characters.
 *
 * On error this function returns an empty string.
 */
unsigned char default_key[] = "\x4c\xe4\x00\x24\x4c\x97\x14\xe4\x1d\x96\x2c\xce\x9f\x48\x6f\x2d";
GMK_EXPORT char *
func_siphash24 (const char *func_name, unsigned int argc, char **argv)
{
    unsigned char *input = (unsigned char *)argv[0];
    unsigned char *key = default_key;
    unsigned char the_hash[HASH_OCTETS];
    char *the_hash_string;

    UNUSED(func_name);
    
    if (argc == 2) {
        if (strlen(argv[1]) < HASH_STRING_SIZE) {
	        return NULL;
      	    the_hash_string = gmk_alloc(1);
      	    the_hash_string[0] = '\0';
            return the_hash_string;
        }
        key = (unsigned char *)argv[1];
    }

    the_hash[0] = 0;
    the_hash[1] = 0;
    the_hash[2] = 0;
    the_hash[3] = 0;
    the_hash[4] = 0;
    the_hash[5] = 0;
    the_hash[6] = 0;
    the_hash[7] = 0;
    the_hash_string = gmk_alloc(HASH_STRING_SIZE + 1);
    siphash(the_hash, input, strlen((char *)input), key);
    (void)snprintf(the_hash_string, HASH_STRING_SIZE + 1,
	"%02x%02x%02x%02x%02x%02x%02x%02x",
	the_hash[0],
	the_hash[1],
	the_hash[2],
	the_hash[3],
	the_hash[4],
	the_hash[5],
	the_hash[6],
	the_hash[7]
	);
    
    if (strlen(the_hash_string) != HASH_STRING_SIZE) {
        return NULL;
    }

    return the_hash_string;
}

GMK_EXPORT
int
hash_gmk_setup (const gmk_floc *flocp)
{
    UNUSED(flocp);
    gmk_add_function ("siphash24", func_siphash24, 1, 2, GMK_FUNC_DEFAULT);
    return 1;
}
