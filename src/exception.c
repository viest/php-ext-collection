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

zend_class_entry *vtiful_collection_exception_ce;

/** {{{ exception_methods
*/
zend_function_entry exception_methods[] = {
        PHP_FE_END
};
/* }}} */

/** {{{ COLLECTION_STARTUP_FUNCTION
*/
COLLECTION_STARTUP_FUNCTION(exception) {
    zend_class_entry ce;

    INIT_NS_CLASS_ENTRY(ce, "Vtiful\\Kernel\\Collection", "Exception", exception_methods);

    vtiful_collection_exception_ce = zend_register_internal_class_ex(&ce, zend_ce_exception);

    return SUCCESS;
}
/* }}} */
