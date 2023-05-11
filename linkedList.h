/**
 * @file linkedList.h
 * @brief Header file of linked list module
 */

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "valCell.h"

/**
 * @struct cell_t
 * @brief Data structure of the linked list's cell
 * 2 fields :
 *      - 'val' : value of a cell
 *      - 'next' : pointer to the next cell
 */
typedef struct cell_t
{
    monom_t val;
    struct cell_t *next;
} cell_t;


/** Example
 * @fn void LL_init_list(cell_t **adrHeadPt)
 * @brief Initialize a void list
 * @param [in, out] adrHeadPt address of head pointer of the list 
 */
void LL_init_list(struct cell_t **adrHeadPt);

/**
 * @brief create a new cell for linked list from its data 
 * @param [in] data_adr address of the data
 * @return address of the new cell
 */
struct cell_t *LL_create_cell(monom_t *data_adr);

/**
 * @brief Insert a cell into a linked list at the given position
 * @param [in, out]  prev_adr address of previous pointer of the cell
 * @param [in]  cell_adr address of the cell to be added to the linked list
 */
void LL_add_cell(struct cell_t **prev_adr, struct cell_t *cell_adr);

/**
 * @brief Create a linked list from a file (in which the data is sorted)
 * @param [in, out] head address of head pointer of a linked list
 * @param [in] file_name name of a file containing the data for a linked list
 * @return head pointer of the linked list
 */
struct cell_t *LL_create_list_fromFileName(cell_t **head, const char *file_name);

/**
 * @brief Write the linked list to an output stream
 * @param [in] fp file pointer of an output stream
 * @param [in] head head pointeur of a linked list
 * @param monom_save2file fonction pointer for printing the data of a cell on an output stream
 */
void LL_save_list_toFile(FILE *fp, struct cell_t *head, void (*monom_save2file)(FILE *, struct monom_t *));


/**
 * @brief Save a linked list into a file
 * @param [in, out] head head pointer of a linked list
 * @param [in] file_name name of the backup file
 * @param monom_save2file fonction pointer for writing the data of a cell to a output stream
 */
void LL_save_list_toFileName(struct cell_t *head, const char *file_name, void (*monom_save2file)(FILE *, struct monom_t *));

/**
 * @brief Search a value in a linked list, and return the address of the previous pointer
 * @param [in] head address of the head pointer
 * @param [in] value address of the value to search
 * @param  cmp_func fonction pointer for comparison of two values
 * @return the address of the previous pointer
 */
struct cell_t **LL_search_prev(struct cell_t **head, const monom_t *value, int (*cmp_func)(const void *, const void *));

/**
 * @brief Delete a cell from a linked list
 * @param [in, out] prev_cell address of the previous pointer of the cell to delete
 */
void LL_del_cell(struct cell_t **prev_cell);


/**
 * @brief Free the memory location occupied by the cells of a linked list
 * @param [in, out] head address of head pointer of a linked list
 */
void LL_free_list(cell_t **head);

#endif