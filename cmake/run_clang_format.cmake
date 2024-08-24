# run_formatting.cmake

execute_process(
    COMMAND find ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/test
        -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \)
        -exec clang-format -style=file:clang_format.yml -i {} \;
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE clang_format_result
    OUTPUT_VARIABLE clang_format_output
    ERROR_VARIABLE clang_format_error
)

if(clang_format_result)
    message(WARNING "clang-format encountered an issue: ${clang_format_error}")
else()
    message(STATUS "clang-format completed successfully.")
endif()
