include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        origin/main
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(doubly_linked_list_test)
add_subdirectory(test_utils)
