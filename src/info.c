#include "common.h"
#include "connection.h"
#include "info.h"

int
forrst_get_stats( struct forrst_ResponseInfo* response,
                  struct forrst_Stats* apiStatus ) {
  char* stats = NULL ;
  size_t stats_len = 0 ;
  int result = -1 ;
  //
  if( NULL == response || NULL == apiStatus ) {
    return FORRST_FAIL ;
  }
  //
  result = forrst_get_data_from_api( FORRST_API_STAT_URL,
                                     FORRST_API_STAT_URL_LEN,
                                     &stats, &stats_len ) ;
  if( FORRST_SUCCESS == result ) {
    json_object* obj = json_tokener_parse( stats ) ;
    json_object* stats_obj = NULL ;
    json_object* value = NULL ;
    //
    if( NULL == obj ) {
      return FORRST_FAIL ;
    }
    //
    forrst_get_response_info( obj, response ) ;
    //
    stats_obj = json_object_object_get( obj, FORRST_API_RESP_STRING ) ;
    value = json_object_object_get( stats_obj, FORRST_API_STAT_RATE_LIMIT_STRING ) ;
    apiStatus->rateLimit = json_object_get_int( value ) ;
    json_object_put( value ) ;
    //
    value = json_object_object_get( stats_obj, FORRST_API_STAT_CALLS_MADE_STRING ) ;
    apiStatus->callsMade = json_object_get_int( stats_obj ) ;
    json_object_put( value ) ;
    //
    json_object_put( stats_obj ) ;
    json_object_put( obj ) ;
    //
    return FORRST_SUCCESS ;
  }
  //
  return FORRST_FAIL ;
}

int
forrst_get_response_info( json_object* obj, struct forrst_ResponseInfo* responseInfo ) {
  json_object* cur_obj = NULL ;
  char* value = NULL ;
  //
  if( NULL == obj || NULL == responseInfo ) {
    return FORRST_FAIL ;
  }
  //
  cur_obj = json_object_object_get( obj, FORRST_API_STAT_STAT_STRING ) ;
  value = (char*)json_object_get_string( cur_obj ) ;
  if( 0 == strcmp( "ok", value ) ) {
    responseInfo->status = FORRST_API_OK ;
  }
  else {
    responseInfo->status = FORRST_API_FAIL ;
  }
  json_object_put( cur_obj ) ;
  //
  cur_obj = json_object_object_get( obj, FORRST_API_STAT_IN_STRING ) ;
  responseInfo->responseTime = json_object_get_double( cur_obj ) ;
  json_object_put( cur_obj ) ;
  //
  cur_obj = json_object_object_get( obj, FORRST_API_STAT_ENV_STRING ) ;
  value = (char*)json_object_get_string( cur_obj ) ;
  if( 0 == strcmp("prod", value) ) {
    responseInfo->environment = FORRST_API_PRODUCTION ;
  }
  else {
    responseInfo->environment = FORRST_API_DEVELOPMENT ;
  }
  json_object_put( cur_obj ) ;
  //
  cur_obj = json_object_object_get( obj, FORRST_API_STAT_AUTHED_STRING ) ;
  value = (char*)json_object_get_string( cur_obj ) ;
  if( 0 == strcmp("true", value) ) {
    responseInfo->authed = 1 ;
  }
  else {
    responseInfo->authed = 0 ;
  }
  json_object_put( cur_obj ) ;
  //
  cur_obj = json_object_object_get( obj, FORRST_API_STAT_AUTHED_AS_STRING ) ;
  value = (char*)json_object_get_string( cur_obj ) ;
  responseInfo->authedAs = (char*)malloc( sizeof(char) * (strlen(value) + 1) ) ;
  strcpy( responseInfo->authedAs, value ) ;
  responseInfo->authedAsLen = strlen( value ) ;
  json_object_put( cur_obj ) ;
  //
  return FORRST_SUCCESS ;
}

