#include<QueueP/QueueP.h>
#include<CQueueP/CQueueP.h>
#include<unordered_map>
//singleton

typedef int hold;

class QueueP_manager {
public:
	static QueueP_manager& getInstance() {
		static QueueP_manager instance;
		return instance;
	}

	QueueP_manager(const QueueP_manager&) = delete;
	QueueP_manager& operator=(QueueP_manager const&) = delete;
	QueueP_manager(QueueP_manager&&) = delete;
	QueueP_manager& operator=(QueueP_manager&&) = delete;


	hold makeQueueP();
	void popQueueP(hold q);
	int topQueueP(hold q);
	void pushQueueP(hold q, int data);
	bool isEmptyQueueP(hold q);
	int getLengthQueueP(hold q);

private:
	QueueP_manager() = default;
	~QueueP_manager() = default;

	std::unordered_map<hold, QueueP> hold_m;

	void chek_holder(hold q);

	int32_t counter = 0;
};

hold QueueP_manager::makeQueueP() {
	counter++;
	hold_m[counter] = QueueP();
	return counter;
};
void QueueP_manager::popQueueP(hold q) {
	chek_holder(q);
	hold_m[q].pop();
};
int QueueP_manager::topQueueP(hold q) {
	chek_holder(q);
	return hold_m[q].top();
};
void QueueP_manager::pushQueueP(hold q, int data) {
	chek_holder(q);
	hold_m[q].push(data);
};
bool QueueP_manager::isEmptyQueueP(hold q) {
	chek_holder(q);
	return hold_m[q].isEmpty();
};
int QueueP_manager::getLengthQueueP(hold q) {
	chek_holder(q);
	return hold_m[q].getLength();
};

void QueueP_manager::chek_holder(hold q) {
	if (hold_m.find(q) == hold_m.end()) {
		throw "You are using unexicting hold";
	}
};