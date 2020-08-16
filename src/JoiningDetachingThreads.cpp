#include<iostream>
#include<thread>
#include<algorithm>
#include<vector>
#include<functional>
class WorkerThread
{
public:
    void operator()()
    {
        std::cout << "Worker thread " << std::this_thread::get_id() << "is Executing " << std::endl;
    }
};
int main()
{
    std::vector<std::thread> threadList;
    for (int i = 0; i < 10; i++)
    {
        threadList.push_back(std::thread(WorkerThread()));
    }
    std::cout << "Wait for all worker thread to Finish " << std::endl;
    std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
    std::cout << "Exiting from main thread " << std::endl;
    return 0;
} 

