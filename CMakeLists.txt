cmake_minimum_required(VERSION 3.5)
project(jconsole)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

find_package(java REQUIRED)
find_package(jni REQUIRED)
find_program(JNI_JAVAH NAMES javah)
find_package(curses)
find_path(WIN32_INCLUDE_DIR windows.h)

if (NOT JNI_JAVAH)
    message(FATAL_ERROR "Unable to find javah.")
endif()

if (CURSES_FOUND)
    message(STATUS "Using Curses.")
    set(SOURCE_FILES src/native/jconsole_Console_Curses.c)
elseif(WIN32_INCLUDE_DIR)
    message(STATUS "Using WinAPI.")
    set(SOURCE_FILES src/native/jconsole_Console_WinAPI.c)
else()
    message(FATAL_ERROR "Unable to find Curses or WinAPI.")
endif()

add_custom_target(
    jconsole-java-classes
    COMMAND ${JAVA_COMPILE} -d ${CMAKE_CURRENT_BINARY_DIR} jconsole/Console.java
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_custom_target(
    jconsole-java-doc
    COMMAND ${Java_JAVADOC_EXECUTABLE} -d ${CMAKE_CURRENT_SOURCE_DIR}/doc jconsole
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_custom_target(
    jconsole-javah
    COMMAND ${JNI_JAVAH} -jni -d src/native -classpath ${CMAKE_CURRENT_BINARY_DIR} jconsole.Console
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(
    jconsole-java-jar
    COMMAND ${JAVA_ARCHIVE} -cvf ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/jconsole.jar jconsole/Console.class
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_library(jconsole SHARED ${SOURCE_FILES})

include_directories(${JNI_INCLUDE_DIRS})
target_link_libraries(jconsole ${JNI_LIBRARIES})

if (CURSES_FOUND)
    include_directories(${CURSES_INCLUDE_DIRS})
    target_link_libraries(jconsole ${CURSES_LIBRARIES})
elseif(WIN32_INCLUDE_DIR)
    include_directories(${WIN32_INCLUDE_DIR})
endif()

add_dependencies(jconsole jconsole-javah)
add_dependencies(jconsole-javah jconsole-java-classes)
add_dependencies(jconsole-java-jar jconsole-java-classes)
add_dependencies(jconsole jconsole-java-jar)

add_dependencies(jconsole jconsole-java-doc)
add_dependencies(jconsole-java-doc jconsole-java-classes)