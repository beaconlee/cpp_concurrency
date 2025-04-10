#include <thread>
#include <iostream>

class SubThread
{
public:
  SubThread()
  {
    thread_ = std::make_unique<std::thread>(
        [this]()
        {
          while(running_)
          {
            std::cout << "cur age:" << age_ << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
          }
        });
    // 之前自己一直有一个错误的想法,就是这里必须要调用 detach,因为自己记得一个线程对象在销毁前,必须调用其detach或join
    /*
      在 C++ 中，std::thread 是一个管理线程的类。当你创建了一个 std::thread 对象时，它会关联一个底层线程。
      如果这个对象在销毁时仍然是“可加入的”（即 joinable），而你既没有调用 join() 也没有调用 detach()，
      程序会调用 std::terminate()，导致异常终止。
    */
    // 但是这里的 thread_ 是类的成员变量,在类被销毁前,它的成员是不会被销毁的
    // 所以这里不用立即调用其 detach 或 join 方法
    // thread_->detach();
  }

  virtual ~SubThread()
  {
    running_ = false;
    if(thread_ && thread_->joinable())
    {
      thread_->join();
    }
    std::cout << "销毁线程\n";
  }

private:
  int age_{17};
  std::unique_ptr<std::thread> thread_;
  std::atomic_bool running_{true};
};


int
main()
{
  {
    SubThread sub;
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  // 这样造成的结果是,当SubThread类被销毁时,线程任然在访问成员变量,可能导致程序崩溃
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return 0;
}