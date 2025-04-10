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
    thread_->detach();
  }

  virtual ~SubThread()
  {
    running_ = false;
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
  std::this_thread::sleep_for(std::chrono::seconds(10));
  return 0;
}