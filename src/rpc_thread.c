/*
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <stdio.h>
#include <assert.h>
#include "rpc_private.h"

#ifdef __UCLIBC_HAS_THREADS__

#include <pthread.h>

/* Define once control variable.  */
# define __libc_once_define(CLASS, NAME) \
  CLASS pthread_once_t NAME = PTHREAD_ONCE_INIT

/* Call handler iff the first call.  */
#define __libc_once(ONCE_CONTROL, INIT_FUNCTION)	\
  do {							\
      pthread_once (&(ONCE_CONTROL), INIT_FUNCTION);	\
  } while (0)


/* This file defines the following macros for accessing a small fixed
   set of thread-specific `void *' data used only internally by libc.

   __libc_tsd_define(CLASS, KEY)	-- Define or declare a `void *' datum
                       for KEY.  CLASS can be `static' for
					   keys used in only one source file,
					   empty for global definitions, or
					   `extern' for global declarations.
   __libc_tsd_address(KEY)		-- Return the `void **' pointing to
                       the current thread's datum for KEY.
   __libc_tsd_get(KEY)			-- Return the `void *' datum for KEY.
   __libc_tsd_set(KEY, VALUE)		-- Set the datum for KEY to VALUE.

   The set of available KEY's will usually be provided as an enum,
   and contains (at least):
		_LIBC_TSD_KEY_MALLOC
		_LIBC_TSD_KEY_DL_ERROR
		_LIBC_TSD_KEY_RPC_VARS
   All uses must be the literal _LIBC_TSD_* name in the __libc_tsd_* macros.
   Some implementations may not provide any enum at all and instead
   using string pasting in the macros.  */

# define __libc_tsd_define(CLASS, KEY)	CLASS pthread_key_t __libc_tsd_##KEY
# define __libc_tsd_create(KEY) 	pthread_key_create(&__libc_tsd_##KEY, NULL)
# define __libc_tsd_get(KEY)		pthread_getspecific(__libc_tsd_##KEY)
# define __libc_tsd_set(KEY, VALUE)	pthread_setspecific(__libc_tsd_##KEY, (VALUE))

/* Variable used in non-threaded applications or for the first thread.  */
static struct rpc_thread_variables __libc_tsd_RPC_VARS_mem;
static __libc_tsd_define (, RPC_VARS);

/*
 * Task-variable destructor
 */
void
__rpc_thread_destroy (void)
{
	struct rpc_thread_variables *tvp = __libc_tsd_get (RPC_VARS);

	if (tvp != NULL && tvp != &__libc_tsd_RPC_VARS_mem) {
		__rpc_thread_svc_cleanup ();
		__rpc_thread_clnt_cleanup ();
		/*__rpc_thread_key_cleanup (); */
		free (tvp->clnt_perr_buf_s);
		free (tvp->clntraw_private_s);
		free (tvp->svcraw_private_s);
		free (tvp->authdes_cache_s);
		free (tvp->authdes_lru_s);
		free (tvp);
		__libc_tsd_set (RPC_VARS, NULL);
	}
}

/*
 * Initialize RPC multi-threaded operation
 */
static void
rpc_thread_multi (void)
{
  __libc_tsd_create(RPC_VARS);
  __libc_tsd_set (RPC_VARS, &__libc_tsd_RPC_VARS_mem);
}


struct rpc_thread_variables attribute_hidden *
__rpc_thread_variables (void)
{
	__libc_once_define (static, once);
	struct rpc_thread_variables *tvp;

	__libc_once (once, rpc_thread_multi);
	tvp = __libc_tsd_get (RPC_VARS);
	if (tvp == NULL) {
		tvp = calloc (1, sizeof *tvp);
		if (tvp != NULL)
			__libc_tsd_set (RPC_VARS, tvp);
		else
			tvp = __libc_tsd_get (RPC_VARS);
	}
	return tvp;
}


/* Global variables If we're single-threaded, or if this is the first
   thread using the variable, use the existing global variable.  This
   provides backwards compatability for existing applications which
   dynamically link against this code.  */
#undef svc_fdset
#undef rpc_createerr
#undef svc_pollfd
#undef svc_max_pollfd

fd_set *
__rpc_thread_svc_fdset (void)
{
	struct rpc_thread_variables *tvp;

	tvp = __rpc_thread_variables ();
	if (tvp == &__libc_tsd_RPC_VARS_mem)
		return &svc_fdset;
	return &tvp->svc_fdset_s;
}

struct rpc_createerr *
__rpc_thread_createerr (void)
{
	struct rpc_thread_variables *tvp;

	tvp = __rpc_thread_variables ();
	if (tvp == &__libc_tsd_RPC_VARS_mem)
		return &rpc_createerr;
	return &tvp->rpc_createerr_s;
}

struct pollfd **
__rpc_thread_svc_pollfd (void)
{
	struct rpc_thread_variables *tvp;

	tvp = __rpc_thread_variables ();
	if (tvp == &__libc_tsd_RPC_VARS_mem)
		return &svc_pollfd;
	return &tvp->svc_pollfd_s;
}

int *
__rpc_thread_svc_max_pollfd (void)
{
	struct rpc_thread_variables *tvp;

	tvp = __rpc_thread_variables ();
	if (tvp == &__libc_tsd_RPC_VARS_mem)
		return &svc_max_pollfd;
	return &tvp->svc_max_pollfd_s;
}
#else

#undef svc_fdset
#undef rpc_createerr
#undef svc_pollfd
#undef svc_max_pollfd

extern fd_set svc_fdset;
fd_set * __rpc_thread_svc_fdset (void)
{
    return &(svc_fdset);
}

extern struct rpc_createerr rpc_createerr;
struct rpc_createerr * __rpc_thread_createerr (void)
{
    return &(rpc_createerr);
}

extern struct pollfd *svc_pollfd;
struct pollfd ** __rpc_thread_svc_pollfd (void)
{
    return &(svc_pollfd);
}

extern int svc_max_pollfd;
int * __rpc_thread_svc_max_pollfd (void)
{
    return &(svc_max_pollfd);
}

#endif /* __UCLIBC_HAS_THREADS__ */

