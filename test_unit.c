/******************************************************************************
 * ESIEE Paris
 * Algorithmique et programmation pour l'ingénieur
 *
 * TP2 — Tests unitaires de la bibliothèque vector
 * Fichier : test_unit.c
 *
 * Ce programme contient une série de tests permettant de vérifier le bon
 * fonctionnement des fonctions implémentées dans vector.c.
 *
 * Les étudiants peuvent compléter ou enrichir ces tests.
 *
 ******************************************************************************/

#include <stdio.h>
#include "vector.h"

// Macro pour les tests unitaires
#define ASSERT(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "Assertion échouée dans %s:%d: %s\n", __FILE__, __LINE__, #condition); \
        return 1; \
    } \
} while (0)

// Test d'allocation et de libération de mémoire
int test_vector_alloc_free() {
    p_s_vector vec = vector_alloc(5);
    ASSERT(vec != NULL);
    ASSERT(vec->size == 5);
    ASSERT(vec->data != NULL);
    ASSERT(vec->data[0] == 0.0); // Vérifie que les éléments sont initialisés à 0
    
    VectorStatus status = vector_free(&vec);
    ASSERT(status == VECTOR_SUCCESS);
    ASSERT(vec == NULL);

    status = vector_free(&vec);
    ASSERT(status == VECTOR_ERROR_NULL_POINTER);

    return 0;
}

// Test d'insertion et de récupération d'éléments (à compléter par les étudiants)
int test_vector_set_get() {
    p_s_vector vec = vector_alloc(5);

    VectorStatus status = vector_set(vec, 0, 3.14);
    ASSERT(status == VECTOR_SUCCESS);

    double value;
    status = vector_get(vec, 0, &value);
    ASSERT(status == VECTOR_SUCCESS);
    ASSERT(value == 3.14);

    status = vector_free(&vec);
    status = vector_set(vec, 0, 2.71);
    ASSERT(status == VECTOR_ERROR_NULL_POINTER);
    status = vector_get(vec, 0, &value);
    ASSERT(status == VECTOR_ERROR_NULL_POINTER);

    return 0;
}

// Test d'insertion et suppression d'éléments (à compléter par les étudiants)
int test_vector_insert_erase() {
    double v1 = 3.14, v2 = 31.4, value;

    p_s_vector vec = vector_alloc(5);

    ASSERT(vector_insert(NULL, 0, v1) == VECTOR_ERROR_NULL_POINTER);
    ASSERT(vector_insert(vec, -1, v1) == VECTOR_ERROR_OUT_OF_BOUNDS);
    
    ASSERT(vector_insert(vec, 0, v1) == VECTOR_SUCCESS);
    ASSERT(vector_get(vec, 0, &value) == VECTOR_SUCCESS && value == v1);

    ASSERT(vector_insert(vec, 1, v2) == VECTOR_SUCCESS);
    ASSERT(vector_get(vec, 0, &value) == VECTOR_SUCCESS && value == v1);
    ASSERT(vector_get(vec, 1, &value) == VECTOR_SUCCESS && value == v2);

    ASSERT(vector_erase(NULL, 0) == VECTOR_ERROR_NULL_POINTER);
    ASSERT(vector_erase(vec, -1) == VECTOR_ERROR_OUT_OF_BOUNDS);

    ASSERT(vector_erase(vec, 0) == VECTOR_SUCCESS);
    ASSERT(vector_get(vec, 0, &value) == VECTOR_SUCCESS && value == v2);
    return 0;
}

// Test de la fonction vector_empty()
int test_vector_empty() {
    ASSERT(vector_empty(NULL) == VECTOR_ERROR_NULL_POINTER);

    p_s_vector vec = vector_alloc(5);
    ASSERT(vector_empty(vec) == VECTOR_ERROR_NOT_EMPTY);
    ASSERT(vector_clear(vec) == VECTOR_SUCCESS && vector_empty(vec) == VECTOR_SUCCESS);
    return 0;
}

// Fonction principale exécutant les tests
int main() {
    int failed = 0;

    printf("[INFO] Lancement de la campagne de tests...\n");

    failed += test_vector_alloc_free();
    failed += test_vector_set_get();
    failed += test_vector_insert_erase();
    failed += test_vector_empty();

    if (failed == 0) {
        printf("[OK] Tous les tests sont validés.\n");
    } else {
        printf("[ERREUR] Échecs détectés dans %d test(s). \n", failed);
    }

    return failed;
}

/******************************************************************************
 * End of file: test_unit.c
 ******************************************************************************/

