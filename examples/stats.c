
#include <stdio.h>
#include <stdlib.h>

#include "connection.h"

int
main()
{
  char* data = NULL ;
  size_t data_len = 0 ;
  int result = -1 ;
  //
  result = forrst_get_stats( &data, &data_len ) ;
  //
  printf( "%d bytes received\n", data_len ) ;
  printf( "Received data:\n" ) ;
  printf( "%s\n", data ) ;
  //
  return EXIT_SUCCESS ;
}
