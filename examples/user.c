#include <stdio.h>
#include <stdlib.h>

#include "forrst_common.h"
#include "forrst_user.h"

#define TEST_USER_ID 26821
#define TEST_USER_NAME "misham"
#define TEST_USER_NAME_LEN 6

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
#if __WORDSIZE == 64
    printf( "\tid: %lu\n", user.id ) ;
#else
    printf( "\tid: %llu\n", user.id ) ;
#endif
    printf( "\tuser name: %s\n", user.username ) ;
    printf( "\tname: %s\n", user.name ) ;
    printf( "\turl: %s\n", user.url ) ;
    printf( "\tposts: %zu\n", user.numOfPosts ) ;
    printf( "\tcomments: %zu\n", user.numOfComments ) ;
    printf( "\tlikes: %zu\n", user.numOfLikes ) ;
    printf( "\tfollowers: %zu\n", user.numOfFollowers ) ;
    printf( "\tfollowing: %zu\n", user.numOfFollowing ) ;
    printf( "\tbio: %s\n", user.bio ) ;
    printf( "\tis a: %u\n", user.isA ) ;
    printf( "\thomepage: %s\n", user.homepage ) ;
    printf( "\ttwitter: %s\n", user.twitter ) ;
    printf( "\tin directory: %s\n", (user.inDirectory ? "true" : "false") ) ;
    printf( "\ttags: %s\n", user.tags ) ;
    printf( "\tphotos:\n" ) ;
    printf( "\t\txl_url: %s\n", user.photoXl ) ;
    printf( "\t\tlarge_url: %s\n", user.photoLarge ) ;
    printf( "\t\tmedium_url: %s\n", user.photoMedium ) ;
    printf( "\t\tsmall_url: %s\n", user.photoSmall ) ;
    printf( "\t\tthum_url: %s\n", user.photoThumb ) ;
  }
  else {
    printf( "failed to get data\n" ) ;
  }
  //
  result = forrst_user_info_by_username( TEST_USER_NAME, TEST_USER_NAME_LEN, &response, &user ) ;
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
#if __WORDSIZE == 64
    printf( "\tid: %lu\n", user.id ) ;
#else
    printf( "\tid: %llu\n", user.id ) ;
#endif
    printf( "\tuser name: %s\n", user.username ) ;
    printf( "\tname: %s\n", user.name ) ;
    printf( "\turl: %s\n", user.url ) ;
    printf( "\tposts: %zu\n", user.numOfPosts ) ;
    printf( "\tcomments: %zu\n", user.numOfComments ) ;
    printf( "\tlikes: %zu\n", user.numOfLikes ) ;
    printf( "\tfollowers: %zu\n", user.numOfFollowers ) ;
    printf( "\tfollowing: %zu\n", user.numOfFollowing ) ;
    printf( "\tbio: %s\n", user.bio ) ;
    printf( "\tis a: %u\n", user.isA ) ;
    printf( "\thomepage: %s\n", user.homepage ) ;
    printf( "\ttwitter: %s\n", user.twitter ) ;
    printf( "\tin directory: %s\n", (user.inDirectory ? "true" : "false") ) ;
    printf( "\ttags: %s\n", user.tags ) ;
    printf( "\tphotos:\n" ) ;
    printf( "\t\txl_url: %s\n", user.photoXl ) ;
    printf( "\t\tlarge_url: %s\n", user.photoLarge ) ;
    printf( "\t\tmedium_url: %s\n", user.photoMedium ) ;
    printf( "\t\tsmall_url: %s\n", user.photoSmall ) ;
    printf( "\t\tthum_url: %s\n", user.photoThumb ) ;
  }
  else {
    printf( "failed to get data\n" ) ;
  }
  //
  return EXIT_SUCCESS ;
}
