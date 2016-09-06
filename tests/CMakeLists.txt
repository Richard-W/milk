find_package(GTest)
if (GTEST_FOUND)
	add_executable(tests EXCLUDE_FROM_ALL
		"io/file.cpp"
		"io/file_ref.cpp"
		"parser/lexer.cpp"
	)
	target_link_libraries(tests PRIVATE
		milk
		${GTEST_BOTH_LIBRARIES}
	)
	add_custom_target(check
		COMMAND ./tests
	)
	add_dependencies(check tests)
endif()
