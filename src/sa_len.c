/* Copyright (C) 1998, 1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#if 0
#include <netipx/ipx.h>
#include <netash/ash.h>
#include <netatalk/at.h>
#include <netax25/ax25.h>
#include <neteconet/ec.h>
#include <netpacket/packet.h>
#include <netrose/rose.h>
#endif

int __libc_sa_len (sa_family_t af) attribute_hidden;
int __libc_sa_len (sa_family_t af)
{
  switch (af)
    {
#if 0
    case AF_APPLETALK:
      return sizeof (struct sockaddr_at);
    case AF_ASH:
      return sizeof (struct sockaddr_ash);
    case AF_AX25:
      return sizeof (struct sockaddr_ax25);
    case AF_ECONET:
      return sizeof (struct sockaddr_ec);
    case AF_ROSE:
      return sizeof (struct sockaddr_rose);
    case AF_PACKET:
      return sizeof (struct sockaddr_ll);
#endif
    case AF_INET:
      return sizeof (struct sockaddr_in);
    case AF_INET6:
      return sizeof (struct sockaddr_in6);
#if 0
    case AF_IPX:
      return sizeof (struct sockaddr_ipx);
#endif
    case AF_LOCAL:
      return sizeof (struct sockaddr_un);
    }
  return 0;
}
