#include <string.h>
#include <malloc.h>
#include <curl/curl.h>

#include "forrst_common.h"
#include "forrst_connection.h"

size_t
forrst_connection_write_data( void* ptr, size_t size, size_t nmemb, void* data ){
  size_t realsize = size * nmemb ;
  struct forrst_RawData* raw_data = (struct forrst_RawData*)(data) ;
  //
  raw_data->data = realloc( raw_data->data,
                            raw_data->dataLen + realsize + 1 ) ;
  if( NULL == raw_data->data ) {
    printf( "%s:%s:%d failed to store returned data\n",
            __FILE__, __func__, __LINE__ ) ;
    return 0 ;
  }
  //
  memcpy( &(raw_data->data[raw_data->dataLen]),
          ptr,
          realsize ) ;
  raw_data->dataLen += realsize ;
  raw_data->data[raw_data->dataLen] = 0 ;
  //
  return realsize ;
}


int
forrst_get_data_from_api( char* url, size_t urlLen,
                          char** data, size_t* dataLen ) {
  char* local_data = NULL ;
  CURL* curl = curl_easy_init() ;
  int result = FORRST_SUCCESS ;
  struct forrst_RawData raw_data ;
  CURLcode return_code ;
  //
  if( NULL == data || NULL == dataLen || NULL == curl ||
      NULL == url || 0 == urlLen || urlLen != strlen(url) ) {
    curl_easy_cleanup( curl ) ;
    curl_global_cleanup() ;
    result = FORRST_FAIL ;
  }
  //
  if( '\0' != url[urlLen] ) {
    url[urlLen] = '\0' ;
  }
  //
  raw_data.data = malloc(1) ;
  raw_data.dataLen = 0 ;
  //
  curl_easy_setopt( curl, CURLOPT_URL, url ) ;
  curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, forrst_connection_write_data ) ;
  curl_easy_setopt( curl, CURLOPT_WRITEDATA, (void*)(&raw_data) ) ;
  curl_easy_setopt( curl, CURLOPT_USERAGENT, "libcurl-agent/1.0" ) ;
  //
  return_code = curl_easy_perform( curl ) ;
  //
  curl_easy_cleanup( curl ) ;
  //
  local_data = (char*)malloc( sizeof(char) * (raw_data.dataLen + 1) ) ;
  if( NULL == local_data ) {
    result = FORRST_FAIL ;
  }
  local_data = memcpy( local_data, raw_data.data, raw_data.dataLen ) ;
  local_data[raw_data.dataLen] = '\0' ;
  //
  *data = local_data ;
  *dataLen = raw_data.dataLen ;
  //
  if( raw_data.data ) {
    free( raw_data.data ) ;
  }
  curl_global_cleanup() ;
  //
  return result ;
}

