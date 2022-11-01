find_package(GTest QUIET)

if(NOT GTEST_FOUND)
    include(${CMAKE_SOURCE_DIR}/cmake/FetchGoogleTest.cmake)
endif()

add_executable(args_test src/args_test.cpp)
target_compile_features(args_test PRIVATE cxx_auto_type)
target_link_libraries(args_test gtest_main args)
target_include_directories(args_test PRIVATE include)

add_test(NAME args_test COMMAND args_test)