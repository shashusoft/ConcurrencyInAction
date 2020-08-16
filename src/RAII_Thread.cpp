#include<iostream>
#include<thread>
class ThreadRAII
{
public:
    ThreadRAII(std::thread& a_thread)
        : m_thread(a_thread)
    {

    }

    ~ThreadRAII()
    {
        if(m_thread.joinable())
        {
            m_thread.detach();
            std::cout << "Thread is getting detached " << std::endl; 
        }
    }
private:
    std::thread& m_thread;    
};

void thread_function()
{
    for (int i = 0; i < 10000; i++)
    {
        std::cout << "i " << i << std::endl;
    }
}

int main(int argc, char* argv[])
{
    std::thread myThread(thread_function);
    ThreadRAII wrapperObj(myThread); 
    return 0; 
}
