cmake_minimum_required(VERSION 3.15)
project(KeyMiningAlgorithm)

set(CMAKE_CXX_STANDARD 11)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# TODO: Prepared for boost testing
enable_testing()
set(Boost_ADDITIONAL_VERSIONS "1.XX" "1.XX.0")

# TODO: RSA Effiently gcd algorithm and it's test cases
add_library(EfficientlyGCD src/RSA/ProductTree.cpp src/RSA/RemainderTree.cpp src/RSA/EffientlyGcd.cpp)
target_include_directories(EfficientlyGCD
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
set_target_properties(EfficientlyGCD
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
target_link_libraries(EfficientlyGCD gmp boost_unit_test_framework)

add_executable(EfficientlyGCDBoostTest test/EfficientlyGCDBoostTest.cpp)
target_link_libraries(EfficientlyGCDBoostTest boost_unit_test_framework boost_timer EfficientlyGCD)
add_test(NAME EfficientlyGCDTest COMMAND EfficientlyGCDBoostTest)

# TODO: DSA private key cracker and it's test case
add_library(DSAPrivateCracker src/DSA/GetPrivate.cpp src/DSA/Cracker.cpp src/DSA/Signature.cpp)
