# Testsuite
target_sources(${TARGET_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/gtest_main.cc
	${CMAKE_CURRENT_SOURCE_DIR}/command_unit_test.cc
)
