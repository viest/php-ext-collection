/*
  +----------------------------------------------------------------------+
  | Collection Extension                                                 |
  +----------------------------------------------------------------------+
  | Copyright (c) 2016-2018 The Viest                                    |
  +----------------------------------------------------------------------+
  | http://www.viest.me                                                  |
  +----------------------------------------------------------------------+
  | Author: viest <dev@service.viest.me>                                 |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_collection.h"

#include "src/include.h"

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(collection)
{
	COLLECTION_STARTUP_MODULE(kernel);
	COLLECTION_STARTUP_MODULE(exception);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(collection)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(collection)
{
#if defined(COMPILE_DL_COLLECTION) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(collection)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(collection)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "collection support", "enabled");
	php_info_print_table_end();

#if defined(PHP_COLLECTION_VERSION)
	php_info_print_table_row(2, "Collection Version", PHP_COLLECTION_VERSION);
#endif

	php_info_print_table_end();
}
/* }}} */

/* {{{ collection_functions[]
 */
const zend_function_entry collection_functions[] = {
		PHP_FE_END	/* Must be the last line in collection_functions[] */
};
/* }}} */

/* {{{ collection_deps[]
 */
static const zend_module_dep collection_deps[] = { /* {{{ */
        ZEND_MOD_REQUIRED("ds")
        ZEND_MOD_END
};
/* }}} */

/* {{{ collection_module_entry
 */
zend_module_entry collection_module_entry = {
        STANDARD_MODULE_HEADER_EX,
        NULL,
        collection_deps,
		"collection",
		collection_functions,
		PHP_MINIT(collection),
		PHP_MSHUTDOWN(collection),
		PHP_RINIT(collection),
		PHP_RSHUTDOWN(collection),
		PHP_MINFO(collection),
		PHP_COLLECTION_VERSION,
		STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_COLLECTION
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(collection)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
