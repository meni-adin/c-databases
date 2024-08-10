set(TARGET_NAME doubly_linked_list)

set(TARGET_SOURCES
    "doubly_linked_list.c"
)

set(TARGET_HEADERS
    "include/doubly_linked_list.h"
)

add_library(${TARGET_NAME}
    STATIC ${TARGET_SOURCES} ${TARGET_HEADERS}
)

target_include_directories(${TARGET_NAME}
    PUBLIC "include"
)

target_link_libraries(${TARGET_NAME}
    errors
)
