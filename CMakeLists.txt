CMAKE_MINIMUM_REQUIRED(VERSION 3.25)
PROJECT(Expressions VERSION 1.0.0 LANGUAGES CXX)

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

OPTION(BUILD_TESTS "Build tests" OFF)

INCLUDE(FetchContent)

INCLUDE_DIRECTORIES(lib/headers)

FILE(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lib/sources/*.cpp")
FILE(GLOB_RECURSE TESTS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc")

ADD_LIBRARY(expressions STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(expressions PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/headers>
        $<INSTALL_INTERFACE:include>
)

INSTALL(DIRECTORY lib/headers/ DESTINATION include)

INSTALL(TARGETS expressions
        EXPORT ExpressionsTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

INSTALL(EXPORT ExpressionsTargets
        FILE ExpressionsTargets.cmake
        NAMESPACE expressions::
        DESTINATION lib/cmake/Expressions
)

INCLUDE(CMakePackageConfigHelpers)
CONFIGURE_PACKAGE_CONFIG_FILE(
        cmake/ExpressionsConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/ExpressionsConfig.cmake
        INSTALL_DESTINATION lib/cmake/Expressions
)

INSTALL(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/ExpressionsConfig.cmake
        DESTINATION lib/cmake/Expressions
)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if (BUILD_TESTS)
    FETCHCONTENT_DECLARE(
            googletest
            URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip
    )
    SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FETCHCONTENT_MAKEAVAILABLE(googletest)
    ENABLE_TESTING()
    ADD_EXECUTABLE(tests ${TESTS} ${SOURCES})
    TARGET_LINK_LIBRARIES(tests GTest::gtest_main)
    INCLUDE(GoogleTest)
    GTEST_DISCOVER_TESTS(tests)
endif()

