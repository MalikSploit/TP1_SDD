/**
 * @file polynomial_main.c
 * @brief Programme pour les tests des operations sur les polynomes
 * ATTENTION : Il faut creer autant de tests que les cas d'execution pour chaque fonction a tester
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "polynomial.h"
#include "teZZt.h"

BEGIN_TEST_GROUP(polynomial)

/*
TEST(LL_init_list) {
	cell_t *list;

	printf("\nInitialization of the linked list : \n");
	LL_init_list(&list);

	REQUIRE ( list == NULL );
}


TEST(Poly_derive1) {  // exemple
	cell_t *poly = NULL;
	FILE   *file = NULL;
	char   buffer[1024];

	printf("\nDerive of polynomial 1 : \n");

	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );
	LL_create_list_fromFileName(&poly, "poly1.txt");

	LL_save_list_toFile(file, poly, monom_save2file);
	fclose(file);
	LL_save_list_toFile(stdout, poly, monom_save2file);
	printf("\n");
	CHECK( 0 == strcmp(buffer, "5.000, 1\n4.000, 2\n5.000, 3\n6.000, 4\n3.000, 5\n"));

	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file );
	poly_derive(&poly);
	LL_save_list_toFile(file, poly, monom_save2file);
	fclose(file);
	LL_save_list_toFile(stdout, poly, monom_save2file);
    printf("\n");
	CHECK( 0 == strcmp(buffer, "5.000, 0\n8.000, 1\n15.000, 2\n24.000, 3\n15.000, 4\n"));

    //Clean the Memory
	LL_free_list(&poly);
    CHECK(poly == NULL);
}


TEST(Poly_derive2) { // test sur la derivation d'un polynome
    // Initialize the linked list
    cell_t *head = NULL;
    cell_t *node1 = malloc(sizeof(cell_t));
    monom_t term1 = {2, 3};
    node1->val = term1;
    head = node1;

    cell_t *node2 = malloc(sizeof(cell_t));
    monom_t term2 = {3, 4};
    node2->val = term2;
    node1->next = node2;

    //Test with a degree 0, which means it has to be deleted
    cell_t *node3 = malloc(sizeof(cell_t));
    monom_t term3 = {1, 0};
    node3->val = term3;
    node2->next = node3;

    node3->next = NULL;

    // Call the function to derive the polynomial
    poly_derive(&head);

    // Check the resulting polynomial
    cell_t *current = head;
    CHECK(current->val.coef == 6);
    CHECK(current->val.degree == 2);
    current = current->next;
    CHECK(current->val.coef == 12);
    CHECK(current->val.degree == 3);
    CHECK(current->next == NULL);

    // Free the memory
    LL_free_list(&head);
    CHECK(head == NULL);
}
*/

TEST(Poly_addition) { // test sur l'addition de deux polymones

    // Test Case 1: Add polynomials of different sizes
    cell_t *list1 = NULL;
    cell_t *list2 = NULL;

    // Create first polynomial
    monom_t m1 = {1.0, 2};
    monom_t m2 = {2.0, 1};
    monom_t m3 = {3.0, 0};

    cell_t *cell1 = LL_create_cell(&m1);
    cell_t *cell2 = LL_create_cell(&m2);
    cell_t *cell3 = LL_create_cell(&m3);

    LL_add_cell(&list1, cell1);
    LL_add_cell(&list1, cell2);
    LL_add_cell(&list1, cell3);

    // Create second polynomial
    cell_t *cell4 = LL_create_cell(&m1);
    cell_t *cell5 = LL_create_cell(&m2);
    cell_t *cell6 = LL_create_cell(&m3);
    LL_add_cell(&list2, cell4);
    LL_add_cell(&list2, cell5);
    LL_add_cell(&list2, cell6);

    // Add the polynomials
    poly_add(&list1, &list2);

    //Write the first test Polynome to the terminal
    printf("Somme de P1 et P2 pour le test 1 :\n");
    LL_save_list_toFile(stdout, list1, monom_save2file);

    // Check the result
    REQUIRE(list1->val.coef == 6.0);
    REQUIRE(list1->val.degree == 0);
    REQUIRE(list1->next->val.coef == 4.0);
    REQUIRE(list1->next->val.degree == 1);
    REQUIRE(list1->next->next->val.coef == 2.0);
    REQUIRE(list1->next->next->val.degree == 2);

    // Free the memory
    LL_free_list(&list1);
    CHECK(list1 == NULL);
    CHECK(list2 == NULL);
}


