cmake_minimum_required(VERSION 3.20)

project(winsock-http 
    VERSION 1.0.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(${PROJECT_NAME}
    src/main.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC) 
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /WX 
        /permissive-
        /utf-8
    )

    target_compile_definitions(${PROJECT_NAME} PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()