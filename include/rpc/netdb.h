/* @(#)netdb.h	2.1 88/07/29 3.9 RPCSRC */
/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 *
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 *
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 *
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 *
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 *
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */
/*	@(#)rpc.h 1.8 87/07/24 SMI	*/

/* Cleaned up for GNU C library roland@gnu.ai.mit.edu:
   added multiple inclusion protection and use of <sys/cdefs.h>.
   In GNU this file is #include'd by <netdb.h>.  */

#ifndef _RPC_NETDB_H
#define _RPC_NETDB_H	1

#include <features.h>

#define __need_size_t
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rpcent
{
  char *r_name;		/* Name of server for this rpc program.  */
  char **r_aliases;	/* Alias list.  */
  int r_number;		/* RPC program number.  */
};

extern void setrpcent (int __stayopen);
extern void endrpcent (void);
extern struct rpcent *getrpcbyname (const char *__name);
extern struct rpcent *getrpcbynumber (int __number);
extern struct rpcent *getrpcent (void);

#if defined __USE_MISC && defined __UCLIBC_HAS_REENTRANT_RPC__
extern int getrpcbyname_r (const char *__name, struct rpcent *__result_buf,
			   char *__buffer, size_t __buflen,
			   struct rpcent **__result);

extern int getrpcbynumber_r (int __number, struct rpcent *__result_buf,
			     char *__buffer, size_t __buflen,
			     struct rpcent **__result);

extern int getrpcent_r (struct rpcent *__result_buf, char *__buffer,
			size_t __buflen, struct rpcent **__result);
#endif

#ifdef __cplusplus
}
#endif

#endif /* rpc/netdb.h */
