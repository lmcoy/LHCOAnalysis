
enable_testing()

include(ExternalProject)

set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)

ExternalProject_ADD(
    googletest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
    TIMEOUT 10
    CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
			   -Dgtest_force_shared_crt=ON
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

ExternalProject_Get_Property(googletest source_dir)
INCLUDE_DIRECTORIES(${source_dir}/include)


#  -------------
# | Vector3Test |
#  -------------
add_executable(Vector3Test ${PROJECT_SOURCE_DIR}/src/tests/math/vector3_test.cpp)
add_dependencies(Vector3Test googletest)

ExternalProject_Get_Property(googletest binary_dir)

target_link_libraries(Vector3Test
    ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a
	${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a
	math
	pthread)

add_test(Vector3Test Vector3Test)


#  ----------------
# | FourVectorTest |
#  ----------------
add_executable(FourVectorTest ${PROJECT_SOURCE_DIR}/src/tests/math/fourvector_test.cpp)
add_dependencies(FourVectorTest googletest)

ExternalProject_Get_Property(googletest binary_dir)

target_link_libraries(FourVectorTest
    ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a
	${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a
	math
	pthread)

add_test(FourVectorTest FourVectorTest)


