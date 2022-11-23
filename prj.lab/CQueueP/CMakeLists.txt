add_library(CQueueP CQueueP.h CQueueP.C)

add_executable(CQueueP_test CQueueP_test.C)
target_link_libraries(CQueueP_test CQueueP)