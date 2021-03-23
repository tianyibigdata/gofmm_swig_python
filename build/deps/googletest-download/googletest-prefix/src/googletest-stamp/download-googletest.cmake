if(EXISTS "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest-download/googletest-prefix/src/release-1.8.0.zip")
  file("SHA256" "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest-download/googletest-prefix/src/release-1.8.0.zip" hash_value)
  if("x${hash_value}" STREQUAL "xf3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf")
    return()
  endif()
endif()
message(STATUS "downloading...
     src='https://github.com/google/googletest/archive/release-1.8.0.zip'
     dst='/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest-download/googletest-prefix/src/release-1.8.0.zip'
     timeout='none'")




file(DOWNLOAD
  "https://github.com/google/googletest/archive/release-1.8.0.zip"
  "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googletest-download/googletest-prefix/src/release-1.8.0.zip"
  SHOW_PROGRESS
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'https://github.com/google/googletest/archive/release-1.8.0.zip' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
