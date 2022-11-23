add_library(QueueP QueueP.h QueueP.cpp)

add_executable(QueueP_test QueueP_test.cpp)
target_link_libraries(QueueP_test QueueP)