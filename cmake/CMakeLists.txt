cmake_minimum_required(VERSION 3.14)
project(RationalBigIntegerProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include(FetchContent)
include_directories(include)

# --- Fetch BigInteger_Complete ---
FetchContent_Declare(
  BigInteger
  GIT_REPOSITORY https://github.com/UofL-CSE-AutoGrader/BigInteger_Complete.git
  GIT_TAG        v1.0.0
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(BigInteger)

#----- Fetch Unit Tests -----
FetchContent_Declare(
  RationalUnitTests
  GIT_REPOSITORY https://github.com/UofL-CSE-AutoGrader/Rational_BigInteger_AutoGrader
  GIT_TAG        v1.0.1  
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(RationalUnitTests)

# Use all .cpp files in the tests directory 
file(GLOB RATIONAL_TEST_SOURCES "${rationalunittests_SOURCE_DIR}/tests/*.cpp")
add_executable(rational_tests ${RATIONAL_TEST_SOURCES})

target_link_libraries(rational_tests
    gtest_main
    rational_lib
)

include(GoogleTest)
enable_testing()
gtest_discover_tests(rational_tests)


# --- Fetch GoogleTest ---
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)



enable_testing()

# --- Build your Rational library ---
add_library(rational_lib
    src/Rational.cpp
)

target_link_libraries(rational_lib
    PUBLIC BigInteger::BigInteger
)

target_include_directories(rational_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# --- Main executable for manual testing ---
add_executable(rational_main src/main.cpp)
target_link_libraries(rational_main rational_lib)

