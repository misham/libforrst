#ifndef CONNECTION_H__
#define CONNECTION_H__ 1

#include <stdlib.h>

#ifndef FAIL
#define FAIL 0
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

#define FORRST_API_URL "http://forrst.com/api/v2/"

#define FORRST_API_CMD_STATS "stats"

struct forrst_RawData {
  char* data ;
  size_t dataLen ;
} ;

int
forrst_get( char* data, size_t dataLen ) ;

#endif

