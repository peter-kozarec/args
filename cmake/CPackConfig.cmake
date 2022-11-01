################################################################################
# Configure CPack
################################################################################
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME args)
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README.md)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "args")

if(WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full UNIX paths properly.
    # Make sure there is at least one set of four backlashes
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} args")
    set(CPACK_NSIS_CONTACT "peter.kozarec@outlook.sk")
    set(CPACK_NSIS_MODIFY_PATH ON)
else()
    set(CPACK_STRIP_FILES "bin/args")
    set(CPACK_SOURCE_STRIP_FILES "")
endif()

# Don't split into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# Must be last
include(CPack)