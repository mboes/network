#include "HsNet.h"
#include "HsFFI.h"
#include <stdio.h>

#if defined(HAVE_WINSOCK2_H) && !defined(__CYGWIN__)

__attribute__((destructor))
static void
shutdownHandler(void)
{
  WSACleanup();
}

__attribute__((constructor))
static void
initWinSock()
{
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;

  wVersionRequested = MAKEWORD( 2, 2 );

  err = WSAStartup ( wVersionRequested, &wsaData );

  if ( err != 0 ) {
     fprintf(stderr, "Cannot initialize WinSock.\n");
     fprintf(stderr, "\tWSAStartup() failed with error: %d\n", err);
     exit ( 1 );
  }

  if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) {
    fprintf(stderr, "Could not find a usable version of Winsock.dll\n");
    WSACleanup();
    exit ( 1 );
  }
}

#endif
