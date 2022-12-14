cmake_minimum_required(VERSION 3.20)

project(
  Metamorphosis
  VERSION 1.0
  DESCRIPTION "Metamorphosis, a short film; Powered by Bresenham, a rasterization algorithm."
  HOMEPAGE_URL "https://github.com/the-hyp0cr1t3/metamorphosis"
  LANGUAGES CXX C)


#---------------------------
# CMake modules
#---------------------------

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(in-source-guard)
include(variables)

if(PROJECT_IS_TOP_LEVEL)
  include(GNUInstallDirs)
  include(CTest)
endif()

include(FetchContent)
include(LinkTimeOptimization)
include(SupportRPATH)
include(InstallBasicPackageFiles)
include(AddUninstallTarget)

if(${PROJECT_NAME}_DEVELOPER_MODE)
  include(ClangFormat)
  include(ClangTidy)
endif()

if(BUILD_ONLY_DOCS)
  add_subdirectory(docs)
  return()
endif()

#---------------------------
# Build type
#---------------------------

if(PROJECT_IS_TOP_LEVEL)
  if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none were specified.")
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Release")
  endif()
endif()


#---------------------------
# CMake options
#---------------------------

if(PROJECT_IS_TOP_LEVEL)

  # Place all executables in build/bin/
  if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/bin)
  endif()

  # Place all shared libs in build/lib/
  if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/lib)
  endif()

  # Place all static libs in build/lib/
  if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/lib)
  endif()

  # Build position independent code
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)

  # Required on Windows to build shared libraries
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

  # Avoid config naming clashes in install directories
  if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "d")
  endif()

endif()


#---------------------------
# C++ options
#---------------------------

if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard (11/14/17/20/...)")
  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  set(CMAKE_CXX_FLAGS_DEBUG "-g")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3")

endif()


#---------------------------
# Dependencies
#---------------------------

add_subdirectory(extern)

#---------------------------
# Sources
#---------------------------

add_subdirectory(src)

#---------------------------
# Examples
#---------------------------

if(${PROJECT_NAME}_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

#---------------------------
# Documentation
#---------------------------

if(${PROJECT_NAME}_BUILD_DOCS)
  add_subdirectory(docs)
endif()


#---------------------------
# Install
#---------------------------

# Enable RPATH support for installed binaries and libraries
add_install_rpath_support(
  BIN_DIRS "${CMAKE_INSTALL_FULL_BINDIR}"
  LIB_DIRS "${CMAKE_INSTALL_FULL_LIBDIR}"
  INSTALL_NAME_DIR "${CMAKE_INSTALL_FULL_LIBDIR}"
  USE_LINK_PATH)

install_basic_package_files(Bresenham
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
  EXPORT Bresenham
  VARS_PREFIX Bresenham
  NAMESPACE Bresenham::
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  COMPONENT Bresenham_Development
  FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hpp"
    PATTERN "*.hxx"
)


#---------------------------
# Packaging
#---------------------------

set(CPACK_PACKAGE_NAME Bresenham)
set(CPACK_PACKAGE_VENDOR "the-hyp0cr1t3")
set(CPACK_PACKAGE_CONTACT "ghriday.bits@gmail.com")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "the-hyp0cr1t3")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_VERBATIM_VARIABLES YES)
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/packages)
set(CPACK_SOURCE_IGNORE_FILES /\\.git.* /\\.git/ /\\.github/ /build/)

# Source generators
set(CPACK_SOURCE_GENERATOR ZIP TGZ)

# Binary generators
if(WIN32)
  set(CPACK_GENERATOR ZIP WIX)
elseif(APPLE)
  set(CPACK_GENERATOR TGZ productbuild)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CPACK_GENERATOR TGZ DEB RPM)
else()
  set(CPACK_GENERATOR TGZ)
endif()

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()