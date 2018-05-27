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

#ifndef PHP_COLLECTION_H
#define PHP_COLLECTION_H

extern zend_module_entry collection_module_entry;
#define phpext_collection_ptr &collection_module_entry

#define PHP_COLLECTION_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_COLLECTION_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_COLLECTION_API __attribute__ ((visibility("default")))
#else
#	define PHP_COLLECTION_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define COLLECTION_STARTUP_MODULE(module)   ZEND_MODULE_STARTUP_N(vtiful_collection_##module)(INIT_FUNC_ARGS_PASSTHRU)
#define COLLECTION_STARTUP_FUNCTION(module) ZEND_MINIT_FUNCTION(vtiful_collection_##module)

#if defined(ZTS) && defined(COMPILE_DL_COLLECTION)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

PHP_MINIT_FUNCTION(collection);
PHP_MSHUTDOWN_FUNCTION(collection);
PHP_RINIT_FUNCTION(collection);
PHP_RSHUTDOWN_FUNCTION(collection);
PHP_MINFO_FUNCTION(collection);

#endif


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
