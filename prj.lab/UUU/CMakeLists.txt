add_library(UUU UUU.h UUU.cpp)

add_executable(UUU_test UUU_test.cpp)
target_link_libraries(UUU_test UUU)
