enable_testing()

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE ${PROJECT_SOURCE_DIR}/test/catch/)

add_executable(unit_tests
	test_main.cpp
	sample_test.cpp
)

target_include_directories(unit_tests
	PUBLIC
        ${PROJECT_SOURCE_DIR}/src/
)

target_link_libraries(unit_tests
	catch
	game_lib
)

add_test(unit_tests unit_tests)

include(CTest)
add_custom_command(TARGET unit_tests
                   COMMENT "Run tests"
                   POST_BUILD COMMAND ctest ARGS --output-on-failure
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/
)
