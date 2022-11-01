cmake_minimum_required(VERSION 3.19)
project(args VERSION 1.0.0 LANGUAGES CXX)

## Add library
add_library(args)

target_include_directories(args
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_sources(args PRIVATE src/args.cpp)
target_compile_options(args PRIVATE -Wall -Wextra -Wpedantic)
target_compile_features(args PRIVATE cxx_std_17)

set_target_properties(args PROPERTIES EXPORT_NAME args)

# Installation instructions
include(GNUInstallDirs)
include(cmake/CPackConfig.cmake)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/args)

install(TARGETS args EXPORT args-targets LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT args-targets FILE ArgsTargets.cmake DESTINATION ${INSTALL_CONFIGDIR})

##Create a ArgsConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/ArgsConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/ArgsConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/ArgsConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR})

#Install the config, version and custom find modules
install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/ArgsConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/ArgsConfigVersion.cmake
        DESTINATION
            ${INSTALL_CONFIGDIR})

## Exporting from the build tree
export(EXPORT args-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/ArgsTargets.cmake)

#Register package in the User Package Registry
export(PACKAGE args)

## Add test
enable_testing()

# Replace install() to do-nothing macro.
macro(install)
endmacro()
add_subdirectory(tests)
# Restore original install() behavior.
macro(install)
    _install(${ARGN})
endmacro()