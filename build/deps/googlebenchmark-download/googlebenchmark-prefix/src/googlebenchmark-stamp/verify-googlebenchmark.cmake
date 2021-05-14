set(file "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googlebenchmark-download/googlebenchmark-prefix/src/v1.2.0.zip")
message(STATUS "verifying file...
     file='${file}'")
set(expect_value "cc463b28cb3701a35c0855fbcefb75b29068443f1952b64dd5f4f669272e95ea")
set(attempt 0)
set(succeeded 0)
while(${attempt} LESS 3 OR ${attempt} EQUAL 3 AND NOT ${succeeded})
  file(SHA256 "${file}" actual_value)
  if("${actual_value}" STREQUAL "${expect_value}")
    set(succeeded 1)
  elseif(${attempt} LESS 3)
    message(STATUS "SHA256 hash of ${file}
does not match expected value
  expected: ${expect_value}
    actual: ${actual_value}
Retrying download.
")
    file(REMOVE "${file}")
    execute_process(COMMAND ${CMAKE_COMMAND} -P "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googlebenchmark-download/googlebenchmark-prefix/src/googlebenchmark-stamp/download-googlebenchmark.cmake")
  endif()
  math(EXPR attempt "${attempt} + 1")
endwhile()

if(${succeeded})
  message(STATUS "verifying file... done")
else()
  message(FATAL_ERROR "error: SHA256 hash of
  ${file}
does not match expected value
  expected: ${expect_value}
    actual: ${actual_value}
")
endif()
