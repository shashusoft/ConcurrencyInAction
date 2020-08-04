#include <iostream>
#include <thread>

#define PAGE_NO_18 TRUE
#define PAGE_NO_17 FALSE

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

struct func
{
	int& i;
	func(int& a_i)
		: i(a_i)
	{
		std::cout << "func ctor " << std::endl;
	}

	void operator()()
	{
		for (int j = 0; j < 1000000; j++)
		{
			doSomething(i);
			i = j;
		}
	}

	void doSomething(int a_par)
	{
		std::cout << "do something a_par " << a_par << std::endl;
	}
};

void oops()
{
	int someState = 0;
	func myFunc(someState);
	std::thread t(myFunc);
	t.join();
}

void parallelWorld()
{
	std::cout << "Parallel thread " << std::endl;
}

int main(int argc, char* argv[])
{
#if(PAGE_NO_17)
	std::thread t1(parallelWorld);
	std::thread t2{ParallelFunctor()};
	std::cout << "Main thread " << std::endl;
	t1.join();
	t2.join();
#endif
#if(PAGE_NO_18)
	oops();
#endif
}

