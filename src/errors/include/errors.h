
#ifndef ERRORS_H
#define ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef enum status_t_ {
    SUCCESS,
    ERR_MEM_ALLOC,
    ERR_BAD_ARGUMENT,
    ERR_COUNT,
} status_t;

void errors_print(status_t);

const char *errors_get(status_t status);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // ERRORS_H
