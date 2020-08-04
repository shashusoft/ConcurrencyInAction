#include <iostream>
#include <thread>

class ParallelFunctor
{
public:
	void operator()()
	{
		doSomething();
		doSomething_1();
	}

	void doSomething()
	{
		std::cout << "do Something " << std::endl;
	}

	void doSomething_1()
	{
		std::cout << "do Something 1 " << std::endl;
	}
};

void parallelWorld()
{
	std::cout << "Parallel thread " << std::endl;
}

int main(int argc, char* argv[])
{
	std::thread t1(parallelWorld);
	std::thread t2{ParallelFunctor()};
	std::cout << "Main thread " << std::endl;
	t1.join();
	t2.join();
}

