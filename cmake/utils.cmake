function(set_target_c_compiler_flags target)
    if((${CMAKE_C_COMPILER_ID} STREQUAL "AppleClang") OR (${CMAKE_C_COMPILER_ID} STREQUAL "GNU"))
        target_compile_options(${target} PRIVATE
            -Werror
            -Wall
            -Wextra
            -Wpedantic
            -Wvla
            -Wformat
        )
        if(${CMAKE_C_COMPILER_ID} STREQUAL "AppleClang")
        endif()
        if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
            target_compile_options(${target} PRIVATE
                -Wformat-signedness
            )
        endif()
    elseif(${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
        message(WARNING "Missing compiler flags for ${CMAKE_C_COMPILER_ID}")
    else()
        message(FATAL_ERROR "Unknown C compiler: ${CMAKE_C_COMPILER_ID}")
    endif()
endfunction()
