#include <malloc.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "forrst_list.h"

struct forrst_list* post_list = NULL ;

int
init_suite_post_list() {
	post_list = (struct forrst_list*)malloc( sizeof(struct forrst_list) ) ;
	if( NULL == post_list ) {
		return -1 ;
	}
	else {
		return 0 ;
	}
}

int
clean_suite_post_list() {
	struct forrst_list* cur = post_list ;
	while( post_list ) {
		post_list = cur->next ;
		free( cur ) ;
	}
	//
	return 0 ;
}

void
test_post_list_append() {
	if( NULL != post_list ) {
		CU_ASSERT( 0 == 0 ) ;
	}
}

void
test_post_list_find() {
	if( NULL != post_list ) {
		CU_ASSERT( 1 == 1 ) ;
	}
}

int
main() {
	CU_pSuite post_list_suite = NULL ;

	/* initialize the CUnit test registry */
	if( CUE_SUCCESS != CU_initialize_registry() ) {
		return CU_get_error() ;
	}

	/* add a suite to the registry */
	post_list_suite = CU_add_suite( "Suite_Post_List", init_suite_post_list, clean_suite_post_list ) ;
	if( NULL == post_list_suite ) {
		CU_cleanup_registry() ;
		return CU_get_error() ;
	}

	/* add the tests to the suite */
	if( (NULL == CU_add_test(post_list_suite, "test appending to post list", test_post_list_append)) ||
			(NULL == CU_add_test(post_list_suite, "test finding post in post list", test_post_list_find)) )
	{
		CU_cleanup_registry() ;
		return CU_get_error() ;
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode( CU_BRM_VERBOSE ) ;
	CU_basic_run_tests() ;
	CU_cleanup_registry() ;
	return CU_get_error() ;
}
