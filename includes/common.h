#ifndef COMMON_H__
#define COMMON_H__ 1

#define FORRST_FAIL 0
#define FORRST_SUCCESS 1

#ifdef DEBUGGING
#define FORRST_DEBUG( fmt, ... ) \
  fprintf( stderr, "%s:%d: " fmt, __FILE__, __LINE__, \
           ##__VA_ARGS__ )
#else
#define FORRST_DEBUG( fmt, ... )
#endif

#define MAX_NUM_INTEGERS_IN_64_BIT_NUM 20

#define FORRST_API_RESP_STRING "resp"

#endif

