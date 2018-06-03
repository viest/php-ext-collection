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
#include "common.h"

/** {{{ \Vtiful\Kernel\Collection::__construct()
 */
PHP_METHOD(vtiful_collection, __construct)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::__clone()
 */
PHP_METHOD(vtiful_collection, __clone)
{

}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::init([array $collection])
 */
PHP_METHOD(vtiful_collection, init)
{
    zval *collection = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
            Z_PARAM_OPTIONAL
            Z_PARAM_ARRAY(collection)
    ZEND_PARSE_PARAMETERS_END();

    NEW_COLLECTION_OBJ(return_value, collection);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::map(closures $callback)
 */
PHP_METHOD(vtiful_collection, map)
{
    zval fcall_result;
    zend_fcall_info       fci       = empty_fcall_info;
    zend_fcall_info_cache fci_cache = empty_fcall_info_cache;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_FUNC(fci, fci_cache)
    ZEND_PARSE_PARAMETERS_END();

    INIT_FCALL(2, &fcall_result)

    ZEND_HASH_FOREACH_BUCKET(CURRENT_COLLECTION, Bucket* bucket)
            FCALL_TWO_ARGS(bucket)
    ZEND_HASH_FOREACH_END();
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::all()
 */
PHP_METHOD(vtiful_collection, all)
{
    ZVAL_ARR(return_value, CURRENT_COLLECTION);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::avg([string $key])
 */
PHP_METHOD(vtiful_collection, avg)
{
    zend_string *column = NULL;

    ZEND_PARSE_PARAMETERS_START(0, 1)
            Z_PARAM_OPTIONAL
            Z_PARAM_STR(column)
    ZEND_PARSE_PARAMETERS_END();

    double sum = 0;

    if (column == NULL) {
        sum = average_no_column(CURRENT_COLLECTION);
    } else {
        sum = average_column(CURRENT_COLLECTION, column);
    }

    ZVAL_DOUBLE(return_value, (sum/zend_hash_num_elements(CURRENT_COLLECTION)))
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::chunk(int $length)
 */
PHP_METHOD(vtiful_collection, chunk)
{
    zend_long length;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_LONG(length)
    ZEND_PARSE_PARAMETERS_END();

    if (length < 1) {
        zend_throw_exception(vtiful_collection_exception_ce, "Parameter cannot be less than 1", 10);
    }

    NEW_ZVAL_OBJ(return_value);

    collection_chunk(CURRENT_COLLECTION, length, return_value);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::collapse()
 */
PHP_METHOD(vtiful_collection, collapse)
{
    zval result;

    COLLECTION_INIT(&result);

    collection_collapse(CURRENT_COLLECTION, &result);

    NEW_COLLECTION_OBJ(return_value, &result);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::count()
 */
PHP_METHOD(vtiful_collection, count)
{
    ZVAL_LONG(return_value, CURRENT_COLLECTION_COUNT);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::toArray()
 */
PHP_METHOD(vtiful_collection, toArray)
{
    ZVAL_ARR(return_value, CURRENT_COLLECTION);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::combine(array $arrVal)
 */
PHP_METHOD(vtiful_collection, combine)
{
    zval result, *val = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ARRAY(val)
    ZEND_PARSE_PARAMETERS_END();

    COLLECTION_INIT(&result);

    collection_combine(CURRENT_COLLECTION, val, &result);

    NEW_COLLECTION_OBJ(return_value, &result);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::concat(array $arrVal)
 */
PHP_METHOD(vtiful_collection, concat)
{
    zval result, *val = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ARRAY(val)
    ZEND_PARSE_PARAMETERS_END();

    COLLECTION_INIT(&result);

    collection_concat(CURRENT_COLLECTION, val, &result);

    NEW_COLLECTION_OBJ(return_value, &result);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::contains(string $value[, string $value])
 */
PHP_METHOD(vtiful_collection, contains)
{
    zval *key = NULL, *val = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 2)
            Z_PARAM_ZVAL(key)
            Z_PARAM_OPTIONAL
            Z_PARAM_ZVAL(val)
    ZEND_PARSE_PARAMETERS_END();

    if (val == NULL) {
        VAL_IN_COLLECTION(CURRENT_COLLECTION, key, return_value);
    } else {
        KV_IN_COLLECTION(CURRENT_COLLECTION, key, val, return_value);
    }
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::diff(array $array)
 */
PHP_METHOD(vtiful_collection, diff)
{
    zval result, *val = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ARRAY(val)
    ZEND_PARSE_PARAMETERS_END();

    COLLECTION_INIT(&result);

    collection_diff(CURRENT_COLLECTION, val, &result);

    NEW_COLLECTION_OBJ(return_value, &result);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::diffAssoc(array $array)
 */
PHP_METHOD(vtiful_collection, diffAssoc)
{
    zval result, *val = NULL;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ARRAY(val)
    ZEND_PARSE_PARAMETERS_END();

    COLLECTION_INIT(&result);

    collection_diff_assoc(CURRENT_COLLECTION, val, &result);

    NEW_COLLECTION_OBJ(return_value, &result);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::every(closures $callback)
 */
PHP_METHOD(vtiful_collection, every)
{
    zval fcall_result;
    zend_fcall_info       fci       = empty_fcall_info;
    zend_fcall_info_cache fci_cache = empty_fcall_info_cache;

    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_FUNC(fci, fci_cache)
    ZEND_PARSE_PARAMETERS_END();

    INIT_FCALL(2, &fcall_result)

    ZEND_HASH_FOREACH_BUCKET(CURRENT_COLLECTION, Bucket* bucket)
        FCALL_TWO_ARGS(bucket)

        if (Z_TYPE_INFO(fcall_result) == IS_FALSE) {
            ZVAL_FALSE(return_value);
            break;
        }
    ZEND_HASH_FOREACH_END();

    ZVAL_TRUE(return_value);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::except(array $excludedKeys)
 */
PHP_METHOD(vtiful_collection, except)
{
    zval result, *excluded_keys = NULL;

    ZEND_PARSE_PARAMETERS_START(1,1)
        Z_PARAM_ARRAY(excluded_keys)
    ZEND_PARSE_PARAMETERS_END();

    COLLECTION_INIT(&result);

    collection_except(CURRENT_COLLECTION, excluded_keys, &result);

    NEW_COLLECTION_OBJ(return_value, &result);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::filter(closures $callback)
 */
PHP_METHOD(vtiful_collection, filter)
{
    zval fcall_result, result;
    zend_fcall_info       fci       = empty_fcall_info;
    zend_fcall_info_cache fci_cache = empty_fcall_info_cache;

    ZEND_PARSE_PARAMETERS_START(0, 1)
            Z_PARAM_OPTIONAL
            Z_PARAM_FUNC(fci, fci_cache)
    ZEND_PARSE_PARAMETERS_END();

    COLLECTION_INIT(&result);

    if (ZEND_NUM_ARGS() < 1) {
        ZEND_HASH_FOREACH_BUCKET(CURRENT_COLLECTION, Bucket* bucket)
            ZVAL_COPY(&fcall_result, &bucket->val);
            convert_to_boolean(&fcall_result);
            if (Z_TYPE_INFO(fcall_result) == IS_FALSE) {
                continue;
            }
            add_next_index_zval(&result, &bucket->val);
        ZEND_HASH_FOREACH_END();
    } else {
        INIT_FCALL(2, &fcall_result)
        ZEND_HASH_FOREACH_BUCKET(CURRENT_COLLECTION, Bucket* bucket)
            FCALL_TWO_ARGS(bucket)
            if (Z_TYPE_INFO(fcall_result) == IS_FALSE) {
                continue;
            }
            add_next_index_zval(&result, &bucket->val);
        ZEND_HASH_FOREACH_END();
    }

    NEW_COLLECTION_OBJ(return_value, &result);
}
/* }}} */

/** {{{ \Vtiful\Kernel\Collection::first([closures $callback])
 */
PHP_METHOD(vtiful_collection, first)
{
    zend_fcall_info       fci       = empty_fcall_info;
    zend_fcall_info_cache fci_cache = empty_fcall_info_cache;

    ZEND_PARSE_PARAMETERS_START(0, 1)
            Z_PARAM_OPTIONAL
            Z_PARAM_FUNC(fci, fci_cache)
    ZEND_PARSE_PARAMETERS_END();

    if (ZEND_NUM_ARGS() < 1) {
        ZVAL_COPY(return_value, &(CURRENT_COLLECTION->arData[0].val));
    } else {
        zval fcall_result;

        INIT_FCALL(2, &fcall_result)

        ZEND_HASH_FOREACH_BUCKET(CURRENT_COLLECTION, Bucket* bucket)
            FCALL_TWO_ARGS(bucket)

            if (Z_TYPE_INFO(fcall_result) == IS_TRUE) {
                ZVAL_COPY(return_value, &(bucket->val));
                break;
            }
        ZEND_HASH_FOREACH_END();
    }
}
/* }}} */


/** {{{ \Vtiful\Kernel\Collection::firstWhere([closures $callback])
 */
PHP_METHOD(vtiful_collection, firstWhere)
{
    zval result, *find_res = NULL, *symbol = NULL;
    zend_string  *column   = NULL, *val    = NULL;

    ZEND_PARSE_PARAMETERS_START(2, 3)
        Z_PARAM_STR(column)
        Z_PARAM_STR(val)
        Z_PARAM_OPTIONAL
        Z_PARAM_ZVAL(symbol)
    ZEND_PARSE_PARAMETERS_END();

    COLLECTION_INIT(&result);

    if (ZEND_NUM_ARGS() == 2) {
        zval zval_zstr;

        ZEND_HASH_FOREACH_VAL(CURRENT_COLLECTION,  zval *value)
            find_res = zend_hash_find(Z_ARR_P(value), column);

            if (find_res != NULL) {
                ZVAL_STR(&zval_zstr, val);
                if (zval_equal(find_res, &zval_zstr)) {
                    ZVAL_COPY(&result, value);
                    break;
                }
            }
        ZEND_HASH_FOREACH_END();
    } else if (ZEND_NUM_ARGS() == 3) {
        ZEND_HASH_FOREACH_VAL(CURRENT_COLLECTION, zval *value)
            find_res = zend_hash_find(Z_ARR_P(value), column);

            if (find_res != NULL) {
                if (zval_comparison_operations(val, find_res, symbol)) {
                    ZVAL_COPY(&result, value);
                    break;
                }
            }
        ZEND_HASH_FOREACH_END();
    }

    NEW_COLLECTION_OBJ(return_value, &result);
}
/* }}} */