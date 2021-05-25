# Install script for directory: /home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/runtime/thirdparty/utfcpp/extern/gtest/googletest

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/runtime/thirdparty/utfcpp/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/GTest/GTestTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/GTest/GTestTargets.cmake"
         "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-build/extern/gtest/googlemock/gtest/CMakeFiles/Export/lib/cmake/GTest/GTestTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/GTest/GTestTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/GTest/GTestTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/GTest" TYPE FILE FILES "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-build/extern/gtest/googlemock/gtest/CMakeFiles/Export/lib/cmake/GTest/GTestTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/GTest" TYPE FILE FILES "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-build/extern/gtest/googlemock/gtest/CMakeFiles/Export/lib/cmake/GTest/GTestTargets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/GTest" TYPE FILE FILES
    "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-build/extern/gtest/googlemock/gtest/generated/GTestConfigVersion.cmake"
    "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-build/extern/gtest/googlemock/gtest/generated/GTestConfig.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/runtime/thirdparty/utfcpp/extern/gtest/googletest/include/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-build/extern/gtest/googlemock/gtest/libgtest.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-build/extern/gtest/googlemock/gtest/libgtest_main.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-build/extern/gtest/googlemock/gtest/generated/gtest.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/dies/NetBeansProjects/excel_ya/YA_DIPLOMA_EXCEL/antlr4_runtime/runtime/utfcpp-prefix/src/utfcpp-build/extern/gtest/googlemock/gtest/generated/gtest_main.pc")
endif()

