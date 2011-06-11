#ifndef POST_LIST_H__
#define POST_LIST_H__

#include <stdint.h>
#include <stdlib.h>

#ifndef FAIL
#define FAIL -1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

struct forrst_list {
	void*								value ;
	struct forrst_list* next ;
} ;

int
forrst_post_list_append( struct forrst_list* list, struct forrst_list* post ) ;

struct forrst_list*
forrst_post_list_find( struct forrst_list* list, uint64_t postId ) ;

#endif

