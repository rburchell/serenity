project(serenity C CXX ASM)
set(CMAKE_ASM_SOURCE_FILE_EXTENSIONS S)

function(serenity_flags target)
    target_include_directories("${target}" PUBLIC AK LibC Servers LibM)
    set(STANDARD_FLAGS -std=c++17 -Wno-sized-deallocation -fno-sized-deallocation)
    set(WARNING_FLAGS -Wextra -Wall -Wundef -Wcast-qual -Wwrite-strings -Wimplicit-fallthrough)
    set(FLAVOR_FLAGS -fno-exceptions -fno-rtti)
    target_compile_options("${target}" PUBLIC -MMD -MP ${STANDARD_FLAGS} ${WARNING_FLAGS} ${FLAVOR_FLAGS} -DDEBUG -DSANITIZE_PTRS -Os)
endfunction()

add_subdirectory(Kernel)
add_subdirectory(LibC)
