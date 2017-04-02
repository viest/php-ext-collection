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

#ifndef VCOLLECT_APPLICATION_H
#define VCOLLECT_APPLICATION_H

#define ITEMS "items"
#define ARRAYCOLUMN "array_column"
#define ARRAYSUM "array_sum"

extern zend_class_entry *vcollect_application_ce;

VCOLLECT_STARTUP_FUNCTION(application);

#endif
