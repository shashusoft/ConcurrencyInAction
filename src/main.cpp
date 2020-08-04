#include <iostream>
#include <thread>

void parallelWorld()
{
	std::cout << "Parallel thread " << std::endl;
}

int main(int argc, char* argv[])
{
	std::thread t(parallelWorld);
	std::cout << "Main thread " << std::endl;
	t.join();
}

