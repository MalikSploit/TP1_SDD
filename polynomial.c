#include <stdio.h>
#include <stdlib.h>
#include <float.h>  // FLT_EPSILON DBL_EPSILON LDBL_EPSILON

#include "linkedList.h"

/**
 * @brief compute 'in place' the derive of a polynomial
 * @param [in, out] head address of a polynomial's head pointer
 */
/* -------------------------------------------------------------------- */
/* poly_derive dériver un polynome stocké dans une liste chaînée.       */
/*                                                                      */
/* Cette fonction dérive un polynome dans une liste chaînée en          */
/* multipliant pour chaque monome le coefficient du monome et son degré */
/* puis en abaissant le degré du monome. Enfin on supprime le monome de */
/* degré négatif s'il existe.                                           */
/*                                                                      */
/* En entrée : head L'adresse du pointeur de tête de la liste chaînée   */
/*             représentant le polynome.                                */
/* -------------------------------------------------------------------- */
void poly_derive(cell_t **head)
{
    // Définir un pointeur sur la première cellule
    cell_t *current = *head;
    // Définir un pointeur sur la cellule précédente, initialisé à NULL
    cell_t *prev    = NULL;

    // Boucle pour parcourir toutes les cellules de la liste chaînée
    while (current != NULL)
    {
        // Appliquer la dérivation au monôme actuel
        current->val.coef *= current->val.degree;
        current->val.degree--;

        // Si le degré du monôme est négatif
        if (current->val.degree < 0)
        {
            // Si la cellule actuelle est la première de la liste
            if (prev == NULL)
            {
                // Mettre à jour le pointeur de tête de la liste pour pointer sur la cellule suivante
                *head = current->next;
                // Libérer la mémoire allouée pour la cellule actuelle
                free(current);
                // Définir le pointeur actuel sur la nouvelle première cellule
                current = *head;
            }

            // Si la cellule actuelle est une cellule de la liste, mais pas la première
            else
            {
                // Mettre à jour le pointeur de la cellule précédente pour pointer sur la cellule suivante
                prev->next = current->next;
                // Libérer la mémoire allouée pour la cellule actuelle
                free(current);
                // Définir le pointeur actuel sur la cellule suivante
                current = prev->next;
            }
        }
        // Si le degré du monôme est positif ou nul
        else
        {
            // Déplacer le pointeur de la cellule précédente pour pointer sur la cellule actuelle
            prev = current;
            // Déplacer le pointeur actuel pour pointer sur la cellule suivante
            current = current->next;
        }
    }
}

/**
 * @brief compute P1 = P1 + P2, P2 become empty
 * @param head1 [in, out] address of the 1st polynomial's head pointer
 * @param head2 [in, out] address of the 2nd polynomial's head pointer
 */
/* -------------------------------------------------------------------- */
/* poly_add Fais la somme de deux polynomes représentés par des listes  */
/* chaînées.                                                            */
/*                                                                      */
/* Cette fonction parcourt les 2 listes chaînées qui représentent les   */
/* polynomes. Elle somme les coefficients de chaque monome de degré égal*/
/* dans la liste 1 et ajoute à la liste 1 les monomes qui n'existent pas*/
/* dans la liste 2.                                                     */
/*                                                                      */
/* En entrée : head1 Adresse du pointeur de tête de la liste 1 qui est  */
/*             aussi la liste qui contient les valeurs finales.         */
/*             head2 Adresse du pointeur de tête de la liste 2          */
/* -------------------------------------------------------------------- */
void poly_add(cell_t **head1, cell_t **head2)
{
    // Pointeur vers la première cellule du premier polynome
    cell_t *current1 = *head1;
    // Pointeur vers la première cellule du second polynome
    cell_t *current2 = *head2;
    // Pointeur vers la cellule précédente de la liste 1
    cell_t *prev = NULL;

    // Tant que les deux listes ne sont pas entièrement parcourues
    while (current1 && current2)
    {
        // Si les degrés des termes actuels des deux listes sont égaux
        if (current1->val.degree == current2->val.degree)
        {
            // Ajout des coefficients des deux termes
            current1->val.coef += current2->val.coef;

            // Si le coefficient est nul
            if (current1->val.coef == 0)
            {
                // Si la cellule précédente de la liste 1 existe
                if (prev)
                {
                    // Suppression de la cellule actuelle
                    prev->next = current1->next;
                    free(current1);
                    current1 = prev->next;
                }

                // Sinon, la cellule actuelle est la première de la liste
                else
                {
                    // La nouvelle première cellule de la liste est la suivante
                    *head1 = current1->next;
                    free(current1);
                    current1 = *head1;
                }
            }

            // Si le coefficient est non nul
            else
            {
                prev = current1;
                current1 = current1->next;
            }
            // Pointeur vers la cellule actuelle de la liste 2
            cell_t *to_delete = current2;
            current2 = current2->next;
            // Suppression de la cellule actuelle de la liste 2
            free(to_delete);
        }

        // Si le degré du terme actuel de la liste 1 est inférieur au degré du terme actuel de la liste 2
        else if (current1->val.degree < current2->val.degree)
        {
            prev = current1;
            current1 = current1->next;
        }

        // Si le degré du terme actuel de la liste 1 est supérieur au degré du terme actuel de la liste 2
        else
        {
            // Si la cellule précédente de la liste 1 existe
            if (prev)
            {
                // Insertion de la cellule actuelle de la liste 2 avant la cellule actuelle de la liste 1
                prev->next = current2;
                prev = prev->next;
            }

            // Sinon, la cellule actuelle de la liste 2 devient la première de la liste 1
            else
            {
                *head1 = current2;
                prev = *head1;
            }

            current2 = current2->next;
            prev->next = current1;
        }
    }


    while (current2)
    {
        // Si la liste 1 n'est pas vide, ajoute la liste 2 à la fin de la liste 1
        if (prev)
        {
            prev->next = current2;
            prev = prev->next;
        }

        // Sinon, la liste 2 devient la liste 1
        else
        {
            *head1 = current2;
            prev = *head1;
        }
        current2 = current2->next;
    }

    // On supprime la liste 2 puisqu'elle est maintenant vide
    *head2 = NULL;
}


