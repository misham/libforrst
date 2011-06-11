#ifndef POST_H_
#define POST_H_

#include <time.h>

#include "forrst_list.h"

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
	enum forrst_post_type			type ;
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
	struct forrst_list* comments ;
	//
	// :TODO: Store user data
	// :TODO: Store snaps
	//
} ;

int
forrst_show_posts( uint64_t id, char* tinyId,
						uint32_t tinyIdLen, struct forrst_post** curPost  ) ;

int
forrst_get_all_posts( uint64_t afterId, struct forrst_list** posts ) ;

int
forrst_get_posts_by_type( enum forrst_post_type type,
									 enum forrst_post_sort_order orderBy,
									 unsigned int page,
									 struct forrst_list** posts ) ;

#endif

