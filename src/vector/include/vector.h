
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#include "c_databases_config.h"
#include "errors.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct Vector_t_ Vector_t;

typedef void (*VectorDataDestructor_t)(void *data);

typedef int (*VectorDataComparator_t)(const void *data1, const void *data2);

status_t Vector_newVector(Vector_t **vector);

status_t Vector_deleteVector(Vector_t *vector, VectorDataDestructor_t destructor);

status_t Vector_shrinkVector(Vector_t *vector);

status_t Vector_insertElement(Vector_t *vector, size_t index, void *data);

status_t Vector_pushElement(Vector_t *vector, void *data);

status_t Vector_removeElement(Vector_t *vector, size_t index);

status_t Vector_getElement(const Vector_t *vector, size_t index, void **data);

status_t Vector_getLength(const Vector_t *vector, size_t *length);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // VECTOR_H
