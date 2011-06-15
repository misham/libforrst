#ifndef INFO_H__
#define INFO_H__ 1

#include <stdlib.h>
#include <string.h>

#include <json/json.h>

#define FORRST_API_STAT_URL "http://forrst.com/api/v2/stats"
#define FORRST_API_STAT_URL_LEN strlen(FORRST_API_STAT_URL)

#define FORRST_API_STAT_STAT_STRING "stat"
#define FORRST_API_STAT_IN_STRING "in"
#define FORRST_API_STAT_AUTHED_STRING "authed"
#define FORRST_API_STAT_AUTHED_AS_STRING "authed_as"
#define FORRST_API_STAT_ENV_STRING "env"

#define FORRST_API_RESP_STRING "resp"

#define FORRST_API_STAT_RATE_LIMIT_STRING "rate_limit"
#define FORRST_API_STAT_CALLS_MADE_STRING "calls_made"

enum forrst_ResponseStatus {
  FORRST_API_OK,
  FORRST_API_FAIL
} ;

enum forrst_ResponseEnvironment {
  FORRST_API_PRODUCTION,
  FORRST_API_DEVELOPMENT
} ;

struct forrst_ResponseInfo {
  enum forrst_ResponseStatus status ;
  double responseTime ;
  enum forrst_ResponseEnvironment environment ;
  int authed ;
  char* authedAs ;
  size_t authedAsLen ;
} ;

struct forrst_Stats {
  unsigned int rateLimit ;
  unsigned int callsMade ;
} ;

int
forrst_get_stats( struct forrst_ResponseInfo* response,
                  struct forrst_Stats* apiStatus ) ;

int
forrst_get_response_info( json_object* obj,
                          struct forrst_ResponseInfo* responseInfo ) ;

#endif

