#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "user.h"

#define TEST_USER_ID 26821

int
main()
{
  struct forrst_ResponseInfo response ;
  struct forrst_user user ;
  int result = -1 ;
  //
  result = forrst_user_info_by_id( TEST_USER_ID, &response, &user ) ;
  //
  if( FORRST_SUCCESS == result ) {
    printf( "API Request Status:\n" ) ;
    printf( "\tstatus: %d\n", response.status ) ;
    printf( "\tresponseTime: %f\n", response.responseTime ) ;
    printf( "\tenvironment: %d\n", response.environment ) ;
    printf( "\tauthed: %d\n", response.authed ) ;
    printf( "\tauthedAs: %s\n", response.authedAs ) ;
    printf( "-------\n" ) ;
    printf( "User:\n" ) ;
  }
  else {
    printf( "failed to get data\n" ) ;
  }
  //
  return EXIT_SUCCESS ;
}
