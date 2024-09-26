include(fetch_content_wrapper)
fetch_content_wrapper(
    errors
    GIT_REPOSITORY https://github.com/meni-adin/c-errors.git
    GIT_TAG        origin/main
)

add_subdirectory(AVL_tree)
add_subdirectory(doubly_linked_list)
