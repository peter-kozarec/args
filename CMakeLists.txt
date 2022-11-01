cmake_minimum_required(VERSION 3.19)

if(GIT_EXECUTABLE)
    get_filename_component(SRC_DIR ${SRC} DIRECTORY)
    # Generate a git-describe version string from Git repository tags
    execute_process(
            COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --match "v*"
            WORKING_DIRECTORY ${SRC_DIR}
            OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
            RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(NOT GIT_DESCRIBE_ERROR_CODE)
        set(ARGS_VERSION ${GIT_DESCRIBE_VERSION})
    endif()
endif()

if(NOT DEFINED ARGS_VERSION)
    set(ARGS_VERSION v0.0.1)
    message(WARNING "Failed to determine ARGS_VERSION from Git tags. Using default version \"${ARGS_VERSION}\".")
endif()

string(REPLACE v "" ARGS_VERSION_DEF ${ARGS_VERSION})

project(args VERSION ${ARGS_VERSION_DEF} LANGUAGES CXX)

##############################################
## Add library
add_library(args)

target_include_directories(args
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_sources(args PRIVATE src/args.cpp)
target_compile_options(args
        PRIVATE
            $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra -Wpedantic>)
target_compile_features(args PRIVATE cxx_std_17)

##############################################
# Installation instructions
include(GNUInstallDirs)
include(cmake/CPackConfig.cmake)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/args)

install(TARGETS args EXPORT args-targets LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

#This is required so that the exported target has the name JSONUtils and not jsonutils
set_target_properties(args PROPERTIES EXPORT_NAME args)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT
            args-targets
        FILE
            ArgsTargets.cmake
        DESTINATION
            ${INSTALL_CONFIGDIR})

##############################################
##Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/ArgsConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/ArgsConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/ArgsConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR})

#Install the config, configversion and custom find modules
install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/ArgsConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/ArgsConfigVersion.cmake
        DESTINATION
            ${INSTALL_CONFIGDIR})

##############################################
## Exporting from the build tree
export(EXPORT args-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/ArgsTargets.cmake)

#Register package in the User Package Registry
export(PACKAGE args)

##############################################
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