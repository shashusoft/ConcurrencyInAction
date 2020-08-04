#include <iostream>
#include <thread>

#define PAGE_NO_18 0
#define PAGE_NO_17 0
#define PAGE_NO_20 1

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
			doSomething();
			i = j;
		}
	}

	void oufOfThreadCall()
	{
		std::cout << "out of thread call " << std::endl;
	}

	void doSomething()
	{
		std::cout << "do something a_par " << i << std::endl;
	}
};

void oops()
{
	std::cout << "oops()  " << std::endl;
	int someState = 0;
	func myFunc(someState);
	std::thread t(myFunc);
	t.detach();
	myFunc.oufOfThreadCall();
	myFunc.doSomething();
}

void exceptionCall()
{
	std::cout << "exception call " << std::endl;
	int someState = 0;
	func myFunc(someState);
	std::thread t(myFunc);
	try
	{
		throw 0;
	}
	catch(std::exception& e)
	{
		std::cout << "exception occured " << e.what() << std::endl;
		t.join();
		throw;
	}	
	t.join();
}

void doSomebackgroundWork()
{
	std::cout << "doing nothing " << std::endl;
}

class ThreadGuard
{
public:
	explicit ThreadGuard(std::thread& a_t)
		: t(a_t)
	{
		std::cout << "Thread guard " << std::endl;
	}

	~ThreadGuard()
	{
		std::cout << "destructor von thread guard " << std::endl;
		if (t.joinable())
		{
			t.join();
		}
	}

	ThreadGuard(ThreadGuard const&) = delete;
	ThreadGuard& operator=(ThreadGuard const&) = delete;
private:
	std::thread& t;
};

void parallelWorld()
{
	std::cout << "Parallel thread " << std::endl;
}

int main(int argc, char* argv[])
{
	if(PAGE_NO_17)
	{
		std::thread t1(parallelWorld);
		std::thread t2{ParallelFunctor()};
		std::cout << "Main thread " << std::endl;
		t1.join();
		t2.join();
	}
	if(PAGE_NO_18) 
	{
		std::thread t3(exceptionCall);
		ThreadGuard myGuard(t3);
	}
	if (PAGE_NO_20)
	{
		std::thread t4(doSomebackgroundWork);
		if (t4.joinable()) t4.detach();
	}
}

