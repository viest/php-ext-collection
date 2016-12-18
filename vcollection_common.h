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

void __get_array_max (HashTable *htbl, double *retval);
void __get_array_min (HashTable *htbl, double *retval);
void __get_collect_pluck (zval *array, zend_string *args ,zval *retval);

#define v_array_max(htbl, retval) __get_array_max(htbl, retval)
#define v_array_mix(htbl, retval) __get_array_min(htbl, retval)
#define v_collect_pluck(array, args, retval) __get_collect_pluck(array, args, retval)

#endif
