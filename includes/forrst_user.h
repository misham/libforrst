#ifndef USER_H__
#define USER_H__ 1

#include <stdint.h>

#include "forrst_info.h"

#define FORRST_API_USER_INFO_URL "http://forrst.com/api/v2/users/info"

enum forrst_user_type {
	DEVELOPER,
	DESIGNER,
	BOTH
} ;

struct forrst_user {
	uint64_t		    id ;
	char*						username ;
	size_t				  usernameLen ;
	char*						name ;
	size_t				  nameLen ;
	char*						url ;
	size_t				  urlLen ;
	size_t				  numOfPosts ;
	size_t				  numOfComments ;
	size_t				  numOfLikes ;
	size_t				  numOfFollowers ;
	size_t				  numOfFollowing ;
	char*						bio ;
	size_t          bioLen ;
	enum forrst_user_type	isA ;
	char*						homepage ;
	size_t          homepageLen ;
	char*					  twitter ;
	size_t          twitterLen ;
	int							inDirectory ;
	char*						tags ;
	size_t          tagsLen ;
  char*           photoXl ;
  size_t          photoXlLen ;
  char*           photoLarge ;
  size_t          photoLargeLen ;
  char*           photoMedium ;
  size_t          photoMediumLen ;
  char*           photoSmall ;
  size_t          photoSmallLen ;
  char*           photoThumb ;
  size_t          photoThumbLen ;
} ;

int
forrst_user_auth( char* login, size_t loginLen, char* password, size_t passwordLen ) ;

int
forrst_user_info_by_id( uint64_t userId,
                        struct forrst_ResponseInfo* response,
		                    struct forrst_user* userInfo ) ;

int
forrst_user_info_by_username( char* userName, size_t userNameLen,
                              struct forrst_ResponseInfo* response,
		                          struct forrst_user* userInfo ) ;

#endif

