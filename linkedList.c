/**
 * @file linkedList.c
 * @brief Implementation file of linked list module
 */
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

/** Example
 * @fn void LL_init_list(cell_t **adrHeadPt)
 * @brief Initialize a void list
 * @param [in, out] adrHeadPt address of head pointer of the list 
 */
/* -------------------------------------------------------------------- */
/* LL_init_list     Initialisation d'une liste chaînée vide             */
/*                                                                      */
/* En entrée: adrHeadPt l'adresse du pointeur de                        */
/*            tête d'une liste chaînée et initialise ce pointeur à NULL */
/*            pour créer une liste chaînée vide                         */
/*                                                                      */
/* -------------------------------------------------------------------- */
void LL_init_list(struct cell_t **adrHeadPt)
{
    *adrHeadPt = NULL;
}

/**
 * @brief Create a new cell for linked list from its data 
 * @param [in] data_adr address of the data
 * @return address of the new cell
 */
/* -------------------------------------------------------------------- */
/* LL_create_cell Créer une nouvelle cellule pour une liste chaînée     */
/*                                                                      */
/* Cette fonction alloue dynamiquement de la mémoire pour créer une     */
/* nouvelle cellule pour une liste chaînée et initialise ses champs     */
/* avec les données passées en paramètre. Si l'allocation de mémoire    */
/* échoue, elle renvoie un pointeur NULL.                               */
/*                                                                      */
/* En entrée : data_adr Adresse de la structure de données à stocker    */
/*             dans la nouvelle cellule                                 */
/* En sortie : Un pointeur vers la nouvelle cellule créée ou NULL si    */
/*             l'allocation de mémoire échoue                           */
/* -------------------------------------------------------------------- */
struct cell_t *LL_create_cell(monom_t *data_adr)
{
    cell_t *new_cell = (cell_t *)malloc(sizeof(cell_t));

    if (new_cell == NULL)
    {
        return NULL;
    }

    new_cell->val  = *data_adr;
    new_cell->next = NULL;
    return new_cell;
}

/**
 * @brief Insert a cell into a linked list at the given position
 * @param [in, out]  prev_adr address of previous pointer of the cell
 * @param [in]  cell_adr address of the cell to be added to the linked list
 */
/* -------------------------------------------------------------------- */
/* LL_add_cell ajouter une cellule après une autre cellule spécifée en  */
/* paramètre                                                            */
/*                                                                      */
/* Cette fonction ajoute une cellule à la suite d'une autre cellule     */
/* dont l'adresse est donnée en parametre. Si la cellule donnée en       */
/* paramètre n'est pas dans la liste, on ajoute la cellule en fin de    */
/* liste.                                                               */
/*                                                                      */
/* En entrée : prev_adr Adresse de la cellule précédente                */
/*             cell_adr Adresse de la cellule à adjoindre               */
/* -------------------------------------------------------------------- */
void LL_add_cell(struct cell_t **prev_adr, struct cell_t *cell_adr)
{
    // Si la cellule précédente n'existe pas, on insère la nouvelle cellule à la fin de la liste
    if (*prev_adr == NULL)
    {
        *prev_adr = cell_adr;
        cell_adr->next = NULL;
    }

    // Sinon, on insère la nouvelle cellule apres cellule précédente
    else
    {
        cell_adr->next = *prev_adr;
        *prev_adr = cell_adr;
    }
}

/**
 * @brief Create a linked list from a file (in which the data is sorted)
 * @param [in, out] head address of head pointer of a linked list
 * @param [in] file_name name of a file containing the data for a linked list
 * @return head pointer of the linked list
 */
/* -------------------------------------------------------------------- */
/* LL_create_list_fromFileName Créer une liste chaînée à partir du      */
/* nom d'un fichier                                                     */
/*                                                                      */
/* Cette fonction crée une liste chaînée à partir d'un fichier texte    */
/* S'il y a un problème à la lecture du fichier ou à la création des    */
/* cellules, on retourne une liste vide et on affiche un message        */
/* d'erreur.                                                            */
/*                                                                      */
/* En entrée : head Adresse du pointeur de tête de la nouvelle liste    */
/*             file_name Nom du fichier contenant la liste              */
/* En sortie : head Adresse de la tête de la nouvelle liste ou NULL en  */
/*             cas de problème.                                         */
/* -------------------------------------------------------------------- */
struct cell_t *LL_create_list_fromFileName(cell_t **head, const char *file_name)
{
    FILE    *fp;
    cell_t  *new_cell;
    cell_t  *current;
    monom_t data;

