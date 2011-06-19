#include <stdio.h>
#include <stdlib.h>

#include "forrst_info.h"

#ifndef SUCCESS
#define SUCCESS 1
#endif

#ifndef FAIL
#define FAIL 0
#endif

int
main()
{
  struct forrst_ResponseInfo response ;
  struct forrst_Stats api_status ;
  int result = -1 ;
  //
  result = forrst_get_stats( &response, &api_status ) ;
  //
  if( SUCCESS == result ) {
    printf( "API Request Status:\n" ) ;
    printf( "\tstatus: %d\n", response.status ) ;
    printf( "\tresponseTime: %f\n", response.responseTime ) ;
    printf( "\tenvironment: %d\n", response.environment ) ;
    printf( "\tauthed: %d\n", response.authed ) ;
    printf( "\tauthedAs: %s\n", response.authedAs ) ;
    printf( "-------\n" ) ;
    printf( "Stats:\n" ) ;
    printf( "\trate limit: %d\n", api_status.rateLimit ) ;
    printf( "\tcalls made: %d\n", api_status.callsMade ) ;
  }
  else {
    printf( "failed to get data\n" ) ;
  }
  //
  return EXIT_SUCCESS ;
}
