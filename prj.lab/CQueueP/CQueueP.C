#include<Manager/Manager.h>

ErrorCode CreateQueueC(QueueHandler* queue);
ErrorCode CloneQueueC(QueueHandler source, QueueHandler* queue);
ErrorCode DestroyQueueC(QueueHandler queue);
ErrorCode PopC(QueueHandler queue);
ErrorCode PushC(QueueHandler queue, int32_t value);
ErrorCode IsEmptyC(QueueHandler queue, int32_t* result);
ErrorCode TopC(QueueHandler queue, int32_t* result);

ErrorCode CreateQueue(QueueHandler* queue)
{
	return CreateQueueC(queue);
}

ErrorCode CreateQueue(QueueHandler * queue)
{
	return CreateQueueC(queue);
}

ErrorCode CloneQueue(QueueHandler source, QueueHandler * queue)
{
	return CloneQueueC(source, queue);
}

ErrorCode DestroyQueue(QueueHandler queue)
{
	return DestroyQueueC(queue);
}

ErrorCode Pop(QueueHandler queue)
{
	return PopC(queue);
}

ErrorCode Push(QueueHandler queue, int32_t value)
{
	return PushC(queue, value);
}

ErrorCode IsEmpty(QueueHandler queue, int32_t * result)
{
	return IsEmptyC(queue, result);
}

ErrorCode Top(QueueHandler queue, int32_t * result)
{
	return TopC(queue, result);
}

const char* WhatIs(ErrorCode err);
