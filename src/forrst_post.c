#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <json/json.h>

#include "forrst_common.h"
#include "forrst_connection.h"
#include "forrst_post.h"

static int
forrst_post_store_value( char* key, json_object* value,
                         struct forrst_post* post ) ;

int
forrst_posts_get_by_id( uint64_t id,
                        struct forrst_ResponseInfo* response,
                        struct forrst_post* post ) {
  char* full_url = NULL ;
  json_object* obj = NULL ;
	json_object* post_obj = NULL ;
  int result = FORRST_FAIL ;
  char* post_info = NULL ;
  size_t post_info_len = 0 ;
  //
  if( NULL == post || NULL == response ) {
    return FORRST_FAIL ;
  }
  //
  full_url = (char*)malloc( sizeof(char) * (
                              strlen(FORRST_API_POST_SHOW_URL) +
                              MAX_NUM_INTEGERS_IN_64_BIT_NUM +
                              strlen("/?id=") + 1
                            )) ;
  if( NULL == full_url ) {
    return FORRST_FAIL ;
  }
  //
#if __WORDSIZE == 64
  sprintf( full_url, "%s/?id=%lu", FORRST_API_POST_SHOW_URL, id ) ;
#else
  sprintf( full_url, "%s/?id=%llu", FORRST_API_POST_SHOW_URL, id ) ;
#endif
  //
  result = forrst_get_data_from_api( full_url, strlen(full_url),
                                     &post_info, &post_info_len ) ;
  if( FORRST_FAIL == result || NULL == post_info ||
      strlen(post_info) != post_info_len ) {
    return FORRST_FAIL ;
  }
  //
  obj = json_tokener_parse( post_info ) ;
  if( NULL == obj ) {
    return FORRST_FAIL ;
  }
  //
  forrst_get_response_info( obj, response ) ;
	//
	post_obj = json_object_object_get( obj, FORRST_API_RESP_STRING ) ;
	if( NULL == post_obj ) {
		json_object_put( obj ) ;
		return FORRST_FAIL ;
	}
	//
	json_object_object_foreach( post_obj, key, val ) {
		forrst_post_store_value( key, val, post ) ;
	}
	//
	json_object_put( post_obj ) ;
	json_object_put( obj ) ;
  //
  return FORRST_SUCCESS ;
}

int
forrst_posts_get_by_tinyid( char* tinyId, size_t tinyIdLen,
                            struct forrst_ResponseInfo* response,
														struct forrst_post* post ) {
	char* full_url = NULL ;
  json_object* obj = NULL ;
	json_object* post_obj = NULL ;
  int result = FORRST_FAIL ;
  char* post_info = NULL ;
  size_t post_info_len = 0 ;
  //
  if( NULL == post || NULL == response || NULL == tinyId ||
			0 == tinyIdLen || strlen(tinyId) != tinyIdLen ) {
    return FORRST_FAIL ;
  }
  //
  full_url = (char*)malloc( sizeof(char) * (
                              strlen(FORRST_API_POST_SHOW_URL) +
                              tinyIdLen + strlen("/?tiny_id=") + 1
                            )) ;
  if( NULL == full_url ) {
    return FORRST_FAIL ;
  }
  //
  sprintf( full_url, "%s/?tiny_id=%s", FORRST_API_POST_SHOW_URL, tinyId ) ;
  //
  result = forrst_get_data_from_api( full_url, strlen(full_url),
                                     &post_info, &post_info_len ) ;
  if( FORRST_FAIL == result || NULL == post_info ||
      strlen(post_info) != post_info_len ) {
    return FORRST_FAIL ;
  }
  //
  obj = json_tokener_parse( post_info ) ;
  if( NULL == obj ) {
    return FORRST_FAIL ;
  }
  //
  forrst_get_response_info( obj, response ) ;
	//
	post_obj = json_object_object_get( obj, FORRST_API_RESP_STRING ) ;
	if( NULL == post_obj ) {
		json_object_put( obj ) ;
		return FORRST_FAIL ;
	}
	//
	json_object_object_foreach( post_obj, key, val ) {
		forrst_post_store_value( key, val, post ) ;
	}
	//
	json_object_put( post_obj ) ;
	json_object_put( obj ) ;
  //
  return FORRST_SUCCESS ;
}

