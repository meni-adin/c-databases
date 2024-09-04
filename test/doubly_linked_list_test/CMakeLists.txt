set(TARGET_NAME doubly_linked_list_test)

include(GoogleTest)

set(TARGET_SOURCES
    "doubly_linked_list_test.cpp"
)

add_executable(${TARGET_NAME}
    ${TARGET_SOURCES}
)

target_link_libraries(${TARGET_NAME}
    GTest::gmock
    test_utils
    doubly_linked_list
)

gtest_discover_tests(${TARGET_NAME})
