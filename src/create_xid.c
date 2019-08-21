/* Copyright (c) 1998, 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Thorsten Kukuk <kukuk@vt.uni-paderborn.de>, 1998.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "rpc_private.h"


/* The RPC code is not threadsafe, but new code should be threadsafe. */

#include <pthread.h>
static pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;

static int is_initialized;
static struct drand48_data __rpc_lrand48_data;

u_long _create_xid (void)
{
  long res;

  pthread_mutex_lock(&mylock);

  if (!is_initialized)
    {
      struct timeval now;

      gettimeofday (&now, (struct timezone *) 0);
      srand48_r (now.tv_sec ^ now.tv_usec, &__rpc_lrand48_data);
      is_initialized = 1;
    }

  lrand48_r (&__rpc_lrand48_data, &res);

  pthread_mutex_unlock(&mylock);

  return res;
}
