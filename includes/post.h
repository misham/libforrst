#ifndef POST_H_
#define POST_H_ 1

#include <stdint.h>
#include <time.h>

#include "info.h"

#define FORRST_API_POST_SHOW_URL "http://forrst.com/api/v2/posts/show"
#define FORRST_API_POST_ALL_URL "http://forrst.com/api/v2/posts/all"
#define FORRST_API_POST_LIST_URL "http://forrst.com/api/v2/posts/list"

enum forrst_post_type {
	NO_TYPE,
	CODE,
	SNAP,
	LINK,
	QUESTION
} ;

enum forrst_post_sort_order {
	UNORDERED,
	RECENT,
	POPULAR,
	BEST
} ;

struct forrst_comment {
	uint64_t			id ;
	char*					body ;
	uint32_t			bodyLen ;
	struct tm			createdAt ;
	struct tm			updatedAt ;
	//
	// :TODO: link user
	//
} ;

struct forrst_post {
	uint64_t						id ;
	char*								tinyId ;
	uint32_t						tinyIdLen ;
	enum forrst_post_type	type ;
	char*								postUrl ;
	uint32_t						postUrlLen ;
	struct tm						createdAt ;
	struct tm						updatedAt ;
	int									isPublished ;
	int									isPublic ;
	char*								title ;
	uint32_t						titleLen ;
	char*								url ;
	uint32_t						urlLen ;
	char*								content ;
	uint32_t						contentLen ;
	char*								description ;
	uint32_t						descriptionLen ;
	char*								formattedDescription ;
	uint32_t						formattedDescriptionLen ;
	uint32_t						likeCount ;
	uint32_t						commentCount ;
	//
	// :TODO: Store user data
	// :TODO: Store snaps
  // :TODO: Store comments
	//
} ;

int
forrst_posts_get_by_id( uint64_t id,
                        struct forrst_ResponseInfo* response,
                        struct forrst_post* post ) ;

int
forrst_posts_get_by_tinyid( char* tinyId, size_t tinyIdLen,
                            struct forrst_ResponseInfo* response,
                            struct forrst_post* post ) ;

#endif

