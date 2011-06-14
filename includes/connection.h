#ifndef CONNECTION_H__
#define CONNECTION_H__ 1

#include <stdlib.h>

#ifndef FAIL
#define FAIL 0
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

struct forrst_RawData {
  char* data ;
  size_t dataLen ;
} ;

int
forrst_get_data_from_api( char* url, size_t urlLen,
                          char** data, size_t* dataLen ) ;

#endif

