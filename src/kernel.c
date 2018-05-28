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

#include "include.h"

zend_class_entry *vtiful_collection_ce;

/* {{{ ARG_INFO
 */
ZEND_BEGIN_ARG_INFO_EX(collection_init_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, collection)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_map_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ collection_methods
*/
zend_function_entry collection_methods[] = {
        PHP_ME(vtiful_collection, __construct,   NULL,                    ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
        PHP_ME(vtiful_collection, __clone,       NULL,                    ZEND_ACC_PRIVATE|ZEND_ACC_CLONE)
        PHP_ME(vtiful_collection, init,          collection_init_arginfo, ZEND_ACC_PUBLIC |ZEND_ACC_STATIC)
        PHP_ME(vtiful_collection, map,           collection_map_arginfo,  ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, count,         NULL,                    ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, toArray,       NULL,                    ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */

/** {{{ COLLECTION_STARTUP_FUNCTION
*/
COLLECTION_STARTUP_FUNCTION(kernel)
{
    zend_class_entry ce;

    INIT_NS_CLASS_ENTRY(ce, "Vtiful\\Kernel", "Collection", collection_methods);

    vtiful_collection_ce = zend_register_internal_class(&ce);

    return SUCCESS;
}
/* }}} */