    fp = fopen(file_name, "r");

    if (!fp)
    {
        perror("Error opening file");
        *head = NULL;
        return *head;
    }

    *head   = NULL;
    current = NULL;

    while (fscanf(fp, "%lf, %d", &data.coef, &data.degree) != EOF)
    {
        // Création d'une nouvelle cellule avec les données lues à partir du fichier
        new_cell = LL_create_cell(&data);

        // Si la création de la cellule échoue, libérer la liste créée et renvoyer NULL
        if (!new_cell)
        {
            printf("Error allocating memory\n");
            LL_free_list(head);
            *head = NULL;
            fclose(fp);
            return *head;
        }

        // Ajout de la nouvelle cellule à la fin de la liste
        if (*head == NULL)
        {
            *head = new_cell;
            current = *head;
        }

        else
        {
            current->next = new_cell;
            current = current->next;
        }
    }

    fclose(fp);
    return *head;
}

/**
 * @brief Write the linked list to an output stream
 * @param [in] fp file pointer of an output stream
 * @param [in] head head pointer of a linked list
 * @param monom_save2file fonction pointer for printing the data of a cell on an output stream
 */
/* -------------------------------------------------------------------- */
/* LL_save_list_toFile Ecrire une liste chaînée dans un flux            */
/*                                                                      */
/* Cette fonction écrit une liste chaînée dans un flux donné en         */
/* Paramètre. Elle affiche une erreur si le flux n'existe pas.          */
/*                                                                      */
/* En entrée : fp Le pointeur du flux dans lequel on écrit              */
/*             head Le pointeur de tête de la liste chaînée             */
/*             monom_save2file Fonction d'écriture d'un monome dans un  */
/*             flux                                                     */
/* -------------------------------------------------------------------- */

 
void LL_save_list_toFile(FILE *fp, struct cell_t *head, void (*monom_save2file)(FILE *, struct monom_t *))
{
    // Vérifier si le pointeur de fichier est valide
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    // Initialiser un pointeur de cellule pour parcourir la liste
    struct cell_t *curr_ptr = head;

    // Parcourir la liste et écrire chaque monome dans le fichier en utilisant la fonction de sauvegarde de monome donnée
    while (curr_ptr != NULL)
    {
        monom_save2file(fp, &(curr_ptr->val));
        curr_ptr = curr_ptr->next;
    }
}

/**
 * @brief Save a linked list into a file
 * @param [in, out] head head pointer of a linked list
 * @param [in] file_name name of the backup file
 * @param monom_save2file fonction pointer for writing the data of a cell to a output stream
 */
/* -------------------------------------------------------------------- */
/* LL_save_list_toFileName Enregistrer une liste chaînée dans un fichier*/
/* à partir du nom du fichier.                                          */
/*                                                                      */
/* Cette fonction enregistre une liste chaînée dans un fichier avec le  */
/* nom du fichier. S'il n'est pas possible d'ouvrir le fichier, elle    */
/* affiche un message d'erreur.                                         */
/*                                                                      */
/* En entrée : head Le pointeur de tête de la liste chaînée             */
/*             file_name Le pointeur du nom du fichier                  */
/*             monom_save2file Fonction d'écriture d'un monome dans un  */
/*             flux                                                     */
/* -------------------------------------------------------------------- */
void LL_save_list_toFileName(struct cell_t *head, const char *file_name, void (*monom_save2file)(FILE *, struct monom_t *))
{
    FILE *fp = fopen(file_name, "w");

    // Vérifier si le pointeur de fichier est valide
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    else
    {
        struct cell_t *curr_ptr = head;

        //Écrire les données de la liste chaînée dans le fichier
        while (curr_ptr != NULL)
        {
            monom_save2file(fp, &curr_ptr->val);
            curr_ptr = curr_ptr->next;
        }

        fclose(fp);
    }
}