TEST(Poly_addition) { // test sur l'addition de deux polymones

    // Test Case 1: Add polynomials of different sizes
    cell_t *list1 = NULL;
    cell_t *list2 = NULL;

    // Create first polynomial
    monom_t m1 = {1.0, 2};
    monom_t m2 = {2.0, 1};
    monom_t m3 = {3.0, 0};
    LL_add_cell(&list1, LL_create_cell(&m1));
    LL_add_cell(&list1, LL_create_cell(&m2));
    LL_add_cell(&list1, LL_create_cell(&m3));

    // Create second polynomial
    monom_t m4 = {4.0, 1};
    monom_t m5 = {5.0, 0};
    LL_add_cell(&list2, LL_create_cell(&m4));
    LL_add_cell(&list2, LL_create_cell(&m5));

    // Add the polynomials
    poly_add(&list1, &list2);

    //Write the first test Polynome to the terminal
    printf("Somme de P1 et P2 pour le test 1 :\n");
    LL_save_list_toFile(stdout, list1, monom_save2file);

    // Check the result
    REQUIRE(list1->val.coef == 8.0);
    REQUIRE(list1->val.degree == 0);
    REQUIRE(list1->next->val.coef == 6.0);
    REQUIRE(list1->next->val.degree == 1);
    REQUIRE(list1->next->next->val.coef == 1.0);
    REQUIRE(list1->next->next->val.degree == 2);

    // Free the memory
    LL_free_list(&list1);
    CHECK(list1 == NULL);
    CHECK(list2 == NULL);


    // Test Case 2: Add polynomials with negative coefficients
    list1 = NULL;
    list2 = NULL;

    // Create first polynomial
    monom_t m6 = {1.0, 2};
    monom_t m7 = {-2.0, 1};
    monom_t m8 = {3.0, 0};
    LL_add_cell(&list1, LL_create_cell(&m6));
    LL_add_cell(&list1, LL_create_cell(&m7));
    LL_add_cell(&list1, LL_create_cell(&m8));

    // Create second polynomial
    monom_t m9 = {-4.0, 2};
    monom_t m10 = {5.0, 1};
    monom_t m11 = {-6.0, 0};
    LL_add_cell(&list2, LL_create_cell(&m9));
    LL_add_cell(&list2, LL_create_cell(&m10));
    LL_add_cell(&list2, LL_create_cell(&m11));

    // Add the polynomials
    poly_add(&list1, &list2);

    //Write the second test Polynome to the terminal
    printf("Somme de P1 et P2 pour le test 2 :\n");
    LL_save_list_toFile(stdout, list1, monom_save2file);

    // Check the result
    REQUIRE(list1->val.coef == -3.0);
    REQUIRE(list1->val.degree == 0);
    REQUIRE(list1->next->val.coef == 3.0);
    REQUIRE(list1->next->val.degree == 1);
    REQUIRE(list1->next->next->val.coef == -3.0);
    REQUIRE(list1->next->next->val.degree == 2);

    // Free the memory
    LL_free_list(&list1);
    CHECK(list1 == NULL);
    CHECK(list2 == NULL);


    // Test Case 3: Add two zero polynomials
    list1 = NULL;
    list2 = NULL;

    // Add the polynomials
    poly_add(&list1, &list2);

    //Write the third test Polynome to the terminal
    printf("Somme de P1 et P2 pour le test 3 :\n");
    LL_save_list_toFile(stdout, list1, monom_save2file);

    // Check the result
    REQUIRE(list1 == NULL);

    // Free the memory
    LL_free_list(&list1);
    CHECK(list1 == NULL);
    CHECK(list2 == NULL);
}


