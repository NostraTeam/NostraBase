cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

find_package("NostraBuild")

nostra_project("NostraBase" "nba"
    VERSION     "1.0.0.0"
    DESCRIPTION "A library that provides platform detection, versioning and other basic utilities."
    LANGUAGES   "CXX"
    )

set(NBA_Base_SOURCES "src/base.cpp") # Source files should be added here

nostra_add_library(Base ${NBA_Base_SOURCES})
add_library(Nostra::Base ALIAS Base)

if(ON)
    configure_file("cmake/config.h.in" "${CMAKE_CURRENT_BINARY_DIR}/include/nostra/base/config.h")
endif()

target_include_directories(Base
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>" # For additional, configured files
		"$<INSTALL_INTERFACE:include>")

nostra_get_compiler_id(NOSTRA_LANGUAGE_ID)

if("${NOSTRA_LANGUAGE_ID}" STREQUAL "MSVC")
    target_compile_options(Base
        PRIVATE
            "/wd4251")
elseif("${NOSTRA_LANGUAGE_ID}" STREQUAL "AppleClang")
    target_compile_options(Base
        PRIVATE
            "-Wall"
            "-Wextra"
            "-Wpedantic"
            "-fPIC")
elseif("${NOSTRA_LANGUAGE_ID}" STREQUAL "Clang")
    target_compile_options(Base
        PRIVATE
            "-Wall"
            "-Wextra"
            "-Wpedantic"
            "-fPIC")
elseif("${NOSTRA_LANGUAGE_ID}" STREQUAL "GNU")
    target_compile_options(Base
        PRIVATE
            "-Wall"
            "-Wextra"
            "-Wpedantic"
            "-fPIC")
else()
    message(WARNING "The compiler with the ID '${NOSTRA_LANGUAGE_ID}' may not be supported.")
endif()
  
nostra_generate_export_header(Base OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/include/nostra/base")

install(TARGETS Base EXPORT ${PROJECT_EXPORT}
	RUNTIME 
		DESTINATION "bin"
	LIBRARY 
		DESTINATION "lib"
	ARCHIVE	
		DESTINATION "lib/static"
		COMPONENT "Develop"
	INCLUDES 
		DESTINATION "include")

install(DIRECTORY "include" 
	DESTINATION 
		"."
	COMPONENT
		"Develop")
		
# Install the additionally configured file(s)
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/" 
	DESTINATION 
		"include"
	COMPONENT
		"Develop")



nostra_generate_doc()

# Tests start
nostra_add_cpp_test(
    TEST_NAME "version"
    TEST_TYPE "wt"
    TEST_TARGET "Nostra::Base"
    NUMBER "1"
)
# Tests end



# Examples start
    # Add examples here...
# Examples end



install(FILES "README.md" 
	DESTINATION	
		".")

if(EXISTS "LICENSE")
    install(FILES "LICENSE"
    	DESTINATION	
            ".")
endif()


        
include(CMakePackageConfigHelpers)

write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/NostraBaseConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY AnyNewerVersion)

export(EXPORT ${PROJECT_EXPORT}
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_EXPORT}.cmake"
    NAMESPACE Nostra::)

configure_file("cmake/NostraBaseConfig.cmake.in" "NostraBaseConfig.cmake" @ONLY)

set(CONFIG_PACKAGE_LOCATION "lib/cmake/NostraBase")

install(EXPORT ${PROJECT_EXPORT}
    FILE
        "${PROJECT_EXPORT}.cmake"
    NAMESPACE
        Nostra::
    DESTINATION
        "share/NostraBase")

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/NostraBaseConfig.cmake"
  DESTINATION
    "share/NostraBase"
  COMPONENT
    "Develop")

configure_file("cmake/CPackConfig.cmake.in" "cmake/CPackConfig.cmake" @ONLY)

include("${CMAKE_CURRENT_BINARY_DIR}/cmake/CPackConfig.cmake")

include(CPack)
