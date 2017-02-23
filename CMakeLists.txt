cmake_minimum_required(VERSION 3.5)
project(jconsole)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

# Require java and jni packages
find_package(java REQUIRED)
find_package(jni REQUIRED)

# Try finding curses or windows header
find_package(curses)
find_path(WIN32_INCLUDE_DIR windows.h)

if (CURSES_FOUND)
    message(STATUS "Using Curses")
    set(SOURCE_FILES src/native/jconsole_Console_Curses.c)
elseif(WIN32_INCLUDE_DIR)
    message(STATUS "Using WinAPI")
    set(SOURCE_FILES src/native/jconsole_Console_WinAPI.c)
else()
    message(FATAL_ERROR "Unable to find Curses or WinAPI")
endif()

# Compile java files to class files
add_custom_target(
    jconsole-javac
    COMMAND ${Java_JAVAC_EXECUTABLE} -d ${CMAKE_CURRENT_BINARY_DIR} jconsole/Console.java jconsole/test/ConsoleTest.java
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Generate java documentation
add_custom_target(
    jconsole-javadoc
    COMMAND ${Java_JAVADOC_EXECUTABLE} -d ${CMAKE_CURRENT_SOURCE_DIR}/doc jconsole
	DEPENDS jconsole-javac
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Generate headers for native library
add_custom_target(
    jconsole-javah
    COMMAND ${Java_JAVAH_EXECUTABLE} -jni -d src/native -classpath ${CMAKE_CURRENT_BINARY_DIR} jconsole.Console
	DEPENDS jconsole-javac
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Build jar from class files
add_custom_target(
    jconsole-jar
    COMMAND ${Java_JAR_EXECUTABLE} -cvf ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/jconsole.jar jconsole/Console.class
	DEPENDS jconsole-javac
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Execute test
add_custom_target(
	jconsole-run
    COMMAND ${Java_JAVA_EXECUTABLE} -Djava.library.path="${CMAKE_CURRENT_SOURCE_DIR}/lib" jconsole.test.ConsoleTest
    DEPENDS jconsole-javac
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Build native library, make sure to update javadoc and jar as well
add_library(jconsole SHARED ${SOURCE_FILES})
add_dependencies(jconsole jconsole-javah jconsole-jar jconsole-javadoc)

include_directories(${JNI_INCLUDE_DIRS})
target_link_libraries(jconsole ${JNI_LIBRARIES})

if (CURSES_FOUND)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries(jconsole ${CURSES_LIBRARIES})
elseif(WIN32_INCLUDE_DIR)
    include_directories(${WIN32_INCLUDE_DIR})
endif()
