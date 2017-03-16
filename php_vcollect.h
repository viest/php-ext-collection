/**********************************************************\
|                                                          |
|                       vcollec                            |
|                                                          |
| Official WebSite: http://www.vikin.cc                    |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * php_vcollect.h                                         *
 *                                                        *
 *                                                        *
 * LastModified: Dec 15, 2016                             *
 * Author: Wang Jiexin <vikindev@outlook.com>             *
 *                                                        *
\**********************************************************/

#ifndef PHP_VCOLLECT_H
#define PHP_VCOLLECT_H

extern zend_module_entry vcollect_module_entry;
#define phpext_vcollect_ptr &vcollect_module_entry

#define PHP_APPLICATION_VERSION "1.0.0"
#define PHP_APPLICATION_AUTHOR "Wang Jiexin"
#define CLASS_NAME "\\Vikin\\Vcollection"

#ifdef PHP_WIN32
#	define PHP_VCOLLECT_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_VCOLLECT_API __attribute__ ((visibility("default")))
#else
#	define PHP_VCOLLECT_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define VCOLLECT_STARTUP_MODULE(module) ZEND_MODULE_STARTUP_N(vcollect_##module)(INIT_FUNC_ARGS_PASSTHRU)
#define VCOLLECT_STARTUP_FUNCTION(module) ZEND_MINIT_FUNCTION(vcollect_##module)
#define VCOLLECT_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(vcollect, v)

PHP_MINIT_FUNCTION(vcollect);
PHP_MSHUTDOWN_FUNCTION(vcollect);
PHP_RINIT_FUNCTION(vcollect);
PHP_RSHUTDOWN_FUNCTION(vcollect);
PHP_MINFO_FUNCTION(vcollect);

#if defined(ZTS) && defined(COMPILE_DL_VCOLLECT)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif
