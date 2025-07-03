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

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "gnumake.h"

#include "extramake.h"

GMK_EXPORT int plugin_is_GPL_compatible = 1;

/*
 * $(time format)
 *
 * Returns the current time.
 */

static const char *default_time_format = "%Y-%m-%dT%H:%M:%SZ";

/* Should be enough even up to 128 bits */
#define MAX_LENGTH_OCTETS 80

GMK_EXPORT char *func_time(const char *func_name, unsigned int argc,
                           char **argv) {
  char *result = NULL;

  const char *startptr = argv[0];
  struct timespec time;
  struct tm local_t;
  size_t time_length = 0;

  NOTUSED(func_name);
  NOTUSED(argc);

  if (-1 == clock_gettime(CLOCK_REALTIME, &time)) {
    perror("gmake: call to time: ");
    return NULL;
  }

  /* skip any leading spaces */
  while (*startptr == ' ' || *startptr == '\t') {
    startptr++;
  }
  if (*startptr=='+') {
    startptr = default_time_format;
  }

  result = gmk_alloc(MAX_LENGTH_OCTETS);
  localtime_r(&time.tv_sec, &local_t);

  time_length = strftime(result, MAX_LENGTH_OCTETS, startptr, &local_t);

  if (time_length == 0) {
    gmk_free(result);
    return NULL;
  }

  return result;
}

/*
 * $(sleep n) - sleep n seconds where n is an integer
 * return an empty string
 */

GMK_EXPORT char *func_sleep(const char *func_name, unsigned int argc,
                            char **argv) {
  long long seconds = 0;

  char *endptr = NULL;
  const char *startptr = NULL;

  NOTUSED(func_name);
  NOTUSED(argc);

  startptr = argv[0];
  while (*startptr == ' ' || *startptr == '\t') {
    startptr++;
  }
  seconds = strtoll(startptr, &endptr, 10);
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

  sleep(seconds);

  return NULL;
}

GMK_EXPORT
int time_gmk_setup(const gmk_floc *flocp) {
  NOTUSED(flocp);
  gmk_add_function("time", func_time, 1, 1, GMK_FUNC_DEFAULT);
  gmk_add_function("sleep", func_sleep, 1, 1, GMK_FUNC_DEFAULT);
  return 1;
}
