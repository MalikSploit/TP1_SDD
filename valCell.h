/**
 * @file valCell.h
 * @brief relative to the value of linked list's cells
 */

#ifndef __VALCELL_H__
#define __VALCELL_H__

#include <stdio.h>

/**
 * @struct monom_t 
 * @brief Data structure of monomial (value of linked list's cell)
 * 2 fields :
 * 		- 'coef' : double precision real  
 * 		- 'degree' : integer
 */
typedef struct monom_t
{
     double coef;
     int degree;
} monom_t;


/**
 * @brief Compare the degree of two monomials
 * @param [in] a address of the first monomial
 * @param [in] b address of the second monomial
 * @return <0 if m1.degree<m2.degree; =0 if m1.degree=m2.degree;  >0 if m1.degree>m2.degree
 */
int monom_degree_cmp(const void *a, const void *b);


/**
 * @brief write the information of a monomial to the given output stream
 * @param [in] stream file pointer of an output stream
 * @param [in] monom address of a monomial
 */
void monom_save2file(FILE *stream, struct monom_t *monom);

#endif