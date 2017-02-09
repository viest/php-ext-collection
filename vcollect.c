/**********************************************************\
|                                                          |
|                       vcollec                            |
|                                                          |
| Official WebSite: http://www.vikin.cc                    |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * vcollect.c                                             *
 *                                                        *
 *                                                        *
 * LastModified: Dec 15, 2016                             *
 * Author: Wang Jiexin <vikindev@outlook.com>             *
 *                                                        *
\**********************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "zend_API.h"
#include "zend_interfaces.h"
#include "ext/standard/info.h"
#include "php_vcollect.h"
#include "php_vcollection.h"
#include "vcollection_common.h"
#include "ext/standard/php_var.h"

extern zend_class_entry *vcollection_ce;

static int le_vcollect;

PHP_FUNCTION(vcollect)
{
	zval *var_array;
	zval class_name, function_name;
	zend_class_entry *vcoll_ce;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &var_array) == FAILURE) {
		RETURN_NULL();
	}

	ZVAL_STRING(&class_name, CLASS_NAME);
	ZVAL_STRING(&function_name, "getInstance");

	vcoll_ce = zend_fetch_class(zval_get_string(&class_name), ZEND_FETCH_CLASS_AUTO TSRMLS_CC);
	object_init_ex(return_value,vcoll_ce);
	zend_call_method_with_1_params(return_value, vcoll_ce, NULL,"getinstance", return_value, var_array);
}

PHP_FUNCTION(av)
{
	zval *key_data, *val_data, *value, *orig_var, *var_name, *depth_value;
	zval explode_depth_retval, explode_retval, exists_retval;
	zend_long count;
	zend_ulong long_key, depth_long_key;
	zend_array *symbol_table;
    zend_string *str_key, *depth_str_key;

	#ifdef FAST_ZPP
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "aa", &key_data, &val_data) == FAILURE) {
			return;
		}
	#else
		ZEND_PARSE_PARAMETERS_START(2, 2)
			Z_PARAM_ARRAY(&key_data)
			Z_PARAM_ARRAY(&val_data)
		ZEND_PARSE_PARAMETERS_END();
	#endif

	symbol_table = zend_rebuild_symbol_table();

	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(key_data), long_key, str_key, value) {

		v_explode(Z_STR_P(value), &explode_retval);
		HashTable *explode_htbl = Z_ARRVAL(explode_retval);
		HashTable *explode_retval_htbl = Z_ARRVAL_P(&explode_retval);
  		var_name = &explode_retval_htbl->arData[zend_hash_num_elements(explode_retval_htbl)-1].val;

		if (!str_key && zend_hash_num_elements(explode_htbl) == 1) {
			v_key_exists(value, val_data, &exists_retval);
			if(Z_TYPE(exists_retval) == IS_TRUE) {
				HashTable *val_data_htbl = Z_ARRVAL_P(val_data);
				int num = 0;
				while(1) {
					if(val_data_htbl->arData[num].key != NULL) {
						zval strcmp_retval;
						v_strcmp(val_data_htbl->arData[num].key, Z_STR_P(var_name), &strcmp_retval);
						if(zval_get_long(&strcmp_retval) == 0) {
							orig_var = zend_hash_find(symbol_table, Z_STR_P(var_name));
							if(orig_var){
								if (Z_TYPE_P(orig_var) == IS_INDIRECT) {
									orig_var = Z_INDIRECT_P(orig_var);
									if (Z_TYPE_P(orig_var) == IS_UNDEF) {
										ZVAL_COPY_VALUE(orig_var, &val_data_htbl->arData[num].val);
									} else {
										ZVAL_COPY_VALUE(orig_var, &val_data_htbl->arData[num].val);
									}
								}
							}
							break;
						}
					}
					if(zend_hash_num_elements(val_data_htbl) == num) break;
					num++;
				}
			}
		} else if (str_key && zend_hash_num_elements(explode_htbl) == 1) {
			v_explode(str_key, &explode_depth_retval);
			HashTable *explode_depth_htbl = Z_ARRVAL(explode_depth_retval);
			zval temp_value;
			ZEND_HASH_FOREACH_KEY_VAL(explode_depth_htbl, depth_long_key, depth_str_key, depth_value) {
				int num = 0;
				zval strcmp_retval;
				if (depth_long_key < 1) {
					while (1) {
						if(!Z_ARRVAL_P(val_data)->arData[num].key) {
							ZVAL_NULL(&temp_value);
							break;
						}
						v_strcmp(Z_ARRVAL_P(val_data)->arData[num].key, Z_STR_P(depth_value), &strcmp_retval);
						if (zval_get_long(&strcmp_retval) == 0) {
							ZVAL_COPY(&temp_value, &Z_ARRVAL_P(val_data)->arData[num].val);
							break;
						}
						if(zend_hash_num_elements(Z_ARRVAL_P(val_data)) == num) break;
						num++;
					}
					continue;
				}
				if(Z_TYPE(temp_value) == IS_NULL) break;
				v_strcmp(Z_ARRVAL(temp_value)->arData[num].key, Z_STR_P(depth_value), &strcmp_retval);
				if (zval_get_long(&strcmp_retval) == 0) {
					ZVAL_COPY(&temp_value, &Z_ARRVAL(temp_value)->arData[num].val);
				}
				num++;
			} ZEND_HASH_FOREACH_END();
			orig_var = zend_hash_find(symbol_table, Z_STR_P(var_name));
			if(orig_var){
				if (Z_TYPE_P(orig_var) == IS_INDIRECT) {
					orig_var = Z_INDIRECT_P(orig_var);
					if (Z_TYPE_P(orig_var) == IS_UNDEF) {
						ZVAL_COPY_VALUE(orig_var, &temp_value);
					} else {
						ZVAL_COPY_VALUE(orig_var, &temp_value);
					}
				}
			}
		} else if (str_key && zend_hash_num_elements(explode_htbl) > 1) {
			php_error_docref(NULL, E_ERROR, "Variable names defined error!");
		}
	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor(key_data);
	zval_ptr_dtor(val_data);
	zval_ptr_dtor(value);
	zval_ptr_dtor(orig_var);
	zval_ptr_dtor(var_name);
	zval_ptr_dtor(depth_value);
	zval_ptr_dtor(&explode_depth_retval);
	zval_ptr_dtor(&explode_retval);
	zval_ptr_dtor(&exists_retval);
}

PHP_MINIT_FUNCTION(vcollect)
{
	ZEND_MODULE_STARTUP_N(vcollection) (INIT_FUNC_ARGS_PASSTHRU);
	return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(vcollect)
{
	return SUCCESS;
}

PHP_RINIT_FUNCTION(vcollect)
{
#if defined(COMPILE_DL_VCOLLECT) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(vcollect)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(vcollect)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "vcollect support", "enabled");

	#if defined(PHP_VCOLLECTION_VERSION) && defined(PHP_VCOLLECTION_AUTHOR)
	php_info_print_table_row(2, "Vcollect Version", PHP_VCOLLECTION_VERSION);
	php_info_print_table_row(2, "Author", PHP_VCOLLECTION_AUTHOR);
	#endif

	php_info_print_table_end();
}

const zend_function_entry vcollect_functions[] = {
	PHP_FE(vcollect,	NULL)
	PHP_FE(av,	NULL)
	PHP_FE_END
};

zend_module_entry vcollect_module_entry = {
	STANDARD_MODULE_HEADER,
	"vcollect",
	vcollect_functions,
	PHP_MINIT(vcollect),
	PHP_MSHUTDOWN(vcollect),
	PHP_RINIT(vcollect),
	PHP_RSHUTDOWN(vcollect),
	PHP_MINFO(vcollect),
	PHP_VCOLLECT_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_VCOLLECT
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(vcollect)
#endif