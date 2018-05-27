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
#include "depend/src/php/classes/php_collection_ce.h"

static zend_object_handlers collection_handlers;

zend_class_entry *vtiful_collection_ce;

/* {{{ ARG_INFO
 */
ZEND_BEGIN_ARG_INFO_EX(collection_init_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, collection)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ vtiful_object_alloc
 */
static zend_always_inline void *object_alloc(size_t obj_size, zend_class_entry *ce) {
    void *obj = emalloc(obj_size + zend_object_properties_size(ce));
    memset(obj, 0, obj_size);
    return obj;
}
/* }}} */

/* {{{ collection_objects_new
 */
PHP_COLLECTION_API zend_object *collection_objects_new(zend_class_entry *ce)
{
    zend_object *intern = object_alloc(sizeof(zend_object), ce);

    zend_object_std_init(intern, ce);
    object_properties_init(intern, ce);

    intern->handlers = &collection_handlers;

    return intern;
}
/* }}} */

/** {{{ collection_methods
*/
zend_function_entry collection_methods[] = {
        PHP_ME(collection, __construct,   NULL,                    ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
        PHP_ME(collection, init,          collection_init_arginfo, ZEND_ACC_PUBLIC)
        PHP_ME(collection, clear,         NULL,                    ZEND_ACC_PUBLIC)
        PHP_ME(collection, copy,          NULL,                    ZEND_ACC_PUBLIC)
        PHP_ME(collection, count,         NULL,                    ZEND_ACC_PUBLIC)
        PHP_ME(collection, isEmpty,       NULL,                    ZEND_ACC_PUBLIC)
        PHP_ME(collection, jsonSerialize, NULL,                    ZEND_ACC_PUBLIC)
        PHP_ME(collection, toArray,       NULL,                    ZEND_ACC_PUBLIC)
        PHP_FE_END
};
/* }}} */

/** {{{ COLLECTION_STARTUP_FUNCTION
*/
COLLECTION_STARTUP_FUNCTION(kernel)
{
    zend_class_entry ce;

    INIT_NS_CLASS_ENTRY(ce, "Vtiful\\Kernel", "Collection", collection_methods);

    ce.create_object     = collection_objects_new;
    vtiful_collection_ce = zend_register_internal_class(&ce);

    zend_class_implements(vtiful_collection_ce, 1, collection_ce);

    memcpy(&collection_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

    return SUCCESS;
}
/* }}} */
