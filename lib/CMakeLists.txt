# Libraries
#static_library(common_libs)

include_dirs(.)

add_subdirectory(google)

# GTEST
if (CONFIG_UNIT_TEST)
	static_library(gtest)
	include_dirs(gtest/googletest/include)
	target_include_directories(gtest
		PRIVATE
		gtest/googletest
	)
	target_sources(gtest
		PRIVATE
		gtest/googletest/src/gtest-all.cc
	)
endif()