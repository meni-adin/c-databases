function(set_target_c_compiler_flags target)
    if((CMAKE_C_COMPILER_ID STREQUAL "AppleClang") OR (CMAKE_C_COMPILER_ID STREQUAL "GNU"))
        target_compile_options(${target} PRIVATE
            -Werror
            -Wall
            -Wextra
            -Wpedantic
            -Wvla
            -Wformat
            # -Wshadow  # turned off as it may be useful in macros
            -Wconversion
            -Wnull-dereference
            -Wdouble-promotion
            -Wimplicit-fallthrough
        )
        if(CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
        endif()
        if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
            target_compile_options(${target} PRIVATE
                # -Wformat-signedness  # currently fails clang-tidy using compile_commands.json on Ubuntu
            )
        endif()
    elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE
            /Wall
            /WX
        )
else()
        message(FATAL_ERROR "Unknown C compiler: ${CMAKE_C_COMPILER_ID}")
    endif()
endfunction()
