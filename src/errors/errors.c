
#include <stdio.h>
#include "errors.h"

static const char *gErrorsArray[] = {
    [SUCCESS]          = "Operation succeeded",
    [ERR_MEM_ALLOC]    = "Memory allocation failed",
    [ERR_BAD_ARGUMENT] = "Function called with a bad argument"
};

#define ARRAY_LEN(array) (sizeof(array) / sizeof(*array))

_Static_assert(ARRAY_LEN(gErrorsArray) == ERR_COUNT, "Error: seems like a description string for an error is missing");

void errors_print(status_t status)
{
    fprintf(stderr, "%s", gErrorsArray[status]);
}

const char *errors_get(status_t status)
{
    return gErrorsArray[status];
}
