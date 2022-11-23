add_library(Manager Manager.h Manager.cpp)
target_link_libraries(Manager QueueP)
add_executable(Manager_test Manager_test.cpp)
target_link_libraries(Manager_test Manager)