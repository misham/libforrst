#include <string.h>

#include "forrst_common.h"

int
forrst_store_string( char* in, size_t inLen, char** out, size_t* outLen ) {
  char* tmp = NULL ;
  if( NULL == in || NULL == out || strlen(in) != inLen ) {
    return FORRST_FAIL ;
  }
  //
  tmp = malloc( sizeof(char) * inLen ) ;
  if( NULL == tmp ) {
    return FORRST_FAIL ;
  }
  //
  tmp = strncpy( tmp, in, inLen ) ;
  if( NULL == tmp ) {
    return FORRST_FAIL ;
  }
  tmp[inLen] = '\0' ;
  //
  *out = tmp ;
  *outLen = strlen( *out ) ;
  //
  return FORRST_SUCCESS ;
}

