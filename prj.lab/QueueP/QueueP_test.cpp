#include <QueueP/QueueP.h>
#include <iostream>
int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cout.tie(nullptr);
	//uint64_t p = (uint64_t)std::make_unique<QueueP>().get();
	//uint64_t* d(&p);
	//std::cout << p << std::endl;
	//std::cout << d << std::endl;
	//d = (uint64_t*)std::make_unique<QueueP>().get();
	//std::cout << d;

	QueueP a;
	for (size_t i = 0; i < 1000000; i++)
	{
		if (i%1000==0)
		{
			std::cout << i<<std::endl;
		}
		a.push(0);
	}
}