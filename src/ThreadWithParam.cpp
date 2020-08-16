#include<iostream>
#include<thread>
#include<string>
#include<mutex>

std::mutex mu;

void shared_cout(std::string a_message, int id)
{
    mu.lock();
    std::cout << "message " << a_message << " id " << id << std::endl;
    mu.unlock();
}

void thread_function(std::string a_string)
{
    for (int i = 0; i < 1000; i++)
    {
        shared_cout(a_string, 0);
    }
}

int main()
{
    std::string s = "Testing Thread";
    std::thread t(&thread_function, s);
    for(int i = 0; i < 1000; i++)
    {
        shared_cout("Main thread", 0);
    }
    t.join();
    return 0;
}
