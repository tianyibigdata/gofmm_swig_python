CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12 FATAL_ERROR)

PROJECT(googletest-download NONE)

INCLUDE(ExternalProject)
ExternalProject_Add(googletest
	URL https://github.com/google/googletest/archive/release-1.8.0.zip
	URL_HASH SHA256=f3ed3b58511efd272eb074a3a6d6fb79d7c2e6a0e374323d1e6bcbcc1ef141bf
	SOURCE_DIR "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/deps/googletest"
	BINARY_DIR "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/hmlp/hmlp-1/build/deps/googletest"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	TEST_COMMAND ""
)
