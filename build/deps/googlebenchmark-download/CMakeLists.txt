CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12 FATAL_ERROR)

PROJECT(googlebenchmark-download NONE)

INCLUDE(ExternalProject)
ExternalProject_Add(googlebenchmark
	URL https://github.com/google/benchmark/archive/v1.2.0.zip
	URL_HASH SHA256=cc463b28cb3701a35c0855fbcefb75b29068443f1952b64dd5f4f669272e95ea
	SOURCE_DIR "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/deps/googlebenchmark"
	BINARY_DIR "/home/getianyi/Documents/Master/Fall_2020/MasterThesis/severinPackage/hmlp-1/build/deps/googlebenchmark"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	TEST_COMMAND ""
)
