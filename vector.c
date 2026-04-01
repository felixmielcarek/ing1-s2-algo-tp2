/**
 * @file vector.c
 * @brief TP2 - Bibliothèque de tableau dynamique
 * @author ESIEE Paris
 * @date 2026
 *
 * Règles de travail :
 * - compilation sans erreur avec les options fournies ;
 * - gestion systématique des erreurs ;
 * - commentaires attendus sur chaque fonction.
 */

#include "vector.h"
#include <stdlib.h> // Pour malloc, free, realloc

/* ========================================================================== */
/* Allocation / libération                                                    */
/* ========================================================================== */

// Alloue et initialise un tableau dynamique
p_s_vector vector_alloc(size_t n) {
    s_vector* vector = malloc(sizeof(s_vector));
    if (vector == NULL) {
        return NULL;
    }
    vector->size = n;
    vector->data = calloc(n, sizeof(double));
    if (vector->data == NULL) {
        free(vector);
        return NULL;
    }

    return vector;
}

// Libère la mémoire du tableau dynamique et met le pointeur à NULL
VectorStatus vector_free(p_s_vector *p_vector) {
    if (p_vector == NULL || *p_vector == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }

    free((*p_vector)->data);
    free(*p_vector);
    *p_vector = NULL;

    return VECTOR_SUCCESS;
}

/* ========================================================================== */
/* Accès aux données                                                          */
/* ========================================================================== */

// Affecte la valeur v à l'index i du tableau dynamique
VectorStatus vector_set(p_s_vector p_vector, ssize_t i, double v) {
    if (p_vector == NULL || p_vector->data == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (i < 0 || i >= p_vector->size) {
        return VECTOR_ERROR_OUT_OF_BOUNDS;
    }
    p_vector->data[i] = v;
    return VECTOR_SUCCESS;
}

// Récupère la valeur stockée à l'index i et la stocke dans pv
VectorStatus vector_get(p_s_vector p_vector, ssize_t i, double *pv) {
    if (p_vector == NULL || p_vector->data == NULL || pv == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (i < 0 || i >= p_vector->size) {
        return VECTOR_ERROR_OUT_OF_BOUNDS;
    }
    *pv = p_vector->data[i];
    return VECTOR_SUCCESS;
}

/* ========================================================================== */
/* Modifications de structure                                                 */
/* ========================================================================== */

// Insère une nouvelle valeur v à l'index i du tableau dynamique
VectorStatus vector_insert(p_s_vector p_vector, ssize_t i, double v) {

    if (p_vector == NULL || p_vector->data == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (i < 0 || i > p_vector->size) {
        return VECTOR_ERROR_OUT_OF_BOUNDS;
    }

    double* new_data = realloc(p_vector->data, (p_vector->size + 1) * sizeof(double));
    if (new_data == NULL) {
        return VECTOR_ERROR_ALLOCATION;
    }
    p_vector->data = new_data;

    for (ssize_t j = p_vector->size; j > i; j--) {
        p_vector->data[j] = p_vector->data[j - 1];
    }
    p_vector->data[i] = v;
    p_vector->size++;

    return VECTOR_SUCCESS;
}

// Supprime la valeur située à l'index i du tableau dynamique
VectorStatus vector_erase(p_s_vector p_vector, ssize_t i) {
    if (p_vector == NULL || p_vector->data == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (i < 0 || i >= p_vector->size) {
        return VECTOR_ERROR_OUT_OF_BOUNDS;
    }

    double* new_data = realloc(p_vector->data, (p_vector->size - 1) * sizeof(double));
    if (new_data == NULL) {
        return VECTOR_ERROR_ALLOCATION;
    }
    p_vector->data = new_data;

    for (ssize_t j = i; j < p_vector->size - 1; j++) {
        p_vector->data[j] = p_vector->data[j + 1];
    }
    p_vector->size--;

    return VECTOR_SUCCESS;
}

// Ajoute une valeur à la fin du tableau dynamique
VectorStatus vector_push_back(p_s_vector p_vector, double v) {
    if (p_vector == NULL || p_vector->data == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }

    double* new_data = realloc(p_vector->data, (p_vector->size + 1) * sizeof(double));
    if (new_data == NULL) {
        return VECTOR_ERROR_ALLOCATION;
    }
    p_vector->data = new_data;

    p_vector->data[p_vector->size] = v;
    p_vector->size++;

    return VECTOR_SUCCESS;
}

// Supprime la dernière valeur du tableau dynamique
VectorStatus vector_pop_back(p_s_vector p_vector) {
    if (p_vector == NULL || p_vector->data == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    if (p_vector->size == 0) {
        return VECTOR_ERROR_OUT_OF_BOUNDS;
    }

    double* new_data = realloc(p_vector->data, (p_vector->size - 1) * sizeof(double));
    if (new_data == NULL && p_vector->size > 1) {
        return VECTOR_ERROR_ALLOCATION;
    }
    p_vector->data = new_data;
    p_vector->size--;

    return VECTOR_SUCCESS;
}

// Supprime toutes les valeurs du tableau dynamique
VectorStatus vector_clear(p_s_vector p_vector) {
    if (p_vector == NULL || p_vector->data == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    free(p_vector->data);
    p_vector->data = NULL;
    p_vector->size = 0;
    return VECTOR_SUCCESS;
}

// Vérifie si le tableau dynamique est vide
VectorStatus vector_empty(p_s_vector p_vector) {
    if (p_vector == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    return (p_vector->size == 0) ? VECTOR_SUCCESS : VECTOR_ERROR_NOT_EMPTY;
}

// Récupère le nombre d'éléments stockés dans le tableau dynamique
VectorStatus vector_size(p_s_vector p_vector, size_t *size) {
    if (p_vector == NULL || p_vector->data == NULL || size == NULL) {
        return VECTOR_ERROR_NULL_POINTER;
    }
    *size = p_vector->size;
    return VECTOR_SUCCESS;
}

/* End of file: vector.c */

