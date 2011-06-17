#include "common.h"
#include "connection.h"
#include "post.h"

int
forrst_posts_get_by_id( uint64_t id,
                        struct forrst_ResponseInfo* response,
                        struct forrst_post* post ) {
  char* full_url = NULL ;
  json_object* obj = NULL ;
  int result = FORRST_FAIL ;
  char* post_info = NULL ;
  size_t post_info_len = 0 ;
  //
  if( NULL == post || NULL == response ) {
    return FORRST_FAIL ;
  }
  //
  full_url = (char*)malloc( sizeof(char) * (
                              strlen(FORRST_API_POST_SHOW_URL) +
                              MAX_NUM_INTEGERS_IN_64_BIT_NUM +
                              strlen("/?id=") + 1
                            )) ;
  if( NULL == full_url ) {
    return FORRST_FAIL ;
  }
  //
#if __WORDSIZE == 64
  sprintf( full_url, "%s/?id=%lu", FORRST_API_POST_SHOW_URL, id ) ;
#else
  sprintf( full_url, "%s/?id=%llu", FORRST_API_POST_SHOW_URL, id ) ;
#endif
  //
  result = forrst_get_data_from_api( full_url, strlen(full_url),
                                     &post_info, &post_info_len ) ;
  if( FORRST_FAIL == result || NULL == post_info ||
      strlen(post_info) != post_info_len ) {
    return FORRST_FAIL ;
  }
  //
  obj = json_tokener_parse( post_info ) ;
  if( NULL == obj ) {
    return FORRST_FAIL ;
  }
  //
  forrst_get_response_info( obj, response ) ;
  //
  return FORRST_SUCCESS ;
}