/**
 * @brief compute P1 * P2
 * @param head1 [in] head pointer of the 1st polynomial
 * @param head2 [in] head pointer of the 2nd polynomial
 * @return P1*P2
 */
/* -------------------------------------------------------------------- */
/* poly_prod Fais le produit de deux polynomes représentés par des      */
/* listes chaînées.                                                     */
/*                                                                      */
/* Cette fonction fait le produit de chaque monome de la liste 1 avec   */
/* chaque monome de la liste 2 dans un monome temporaire qu'on ajoute   */
/* ensuite à la liste result. On fusionne enfin les monome de même      */
/* degrés. */
/*                                                                      */
/* En entrée : head1 Pointeur de tête de la liste 1.                    */
/*             head2 Pointeur de tête de la liste 2.                    */
/* En sortie : result Pointeur de tête de la liste contenant le         */
/*             résultat du produit entre les deux listes.               */
/* -------------------------------------------------------------------- */
cell_t *poly_prod(cell_t *head1, cell_t *head2)
{
    // Initialisation des variables
    cell_t *current1       = head1;
    cell_t *current2       = head2;
    // La liste de résultats
    cell_t *result      = NULL;
    // La cellule temporaire pour stocker les produits
    cell_t *temp        = NULL;
    // Le pointeur de position actuel dans la liste de résultats
    cell_t *result_curr = NULL;

    // Parcours de la première liste
    while (current1 != NULL)
    {
        // on recommence depuis le début de la deuxième liste
        current2 = head2;

        // Parcours de la deuxième liste
        while (current2 != NULL)
        {
            // Création d'une nouvelle cellule pour stocker le résultat du produit
            temp = (cell_t *)malloc(sizeof(cell_t));
            // coefficient = produit des coefficients
            temp->val.coef = current1->val.coef * current2->val.coef;
            // degré = somme des degrés
            temp->val.degree = current1->val.degree + current2->val.degree;
            temp->next = NULL;

            // Ajout de la cellule temporaire à la liste de résultats
            if (result == NULL)
            {
                result = temp;
                result_curr = result;
            }
            else
            {
                result_curr->next = temp;
                result_curr = temp;
            }

            // Passage à la cellule suivante de la deuxième liste
            current2 = current2->next;
        }
        // Passage à la cellule suivante de la première liste
        current1 = current1->next;
    }

    // Fusion des termes de même degré dans la liste de résultats
    cell_t *curr = result;
    while (curr != NULL)
    {
        // noeud précédent
        cell_t *prev = curr;
        // noeud temporaire pour parcourir la liste
        cell_t *temp = curr->next;

        // pour chaque monome restant dans la liste
        while (temp != NULL)
        {
            // si le degré est le même que le monome courant
            if (temp->val.degree == curr->val.degree)
            {
                curr->val.coef += temp->val.coef;
                // supprime le noeud de la liste
                prev->next = temp->next;
                free(temp);
                temp = prev->next;
            }

            else
            {
                // passe au prochain noeud
                prev = temp;
                temp = temp->next;
            }
        }
        curr = curr->next;
    }
    // Retourne la liste de résultats
    return result;
}
