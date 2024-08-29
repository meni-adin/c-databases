include(FetchContent)
FetchContent_Declare(
  errors
  GIT_REPOSITORY https://github.com/meni-adin/c-errors.git
  GIT_TAG        origin/main
)
FetchContent_MakeAvailable(errors)

add_subdirectory(doubly_linked_list)
