#include <stdio.h>
#include <stdlib.h>

#include "info.h"

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAIL
#define FAIL 0
#endif

int
main()
{
  char* data = NULL ;
  size_t data_len = 0 ;
  int result = -1 ;
  //
  result = forrst_get_stats( &data, &data_len ) ;
  //
  if( SUCCESS == result ) {
    printf( "%zu bytes received\n", data_len ) ;
    printf( "Received data:\n" ) ;
    printf( "%s\n", data ) ;
  }
  else {
    printf( "failed to get data\n" ) ;
  }
  //
  free( data ) ;
  //
  return EXIT_SUCCESS ;
}
