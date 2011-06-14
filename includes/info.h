#ifndef INFO_H__
#define INFO_H__ 1

#include <stdlib.h>
#include <string.h>

#define FORRST_API_URL_STAT "http://forrst.com/api/v2/stats"
#define FORRST_API_URL_STAT_LEN strlen(FORRST_API_URL_STAT)

int
forrst_get_stats( char** data, size_t* dataLen ) ;

#endif

