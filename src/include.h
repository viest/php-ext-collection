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

#ifndef PHP_EXT_COLLECTION_INCLUDE_H
#define PHP_EXT_COLLECTION_INCLUDE_H

#include <php.h>

#include "ext/standard/php_var.h"

#include "zend_types.h"
#include "zend_exceptions.h"
#include "zend.h"
#include "zend_API.h"
#include "php.h"

#include "../php_collection.h"

// Class
extern zend_class_entry *vtiful_collection_ce;
extern zend_class_entry *vtiful_collection_exception_ce;

// Startup Module
COLLECTION_STARTUP_FUNCTION(exception);
COLLECTION_STARTUP_FUNCTION(kernel);

// Kernel Class Method
PHP_METHOD(vtiful_collection, __construct);
PHP_METHOD(vtiful_collection, __clone);
PHP_METHOD(vtiful_collection, init);
PHP_METHOD(vtiful_collection, map);
PHP_METHOD(vtiful_collection, all);
PHP_METHOD(vtiful_collection, avg);
PHP_METHOD(vtiful_collection, chunk);
PHP_METHOD(vtiful_collection, collapse);
PHP_METHOD(vtiful_collection, count);
PHP_METHOD(vtiful_collection, toArray);
PHP_METHOD(vtiful_collection, combine);
PHP_METHOD(vtiful_collection, concat);
PHP_METHOD(vtiful_collection, contains);
PHP_METHOD(vtiful_collection, diff);
PHP_METHOD(vtiful_collection, diffAssoc);
PHP_METHOD(vtiful_collection, every);
PHP_METHOD(vtiful_collection, except);
PHP_METHOD(vtiful_collection, filter);
PHP_METHOD(vtiful_collection, first);
PHP_METHOD(vtiful_collection, firstWhere);
PHP_METHOD(vtiful_collection, flatMap);
PHP_METHOD(vtiful_collection, flatten);
PHP_METHOD(vtiful_collection, flip);
PHP_METHOD(vtiful_collection, forget);
PHP_METHOD(vtiful_collection, forPage);
PHP_METHOD(vtiful_collection, get);
PHP_METHOD(vtiful_collection, groupBy);
PHP_METHOD(vtiful_collection, has);
PHP_METHOD(vtiful_collection, implode);
PHP_METHOD(vtiful_collection, intersect);
PHP_METHOD(vtiful_collection, intersectByKeys);
PHP_METHOD(vtiful_collection, isEmpty);
PHP_METHOD(vtiful_collection, isNotEmpty);
PHP_METHOD(vtiful_collection, keyBy);
PHP_METHOD(vtiful_collection, keys);

// PHP Compatible
#ifndef GC_ADDREF
#define GC_ADDREF(p) ++(&(p->gc))->refcount
#endif

#define GC_ZVAL_ADDREF(zval_p)                                      \
    do {                                                            \
        zend_refcounted *gc = Z_COUNTED_P(zval_p);                  \
        uint32_t t          = Z_TYPE_INFO_P(zval_p);                \
        if((t & (IS_TYPE_REFCOUNTED << Z_TYPE_FLAGS_SHIFT)) != 0) { \
            GC_REFCOUNT(gc)++;                                      \
        }                                                           \
    } while (0)

#define VC_ZVAL_DTOR(zval) zval_ptr_dtor(&zval);

// Define
#define CURRENT_COLLECTION \
        Z_OBJ_P(getThis())->properties

#define CURRENT_COLLECTION_COUNT \
        CURRENT_COLLECTION->nNumOfElements

#define ZVAL_ARRAY_COUNT(zval_p) \
        Z_ARR_P(zval_p)->nNumOfElements

#define COLLECTION_INIT(zval_p) \
        do {                    \
            array_init(zval_p); \
        } while (0)

#define COLLECTION_ADD_INDEX_ZVAL(collection_zval_p, zval_p) \
        add_next_index_zval(collection_zval_p, zval_p);

#define COLLECTION_STRING_DELETE(collection_array_p, zs_key) \
        zend_hash_del(collection_array_p, zs_key);

#define COLLECTION_INDEX_DELETE(collection_array_p, ulong_key) \
        zend_hash_index_del(collection_array_p, ulong_key);

