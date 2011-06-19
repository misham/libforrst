#include <string.h>
#include <json/json.h>
#include <malloc.h>
#include <stdio.h>

#include "forrst_common.h"
#include "forrst_connection.h"
#include "forrst_user.h"

static int
forrst_user_store_value( char* key, json_object* value,
                              struct forrst_user* user ) ;

int
forrst_user_auth( char* login, size_t loginLen,
                  char* password, size_t passwordLen ) {
  if( NULL == login || NULL == password ||
      0 == loginLen || 0 == passwordLen ||
      strlen(login) != loginLen || strlen(password) != passwordLen ) {
    return FORRST_FAIL ;
  }
  //
  // :TODO:
  //
  return FORRST_FAIL ;
}

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
  //
#if __WORDSIZE == 64
  sprintf( full_url, "%s/?id=%lu", FORRST_API_USER_INFO_URL, userId ) ;
#else
  sprintf( full_url, "%s/?id=%llu", FORRST_API_USER_INFO_URL, userId ) ;
#endif
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
  json_object_object_foreach( user_obj, key, val ) {
    forrst_user_store_value( key, val, userInfo ) ;
  }
  //
  json_object_put( user_obj ) ;
  json_object_put( obj ) ;
  //
  return FORRST_SUCCESS ;
}

int
forrst_user_info_by_username( char* userName, size_t userNameLen,
                              struct forrst_ResponseInfo* response,
                              struct forrst_user* userInfo ) {
  char* full_url = NULL ;
  size_t user_info_url_len = 0 ;
  char* user_info = NULL ;
  size_t user_info_len = 0 ;
  int result = -1 ;
  json_object* obj = NULL ;
  json_object* user_obj = NULL ;
  //
  if( NULL == response || NULL == userInfo ||
      NULL == userName || 0 == userNameLen ||
      strlen(userName) != userNameLen ) {
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
  //
  sprintf( full_url, "%s/?username=%s",
           FORRST_API_USER_INFO_URL,
           userName ) ;
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
  json_object_object_foreach( user_obj, key, val ) {
    forrst_user_store_value( key, val, userInfo ) ;
  }
  //
  json_object_put( user_obj ) ;
  json_object_put( obj ) ;
  //
  return FORRST_SUCCESS ;
}

static int
forrst_user_store_value( char* key, json_object* value,
                              struct forrst_user* user ) {
  int result = FORRST_SUCCESS ;
  char* tmp = NULL ;
  if( NULL == user || NULL == key || NULL == value ) {
    return FORRST_FAIL ;
  }
  //
  if( 0 == strcmp(key, "id") ) {
    user->id = json_object_get_int( value ) ;
  }
  else if( 0 == strcmp(key, "username") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->username),
                                  &(user->usernameLen) ) ;
  }
  else if( 0 == strcmp(key, "name") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->name),
                                  &(user->nameLen) ) ;
  }
  else if( 0 == strcmp(key, "url") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->url),
                                  &(user->urlLen) ) ;
  }
  else if( 0 == strcmp(key, "posts") ) {
    user->numOfPosts = json_object_get_int( value ) ;
  }
  else if( 0 == strcmp(key, "comments") ) {
    user->numOfComments = json_object_get_int( value ) ;
  }
  else if( 0 == strcmp(key, "likes") ) {
    user->numOfLikes = json_object_get_int( value ) ;
  }
  else if( 0 == strcmp(key, "followers") ) {
    user->numOfFollowers = json_object_get_int( value ) ;
  }
  else if( 0 == strcmp(key, "following") ) {
    user->numOfFollowing = json_object_get_int( value ) ;
  }
  else if( 0 == strcmp(key, "bio") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->bio),
                                  &(user->bioLen) ) ;
  }
  else if( 0 == strcmp(key, "is_a") ) {
    tmp = (char*)json_object_get_string( value ) ;
    if( 0 == strcmp(tmp, "developer") ) {
      user->isA = DEVELOPER ;
    }
    else if( 0 == strcmp(tmp, "designer") ) {
      user->isA = DESIGNER ;
    }
    else {
      user->isA = BOTH ;
    }
  }
  else if( 0 == strcmp(key, "homepage_url") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->homepage),
                                  &(user->homepageLen) ) ;
  }
  else if( 0 == strcmp(key, "twitter") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->twitter),
                                  &(user->twitterLen) ) ;
  }
  else if( 0 == strcmp(key, "in_directory") ) {
    if( 0 == strcmp(json_object_get_string(value), "true") ) {
      user->inDirectory = 1 ;
    }
    else {
      user->inDirectory = 0 ;
    }
  }
  else if( 0 == strcmp(key, "tag_string") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->tags),
                                  &(user->tagsLen) ) ;
  }
  else if( 0 == strcmp(key, "photos") ) {
    json_object_object_foreach( value, key, val ) {
      forrst_user_store_value( key, val, user ) ;
    }
  }
  else if( 0 == strcmp(key, "xl_url") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->photoXl),
                                  &(user->photoXlLen) ) ;
  }
  else if( 0 == strcmp(key, "large_url") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->photoLarge),
                                  &(user->photoLargeLen) ) ;
  }
  else if( 0 == strcmp(key, "medium_url") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->photoMedium),
                                  &(user->photoMediumLen) ) ;
  }
  else if( 0 == strcmp(key, "small_url") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->photoSmall),
                                  &(user->photoSmallLen) ) ;
  }
  else if( 0 == strcmp(key, "thumb_url") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(user->photoThumb),
                                  &(user->photoThumbLen) ) ;
  }
  //
  return result ;
}

