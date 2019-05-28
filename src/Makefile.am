
AM_CPPFLAGS = -I$(top_srcdir)/include -include compat.h -D_GNU_SOURCE -Wall

AM_CPPFLAGS += -D__UCLIBC_HAS_RPC__ \
               -D__UCLIBC_HAS_REENTRANT_RPC__ \
               -D__UCLIBC_HAS_THREADS__

noinst_HEADERS = compat.h errqueue.h rpc_private.h

lib_LTLIBRARIES = libucrpc.la

libucrpc_la_LDFLAGS = -no-undefined -lpthread

# libucrpc_la_LDFLAGS += -version-info @LT_VERSION_INFO@

# Sources required for NFS mount only ?

libucrpc_la_SOURCES = \
	auth_none.c \
	auth_unix.c \
	authunix_prot.c \
	bindresvport.c \
	clnt_perror.c \
	clnt_simple.c \
	clnt_tcp.c \
	clnt_udp.c \
	create_xid.c \
	getrpcent.c \
	pmap_clnt.c \
	pmap_prot2.c \
	pmap_prot.c \
	pm_getmaps.c \
	pm_getport.c \
	rcmd.c \
	rexec.c \
	rpc_cmsg.c \
	rpc_commondata.c \
	rpc_dtablesize.c \
	rpc_prot.c \
	rpc_thread.c \
	rtime.c \
	ruserpass.c \
	sa_len.c \
	svc_auth.c \
	svc_authux.c \
	svc.c \
	xdr_array.c \
	xdr.c \
	xdr_mem.c \
	xdr_rec.c \
	xdr_reference.c

# Additional sources required for "Full" RPC support ?

libucrpc_la_SOURCES += \
	clnt_generic.c \
	clnt_raw.c \
	clnt_unix.c \
	get_myaddress.c \
	getrpcport.c \
	pmap_rmt.c \
	svc_raw.c \
	svc_run.c \
	svc_simple.c \
	svc_tcp.c \
	svc_udp.c \
	svc_unix.c \
	xdr_float.c \
	xdr_intXX_t.c \
	xdr_stdio.c
