cmake_minimum_required(VERSION 3.12)
find_package(Eigen3 REQUIRED)

project(CxxRandomLogoWrapper)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}/deps")

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

# julia is used to retrieve the CxxWrap library paths
find_program(JULIA julia REQUIRED)

set(WRAPIT_VERBOSITY 1 CACHE STRING "Define verbosity level of the wrapit command. An integer, 0 for a quiet mode, 1 for a normal mode, higher numbers for a verbosity that increases with the number.")

# Find wrapit command (https://github.com/grasph/wrapit), used to generate
# the wrapper code.
find_program(WRAPIT wrapit DOC "wrapit command path")
#FIXME: use REQUIRE option of find_program when migrating to cmake >= 3.18
if(WRAPIT STREQUAL WRAPIT-NOTFOUND)
  message(FATAL_ERROR "Failed to find wrapit executable - aborting")
else()
  message("Found wrapit executable: ${WRAPIT}")
endif()

set(WRAPIT_WIT_FILE "${CMAKE_SOURCE_DIR}/CxxRandomLogoWrapper.wit")
message(STATUS "Wrapit configuration file: ${WRAPIT_WIT_FILE}")

execute_process(
  COMMAND ${WRAPIT} --get module_name ${WRAPIT_WIT_FILE}
  OUTPUT_STRIP_TRAILING_WHITESPACE
  OUTPUT_VARIABLE WRAPPER_MODULE
  RESULT_VARIABLE result)

if(NOT result EQUAL 0)
  message(FATAL_ERROR "Failed to retrieve the Julia module name parameter using the configuration file ${WRAPIT_WIT_FILE}.")
endif()


set(WRAPPER_LIB jl${WRAPPER_MODULE})
set(WRAPPER_JULIA_PACKAGE_DIR ${WRAPPER_MODULE})
set(WRAPPER_JULIA_PACKAGE_FILE ${WRAPPER_MODULE}.jl)

execute_process(
  COMMAND ${JULIA} "--project=${CMAKE_BINARY_DIR}" -e "import TOML; print(get(TOML.parse(open(\"${WRAPIT_WIT_FILE}\")), \"cxxwrap_version\", \"\"));"
  OUTPUT_STRIP_TRAILING_WHITESPACE
  OUTPUT_VARIABLE CXXWRAP_REQUESTED_VERSION
  RESULT_VARIABLE result
  )

if(NOT result EQUAL 0)
  message(FATAL_ERROR "Failed to parse ${WRAPIT_WIT_FILE}")
endif()

if("${CXXWRAP_REQUESTED_VERSION}" STREQUAL "")
execute_process(
    COMMAND ${JULIA} --project=${CMAKE_BINARY_DIR} -e "import Pkg; Pkg.add(\"CxxWrap\"); import CxxWrap; print(pkgversion(CxxWrap));"
  OUTPUT_VARIABLE CXXWRAP_INSTALLED_VERSION
  RESULT_VARIABLE result
)
  #if no CxxWrap version requirement was specified in the .wit file,
  #we align it to the version that was installed
  set(WRAPIT_OPT --add-cfg "cxxwrap_version=\"${CXXWRAP_INSTALLED_VERSION}\"")
  message(STATUS ${WRAPIT})
else()
execute_process(
    COMMAND ${JULIA} --project=${CMAKE_BINARY_DIR} -e "import Pkg; import CxxWrap; Pkg.add(name=\"CxxWrap\", version=\"${CXXWRAP_REQUESTED_VERSION}\"); Pkg.resolve(); print(pkgversion(CxxWrap));"
  OUTPUT_VARIABLE CXXWRAP_INSTALLED_VERSION
  RESULT_VARIABLE result)
endif()

if(NOT result EQUAL 0)
  message(FATAL_ERROR "Failed to install CxxWrap")
elseif("${CXXWRAP_REQUESTED_VERSION}" STREQUAL "")
  message(STATUS "CxxWrap version requested to be compatible with any version, using v${CXXWRAP_INSTALLED_VERSION}")
else()
  message(STATUS "CxxWrap version requested to be compatible with ${CXXWRAP_REQUESTED_VERSION}, using version: ${CXXWRAP_INSTALLED_VERSION}")
endif()

execute_process(
  COMMAND "${JULIA}" --project=${CMAKE_BINARY_DIR} -e "import CxxWrap; print(CxxWrap.prefix_path())"
  OUTPUT_STRIP_TRAILING_WHITESPACE
  OUTPUT_VARIABLE CXXWRAP_PREFIX
  RESULT_VARIABLE result)

if(NOT result EQUAL 0)
  message(FATAL_ERROR "Failed to retrieve CxxWrap library path")
else()
  message(STATUS "CxxWrap library path prefix: ${CXXWRAP_PREFIX}")
endif()

find_package(JlCxx PATHS ${CXXWRAP_PREFIX})

get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")


# Generate the wrapper code. This is done at configure time.
execute_process(
  COMMAND "${WRAPIT}" ${WRAPIT_OPT} -v "${WRAPIT_VERBOSITY}" --force --update --cmake --output-prefix "${CMAKE_BINARY_DIR}" "${WRAPIT_WIT_FILE}"
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  COMMAND_ECHO STDERR
  RESULT_VARIABLE result)

if(NOT result EQUAL 0)
  message(FATAL_ERROR "Execution of wrapit failed")
endif()

# File generated by wrapit that defines two variables, WRAPIT_PRODUCTS and
# WRAPIT_INPUT, with respectively the list of produced c++ code file and
# the list of files their contents on.
include("${CMAKE_BINARY_DIR}/wrapit.cmake")

# Require reconfiguration if one of the dependency of the contents produced
# by wrapit (itself executed at configure step) changed:
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${WRAPIT_DEPENDS}" "${WRAPIT_WIT_FILE}")

# Build the library.
add_library(${WRAPPER_LIB} SHARED ${WRAPIT_PRODUCTS} ../src/affine.cpp)
set_target_properties(${WRAPPER_LIB}
  PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${WRAPPER_JULIA_PACKAGE_DIR}/deps)
target_include_directories(${WRAPPER_LIB} PRIVATE ${CMAKE_SOURCE_DIR}/../src)
target_link_libraries(${WRAPPER_LIB} JlCxx::cxxwrap_julia Eigen3::Eigen)

# Installation paths:
set(WRAPPER_INSTALL_DIR "share/wrapit" CACHE FILEPATH "Installation path for the test modules")
install(FILES ${CMAKE_BINARY_DIR}/${WRAPPER_JULIA_PACKAGE_DIR}/src/${WRAPPER_JULIA_PACKAGE_FILE}
  DESTINATION ${WRAPPER_INSTALL_DIR}/${WRAPPER_JULIA_PACKAGE_DIR}/src)
install(TARGETS ${WRAPPER_LIB}
  LIBRARY DESTINATION  ${WRAPPER_INSTALL_DIR}/${WRAPPER_JULIA_PACKAGE_DIR}/deps
  ARCHIVE DESTINATION ${WRAPPER_INSTALL_DIR}/${WRAPPER_JULIA_PACKAGE_DIR}/deps
  RUNTIME DESTINATION ${WRAPPER_INSTALL_DIR}/${WRAPPER_JULIA_PACKAGE_DIR}/deps)

