set(TARGET_NAME doubly_linked_list_test)

enable_testing()
include(GoogleTest)

set(TARGET_SOURCES
    "doubly_linked_list_test.cpp"
)

set(TARGET_HEADERS
)


add_executable(${TARGET_NAME}
    ${TARGET_SOURCES}
)

target_link_libraries(${TARGET_NAME}
    GTest::gmock
    doubly_linked_list
)

gtest_discover_tests(${TARGET_NAME})

