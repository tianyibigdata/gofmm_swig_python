if(EXISTS "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googlebenchmark-download/googlebenchmark-prefix/src/v1.2.0.zip")
  file("SHA256" "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googlebenchmark-download/googlebenchmark-prefix/src/v1.2.0.zip" hash_value)
  if("x${hash_value}" STREQUAL "xcc463b28cb3701a35c0855fbcefb75b29068443f1952b64dd5f4f669272e95ea")
    return()
  endif()
endif()
message(STATUS "downloading...
     src='https://github.com/google/benchmark/archive/v1.2.0.zip'
     dst='/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googlebenchmark-download/googlebenchmark-prefix/src/v1.2.0.zip'
     timeout='none'")




file(DOWNLOAD
  "https://github.com/google/benchmark/archive/v1.2.0.zip"
  "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googlebenchmark-download/googlebenchmark-prefix/src/v1.2.0.zip"
  SHOW_PROGRESS
  # no TIMEOUT
  STATUS status
  LOG log)

list(GET status 0 status_code)
list(GET status 1 status_string)

if(NOT status_code EQUAL 0)
  message(FATAL_ERROR "error: downloading 'https://github.com/google/benchmark/archive/v1.2.0.zip' failed
  status_code: ${status_code}
  status_string: ${status_string}
  log: ${log}
")
endif()

message(STATUS "downloading... done")
