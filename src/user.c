#include "user.h"

#include "connection.h"

int
forrst_user_info( char* userId, size_t userIdLen,
                  char* username, size_t usernameLen,
		              struct forrst_user* userInfo ) {
  char* full_url = NULL ;
  char* user_id = NULL ;
  //
  if( NULL == username || 0 == usernameLen ||
      strlen(username) != usernameLen || NULL == userInfo ) {
    return FAIL ;
  }
  //
  user_id = (char*)malloc( sizeof(char) * (
                           )) ;
  full_url = (char*)malloc( sizeof(char) * (
                              strlen(FORRST_API_USER_INFO_URL) +
                              usernameLen + strlen(itoa(userId))
                            )) ;
  //
  return FAIL ;
}

int
forrst_user_auth( char* username, uint32_t usernameLen,
					        char* password, uint32_t passwordLen,
					        char** authToken, uint32_t authTokenLen ) {
  // :NOT WORKING:
  //
  return FAIL ;
}

int
forrst_user_posts( uint32_t userId, char* username, uint32_t usernameLen,
					         enum forrst_post_type postType, uint32_t postLimit,
						       uint32_t afterPostId,
						       struct forrst_list** usersPosts ) {
  //
  return FAIL ;
}

