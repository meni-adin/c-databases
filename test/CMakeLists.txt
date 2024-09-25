include(fetch_content_wrapper)
fetch_content_wrapper(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        origin/main
)

enable_testing()

add_subdirectory(test_utils)
add_subdirectory(doubly_linked_list_test)
add_subdirectory(vector_test)
