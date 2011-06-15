#ifndef USER_H__
#define USER_H__ 1

#include <stdint.h>

#include "forrst_list.h"
#include "post.h"

#ifndef FAIL
#define FAIL 0
#endif

#ifndef SUCCESS
#define SUCCESS 1
#endif

#define FORRST_API_USER_INFO_URL "http://forrst.com/api/v2/users/info"

enum forrst_user_type {
	DEVELOPER,
	DESIGNER,
	BOTH
} ;

struct forrst_user {
	char*				    id ;
  size_t          idLen ;
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
	//
	// :TODO: Photos?
	//
} ;

int
forrst_user_auth( char* username, uint32_t usernameLen,
					        char* password, uint32_t passwordLen,
					        char** authToken, uint32_t authTokenLen ) ;

int
forrst_user_info( uint32_t userId, char* username, uint32_t usernameLen,
		              struct forrst_user* userInfo ) ;

int
forrst_user_posts( uint32_t userId, char* username, uint32_t usernameLen,
					         enum forrst_post_type postType, uint32_t postLimit,
						       uint32_t afterPostId,
						       struct forrst_list** usersPosts ) ;

#endif