/**
 * @brief Search a value in a linked list, and return the address of the previous pointer
 * @param [in] head address of the head pointer
 * @param [in] value address of the value to search
 * @param  cmp_func fonction pointer for comparison of two values
 * @return the address of the previous pointer
 */
/* -------------------------------------------------------------------- */
/* LL_search_prev Recherche de la cellule précendent la cellule du      */
/* degré donné en paramètre.                                            */
/*                                                                      */
/* Cette fonction recherche la cellule précendente à celle du degré     */
/* donné en paramètre. Si la liste ne contient pas de monome de degré   */
/* donné en paramètre, ou si la liste est vide, la fonction renvoit NULL*/
/*                                                                      */
/* En entrée : head Adresse du pointeur de tête de la liste chaînée.    */
/*             value Pointeur de la valeur du degré du monome recherché */
/*             cmp_func Fonction de comparaison entre deux valeurs      */
/* En sortie : prev Adresse du pointeur de la cellule précédent la      */
/*             cellule de degré value.                                  */
/* -------------------------------------------------------------------- */

struct cell_t **LL_search_prev(struct cell_t **head, const monom_t *value, int (*cmp_func)(const void *, const void *))
{
    // Initialisation du pointeur de cellule courante et du pointeur de cellule précédante.
    struct cell_t *current = *head;
    struct cell_t **prev   = head;

    // Parcours de la liste chaînée jusqu'à trouver la cellule précédant celle contenant 'value' dans la liste triée.
    while (current != NULL && (cmp_func(&(current->val), value) < 0) )
    {
        // Déplacement des pointeurs pour passer à la cellule suivante.
        prev = &(current->next);
        current = current->next;
    }

    // Retourne l'adresse du pointeur qui pointe vers la cellule précédant celle contenant 'value'.
    return prev;
}


/**
 * @brief Delete a cell from a linked list
 * @param [in, out] prev_cell address of the previous pointer of the cell to delete
 */
/* -------------------------------------------------------------------- */
/* LL_del_cell Suppression d'une cellule dans une liste chaînée à       */
/* partir de la précédente                                              */
/*                                                                      */
/* Cette fonction supprime une cellule dans une liste chaînée en        */
/* modifiant la cellule précédente pour la faire pointer vers la cellule*/
/* sur laquelle pointait la cellule à supprimer. La fonction libère     */
/* ensuite l'espace mémoire utilisé par la cellule.                     */
/*                                                                      */
/* En entrée : prev_cell Adresse du pointeur de la cellule précédente   */
/*             à la cellule à supprimer.                                */
/* -------------------------------------------------------------------- */
void LL_del_cell(cell_t **prev_cell)
{
    // Stocker l'adresse de la cellule à supprimer
    cell_t *cell_to_delete = (*prev_cell)->next;
    // Mettre à jour le pointeur de la cellule précédente pour sauter la cellule à supprimer
    (*prev_cell)->next     = cell_to_delete->next;
    // Libérer la mémoire allouée pour la cellule à supprimer
    free(cell_to_delete);
}

/**
 * @brief Free the memory location occupied by a linked list
 * @param [in, out] head address of head pointer of a linked list
 */
/* -------------------------------------------------------------------- */
/* LL_free_list Suppression d'une liste chaînée                         */
/*                                                                      */
/* Cette fonction libère l'espace mémoire de toutes les cellules d'une  */
/* liste chaînée et fait pointer la tête de la liste chaînée sur NULL   */
/*                                                                      */
/* En entrée : head Adresse du pointeur de tête de la liste chaînée     */
/* -------------------------------------------------------------------- */
void LL_free_list(cell_t **head)
{
    cell_t *current = *head;

    // Parcours de tous les éléments de la liste
    while (current != NULL)
    {
        cell_t *next = current->next;
        // Libère la mémoire allouée pour l'élément courant
        free(current);
        // Passe à l'élément suivant
        current = next;
    }
    // Met le pointeur de tête à NULL pour signaler que la liste est vide
    *head = NULL;
}
