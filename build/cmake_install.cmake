# Install script for directory: /home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  execute_process(COMMAND virtualenv --system-site-packages /home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/python)
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/libhmlp.so")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/include/hmlp.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/include")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/distributed_fast_matvec_solver")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/custom_kernel")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/test_mpigofmm")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/distributed_matrix")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/nearest_neighbor")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/kij_interface_inheritance")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/distributed_nearest_neighbor")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/test_gofmm")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/fast_matvec_solver")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/example/sbatch_gofmm_userdefine.sh"
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/example/sbatch_gofmm_chao.sh"
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/example/run_gofmm_userdefined.sh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/artifact_sc18gofmm")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/artifact/sc18gofmm/run_artifact_sc18gofmm_default.sh"
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/artifact/sc18gofmm/sbatch_artifact_sc18gofmm_default.sh"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/datasets" TYPE FILE FILES
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/artifact/sc18gofmm/datasets/calc2_functions.m"
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/artifact/sc18gofmm/datasets/calc2.m"
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/artifact/sc18gofmm/datasets/savelargematrix.m"
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/artifact/sc18gofmm/datasets/calc1.m"
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/artifact/sc18gofmm/datasets/calc3_functions.m"
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/artifact/sc18gofmm/datasets/spdmatrices.m"
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/artifact/sc18gofmm/datasets/calc.m"
    "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/artifact/sc18gofmm/datasets/calc3.m"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/CMakeFiles/CMakeRelink.dir/unitTest")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/deps/googletest/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
