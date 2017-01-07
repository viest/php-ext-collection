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

	// zend_call_method_with_1_params(return_value, vcoll_ce, NULL,"getinstance", return_value, var_array);

	// zval_ptr_dtor(var_array);
	// php_printf("%s", "vikin");
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