TEST(Poly_produit) { // test sur le calcul du produit de deux polymones
    // Test Case 1: Product of polynomials of different sizes
    cell_t *list1 = NULL;
    cell_t *list2 = NULL;
    cell_t *list3 = NULL;

    // Create first polynomial
    monom_t m1 = {1.0, 2};
    monom_t m2 = {2.0, 1};
    monom_t m3 = {3.0, 0};
    LL_add_cell(&list1, LL_create_cell(&m1));
    LL_add_cell(&list1, LL_create_cell(&m2));
    LL_add_cell(&list1, LL_create_cell(&m3));

    // Create second polynomial
    monom_t m4 = {4.0, 1};
    monom_t m5 = {5.0, 0};
    LL_add_cell(&list2, LL_create_cell(&m4));
    LL_add_cell(&list2, LL_create_cell(&m5));

    // Multiply the polynomials
    list3 = poly_prod(list1, list2);

    //Write the first test Polynome to the terminal
    printf("Produit de P1 et P2 pour le test 1 :\n");
    LL_save_list_toFile(stdout, list3, monom_save2file);

    // Check the result
    REQUIRE(list3->val.coef == 15);
    REQUIRE(list3->val.degree == 0);
    REQUIRE(list3->next->val.coef == 22.0);
    REQUIRE(list3->next->val.degree == 1);
    REQUIRE(list3->next->next->val.coef == 13.0);
    REQUIRE(list3->next->next->val.degree == 2);
    REQUIRE(list3->next->next->next->val.coef == 4.0);
    REQUIRE(list3->next->next->next->val.degree == 3);

    // Free the memory
    LL_free_list(&list1);
    LL_free_list(&list2);
    LL_free_list(&list3);
    CHECK(list1 == NULL);
    CHECK(list2 == NULL);
    CHECK(list3 == NULL);

    // Test Case 2: Product of polynomials with negative coefficients
    list1 = NULL;
    list2 = NULL;
    list3 = NULL;

    // Create first polynomial
    monom_t m6 = {1.0, 2};
    monom_t m7 = {-2.0, 1};
    monom_t m8 = {3.0, 0};
    LL_add_cell(&list1, LL_create_cell(&m6));
    LL_add_cell(&list1, LL_create_cell(&m7));
    LL_add_cell(&list1, LL_create_cell(&m8));

    // Create second polynomial
    monom_t m9 = {-4.0, 2};
    monom_t m10 = {5.0, 1};
    monom_t m11 = {-6.0, 0};
    LL_add_cell(&list2, LL_create_cell(&m9));
    LL_add_cell(&list2, LL_create_cell(&m10));
    LL_add_cell(&list2, LL_create_cell(&m11));

    // Multiply the polynomials
    list3 = poly_prod(list1, list2);

    //Write the second test Polynome to the terminal
    printf("Produit de P1 et P2 pour le test 2 :\n");
    LL_save_list_toFile(stdout, list3, monom_save2file);

    // Check the result
    REQUIRE(list3->val.coef == -18.0);
    REQUIRE(list3->val.degree == 0);
    REQUIRE(list3->next->val.coef == 27.0);
    REQUIRE(list3->next->val.degree == 1);
    REQUIRE(list3->next->next->val.coef == -28.0);
    REQUIRE(list3->next->next->val.degree == 2);
    REQUIRE(list3->next->next->next->val.coef == 13.0);
    REQUIRE(list3->next->next->next->val.degree == 3);
    REQUIRE(list3->next->next->next->next->val.coef == -4.0);
    REQUIRE(list3->next->next->next->next->val.degree == 4);

    // Free the memory
    LL_free_list(&list1);
    LL_free_list(&list2);
    LL_free_list(&list3);

    // Test Case 3: Product of two zero polynomials
    list1 = NULL;
    list2 = NULL;
    list3 = NULL;

    // Add the polynomials
    list3 = poly_prod(list1, list2);

    //Write the third test Polynome to the terminal
    printf("Produit de P1 et P2 pour le test 3 :\n");
    LL_save_list_toFile(stdout, list3, monom_save2file);

    // Check the result
    REQUIRE(list3 == NULL);

    // Free the memory
    LL_free_list(&list1);
    LL_free_list(&list2);
    LL_free_list(&list3);
    CHECK(list1 == NULL);
    CHECK(list2 == NULL);
    CHECK(list3 == NULL);
}


