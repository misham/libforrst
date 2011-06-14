#ifndef USER_H__
#define USER_H__ 1

#include <stdint.h>

#include "forrst_list.h"
#include "post.h"

#ifndef ERROR
#define ERROR -1
#endif

#ifndef SUCCESS
#define SUCCESS
#endif

enum forrst_user_type {
	DEVELOPER,
	DESIGNER,
	BOTH
} ;

struct forrst_user {
	uint64_t				id ;
	char*						username ;
	uint32_t				usernameLen ;
	char*						name ;
	uint32_t				nameLen ;
	char*						url ;
	uint32_t				urlLen ;
	uint32_t				numOfPosts ;
	uint32_t				numOfComments ;
	uint32_t				numOfLikes ;
	uint32_t				numOfFollowers ;
	uint32_t				numOfFollowing ;
	char*						bio ;
	uint64_t				bioLen ;
	enum forrst_user_type	isA ;
	char*						homepage ;
	uint32_t				homepageLen ;
	char*					  twitter ;
	uint32_t				twitterLen ;
	int							inDirectory ;
	char*						tags ;
	uint32_t				tagsLen ;
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
		       struct forrst_user userInfo ) ;

int
forrst_user_posts( uint32_t userId, char* username, uint32_t usernameLen,
					  enum forrst_post_type postType, uint32_t postLimit,
						uint32_t afterPostId,
						struct forrst_list** usersPosts ) ;

#endif

