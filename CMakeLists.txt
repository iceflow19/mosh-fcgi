#============================================================
# Header/License goes here, blah blah blah
#============================================================

project (mosh-fcgi)
cmake_minimum_required (VERSION 2.8)

#============================================================
# Helper Macros
#============================================================

# Simplify appending additional flags to CMAKE_CXX_FLAGS.
macro(add_cxx_flags flags)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flags}")
endmacro()


# Allow removing of flags from CMAKE_CXX_FLAGS
# http://stackoverflow.com/a/18234926/211160
macro(remove_cxx_flag flag)
    string(REPLACE "${flag}" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endmacro()


# Helper for dumping lists, each item on a new line and not pushed together
# without spaces (which is the default behavior)
macro(dump_list message list)
    message(STATUS ${message})
    foreach(ITEM ${list})
        message(STATUS "  " ${ITEM})
    endforeach()
endmacro()


# Equivalent to list(REMOVE_ITEM list item) but checks to make sure the
# removal actually happened.  There must be an easier way to say this.
macro(ensure_remove_item list_name item)
    list(FIND "${list_name}" ${item} ITEM_INDEX)
    if(ITEM_INDEX EQUAL -1)
        message(FATAL_ERROR "Couldn't find item to remove " ${item})
    endif()
    list(REMOVE_AT "${list_name}" ${ITEM_INDEX})
    list(FIND "${list_name}" ${item} ITEM_INDEX)
    if(NOT ITEM_INDEX EQUAL -1)
        message(FATAL_ERROR "Removal failed of item " ${item})
    endif()
endmacro()

# Function to list all header files in the current directory, recursing into sub-directories
# HEADER_FILES - To be filled with the found header files
function(list_header_files HEADER_FILES)
    file(GLOB_RECURSE HEADER_FILES_TMP "*.h" "*.hpp" "*.inl" "*.pch")
    set(HEADER_FILES ${HEADER_FILES_TMP} PARENT_SCOPE)
endfunction()
 
# Function to list all source files in the current directory, recursing into sub-directories
# SOURCE_FILES - To be filled with the found source files
function(list_source_files SOURCE_FILES)
    file(GLOB_RECURSE SOURCE_FILES_TMP "*.c" "*.cpp")
    set(SOURCE_FILES ${SOURCE_FILES_TMP} PARENT_SCOPE)
endfunction()

# Function to setup some standard project items
# PROJECTNAME - The name of the project being setup
# TARGETDIR - The target directory for output files (relative to CMAKE_SOURCE_DIR)
function(setup_project_common PROJECTNAME TARGETDIR)
    # Set the Debug and Release names
    set_target_properties(
        ${PROJECTNAME} 
        PROPERTIES 
        DEBUG_OUTPUT_NAME ${PROJECTNAME}_d 
        RELEASE_OUTPUT_NAME ${PROJECTNAME}
    )
 
    # Add a post-build step for MSVC to copy the output to the target directory
    if(MSVC)
        add_custom_command(
            TARGET ${PROJECTNAME} 
            POST_BUILD COMMAND 
            copy \"$(TargetPath)\" \"${CMAKE_SOURCE_DIR}/${TARGETDIR}\"
        )
    endif()
 
    # Setup install to copy the built output to the target directory 
    # (for compilers that don't have post build steps)
    install(
        TARGETS ${PROJECTNAME}
        LIBRARY DESTINATION "${CMAKE_SOURCE_DIR}/${TARGETDIR}"
        ARCHIVE DESTINATION "${CMAKE_SOURCE_DIR}/${TARGETDIR}"
        RUNTIME DESTINATION "${CMAKE_SOURCE_DIR}/${TARGETDIR}"
    )
endfunction()
 
# Function to setup some project items for an executable or DLL
# PROJECTNAME - The name of the project being setup
function(setup_project_bin PROJECTNAME)
    setup_project_common(${PROJECTNAME} Bin)
endfunction()
 
# Function to setup some project items for static library
# PROJECTNAME - The name of the project being setup
function(setup_project_lib PROJECTNAME)
    setup_project_common(${PROJECTNAME} Lib)
endfunction()

#============================================================
# Set the CXX Flags
#============================================================

add_cxx_flags(-std=c++11)
add_cxx_flags(-Wno-documentation-unknown-command)
add_cxx_flags(-Wno-c++98-compat)
add_cxx_flags(-Wno-c++98-compat-pedantic)
add_cxx_flags(-O2)
add_cxx_flags(-march=native)
add_cxx_flags(-g)
add_cxx_flags(-ggdb)
add_cxx_flags(-MM)
add_cxx_flags(-MQ)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # using regular Clang or AppleClang
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  # using GCC
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
  # using Intel C++
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  # using Visual Studio C++
endif()

#============================================================
# cmake mosh-fcgi makefile
#============================================================

find_package(Boost)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_subdirectory(src)

add_library(LIBMOSH_FCGI STATIC $<TARGET_OBJECTS:CORE> $<TARGET_OBJECTS:HTTP> $<TARGET_OBJECTS:HTML>)

setup_project_lib(LIBMOSH_FCGI)
