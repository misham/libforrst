#include <string.h>
#include <json/json.h>
#include <malloc.h>
#include <stdio.h>

#include "common.h"
#include "connection.h"
#include "user.h"

int
forrst_user_info_store_value( char* key, json_object* value,
                              struct forrst_user* user ) ;

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
    forrst_user_info_store_value( key, val, userInfo ) ;
  }
  //
  json_object_put( obj ) ;
  //
  return FORRST_SUCCESS ;
}

int
forrst_user_info_store_value( char* key, json_object* value,
                              struct forrst_user* user ) {
  if( NULL == user || NULL == key || NULL == value ) {
    return FORRST_FAIL ;
  }
  //
  if( 0 == strcmp(key, "id") ) {
    user->id = json_object_get_int( value ) ;
  }
  else if( 0 == strcmp(key, "username") ) {
    user->username = (char*)json_object_get_string( value ) ;
    user->usernameLen = strlen( user->username ) ;
    user->username[user->usernameLen] = '\0' ;
  }
  else if( 0 == strcmp(key, "name") ) {
    user->name = (char*)json_object_get_string( value ) ;
    user->nameLen = strlen( user->name ) ;
    user->name[user->nameLen] = '\0' ;
  }
  else if( 0 == strcmp(key, "url") ) {
    user->url = (char*)json_object_get_string( value ) ;
    user->urlLen = strlen( user->url ) ;
    user->url[user->urlLen] = '\0' ;
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
    user->bio = (char*)json_object_get_string( value ) ;
    user->bioLen = strlen( user->bio ) ;
  }
  else if( 0 == strcmp(key, "is_a") ) {
    char* tmp = (char*)json_object_get_string( value ) ;
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
    user->homepage = (char*)json_object_get_string( value ) ;
    user->homepageLen = strlen( user->homepage ) ;
  }
  else if( 0 == strcmp(key, "twitter") ) {
    user->twitter = (char*)json_object_get_string( value ) ;
    user->twitterLen = strlen( user->twitter ) ;
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
    user->tags = (char*)json_object_get_string( value ) ;
    user->tagsLen = strlen( user->tags ) ;
  }
  else if( 0 == strcmp(key, "photos") ) {
    // :TODO:
  }
  //
  return FORRST_SUCCESS ;
}

