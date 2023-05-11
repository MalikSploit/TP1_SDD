/**
 * @file linkedList_main.c
 * @brief Programme pour les tests de fonctions de gestion de liste chainee
 * ATTENTION : Il faut creer autant de tests que les cas d'execution pour chaque fonction a tester
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "teZZt.h"

BEGIN_TEST_GROUP(linkedList)

TEST(monom_degree_cmp) {
	monom_t v1 = {5.11, 7};
	monom_t v2 = {3., 5};
	monom_t v3 = {5.25, 7};

	printf("\nComparaison des monomes : \n");
	CHECK( monom_degree_cmp(&v1, &v2) > 0 );
	CHECK( monom_degree_cmp(&v2, &v1) < 0 );
	CHECK( monom_degree_cmp(&v1, &v3) == 0 );
}

TEST(monom_save2file) {
	monom_t v = {5., 7};

	// creation du flux de texte => buffer
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	monom_save2file(file, &v);

	fclose(file);

	CHECK( 0 == strcmp(buffer, "5.000, 7\n") );
}


TEST(LL_init_list) {
	cell_t *list;

	printf("\nInitialization of the linked list : \n");
	LL_init_list(&list);

	REQUIRE ( list == NULL );
}


TEST(LL_create_cell) { // test de creation de cellule
	cell_t *new = NULL;
	monom_t m1 = {3.245, 17};

	printf("\nCreate a new cell (3.245, 17) : \n");
	new = LL_create_cell(&m1);
	REQUIRE ( NULL != new );
	CHECK ( NULL == new->next );

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	monom_save2file(file, &(new->val));
	fclose(file);
	CHECK( 0 == strcmp(buffer, "3.245, 17\n") );

    //Clean the Memory
    LL_free_list(&new);
}


// test d'insertion de cellule - liste a une cellule
TEST(LL_add_cell1) { 
	cell_t *list = NULL;
	cell_t *new = NULL;
	monom_t m1 = {3.45, 17};

	printf("\nAdd a cell to a linked list : \n");

	new = LL_create_cell(&m1);
	REQUIRE ( new != NULL );
	LL_add_cell(&list, new);
	CHECK( list == new );

	CHECK( list->val.coef == 3.45 );  // 3.45 est une valeur non approchee
	CHECK( list->val.degree == 17 );  
	CHECK( list->next == NULL );

    LL_free_list(&list);
}


// test d'insertion de cellule - liste a deux cellules
TEST(LL_add_cell2) { 
	cell_t *list = NULL;
	cell_t *new = NULL;
	monom_t m1 = {3.45, 17};
	monom_t m2 = {25.8, 9};

	printf("\nAdd two cells to a linked list : \n");

	new = LL_create_cell(&m1);
	REQUIRE ( new != NULL );
	LL_add_cell(&list, new);
	CHECK( list == new ); 

	new = LL_create_cell(&m2);
	REQUIRE ( new != NULL );
	LL_add_cell(&list, new);
	CHECK( list == new ); 

	// tester les valeurs de la liste
    cell_t *current = list;
    REQUIRE( current->val.coef == 25.8 );
    REQUIRE( current->val.degree == 9 );
    current = current->next;
    REQUIRE( current->val.coef == 3.45 );
    REQUIRE( current->val.degree == 17 );
    REQUIRE( current->next == NULL );

	// liberer la liste
    LL_free_list(&list);
}


// test d'insertion de cellule - liste a trois cellules
TEST(LL_add_cell3) {
	cell_t *list = NULL;
	cell_t *new = NULL;
	monom_t m1 = {3.245, 17};
	monom_t m2 = {25.8, 9};
	monom_t m3 = {12.4, 3};

	printf("\nAdd three cells to a linked list : \n");

	new = LL_create_cell(&m1);
	REQUIRE ( new != NULL );
	LL_add_cell(&list, new);
	CHECK( list == new );

	new = LL_create_cell(&m2);
	REQUIRE ( new != NULL );
	LL_add_cell(&list, new);
	CHECK( list == new );

	// ajouter le m3 en tete de la liste
    new = LL_create_cell(&m3);
    REQUIRE ( new != NULL );
    LL_add_cell(&list, new);
    CHECK( list == new );

	// tester les valeurs de la liste
    CHECK( list->val.coef == m3.coef );
    CHECK( list->val.degree == m3.degree );
    CHECK( list->next->val.coef == m2.coef );
    CHECK( list->next->val.degree == m2.degree );
    CHECK( list->next->next->val.coef == m1.coef );
    CHECK( list->next->next->val.degree == m1.degree );

	// liberer la liste
    LL_free_list(&list);
}



// test pour la creation d'un polynome a partir d'un fichier - exemple
TEST(LL_create_list_fromFileName) {
	cell_t *list;

	printf("\nCreate a linked list from file name0: \n");
    LL_create_list_fromFileName(&list, "notExist.txt");
	CHECK( NULL == list );
}


// test pour la creation d'un polynome à partir d'un fichier
TEST(LL_create_list_fromFileName) {
        cell_t *list = NULL;

        printf("\nCreate a linked list from file name : \n");
        LL_create_list_fromFileName(&list, "Creation_Polynome_1.txt");
        REQUIRE( list != NULL );

        // test the values of the linked list
        cell_t *current = list;
        CHECK( current->val.coef == 3.0 );
        CHECK( current->val.degree == 4 );

        current = current->next;
        CHECK( current->val.coef == -2.5 );
        CHECK( current->val.degree == 3 );

        current = current->next;
        CHECK( current->val.coef == 0.0 );
        CHECK( current->val.degree == 2 );

        current = current->next;
        CHECK( current->val.coef == 6.0 );
        CHECK( current->val.degree == 0 );

        // free the linked list
        LL_free_list(&list);
        CHECK(list == NULL);
}


TEST(LL_save_list_toFile) { // test pour l'ecriture d'un polynome sur un flux de sortie
        cell_t *list = NULL;
        cell_t *new = NULL;
        monom_t m1 = {3.245, 17};
        monom_t m2 = {25.8, 9};
        monom_t m3 = {12.4, 3};

        printf("\nWrite a linked list to a file:\n");

        // Create cells and add them to the linked list
        new = LL_create_cell(&m1);
        REQUIRE(new != NULL);
        LL_add_cell(&list, new);
        CHECK(list == new);

        new = LL_create_cell(&m2);
        REQUIRE(new != NULL);
        LL_add_cell(&list, new);
        CHECK(list == new);

        new = LL_create_cell(&m3);
        REQUIRE(new != NULL);
        LL_add_cell(&list, new);
        CHECK(list == new);

        // Write the linked list to a file
        FILE *fp = fopen("Ecriture_Polynome_1.txt", "w");
        REQUIRE(fp != NULL);
        LL_save_list_toFile(fp, list, monom_save2file);
        fclose(fp);

        // Compare the file content with the expected content
        char expected_content[] = "12.400, 3\n25.800, 9\n3.245, 17\n";
        char content[100];
        fp = fopen("Ecriture_Polynome_1.txt", "r");
        REQUIRE(fp != NULL);
        fread(content, 1, strlen(expected_content), fp);
        content[strlen(expected_content)] = '\0';
        fclose(fp);
        CHECK(strcmp(content, expected_content) == 0);

        // Clean up
        LL_free_list(&list);
        CHECK(list == NULL);
}

TEST(LL_search_prev)
{
    // Allocate memory for the head node
    struct cell_t *head = NULL;

    // Allocate memory for the first node and initialize its degree to 3
    struct cell_t *node1 = (struct cell_t *) malloc(sizeof(struct cell_t));
    node1->val.degree = 3;
    node1->next = NULL;
    head = node1;

    // Search for the previous node of node1 and store the result in result
    struct cell_t **result = LL_search_prev(&head, &(node1->val), monom_degree_cmp);

    // Check if the result is equal to node1
    CHECK(*result == node1);

    // Allocate memory for the second node and initialize its degree to 5
    struct cell_t *node2 = (struct cell_t *) malloc(sizeof(struct cell_t));
    node2->val.degree = 5;
    node2->next = NULL;
    node1->next = node2;

    // Search for the previous node of node2 and store the result in result
    result = LL_search_prev(&head, &(node2->val), monom_degree_cmp);

    // Check if the result is equal to node2
    CHECK(*result == node2);

    // Allocate memory for the third node and initialize its degree to 1
    struct cell_t *node3 = (struct cell_t *) malloc(sizeof(struct cell_t));
    node3->val.degree = 1;
    node3->next = NULL;
    head = node3;
    node3->next = node1;

    // Search for the previous node of node1 and store the result in result
    result = LL_search_prev(&head, &(node1->val), monom_degree_cmp);

    // Check if the result is equal to node1
    CHECK(*result == node1);

    // Search for the previous node of node2 and store the result in result
    result = LL_search_prev(&head, &(node2->val), monom_degree_cmp);

    // Check if the result is equal to node2
    CHECK(*result == node2);

    // Search for the previous node of node3 and store the result in result
    result = LL_search_prev(&head, &(node3->val), monom_degree_cmp);

    // Check if the result is equal to node3
    CHECK(*result == node3);

    //Free memory
    LL_free_list(&head);
    CHECK(head == NULL);
}


TEST(LL_add_celln) { // test d'insertion de cellule - liste a n cellules
    cell_t *list = NULL;

    monom_t monom1 = {2.0, 3};
    cell_t *cell1 = (cell_t *)malloc(sizeof(cell_t));
    cell1->val = monom1;
    cell1->next = NULL;

    monom_t monom2 = {-1.5, 2};
    cell_t *cell2 = (cell_t *)malloc(sizeof(cell_t));
    cell2->val = monom2;
    cell2->next = NULL;

    monom_t monom3 = {4.0, 1};
    cell_t *cell3 = (cell_t *)malloc(sizeof(cell_t));
    cell3->val = monom3;
    cell3->next = NULL;

    monom_t monom4 = {3.0, 0};
    cell_t *cell4 = (cell_t *)malloc(sizeof(cell_t));
    cell4->val = monom4;
    cell4->next = NULL;

    LL_add_cell(&list, cell1);
    LL_add_cell(&list, cell2);
    LL_add_cell(&list, cell3);
    LL_add_cell(&list, cell4);

    CHECK(list->val.coef == 3.0);
    CHECK(list->val.degree == 0);
    CHECK(list->next->val.coef == 4.0);
    CHECK(list->next->val.degree == 1);
    CHECK(list->next->next->val.coef == -1.5);
    CHECK(list->next->next->val.degree == 2);
    CHECK(list->next->next->next->val.coef == 2.0);
    CHECK(list->next->next->next->val.degree == 3);
    CHECK(list->next->next->next->next == NULL);

    FILE *fp = fopen("Insertion_Fichier_Vers_Polynome.txt", "w");
    LL_save_list_toFile(fp, list, monom_save2file);
    fclose(fp);

    fp = fopen("Insertion_Fichier_Vers_Polynome.txt", "r");
    char output_buffer[100];
    char expected_output_1[] = "3.000, 0\n";
    char expected_output_2[] = "4.000, 1\n";
    char expected_output_3[] = "-1.500, 2\n";
    char expected_output_4[] = "2.000, 3\n";
    fgets(output_buffer, 100, fp);
    CHECK(strcmp(output_buffer, expected_output_1) == 0);
    fgets(output_buffer, 100, fp);
    CHECK(strcmp(output_buffer, expected_output_2) == 0);
    fgets(output_buffer, 100, fp);
    CHECK(strcmp(output_buffer, expected_output_3) == 0);
    fgets(output_buffer, 100, fp);
    CHECK(strcmp(output_buffer, expected_output_4) == 0);
    fclose(fp);

    LL_free_list(&list);
    CHECK(list == NULL);
}

TEST(LL_del_cell) { // test de la suppression d'un element
        // Create a linked list with three elements
        cell_t *head = malloc(sizeof(cell_t));
        head->val.coef = 1.0;
        head->val.degree = 3;
        head->next = malloc(sizeof(cell_t));
        head->next->val.coef = 2.0;
        head->next->val.degree = 2;
        head->next->next = malloc(sizeof(cell_t));
        head->next->next->val.coef = 3.0;
        head->next->next->val.degree = 1;
        head->next->next->next = NULL;

        // Save a pointer to the second element
        cell_t *second_element = head->next;

        // Delete the second element
        LL_del_cell(&head);

        // Verify that the linked list now only contains two elements
        CHECK(head->next != second_element);
        CHECK(head->val.coef == 1.0);
        CHECK(head->val.degree == 3);
        CHECK(head->next->val.coef == 3.0);
        CHECK(head->next->val.degree == 1);

        // Clean up memory
        LL_free_list(&head);
        CHECK(head == NULL);
}


TEST(LL_free_list) { // test de la liberation de liste
    cell_t *list, *current;

    // allocate a list with three elements
    list = (cell_t *) malloc(sizeof(cell_t));
    list->val.coef = 1;
    list->val.degree = 2;
    list->next = (cell_t *) malloc(sizeof(cell_t));
    list->next->val.coef = 2;
    list->next->val.degree = 1;
    list->next->next = (cell_t *) malloc(sizeof(cell_t));
    list->next->next->val.coef = 3;
    list->next->next->val.degree = 0;
    list->next->next->next = NULL;

    // call the function to be tested
    LL_free_list(&list);

    // verify that all elements in the list have been freed
    REQUIRE(list == NULL);
    current = list;
    while (current != NULL)
    {
        CHECK(0 && "List not freed");
        current = current->next;
    }
}

TEST(LL_save_list_toFileName) {
    cell_t *list;
    char file_name[] = "Polynome_Vers_Fichier.txt";

    // allocate a list with three elements
    list = (cell_t *) malloc(sizeof(cell_t));
    list->val.coef = 1;
    list->val.degree = 2;
    list->next = (cell_t *) malloc(sizeof(cell_t));
    list->next->val.coef = 2;
    list->next->val.degree = 1;
    list->next->next = (cell_t *) malloc(sizeof(cell_t));
    list->next->next->val.coef = 3;
    list->next->next->val.degree = 0;
    list->next->next->next = NULL;

    // call the function to be tested
    LL_save_list_toFileName(list, file_name, monom_save2file);

    // check that the file has been created
    FILE *fp = fopen(file_name, "r");
    REQUIRE(fp != NULL);
    fclose(fp);

    // check that the file contains the expected data
    char line[100];
    fp = fopen(file_name, "r");
    fgets(line, sizeof(line), fp);
    CHECK(strcmp(line, "1.000, 2\n") == 0);
    fgets(line, sizeof(line), fp);
    CHECK(strcmp(line, "2.000, 1\n") == 0);
    fgets(line, sizeof(line), fp);
    CHECK(strcmp(line, "3.000, 0\n") == 0);
    fclose(fp);

    //Clean Memory
    LL_free_list(&list);
    CHECK(list == NULL);
}

END_TEST_GROUP(linkedList)

int main(void)
{
	RUN_TEST_GROUP(linkedList);
	return EXIT_SUCCESS;
}
