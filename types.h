/**
 * @file types.h
 * @author Teaching team of EDAT.
 * @date April 2023.
 * @brief ADTs Boolean, Status and pointer to comparison/print functions.
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdio.h>

/**
 * @brief ADT Boolean
 */
typedef enum {
    FALSE=0, /*!< False value */
    TRUE=1  /*!< True value  */
} Bool;

/**
 * @brief ADT Status
 */
typedef enum {
    ERROR=0, /*!< To codify an ERROR output */
    OK=1     /*!< OK output */
} Status;

/**
 * P_ele_print type definition: pointer to a function that prints an
 * element to an output stream. It is assumed that this function returns: (1)
 * the number of characters printed upon success; or (2) a negative number in
 * case of error.
 */
typedef int (*P_ele_print)(FILE *, const void *);

/**
 * P_ele_cmp type definition: pointer to a function that compares two
 * elements. It returns an integer less than, equal to, or greater
 * than zero if e1 is found, respectively, to be less than, to match, or to be
 * greater than e2.
 */
typedef int (*P_ele_cmp)(const void *, const void *);

#endif /* TYPES_H_ */
