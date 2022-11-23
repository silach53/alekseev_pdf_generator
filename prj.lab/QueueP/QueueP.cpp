#include <QueueP/QueueP.h>
#include <algorithm>
#include <algorithm>
QueueP::Node::Node(int data, std::unique_ptr<Node> next) {
    this->data = data;
    this->next = std::move(next);
}
QueueP::QueueP() {
    this->len = 0;
    this->head = nullptr;
}
QueueP::QueueP(const std::vector<int>& v) {
    for (int elem : v) {
        push(elem);
    }
    this->len = v.size();
}
QueueP::QueueP(const int* mas, const int len) {
    for (int i = 0; i < len; ++i) {
        push(mas[i]);
    }
    this->len = len;
}
void QueueP::push(const int& data) {
    if (len) {
        if (data < head->data) {
            head = std::make_unique<Node>(data, std::move(head));
            ++len;
            return;
        }
        Node* counter = head.get();
        while ((counter->next != nullptr) && (counter->next->data < data)) {
            counter = counter->next.get();
        }
        std::unique_ptr<Node> item = std::make_unique<Node>(data, std::move(counter->next));
        counter->next = std::move(item);
    }
    else
        head = std::make_unique<Node>(data, nullptr);
    ++len;
}
void QueueP::pop() {
    if (len) {
        head = std::move(head->next);
        --len;
    }
}
const int& QueueP::top() const {
    if (len)
        return head->data;
    else
        throw QueueP::QueueOutOfRangeException();

}
bool QueueP::isEmpty() const {
    return len == 0;
}
QueueP::~QueueP() {
    while (!isEmpty())
        pop();
}