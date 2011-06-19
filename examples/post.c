#include <stdio.h>
#include <stdlib.h>

#include "forrst_common.h"
#include "forrst_post.h"

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
    printf( "\ttype: %d\n", post.type ) ;
    printf( "\tpost url: %s\n", post.postUrl ) ;
    printf( "\tcreated at: :TODO:\n" ) ;
    printf( "\tupdated at: :TODO:\n" ) ;
    printf( "\tpublished: %s\n", (post.isPublished ? "true" : "false") ) ;
    printf( "\tpublic: %s\n", (post.isPublic ? "true" : "false") ) ;
    printf( "\ttitle: %s\n", post.title ) ;
    if( LINK == post.type ) {
      printf( "\turl: %s\n", post.url ) ;
    }
    printf( "\t----------\n" ) ;
    printf( "\tcontent: %s\n", post.content ) ;
    printf( "\t----------\n" ) ;
    printf( "\tformatted content: %s\n", post.formattedContent ) ;
    printf( "\t----------\n" ) ;
    printf( "\tdescription: %s\n", post.description ) ;
    printf( "\t----------\n" ) ;
    printf( "\tformatted description: %s\n", post.formattedDescription ) ;
    printf( "\t----------\n" ) ;
    printf( "\tlike count: %d\n", post.likeCount ) ;
    printf( "\tcomment count: %d\n", post.commentCount ) ;
    printf( "\ttag string: %s\n", post.tagString ) ;
    if( SNAP == post.type ) {
      printf( "\tsnaps:\n" ) ;
      printf( "\tmega url: %s\n", post.snapsMediumUrl ) ;
      printf( "\tkeith url: %s\n", post.snapsKeithUrl ) ;
      printf( "\tlarge url: %s\n", post.snapsLargeUrl ) ;
      printf( "\tmedium url: %s\n", post.snapsMediumUrl ) ;
      printf( "\tsmall url: %s\n", post.snapsSmallUrl ) ;
      printf( "\tthumb url: %s\n", post.snapsThumUrl ) ;
      printf( "\toriginal url: %s\n", post.snapsOriginalUrl ) ;
    }
  }
  else {
    printf( "failed to get data\n" ) ;
  }
  //
  //
  return EXIT_SUCCESS ;
}
