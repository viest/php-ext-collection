/**********************************************************\
|                                                          |
|                       vcollec                            |
|                                                          |
| Official WebSite: http://www.vikin.cc                    |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * php_vcollection.h                                      *
 *                                                        *
 *                                                        *
 * LastModified: Dec 15, 2016                             *
 * Author: Wang Jiexin <vikindev@outlook.com>             *
 *                                                        *
\**********************************************************/

#ifndef PHP_VCOLLECTION_H
#define PHP_VCOLLECTION_H

extern zend_module_entry vcollection_module_entry;
#define phpext_vcollection_ptr &vcollection_module_entry

#define PHP_VCOLLECTION_VERSION "1.0.0"
#define PHP_VCOLLECTION_AUTHOR "Wang Jiexin"

#ifdef PHP_WIN32
#	define PHP_VCOLLECTION_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_VCOLLECTION_API __attribute__ ((visibility("default")))
#else
#	define PHP_VCOLLECTION_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define CLASS_NAME "\\Vikin\\Vcollection"

extern zend_class_entry *vcollection_ce;
PHP_METHOD(vcollection_ce, __construct);
PHP_METHOD(vcollection_ce, map);
PHP_METHOD(vcollection_ce, collapse);
PHP_METHOD(vcollection_ce, avg);
PHP_METHOD(vcollection_ce, has);
PHP_METHOD(vcollection_ce, mx);
PHP_METHOD(vcollection_ce, mi);
PHP_METHOD(vcollection_ce, toArray);
PHP_METHOD(vcollection_ce, toJson);
PHP_METHOD(vcollection_ce, take);
PHP_METHOD(vcollection_ce, pluck);
PHP_METHOD(vcollection_ce, where);
PHP_MINIT_FUNCTION(vcollection);

#define VCOLLECTION_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(vcollection, v)

#if defined(ZTS) && defined(COMPILE_DL_VCOLLECTION)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif