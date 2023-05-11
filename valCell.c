/**
 * @file valCell.c
 * Implementation file for comparison and display of linked list's cells
 */

#include <stdio.h>
#include "valCell.h"

/**
 * @brief Compare the degree of two monomials
 * @param [in] a address of the first monomial
 * @param [in] b address of the second monomial
 * @return <0 if degree1<degree2; =0 if degree1=degree2;  >0 if degree1>degree2
 */
/* -------------------------------------------------------------------- */
/* monom_degree_cmp           Compare le degré de deux monômes          */
/*                                                                      */
/* En entrée: a, b Deux adresses de monômes                             */
/*                                                                      */
/* En sortie: Un entier qui est inférieur à zero si le degré du premier */
/*            monômes est inférieur au degré du deuxième monôme, égale  */
/*            à zero si les deux monômes ont le meme degré et supérieur */
/*            à zero si le degré du premier monôme est supérieur au     */
/*            degré du deuxième monôme.                                 */
/* -------------------------------------------------------------------- */
int monom_degree_cmp(const void *a, const void *b)
{
    const struct monom_t *m1 = (const struct monom_t *)a;
    const struct monom_t *m2 = (const struct monom_t *)b;
    return (m1->degree > m2->degree) - (m1->degree < m2->degree);
}


/**
 * @brief write the information of a monomial to the given output stream
 * @param [in] stream file pointer of an output stream
 * @param [in] monom address of a monomial
 */
/* -------------------------------------------------------------------- */
/* monom_save2file      Sauvegarde un monôme dans un fichier            */
/*                                                                      */
/* En entrée: stream, monom un pointeur sur un fichier et un pointeur   */
/*                  sur un monôme, puis sauvegarde les informations du  */
/*                  monôme dans le fichier selon le format %.3lf, %d\n  */
/*                                                                      */
/* -------------------------------------------------------------------- */
void monom_save2file(FILE *stream, struct monom_t *monom)
{
    fprintf(stream, "%.3lf, %d\n", monom->coef, monom->degree);
}