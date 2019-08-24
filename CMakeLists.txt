cmake_minimum_required(VERSION 3.8)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION_BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION_BUILD 0)
endif()

project(Allocator VERSION 0.0.${VERSION_BUILD})

add_executable(
Allocator
src/main.cpp
src/smart_dynamic_allocator.h
src/dynamic_allocator.h
src/static_allocator.h
src/smart_queue.h
)

set_property(TARGET Allocator PROPERTY CXX_STANDARD 17)

set_target_properties(Allocator PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(Allocator
    PRIVATE "${CMAKE_BINARY_DIR}" src/
)

if (MSVC)
    target_compile_options(Allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(Allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS Allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT askimarhond@gmail.com)

include(CPack)
