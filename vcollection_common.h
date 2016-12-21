/**********************************************************\
|                                                          |
|                       vcollec                            |
|                                                          |
| Official WebSite: http://www.vikin.cc                    |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * vcollection_common.h                                   *
 *                                                        *
 *                                                        *
 * LastModified: Dec 18, 2016                             *
 * Author: Wang Jiexin <vikindev@outlook.com>             *
 *                                                        *
\**********************************************************/

#ifndef VCOLLECTION_COMMON_H
#define VCOLLECTION_COMMON_H

#define ARRAY_COLUMN(arg) ZVAL_STRING(arg, "array_column")
#define EXPLODE(arg) ZVAL_STRING(arg, "explode")
#define KEY_EXISTS(arg) ZVAL_STRING(arg, "array_key_exists")
#define STRCMP(arg)  ZVAL_STRING(arg, "strcmp")
#define INTVAL(arg)  ZVAL_STRING(arg, "intval")

void __get_array_max (HashTable *htbl, double *retval);
void __get_array_min (HashTable *htbl, double *retval);
void __get_collect_pluck (zval *array, zend_string *args ,zval *retval);
void __key_exists(zval *key, zval *array, zval *retval);
void __explode(zend_string *str_arg, zval *explode_retval);
void __column(zval *array, zval *str_arg, zval *column_retval);
void __strcmp(zend_string *op1, zend_string *op2, zval *retval);
void __intval(zend_string *op1, zval *retval);

#define v_array_max(htbl, retval) __get_array_max(htbl, retval)
#define v_array_mix(htbl, retval) __get_array_min(htbl, retval)
#define v_collect_pluck(array, args, retval) __get_collect_pluck(array, args, retval)
#define v_key_exists(key, array, retval) __key_exists(key, array, retval)
#define v_explode(arg, retval) __explode(arg, retval)
#define v_column(array, arg, retval) __column(array, arg, retval)
#define v_strcmp(op1, op2, retval) __strcmp(op1, op2, retval)
#define v_intval(op1, retval) __intval(op1, retval)

#endif