static int
forrst_post_store_value( char* key, json_object* value,
												 struct forrst_post* post ) {
	int result = FORRST_SUCCESS ;
	char* tmp = NULL ;
	//
	if( NULL == key || NULL == value || NULL == post ) {
		return FORRST_FAIL ;
	}
	//
	if( 0 == strcmp(key, "id") ) {
    post->id = json_object_get_int( value ) ;
  }
  else if( 0 == strcmp(key, "tiny_id") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->tinyId),
                                  &(post->tinyIdLen) ) ;
  }
	else if( 0 == strcmp(key, "post_type") ) {
    tmp = (char*)json_object_get_string( value ) ;
		if( 0 == strcmp(tmp, "code") ) {
			post->type = CODE ;
		}
		else if( 0 == strcmp(tmp, "snap") ) {
			post->type = SNAP ;
		}
		else if( 0 == strcmp(tmp, "link") ) {
			post->type = LINK ;
		}
		else if( 0 == strcmp(tmp, "question") ) {
			post->type = QUESTION ;
		}
		else {
			post->type = NO_TYPE ;
		}
  }
	else if( 0 == strcmp(key, "post_url") ) {
    tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->postUrl),
                                  &(post->postUrlLen) ) ;
  }
	else if( 0 == strcmp(key, "created_at") ) {
  }
	else if( 0 == strcmp(key, "updated_at") ) {
  }
	else if( 0 == strcmp(key, "published") ) {
		if( TRUE == json_object_get_boolean( value ) ) {
			post->isPublished = 1 ;
		}
		else {
			post->isPublished = 0 ;
		}
	}
	else if( 0 == strcmp(key, "public") ) {
		if( TRUE == json_object_get_boolean( value ) ) {
			post->isPublic = 1 ;
		}
		else {
			post->isPublic = 0 ;
		}
	}
	else if( 0 == strcmp(key, "title") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->title),
                                  &(post->titleLen) ) ;
	}
	else if( 0 == strcmp(key, "url") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->url),
                                  &(post->urlLen) ) ;
	}
	else if( 0 == strcmp(key, "content") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->content),
                                  &(post->contentLen) ) ;
	}
	else if( 0 == strcmp(key, "formatted_content") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->formattedContent),
                                  &(post->formattedContentLen) ) ;
	}
	else if( 0 == strcmp(key, "description") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->description),
                                  &(post->descriptionLen) ) ;
	}
	else if( 0 == strcmp(key, "formatted_description") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->formattedDescription),
                                  &(post->formattedDescriptionLen) ) ;
	}
	else if( 0 == strcmp(key, "like_count") ) {
		post->likeCount = json_object_get_int( value ) ;
	}
	else if( 0 == strcmp(key, "comment_count") ) {
		post->commentCount = json_object_get_int( value ) ;
	}
	else if( 0 == strcmp(key, "tag_string") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->tagString),
                                  &(post->tagStringLen) ) ;
	}
	else if( 0 == strcmp(key, "snaps") ) {
		json_object* tmp = value ;
		json_object_object_foreach( tmp, key, val ) {
			forrst_post_store_value( key, val, post ) ;
		}
	}
	else if( 0 == strcmp(key, "mega_url") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->snapsMediumUrl),
                                  &(post->snapsMediumUrlLen) ) ;
	}
	else if( 0 == strcmp(key, "keith_url") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->snapsKeithUrl),
                                  &(post->snapsKeithUrlLen) ) ;
	}
	else if( 0 == strcmp(key, "large_url") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->snapsLargeUrl),
                                  &(post->snapsLargeUrlLen) ) ;
	}
	else if( 0 == strcmp(key, "medium_url") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->snapsMediumUrl),
                                  &(post->snapsMediumUrlLen) ) ;
	}
	else if( 0 == strcmp(key, "small_url") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->snapsSmallUrl),
                                  &(post->snapsSmallUrlLen) ) ;
	}
	else if( 0 == strcmp(key, "thumb_url") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->snapsThumUrl),
                                  &(post->snapsThumUrlLen) ) ;
	}
	else if( 0 == strcmp(key, "original_url") ) {
		tmp = (char*)json_object_get_string( value ) ;
    result = forrst_store_string( tmp, strlen(tmp),
                                  &(post->snapsOriginalUrl),
                                  &(post->snapsOriginalUrlLen) ) ;
	}
	else if( 0 == strcmp(key, "tags") ) {
		// :TODO:
	}
	//
	return result ;
}

