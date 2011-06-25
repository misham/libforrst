#ifndef POST_H_
#define POST_H_ 1

#include <stdint.h>
#include <time.h>

#include "forrst_info.h"

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

struct forrst_post_tag {
	char* tagValue ;
	size_t tagValueLen ;
} ;

struct forrst_post {
	uint64_t									id ;
	char*											tinyId ;
	size_t										tinyIdLen ;
	enum forrst_post_type			type ;
	char*											postUrl ;
	size_t										postUrlLen ;
	struct tm									createdAt ;
	struct tm									updatedAt ;
	int												isPublished ;
	int												isPublic ;
	char*											title ;
	size_t										titleLen ;
	char*											url ;
	size_t										urlLen ;
	char*											content ;
	size_t										contentLen ;
	char*											formattedContent ;
	size_t										formattedContentLen ;
	char*											description ;
	size_t										descriptionLen ;
	char*											formattedDescription ;
	size_t										formattedDescriptionLen ;
  uint32_t									likeCount ;
	uint32_t									commentCount ;
	char*											tagString ;
	size_t										tagStringLen ;
	char*											snapsMegaUrl ;
	size_t										snapsMegaUrlLen ;
	char*											snapsKeithUrl ;
	size_t										snapsKeithUrlLen ;
	char*											snapsLargeUrl ;
	size_t										snapsLargeUrlLen ;
	char*											snapsMediumUrl ;
	size_t										snapsMediumUrlLen ;
	char*											snapsSmallUrl ;
	size_t										snapsSmallUrlLen ;
	char*											snapsThumUrl ;
	size_t										snapsThumUrlLen ;
	char*											snapsOriginalUrl ;
	size_t										snapsOriginalUrlLen ;
	//
	// :TODO: Store user data
  // :TODO: Store comments
	//
} ;

int
forrst_posts_init_post( struct forrst_post* post ) ;

int
forrst_posts_free_post( struct forrst_post* post ) ;

int
forrst_posts_get_by_id( uint64_t id,
                        struct forrst_ResponseInfo* response,
                        struct forrst_post* post ) ;

int
forrst_posts_get_by_tinyid( char* tinyId, size_t tinyIdLen,
                            struct forrst_ResponseInfo* response,
                            struct forrst_post* post ) ;

int
forrst_posts_get_all( struct forrst_ResponseInfo* response,
                      struct forrst_post* post,
                      uint64_t afterId ) ;

#endif

