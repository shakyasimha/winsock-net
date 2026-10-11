cmake_minimum_required(VERSION 3.20)

project(winsock-http 
    VERSION 1.0.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Define executables
# add_executable(${PROJECT_NAME} src/main.c)
add_executable(server src/server.c)
add_executable(client src/client.c)

# Define shared include directories for all targets
foreach(target server client)
    target_include_directories(${target} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endforeach()

# Apply MSVC settings and link Winsock (ws2_32) for Windows network programming
foreach(target server client)
    if(MSVC) 
        target_compile_options(${target} PRIVATE
            /W4
            /WX 
            /permissive-
            /utf-8
        )

        target_compile_definitions(${target} PRIVATE
            _CRT_SECURE_NO_WARNINGS
        )
    endif()

    # Winsock requires linking ws2_32.lib on Windows
    if(WIN32)
        target_link_libraries(${target} PRIVATE ws2_32)
    endif()
endforeach()