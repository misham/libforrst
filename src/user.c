#include <string.h>
#include <json/json.h>
#include <malloc.h>
#include <stdio.h>

#include "common.h"
#include "connection.h"
#include "user.h"

int
forrst_user_info_by_id( uint64_t userId,
                        struct forrst_ResponseInfo* response,
		                    struct forrst_user* userInfo ) {
  char* full_url = NULL ;
  size_t user_info_url_len = 0 ;
  char* user_info = NULL ;
  size_t user_info_len = 0 ;
  int result = -1 ;
  json_object* obj = NULL ;
  json_object* user_obj = NULL ;
  json_object* cur_obj = NULL ;
  //
  if( NULL == response || NULL == userInfo ) {
    return FORRST_FAIL ;
  }
  //
  user_info_url_len = strlen( FORRST_API_USER_INFO_URL ) ;
  full_url = (char*)malloc( sizeof(char) * (
                              user_info_url_len +
                              MAX_NUM_INTEGERS_IN_64_BIT_NUM +
                              strlen("/?id=") + 1
                            )) ;
  if( NULL == full_url ) {
    return FORRST_FAIL ;
  }
  sprintf( full_url, "%s/?id=%llu", FORRST_API_USER_INFO_URL, userId ) ;
  //
  result = forrst_get_data_from_api( full_url, strlen(full_url),
                                     &user_info, &user_info_len ) ;
  if( FORRST_FAIL == result || NULL == user_info ||
      strlen(user_info) != user_info_len ) {
    return FORRST_FAIL ;
  }
  //
  obj = json_tokener_parse( user_info ) ;
  if( NULL == obj ) {
    return FORRST_FAIL ;
  }
  //
  forrst_get_response_info( obj, response ) ;
  //
  user_obj = json_object_object_get( obj, FORRST_API_RESP_STRING ) ;
  if( NULL == user_obj ) {
    json_object_put( obj ) ;
    return FORRST_FAIL ;
  }
  //
  json_object_put( obj ) ;
  //
  return FORRST_SUCCESS ;
}