TEST(LL_save_list_toFileName) { // test pour l'ecriture d'un polynome dans un fichier
    cell_t *poly = NULL;
    FILE   *file = NULL;
    char   buffer[1024];

    //Test 1 : Derivative to file
    printf("Testing derivative of polynomial to file : \n");

    //We read the polynomial from the file
    file = fmemopen(buffer, 1024, "w");
    REQUIRE ( NULL != file );
    LL_create_list_fromFileName(&poly, "poly1.txt");

    //We check that we have the same polynomial as in the file
    LL_save_list_toFile(file, poly, monom_save2file);
    fclose(file);
    CHECK( 0 == strcmp(buffer, "5.000, 1\n4.000, 2\n5.000, 3\n6.000, 4\n3.000, 5\n"));

    //We calculate the derivative of the polynomial
    file = fmemopen(buffer, 1024, "w");
    REQUIRE ( NULL != file );
    poly_derive(&poly);
    LL_save_list_toFile(file, poly, monom_save2file);
    fclose(file);
    CHECK( 0 == strcmp(buffer, "5.000, 0\n8.000, 1\n15.000, 2\n24.000, 3\n15.000, 4\n"));

    // Write the Derivated polynome to the file
    char file_name[] = "Test_Derive_Vers_Fichier.txt";
    LL_save_list_toFileName(poly, file_name, monom_save2file);

    // check that the file has been created
    FILE *fp = fopen(file_name, "r");
    REQUIRE(fp != NULL);
    fclose(fp);

    // check that the file contains the expected data
    char line[100];
    fp = fopen(file_name, "r");
    fgets(line, sizeof(line), fp);
    CHECK(strcmp(line, "5.000, 0\n") == 0);
    fgets(line, sizeof(line), fp);
    CHECK(strcmp(line, "8.000, 1\n") == 0);
    fgets(line, sizeof(line), fp);
    CHECK(strcmp(line, "15.000, 2\n") == 0);
    fgets(line, sizeof(line), fp);
    CHECK(strcmp(line, "24.000, 3\n") == 0);
    fgets(line, sizeof(line), fp);
    CHECK(strcmp(line, "15.000, 4\n") == 0);
    fclose(fp);

    //Free the memory
    LL_free_list(&poly);
    CHECK(poly == NULL);


    //Test 2 : Addition of Polynomial to file
    printf("Testing addition of polynomial to file : \n");
    char file_name2[] = "Test_Addition_Vers_Fichier.txt";
    cell_t *list1 = NULL;
    cell_t *list2 = NULL;

    // Create first polynomial
    monom_t m1 = {1.0, 2};
    monom_t m2 = {2.0, 1};
    monom_t m3 = {3.0, 0};
    LL_add_cell(&list1, LL_create_cell(&m1));
    LL_add_cell(&list1, LL_create_cell(&m2));
    LL_add_cell(&list1, LL_create_cell(&m3));

    // Create second polynomial
    monom_t m4 = {4.0, 1};
    monom_t m5 = {5.0, 0};
    LL_add_cell(&list2, LL_create_cell(&m4));
    LL_add_cell(&list2, LL_create_cell(&m5));

    // Add the polynomials
    poly_add(&list1, &list2);

    // Write the addition of polynomials to the file
    LL_save_list_toFileName(list1, file_name2, monom_save2file);

    // check that the file has been created
    FILE *fp2 = fopen(file_name2, "r");
    REQUIRE(fp2 != NULL);
    fclose(fp2);

    // check that the file contains the expected data
    char line2[100];
    fp2 = fopen(file_name2, "r");
    fgets(line2, sizeof(line2), fp2);
    CHECK(strcmp(line2, "8.000, 0\n") == 0);
    fgets(line2, sizeof(line2), fp2);
    CHECK(strcmp(line2, "6.000, 1\n") == 0);
    fgets(line2, sizeof(line2), fp2);
    CHECK(strcmp(line2, "1.000, 2\n") == 0);
    fclose(fp2);

    // Free the memory
    LL_free_list(&list1);
    LL_free_list(&list2);
    CHECK(list1 == NULL);
    CHECK(list2 == NULL);


    //Test 3 : Product of Polynomial to file
    printf("Testing product of polynomial to file : \n");
    char file_name3[] = "Test_Produit_Vers_Fichier.txt";
    list1 = NULL;
    list2 = NULL;
    cell_t *list3 = NULL;

    // Create first polynomial (the exact same as for the addition)
    LL_add_cell(&list1, LL_create_cell(&m1));
    LL_add_cell(&list1, LL_create_cell(&m2));
    LL_add_cell(&list1, LL_create_cell(&m3));

    // Create second polynomial (the exact same as for the addition)
    LL_add_cell(&list2, LL_create_cell(&m4));
    LL_add_cell(&list2, LL_create_cell(&m5));

    // Multiply the polynomials
    list3 = poly_prod(list1, list2);

    // Write the product of polynomials to the file
    LL_save_list_toFileName(list3, file_name3, monom_save2file);

    // check that the file has been created
    FILE *fp3 = fopen(file_name3, "r");
    REQUIRE(fp3 != NULL);
    fclose(fp3);

    // check that the file contains the expected data
    char line3[100];
    fp3 = fopen(file_name3, "r");
    fgets(line3, sizeof(line3), fp3);
    CHECK(strcmp(line3, "15.000, 0\n") == 0);
    fgets(line3, sizeof(line3), fp3);
    CHECK(strcmp(line3, "22.000, 1\n") == 0);
    fgets(line3, sizeof(line3), fp3);
    CHECK(strcmp(line3, "13.000, 2\n") == 0);
    fgets(line3, sizeof(line3), fp3);
    CHECK(strcmp(line3, "4.000, 3\n") == 0);
    fclose(fp3);

    // Free the memory
    LL_free_list(&list1);
    LL_free_list(&list2);
    LL_free_list(&list3);
    CHECK(list1 == NULL);
    CHECK(list2 == NULL);
    CHECK(list3 == NULL);
}

END_TEST_GROUP(polynomial)

int main(void) {
	RUN_TEST_GROUP(polynomial);
	return EXIT_SUCCESS;
}
