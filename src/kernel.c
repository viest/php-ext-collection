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

ZEND_BEGIN_ARG_INFO_EX(collection_avg_arginfo, 0, 0, 0)
                ZEND_ARG_INFO(0, column)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_chunk_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_combine_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_concat_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_contains_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, key)
                ZEND_ARG_INFO(0, val)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_diff_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_every_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_except_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, excluded_keys)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_filter_arginfo, 0, 0, 0)
                ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_first_arginfo, 0, 0, 0)
                ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_first_where_arginfo, 0, 0, 2)
                ZEND_ARG_INFO(0, column)
                ZEND_ARG_INFO(0, val)
                ZEND_ARG_INFO(0, symbol)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_flat_map_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_flatten_arginfo, 0, 0, 0)
                ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_forget_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_for_page_arginfo, 0, 0, 2)
                ZEND_ARG_INFO(0, page)
                ZEND_ARG_INFO(0, number)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_get_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, key)
                ZEND_ARG_INFO(0, default_val)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_group_by_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_has_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_implode_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, key)
                ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_intersect_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_intersect_keys_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, array)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(collection_key_by_arginfo, 0, 0, 1)
                ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()
/* }}} */

/** {{{ collection_methods
*/
zend_function_entry collection_methods[] = {
        PHP_ME(vtiful_collection, __construct,     NULL,                              ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
        PHP_ME(vtiful_collection, __clone,         NULL,                              ZEND_ACC_PRIVATE|ZEND_ACC_FINAL)
        PHP_ME(vtiful_collection, init,            collection_init_arginfo,           ZEND_ACC_PUBLIC |ZEND_ACC_STATIC)
        PHP_ME(vtiful_collection, map,             collection_map_arginfo,            ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, all,             NULL,                              ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, avg,             collection_avg_arginfo,            ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, chunk,           collection_chunk_arginfo,          ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, collapse,        NULL,                              ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, count,           NULL,                              ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, toArray,         NULL,                              ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, combine,         collection_combine_arginfo,        ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, concat,          collection_concat_arginfo,         ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, contains,        collection_contains_arginfo,       ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, diff,            collection_diff_arginfo,           ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, diffAssoc,       collection_diff_arginfo,           ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, every,           collection_every_arginfo,          ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, except,          collection_except_arginfo,         ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, filter,          collection_filter_arginfo,         ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, first,           collection_first_arginfo,          ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, firstWhere,      collection_first_where_arginfo,    ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, flatMap,         collection_flat_map_arginfo,       ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, flatten,         collection_flatten_arginfo,        ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, flip,            NULL,                              ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, forget,          collection_forget_arginfo,         ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, forPage,         collection_for_page_arginfo,       ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, get,             collection_get_arginfo,            ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, groupBy,         collection_group_by_arginfo,       ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, has,             collection_has_arginfo,            ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, implode,         collection_implode_arginfo,        ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, intersect,       collection_intersect_arginfo,      ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, intersectByKeys, collection_intersect_keys_arginfo, ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, isEmpty,         NULL,                              ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, isNotEmpty,      NULL,                              ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, keyBy,           collection_key_by_arginfo,         ZEND_ACC_PUBLIC)
        PHP_ME(vtiful_collection, keys,            NULL,                              ZEND_ACC_PUBLIC)
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
