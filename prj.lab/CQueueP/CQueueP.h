#ifdef __cplusplus
#include <cstdint>
using std::uint64_t;
using std::int32_t;
extern "C" {
#else
#include <stdint.h>
#endif

typedef enum {
    kGood = 0,   // all right
    kHandlerError = 1, // bad handler
    kOutOfRange = 2    // queue is empty
} ErrorCode;

typedef uint64_t QueueHandler;
const uint64_t EmptyHandler = ~0ULL;
static QueueHandler Handle = 0;
ErrorCode CreateQueue(QueueHandler* queue);

ErrorCode CloneQueue(QueueHandler source, QueueHandler* queue);

ErrorCode DestroyQueue(QueueHandler queue);

ErrorCode Pop(QueueHandler queue);

ErrorCode Push(QueueHandler queue, int32_t value);

ErrorCode IsEmpty(QueueHandler queue, int32_t* result);

ErrorCode Top(QueueHandler queue, int32_t* result);

const char* WhatIs(ErrorCode err);

#ifdef __cplusplus
};
#endif
