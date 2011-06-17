#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "post.h"

#define TEST_POST_ID 45114
#define TEST_POST_TINY_ID "BMH"
#define TEST_POST_TINY_ID_LEN 3

int
main()
{
  struct forrst_ResponseInfo response ;
  struct forrst_post post ;
  int result = -1 ;
  //
  result = forrst_posts_get_by_id( TEST_POST_ID, &response, &post ) ;
  //
  if( FORRST_SUCCESS == result ) {
    printf( "API Request Status:\n" ) ;
    printf( "\tstatus: %d\n", response.status ) ;
    printf( "\tresponseTime: %f\n", response.responseTime ) ;
    printf( "\tenvironment: %d\n", response.environment ) ;
    printf( "\tauthed: %d\n", response.authed ) ;
    printf( "\tauthedAs: %s\n", response.authedAs ) ;
    printf( "-------\n" ) ;
    printf( "Post:\n" ) ;
#if __WORDSIZE == 64
    printf( "\tid: %lu\n", post.id ) ;
#else
    printf( "\tid: %llu\n", post.id ) ;
#endif
    printf( "\ttiny id: %s\n", post.tinyId ) ;
  }
  else {
    printf( "failed to get data\n" ) ;
  }
  //
  //
  return EXIT_SUCCESS ;
}
