add_executable(mmz_test test.cpp)
target_link_libraries(mmz_test -lpthread -lm)
target_link_libraries(mmz_test ${MMZ_LIB})