
#include "vector.h"

#include <stdlib.h>

#include "errors.h"

struct Vector_t_ {
    void **arr;
    size_t length;
    size_t capacity;
};

#define VECTOR_GROWTH_FACTOR 2

status_t Vector_newVector(Vector_t **vector) {
#ifdef C_DATABASES_SAFE_MODE
    if (!vector) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    Vector_t *newVector = malloc(sizeof(*newVector));
    if (!newVector) {
        return ERR_MEM_ALLOC;
    }

    *newVector = (Vector_t){
        .arr      = NULL,
        .length   = 0,
        .capacity = 0,
    };
    *vector = newVector;

    return SUCCESS;
}

status_t Vector_deleteVector(Vector_t *vector, VectorDataDestructor_t destructor) {
#ifdef C_DATABASES_SAFE_MODE
    if (!vector) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    if (destructor) {
        for (size_t index = 0; index < vector->length; ++index) {
            destructor(vector->arr[index]);
        }
    }
    free(vector->arr);
#ifdef C_DATABASES_SAFE_MODE
    *vector = (Vector_t){0};
#endif  // C_DATABASES_SAFE_MODE
    free(vector);

    return SUCCESS;
}

status_t Vector_shrinkVector(Vector_t *vector) {
#ifdef C_DATABASES_SAFE_MODE
    if (!vector) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    if (vector->length < vector->capacity) {
        void *tempArr = vector->arr;
        vector->arr   = realloc(vector->arr, vector->length * sizeof(*(vector->arr)));
        if (vector->arr == NULL) {
            vector->arr = tempArr;
            return ERR_MEM_ALLOC;
        }
    }

    return SUCCESS;
}

status_t Vector_insertElement(Vector_t *vector, size_t index, void *data) {
#ifdef C_DATABASES_SAFE_MODE
    if (!vector) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    if (index >= vector->capacity) {
        void  *tempArr     = vector->arr;
        size_t newCapacity = index + 1;
        vector->arr        = realloc(vector->arr, newCapacity * sizeof(*(vector->arr)));
        if (vector->arr == NULL) {
            vector->arr = tempArr;
            return ERR_MEM_ALLOC;
        }
        vector->capacity = newCapacity;
    }

    for (size_t currentIndex = vector->length; currentIndex < index; ++currentIndex) {
        vector->arr[currentIndex] = NULL;
    }

    vector->arr[index] = data;
    if (index >= vector->length) {
        vector->length = index + 1;
    }

    return SUCCESS;
}

status_t Vector_pushElement(Vector_t *vector, void *data) {
#ifdef C_DATABASES_SAFE_MODE
    if (!vector) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    if (vector->length == vector->capacity) {
        void *tempArr = vector->arr;
        vector->arr   = realloc(vector->arr, VECTOR_GROWTH_FACTOR * vector->length * sizeof(*(vector->arr)));
        if (vector->arr == NULL) {
            vector->arr = tempArr;
            return ERR_MEM_ALLOC;
        }
        vector->capacity *= VECTOR_GROWTH_FACTOR;
    }

    vector->arr[vector->length] = data;
    ++(vector->length);

    return SUCCESS;
}

status_t Vector_removeElement(Vector_t *vector, size_t index) {
#ifdef C_DATABASES_SAFE_MODE
    if (!vector || (index >= vector->length)) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    vector->arr[index] = NULL;

    return SUCCESS;
}

status_t Vector_getElement(const Vector_t *vector, size_t index, void **data) {
#ifdef C_DATABASES_SAFE_MODE
    if (!vector || (index >= vector->length) || !data) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    *data = vector->arr[index];

    return SUCCESS;
}

status_t Vector_getLength(const Vector_t *vector, size_t *length) {
#ifdef C_DATABASES_SAFE_MODE
    if (!vector || !length) {
        return ERR_BAD_ARGUMENT;
    }
#endif  // C_DATABASES_SAFE_MODE

    *length = vector->length;

    return SUCCESS;
}
