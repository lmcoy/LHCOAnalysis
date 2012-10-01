
add_subdirectory(lhco)
add_subdirectory(utils)
add_subdirectory(math)
add_subdirectory(tests)


add_executable(LHCOAnalysis LHCOAnalysis.cpp)
target_link_libraries(LHCOAnalysis math utils lhco)
