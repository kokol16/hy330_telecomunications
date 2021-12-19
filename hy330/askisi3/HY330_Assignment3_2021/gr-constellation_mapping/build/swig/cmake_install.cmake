# Install script for directory: /home/gkokol/Documents/GitHub/hy330_telecomunications/hy330/askisi3/HY330_Assignment3_2021/gr-constellation_mapping/swig

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/constellation_mapping/_constellation_mapping_swig.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/constellation_mapping/_constellation_mapping_swig.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/constellation_mapping/_constellation_mapping_swig.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/constellation_mapping" TYPE MODULE FILES "/home/gkokol/Documents/GitHub/hy330_telecomunications/hy330/askisi3/HY330_Assignment3_2021/gr-constellation_mapping/build/swig/_constellation_mapping_swig.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/constellation_mapping/_constellation_mapping_swig.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/constellation_mapping/_constellation_mapping_swig.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/constellation_mapping/_constellation_mapping_swig.so"
         OLD_RPATH "/home/gkokol/Documents/GitHub/hy330_telecomunications/hy330/askisi3/HY330_Assignment3_2021/gr-constellation_mapping/build/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/constellation_mapping/_constellation_mapping_swig.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/constellation_mapping" TYPE FILE FILES "/home/gkokol/Documents/GitHub/hy330_telecomunications/hy330/askisi3/HY330_Assignment3_2021/gr-constellation_mapping/build/swig/constellation_mapping_swig.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages/constellation_mapping" TYPE FILE FILES
    "/home/gkokol/Documents/GitHub/hy330_telecomunications/hy330/askisi3/HY330_Assignment3_2021/gr-constellation_mapping/build/swig/constellation_mapping_swig.pyc"
    "/home/gkokol/Documents/GitHub/hy330_telecomunications/hy330/askisi3/HY330_Assignment3_2021/gr-constellation_mapping/build/swig/constellation_mapping_swig.pyo"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/constellation_mapping/constellation_mapping/swig" TYPE FILE FILES
    "/home/gkokol/Documents/GitHub/hy330_telecomunications/hy330/askisi3/HY330_Assignment3_2021/gr-constellation_mapping/swig/constellation_mapping_swig.i"
    "/home/gkokol/Documents/GitHub/hy330_telecomunications/hy330/askisi3/HY330_Assignment3_2021/gr-constellation_mapping/build/swig/constellation_mapping_swig_doc.i"
    )
endif()

