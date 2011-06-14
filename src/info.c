#include "connection.h"
#include "info.h"

int
forrst_get_stats( char** data, size_t* dataLen ) {
  char* stats = NULL ;
  size_t stats_len = 0 ;
  int result = -1 ;
  //
  if( NULL == data || NULL == dataLen ) {
    return FAIL ;
  }
  //
  result = forrst_get_data_from_api( FORRST_API_URL_STAT,
                                     FORRST_API_URL_STAT_LEN,
                                     &stats, & stats_len ) ;
  if( SUCCESS == result ) {
    *data = stats ;
    *dataLen = stats_len ;
    return SUCCESS ;
  }
  //
  return FAIL ;
}

