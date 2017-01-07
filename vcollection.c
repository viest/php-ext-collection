/**********************************************************\
|                                                          |
|                       vcollec                            |
|                                                          |
| Official WebSite: http://www.vikin.cc                    |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * vcollection.c                                          *
 *                                                        *
 *                                                        *
 * LastModified: Dec 18, 2016                             *
 * Author: Wang Jiexin <vikindev@outlook.com>             *
 *                                                        *
\**********************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/basic_functions.h"
#include "ext/standard/php_var.h"
#include "vcollection_common.h"
#include "php_vcollection.h"

#include "zend.h"
#include "zend_API.h"

static int le_vcollection;

zend_class_entry *vcollection_ce;

ZEND_BEGIN_ARG_INFO_EX(new_arg, 0, 0, 1)
    ZEND_ARG_ARRAY_INFO(0, var_items, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(call_fun, 0, 0, 1)
    ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(avg_arg, 0, 0, 0)
	ZEND_ARG_INFO(0, args)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(has_arg, 0, 0, 0)
	ZEND_ARG_INFO(0, arg)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(max_arg, 0, 0, 0)
	ZEND_ARG_INFO(0, max)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(min_arg, 0, 0, 0)
	ZEND_ARG_INFO(0, min)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(take_arg, 0, 0, 0)
	ZEND_ARG_INFO(0, take)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(pluck_arg, 0, 0, 0)
	ZEND_ARG_INFO(0, arg_val)
	ZEND_ARG_INFO(0, arg_key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(where_arg, 0, 0, 2)
	ZEND_ARG_INFO(0, arg_key)
	ZEND_ARG_INFO(0, arg_val)
	ZEND_ARG_INFO(0, arg_conditional)
ZEND_END_ARG_INFO()

ZEND_METHOD(vcollection, __construct) {

}

ZEND_METHOD(vcollection, getinstance) {
	zval *instance, *var_items;
	
	instance = zend_read_static_property(vcollection_ce, "instance", sizeof("instance")-1, 0);

	if(Z_TYPE_P(instance) == IS_NULL) {

	#ifdef FAST_ZPP
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &var_items) == FAILURE) {
			return;
		}
	#else
		ZEND_PARSE_PARAMETERS_START(1, 1)
			Z_PARAM_ARRAY(&var_items)
		ZEND_PARSE_PARAMETERS_END();
	#endif

		object_init_ex(return_value, vcollection_ce);

		zend_update_property(vcollection_ce, return_value, "items", sizeof("items")-1, var_items TSRMLS_CC);
		zend_update_static_property(vcollection_ce, "instance", sizeof("instance")-1, return_value TSRMLS_CC);

	} else {
		RETURN_ZVAL(instance, 1, 0);
	}
}

ZEND_METHOD(vcollection, map) {
	zval *arrays = NULL;
	zval *value;
	zval args[2];
	zval retval, map_retval;
	zval rv;
	zend_ulong long_key;
    zend_string *str_key;
	zend_fcall_info fci = empty_fcall_info;
	zend_fcall_info_cache fci_cache = empty_fcall_info_cache;
	HashTable *htbl;
	arrays = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 0, &rv TSRMLS_DC);
	ZEND_PARSE_PARAMETERS_START(1, -1)
		Z_PARAM_FUNC_EX(fci, fci_cache, 1, 0)
	ZEND_PARSE_PARAMETERS_END();
	htbl = Z_ARRVAL_P(arrays);
	if (zend_hash_num_elements(htbl) == 0) {
		return;
	}
	ZEND_HASH_FOREACH_KEY_VAL(htbl, long_key, str_key, value)
	{
		fci.retval = &retval;
		fci.param_count = 2;
		fci.params = args;
		fci.no_separation = 0;
		if (str_key) {
			ZVAL_STR_COPY(&args[0], str_key);
		} else {
			ZVAL_LONG(&args[0], long_key);
		}
		ZVAL_COPY(&args[1], value);
		if (zend_call_function(&fci, &fci_cache) == SUCCESS && Z_TYPE(retval) != IS_UNDEF) {
			if(str_key) {
				zend_hash_update(htbl, str_key, &retval);
			}else{
				zend_hash_index_update(htbl, long_key, &retval);
			}
			zval_ptr_dtor(&args[1]);
			zval_ptr_dtor(&args[0]);
		} else {
			zval_ptr_dtor(&args[1]);
			zval_ptr_dtor(&args[0]);
			RETURN_NULL();
		}
	} ZEND_HASH_FOREACH_END();
	ZVAL_COPY(&map_retval, getThis());
	RETURN_ZVAL(&map_retval, 0, 0);
}

ZEND_METHOD(vcollection, collapse) {
	zval *items = NULL;
	zval *value;
	zval *valuea;
	zval ret_val, retval;
	zval temp;
	zval rv;
	HashTable *htbl;
	HashTable *htbla;
	zval *object;
	array_init(&ret_val);
	items = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 0, &rv TSRMLS_DC);
	htbl = Z_ARRVAL_P(items);
	ZEND_HASH_FOREACH_VAL(htbl, value) {
		if( Z_TYPE_P(value) != IS_NULL && Z_TYPE_P(value) == IS_ARRAY ){
			htbla = Z_ARRVAL_P(value);
        	ZEND_HASH_FOREACH_VAL(htbla, valuea) {
        		ZVAL_COPY(&temp, valuea);
        		add_next_index_zval(&ret_val, &temp);
			} ZEND_HASH_FOREACH_END();
    	} else {
    		ZVAL_COPY(&temp, value);
        	add_next_index_zval(&ret_val, &temp);
    	}
	} ZEND_HASH_FOREACH_END();
	zend_update_property(vcollection_ce, getThis(), "items", sizeof("items")-1, &ret_val TSRMLS_CC);
	ZVAL_COPY(&retval, getThis());
	RETURN_ZVAL(&retval, 0, 0);
}

ZEND_METHOD(vcollection, avg) {
	zval *arrays = NULL;
	zval call_args[2];
	zval *value;
	zval rv;
	zval call_result;
	zval result;
  	zval leng;
  	zval sum;
	zend_string *args = NULL;
	HashTable *htbl;
  	long a,b;
  	int num = 0;
  	double aa;
	ZVAL_LONG(&leng, 0);
	zval function_array_column;
	zval function_array_sum;
	ZVAL_STRING(&function_array_column, "array_column");
	ZVAL_STRING(&function_array_sum, "array_sum");
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR(args)
	ZEND_PARSE_PARAMETERS_END();
	arrays = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 0, &rv TSRMLS_DC);
	if (args != NULL) {
		ZVAL_COPY(&call_args[0], arrays);
		ZVAL_STR_COPY(&call_args[1], args);
		if (call_user_function(EG(function_table), NULL, &function_array_column, &call_result, 2, call_args) == FAILURE) {
			zval_ptr_dtor(&call_args[1]);
			zval_ptr_dtor(&call_args[0]);
			zval_ptr_dtor(&call_result);
			ZVAL_UNDEF(&call_result);
		} else if (Z_ISUNDEF(call_result)) {
			ZVAL_NULL(&call_result);
			zval_ptr_dtor(&call_args[1]);
			zval_ptr_dtor(&call_args[0]);
		}
	    if(Z_TYPE(call_result) == IS_ARRAY){
	      if(call_user_function(EG(function_table), NULL, &function_array_sum, &sum, 1, &call_result) == FAILURE) {
	        zval_ptr_dtor(&sum);
	        ZVAL_UNDEF(&sum);
	      }
	    }
	    if(Z_TYPE(sum) == IS_LONG) {
	      ZVAL_LONG(&leng, zend_hash_num_elements(Z_ARRVAL_P(&call_result)));
	      a = Z_LVAL_P(&sum);
	      b = Z_LVAL_P(&leng);
	      if((((double)a/b) - (long)(a/b)) > 0) {
	      	RETURN_DOUBLE(((double)a/b));
	      }
	      RETURN_LONG((a/b));
	    } else if (Z_TYPE(sum) == IS_DOUBLE) {
	      ZVAL_LONG(&leng, zend_hash_num_elements(Z_ARRVAL_P(&call_result)));
	      aa = Z_DVAL_P(&sum);
	      b = Z_LVAL_P(&leng);
	      RETURN_DOUBLE((aa/b));
	    }
	} else {
		htbl = Z_ARRVAL_P(arrays);
		ZEND_HASH_FOREACH_VAL(htbl, value) {
			if( Z_TYPE_P(value) != IS_NULL && Z_TYPE_P(value) == IS_ARRAY ){
				continue;
	    	} else {
	    		num += 1;
	    	}
		} ZEND_HASH_FOREACH_END();
		if(call_user_function(EG(function_table), NULL, &function_array_sum, &sum, 1, arrays) == FAILURE) {
	        zval_ptr_dtor(&sum);
	        ZVAL_UNDEF(&sum);
	    }
	    if(Z_TYPE(sum) == IS_LONG) {
	      ZVAL_LONG(&leng, zend_hash_num_elements(Z_ARRVAL_P(&call_result)));
	      a = Z_LVAL_P(&sum);
	      if((((double)a/num) - (long)(a/num)) > 0) {
	      	RETURN_DOUBLE(((double)a/num));
	      }
	      RETURN_LONG((a/num));
	    } else if (Z_TYPE(sum) == IS_DOUBLE) {
	      ZVAL_LONG(&leng, zend_hash_num_elements(Z_ARRVAL_P(&call_result)));
	      aa = Z_DVAL_P(&sum);
	      RETURN_DOUBLE((aa/num));
	    }
	}
}

ZEND_METHOD(vcollection, has) {
	zval *arrays = NULL;
	zval *arg;
	zend_long arg_long;
	zend_string arg_string;
	zend_bool result;
	zval rv;
	HashTable *htbl;
#ifdef FAST_ZPP
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &arg) == FAILURE) {
		return;
	}
#else
 	ZEND_PARSE_PARAMETERS_START(1, 1)
 		Z_PARAM_ZVAL(&arg)
 	ZEND_PARSE_PARAMETERS_END();
#endif
 	arrays = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 0, &rv TSRMLS_DC);
 	htbl = Z_ARRVAL_P(arrays);
 	if(Z_TYPE_P(arg) == IS_STRING) {
 		RETURN_BOOL(zend_hash_exists(htbl, Z_STR(*arg)));
 	} else if (Z_TYPE_P(arg) == IS_LONG) {
 		RETURN_BOOL(zend_hash_index_exists(htbl, Z_LVAL(*arg)));
 	} else {
 		php_error_docref(NULL, E_ERROR, "Only accept integers and string type parameters");
		RETURN_FALSE;
 	}
}

ZEND_METHOD(vcollection, mx) {
	zval *arrays = NULL;
	zval *value;
  	zval call_result, rv, call_args[2];
	HashTable *htbl;
	zend_string *arg = NULL;
  	zval function_array_column;
  	double temp = 0;
	ZVAL_STRING(&function_array_column, "array_column");
#ifdef FAST_ZPP
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|S", &arg) == FAILURE) {
		return;
	}
#else
 	ZEND_PARSE_PARAMETERS_START(0, 1)
 		Z_PARAM_OPTIONAL
 		Z_PARAM_STR(arg)
 	ZEND_PARSE_PARAMETERS_END();
#endif
 	arrays = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 0, &rv TSRMLS_DC);
 	if(arg != NULL) {
    	ZVAL_COPY(&call_args[0], arrays);
		ZVAL_STR_COPY(&call_args[1], arg);
	    if (call_user_function(EG(function_table), NULL, &function_array_column, &call_result, 2, call_args) == FAILURE) {
			zval_ptr_dtor(&call_args[1]);
			zval_ptr_dtor(&call_args[0]);
			zval_ptr_dtor(&call_result);
			ZVAL_UNDEF(&call_result);
		} else if (Z_ISUNDEF(call_result)) {
			ZVAL_NULL(&call_result);
			zval_ptr_dtor(&call_args[1]);
			zval_ptr_dtor(&call_args[0]);
		}
		if (Z_TYPE(call_result) == IS_ARRAY) {
	    	htbl = Z_ARRVAL(call_result);
	    	v_array_max(htbl, &temp);
	    }
		if(temp - (long)temp > 0) {
 			RETURN_DOUBLE(temp);
 		} else {
 			RETURN_LONG(temp);
 		}
 	} else {
    	htbl = Z_ARRVAL_P(arrays);
    	v_array_max(htbl, &temp);
 		if(temp - (long)temp > 0) {
 			RETURN_DOUBLE(temp);
 		} else {
 			RETURN_LONG(temp);
 		}
 	}
}

ZEND_METHOD(vcollection, mi) {
	zval *arrays = NULL;
	zval *value;
  	zval call_result, rv, call_args[2];
	HashTable *htbl;
	zend_string *arg = NULL;
  	zval function_array_column;
  	double temp = 0;
	ZVAL_STRING(&function_array_column, "array_column");
#ifdef FAST_ZPP
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|S", &arg) == FAILURE) {
		return;
	}
#else
 	ZEND_PARSE_PARAMETERS_START(0, 1)
 		Z_PARAM_OPTIONAL
 		Z_PARAM_STR(arg)
 	ZEND_PARSE_PARAMETERS_END();
#endif
 	arrays = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 0, &rv TSRMLS_DC);
 	if(arg != NULL) {
    	ZVAL_COPY(&call_args[0], arrays);
		ZVAL_STR_COPY(&call_args[1], arg);
	    if (call_user_function(EG(function_table), NULL, &function_array_column, &call_result, 2, call_args) == FAILURE) {
			zval_ptr_dtor(&call_args[1]);
			zval_ptr_dtor(&call_args[0]);
			zval_ptr_dtor(&call_result);
			ZVAL_UNDEF(&call_result);
		} else if (Z_ISUNDEF(call_result)) {
			ZVAL_NULL(&call_result);
			zval_ptr_dtor(&call_args[1]);
			zval_ptr_dtor(&call_args[0]);
		}
		if (Z_TYPE(call_result) == IS_ARRAY) {
	    	htbl = Z_ARRVAL(call_result);
	    	v_array_mix(htbl, &temp);
	    }
		if(temp - (long)temp > 0) {
 			RETURN_DOUBLE(temp);
 		} else {
 			RETURN_LONG(temp);
 		}
 	} else {
    	htbl = Z_ARRVAL_P(arrays);
    	v_array_mix(htbl, &temp);
 		if(temp - (long)temp > 0) {
 			RETURN_DOUBLE(temp);
 		} else {
 			RETURN_LONG(temp);
 		}
 	}
}

ZEND_METHOD (vcollection, toJson) {
	zval *arrays = NULL;
	zval rv, call_result, function_to_json;

	ZVAL_STRING(&function_to_json, "json_encode");
	arrays = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 1, &rv TSRMLS_DC);

	if (call_user_function(EG(function_table), NULL, &function_to_json, &call_result, 1, arrays) == FAILURE) {
		zval_dtor(arrays);
		zval_ptr_dtor(&call_result);
		ZVAL_UNDEF(&call_result);
	} else if (Z_ISUNDEF(call_result)) {
		zval_dtor(arrays);
		ZVAL_NULL(&call_result);
	}

	RETURN_ZVAL(&call_result, 0 ,0);
}

ZEND_METHOD (vcollection, toArray) {
	zval *arrays = NULL;
	zval rv, retval;
	arrays = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 0, &rv);

	ZVAL_COPY(&retval, arrays);
	zval_ptr_dtor(arrays);

	zend_update_property(vcollection_ce, getThis(), "items", sizeof("items")-1, &retval);

	RETURN_ZVAL(&retval, 0, 0);
}

ZEND_METHOD (vcollection, take) {
	zval *arg;
	zval rv, function_to_slice, call_result, args[3], retval;
	zval *arrays = NULL;

#ifdef FAST_ZPP
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &arg) == FAILURE) {
		return;
	}
#else
 	ZEND_PARSE_PARAMETERS_START(0, 1)
 		Z_PARAM_OPTIONAL
 		Z_PARAM_ZVAL(&arg)
 	ZEND_PARSE_PARAMETERS_END();
#endif

 	ZVAL_STRING(&function_to_slice, "array_slice");
 	arrays = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 0, &rv TSRMLS_DC);

 	if(Z_TYPE_P(arg) == IS_LONG) {
 		if(Z_LVAL_P(arg) < 0) {
	 		ZVAL_COPY(&args[0], arrays);
			ZVAL_LONG(&args[1], Z_LVAL_P(arg));
			ZVAL_LONG(&args[2], abs((int)Z_LVAL_P(arg)));
		} else {
			ZVAL_COPY(&args[0], arrays);
			ZVAL_LONG(&args[1], 0);
			ZVAL_LONG(&args[2], Z_LVAL_P(arg));
		}
	 	if (call_user_function(EG(function_table), NULL, &function_to_slice, &call_result, 3, args) == FAILURE) {
	 		zval_ptr_dtor(&args[2]);
			zval_ptr_dtor(&args[1]);
			zval_ptr_dtor(&args[0]);
			zval_ptr_dtor(&call_result);
			ZVAL_UNDEF(&call_result);
		} else if (Z_ISUNDEF(call_result)) {
			zval_ptr_dtor(&args[2]);
			zval_ptr_dtor(&args[1]);
			zval_ptr_dtor(&args[0]);
			ZVAL_NULL(&call_result);
		}
		zend_update_property(vcollection_ce, getThis(), "items", sizeof("items")-1, &call_result TSRMLS_CC);
		ZVAL_COPY(&retval, getThis());
		RETURN_ZVAL(&retval, 0, 0);
 	} else {
 		php_error_docref(NULL, E_ERROR, "Only accept integers type parameters");
 	}
}

ZEND_METHOD(vcollection, pluck) {
	zval *array = NULL;
	zval rv;
	zval combine;
	zval args[2];
	zval result_val;
	zval result_key;
	zval result_all;
	zend_string *arg_val;
	zend_string *arg_key = NULL;

#ifdef FAST_ZPP
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "S|S", &arg_val, &arg_key) == FAILURE) {
		return;
	}
#else
 	ZEND_PARSE_PARAMETERS_START(1, 2)
 		Z_PARAM_STR(&arg_val)
 		Z_PARAM_OPTIONAL
 		Z_PARAM_STR(&arg_key)
 	ZEND_PARSE_PARAMETERS_END();
#endif

 	array = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 0, &rv TSRMLS_DC);
  	v_collect_pluck(array, arg_val, &result_val);

  	if(arg_key != NULL) {
  		v_collect_pluck(array, arg_key, &result_key);
  		ZVAL_STRING(&combine, "array_combine");
  		ZVAL_COPY(&args[0], &result_key);
  		ZVAL_COPY(&args[1], &result_val);
  		if (call_user_function(EG(function_table), NULL, &combine, &result_all, 2, args) == FAILURE) {
			zval_ptr_dtor(&args[1]);
			zval_ptr_dtor(&args[0]);
			zval_ptr_dtor(&result_all);
			ZVAL_UNDEF(&result_all);
		} else if (Z_ISUNDEF(result_all)) {
			zval_ptr_dtor(&args[1]);
			zval_ptr_dtor(&args[0]);
			ZVAL_NULL(&result_all);
		}
  		
  		RETURN_ZVAL(&result_all, 0, 0);
  	}
  	
	RETURN_ZVAL(&result_val, 0, 0);
}

ZEND_METHOD(vcollection, where) {
	zval *array = NULL;
	zval *value;
	zval rv;
	zend_string *arg_key;
	zend_string *arg_val = NULL;
	// zend_string *arg_conditional = NULL;
	zend_ulong long_key;
    zend_string *str_key;
    zval explode_retval;
    zend_long explode_no = 0;
    zval exists_retval;
    zval column_retval;
    zval result;

#ifdef FAST_ZPP
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "SS|S", &arg_key, &arg_val) == FAILURE) {
		return;
	}
#else
 	ZEND_PARSE_PARAMETERS_START(2, 3)
 		Z_PARAM_STR(&arg_key)
 		Z_PARAM_STR(&arg_val)
 		// Z_PARAM_OPTIONAL
 		// Z_PARAM_STR(&arg_conditional)
 	ZEND_PARSE_PARAMETERS_END();
#endif

 	array = zend_read_property(vcollection_ce, getThis(), "items", sizeof("items")-1, 0, &rv TSRMLS_DC);

 	// if(arg_conditional == NULL) {
 		array_init(&result);

 		v_explode(arg_key, &explode_retval);
 		HashTable *explode_htbl = Z_ARRVAL(explode_retval);
 		
 		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(array), long_key, str_key, value) {
 			explode_no = 0;
 			Bucket *explode_bucket = &explode_htbl->arData[explode_no];
 			v_key_exists(&(explode_bucket->val), value, &exists_retval);

 			if(Z_TYPE(exists_retval) == IS_TRUE) {
 				while(1) {
 					if(explode_no == 0 && zend_hash_num_elements(explode_htbl) > 1) {
	 					explode_no++;
	 					explode_bucket = &explode_htbl->arData[explode_no];
	 					v_column(value, &(explode_bucket->val), &column_retval);
	 				} else if(explode_no == 0 && zend_hash_num_elements(explode_htbl) == 1) {
	 					array_init(&column_retval);
	 					HashTable *value_htbl = Z_ARRVAL_P(value);
	 					for (int i = 0; i < zend_hash_num_elements(value_htbl); ++i)
	 					{
							zval retval;
							v_strcmp(value_htbl->arData[i].key, Z_STR(explode_bucket->val), &retval);
							if( zval_get_long(&retval) == 0) {
								add_index_zval(&column_retval, zval_get_long(&retval), &(value_htbl->arData[i].val));
							}
	 					}
	 				} else {
	 					explode_bucket = &explode_htbl->arData[explode_no];
	 					v_column(&column_retval, &(explode_bucket->val), &column_retval);
	 				}

	 				HashTable *column_htbl = Z_ARRVAL(column_retval);
	 				zend_long no_temp = 0;

	 				if(zend_hash_num_elements(column_htbl) == 1 && Z_TYPE_P(&column_htbl->arData[no_temp].val) != IS_ARRAY) {
	 					zval retvala;
	 					if(Z_TYPE_P(&column_htbl->arData[no_temp].val) == IS_STRING){
	 						v_strcmp(Z_STR_P(&column_htbl->arData[no_temp].val), arg_val, &retvala);
	 					} else if (Z_TYPE_P(&column_htbl->arData[no_temp].val) == IS_LONG) {
	 						zval retvala_long;
	 						v_intval(arg_val, &retvala_long);
	 						if(Z_LVAL_P(&column_htbl->arData[no_temp].val) == zval_get_long(&retvala_long)) {
	 							ZVAL_LONG(&retvala, 0);
	 						}else{
	 							ZVAL_LONG(&retvala, 1);
	 						}
	 						zval_ptr_dtor(&retvala_long);
	 					} else if (Z_TYPE_P(&column_htbl->arData[no_temp].val) == IS_DOUBLE) {
	 						zval retvala_double;
	 						v_floatval(arg_val, &retvala_double);
	 						if(Z_DVAL_P(&column_htbl->arData[no_temp].val) == zval_get_double(&retvala_double)) {
	 							ZVAL_LONG(&retvala, 0);
	 						}else{
	 							ZVAL_LONG(&retvala, 1);
	 						}
	 						zval_ptr_dtor(&retvala_double);
	 					}

	 					if(zval_get_long(&retvala) == 0) {
	 						HashTable *arr_htbl = Z_ARRVAL_P(array);
	 						add_next_index_zval(&result, &arr_htbl->arData[long_key].val);
	 					}
	 					zval_ptr_dtor(&retvala);
	 					explode_no = 0;
	 					break;
	 				}

	 				if(explode_no > zend_hash_num_elements(explode_htbl)) {
	 					break;
	 				}

	 				explode_no++;
 				}
 				
 			}
 			ZVAL_NULL(&exists_retval);
		} ZEND_HASH_FOREACH_END();

		zend_update_property(vcollection_ce, getThis(), "items", sizeof("items")-1, &result);

		ZVAL_COPY(return_value, getThis());
		RETURN_ZVAL(return_value, 0, 0);

 	// } else {
 	// 	RETURN_STR(arg_conditional);
 	// }
}

PHP_MSHUTDOWN_FUNCTION(vcollection)
{
	return SUCCESS;
}

PHP_RINIT_FUNCTION(vcollection)
{
#if defined(COMPILE_DL_VCOLLECTION) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}


PHP_RSHUTDOWN_FUNCTION(vcollection)
{
	return SUCCESS;
}


PHP_MINFO_FUNCTION(vcollection)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "vcollection support", "enabled");

	#if defined(PHP_VCOLLECTION_VERSION) && defined(PHP_VCOLLECTION_AUTHOR)
	php_info_print_table_row(2, "Vcollect Version", PHP_VCOLLECTION_VERSION);
	php_info_print_table_row(2, "Author", PHP_VCOLLECTION_AUTHOR);
	#endif

	php_info_print_table_end();
}


const zend_function_entry vcollection_functions[] = {
	ZEND_ME(vcollection, __construct, new_arg, ZEND_ACC_PRIVATE)
	ZEND_ME(vcollection, getinstance, new_arg, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(vcollection, map, call_fun, ZEND_ACC_PUBLIC)
	ZEND_ME(vcollection, collapse, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(vcollection, avg, avg_arg, ZEND_ACC_PUBLIC)
	ZEND_ME(vcollection, has, has_arg, ZEND_ACC_PUBLIC)
	ZEND_ME(vcollection, mx, max_arg, ZEND_ACC_PUBLIC)
	ZEND_ME(vcollection, mi, min_arg, ZEND_ACC_PUBLIC)
	ZEND_ME(vcollection, toJson, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(vcollection, toArray, NULL, ZEND_ACC_PUBLIC)
	ZEND_ME(vcollection, take, take_arg, ZEND_ACC_PUBLIC)
	ZEND_ME(vcollection, pluck, pluck_arg, ZEND_ACC_PUBLIC)
	ZEND_ME(vcollection, where, where_arg, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


PHP_MINIT_FUNCTION(vcollection)
{
	zend_class_entry ce;

	INIT_NS_CLASS_ENTRY(ce, "Vikin", "Vcollection", vcollection_functions);
	vcollection_ce = zend_register_internal_class(&ce TSRMLS_CC);

	zend_declare_property_null(vcollection_ce, "instance", sizeof("instance")-1, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC);
	zend_declare_property_null(vcollection_ce, "items", sizeof("items")-1, ZEND_ACC_PUBLIC);

	return SUCCESS;
}

zend_module_entry vcollection_module_entry = {
	STANDARD_MODULE_HEADER,
	"vcollection",
	vcollection_functions,
	PHP_MINIT(vcollection),
	PHP_MSHUTDOWN(vcollection),
	PHP_RINIT(vcollection),
	PHP_RSHUTDOWN(vcollection),
	PHP_MINFO(vcollection),
	PHP_VCOLLECTION_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_VCOLLECTION
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(vcollection)
#endif
