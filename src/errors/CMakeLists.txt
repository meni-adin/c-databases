set(TARGET_NAME errors)

set(TARGET_SOURCES
    "errors.c"
)

set(TARGET_HEADERS
    "include/errors.h"
)

add_library(${TARGET_NAME}
    STATIC ${TARGET_SOURCES} ${TARGET_HEADERS}
)

target_include_directories(${TARGET_NAME}
    PUBLIC "include"
)
