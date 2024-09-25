set(TARGET_NAME vector_test)

include(GoogleTest)

set(TARGET_SOURCES
    "vector_test.cpp"
)

add_executable(${TARGET_NAME}
    ${TARGET_SOURCES}
)

target_link_libraries(${TARGET_NAME}
    GTest::gmock
    test_utils
    vector
)

gtest_discover_tests(${TARGET_NAME})
