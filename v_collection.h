/**********************************************************\
|                                                          |
|                       vcollec                            |
|                                                          |
| Official WebSite: http://www.vikin.cc                    |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * v_collection.h                                         *
 *                                                        *
 *                                                        *
 * LastModified: Dec 15, 2016                             *
 * Author: Jiexin Wang <vikindev@outlook.com>             *
 *                                                        *
\**********************************************************/

#ifndef V_COLLECTION_H
#define V_COLLECTION_H

#define ITEMS "items"
#define ARRAYCOLUMN "array_column"
#define ARRAYSUM "array_sum"
#define JSONEN "json_encode"

extern zend_class_entry *vcollect_application_ce;

VCOLLECT_STARTUP_FUNCTION(application);

#endif
