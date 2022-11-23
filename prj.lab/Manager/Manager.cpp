#include <Manager/Manager.h>

extern "C" {
	hold makeQueueP() {
		return (QueueP_manager::getInstance()).makeQueueP();
	};
	void PopC(hold q) {
		return (QueueP_manager::getInstance()).popQueueP(q);
	}
	void PushC(hold q, int32_t value) {
		return (QueueP_manager::getInstance()).pushQueueP(q, value);
	}
	bool IsEmptyC(hold q) {
		return (QueueP_manager::getInstance()).isEmptyQueueP(q);
	}
	int32_t TopC(hold q) {
		return (QueueP_manager::getInstance()).topQueueP(q);
	}
}

/*
* 
* if i would like to rewrite it to erorr stile
ErrorCode IsEmptyC(hold q, int32_t * result)
	{
		return (QM::getInstance()).isEmptyQueueP(q, result);
	}
*/