#define COLLECTION_INIT_IN_CURRENT(zval_p) \
        COLLECTION_INIT(zval_p);           \
        zend_hash_copy(Z_ARR_P(zval_p), CURRENT_COLLECTION, zval_add_ref);

#define COLLECTION_UPDATE(array_p, bucket, new_zval_p) \
        ZVAL_COPY_VALUE(&(Z_ARR_P(array_p)->arData[bucket->h].val), new_zval_p)

#define NEW_ZVAL_OBJ(zval_p)                              \
        do {                                              \
            object_init_ex(zval_p, vtiful_collection_ce); \
        } while (0)

#define UPDATE_OBJ_COLLECTION(zo_p, z_collection_p)            \
        do {                                                   \
            if (Z_TYPE_P(z_collection_p) == IS_ARRAY) {        \
                zend_object *obj = Z_OBJ_P(zo_p);              \
                GC_ZVAL_ADDREF(z_collection_p);                \
                obj->properties  = Z_ARRVAL_P(z_collection_p); \
            }                                                  \
        } while (0)

#define NEW_COLLECTION_OBJ(ret_val, collection)     \
        NEW_ZVAL_OBJ(ret_val);                      \
        UPDATE_OBJ_COLLECTION(ret_val, collection);

#define INIT_FCALL(arg_num, ret_val_p) \
        zval args[arg_num];            \
        fci.param_count = arg_num;     \
        fci.retval      = ret_val_p;   \
        fci.params      = args;

#define FCALL_DTOR(arg_num)         \
        int i = 0;                  \
        for (i; i < arg_num; i++) { \
            VC_ZVAL_DTOR(args[i])   \
        }

#define FCALL_TWO_ARGS(bucket)                   \
        ZVAL_COPY_VALUE(&args[0], &bucket->val); \
        if (bucket->key) {                       \
            ZVAL_STR(&args[1], bucket->key);     \
        } else {                                 \
            ZVAL_LONG(&args[1], bucket->h);      \
        }                                        \
        zend_call_function(&fci, &fci_cache);

#define FCALL_ONE_ARGS(bucket) \
        ZVAL_COPY_VALUE(&args[0], &bucket->val); \
        zend_call_function(&fci, &fci_cache);

#define ARRAY_INDEX_FIND(zval_p, index, zval_result_p)                      \
        do {                                                                \
            ZVAL_COPY(zval_result_p, &(Z_ARR_P(zval_p)->arData[index].val));\
        } while (0)

#define ARRAY_STR_FIND(zval_p, zs_key_p, zval_result_p)                \
        do {                                                           \
            zval_result_p = zend_hash_find(Z_ARR_P(zval_p), zs_key_p); \
        } while (0)

#define COLLECTION_INDEX_FIND(collection, index, zval_result_p)   \
        do {                                                      \
            if (index < CURRENT_COLLECTION->nNumOfElements) {     \
                zval_result_p = &(collection->arData[index].val); \
            } else {                                              \
                ZVAL_NULL(zval_result_p);                         \
            }                                                     \
        } while (0)

#define COLLECTION_STR_FIND(collection, zs_key_p, zval_result_p)  \
        do {                                                      \
            zval_result_p = zend_hash_find(collection, zs_key_p); \
        } while (0)

#define ZVAL_ARRAY_INSERT_BUCKET_KEY_ZVAL_VAL(zval_p, bucket, zval_val_p)                                    \
        do {                                                                                                 \
            zval value;                                                                                      \
            if (Z_TYPE(bucket->val) == IS_STRING) {                                                          \
                ARRAY_INDEX_FIND(zval_val_p, bucket->h, &value);                                             \
                zend_hash_str_update(Z_ARR_P(zval_p), Z_STRVAL(bucket->val), Z_STRLEN(bucket->val), &value); \
            }                                                                                                \
            if (Z_TYPE(bucket->val) == IS_LONG) {                                                            \
                ARRAY_INDEX_FIND(zval_val_p, bucket->h, &value);                                             \
                zend_hash_index_update(Z_ARR_P(zval_p), Z_LVAL(bucket->val), &value);                        \
            }                                                                                                \
        } while(0)

#define ZVAL_IS_NOT_ARRAY_SO_CONTINUE(zval_p) \
        if (Z_TYPE_P(value) != IS_ARRAY) continue;

#define RETURN_THIS \
        ZVAL_COPY(return_value, getThis());

#endif
