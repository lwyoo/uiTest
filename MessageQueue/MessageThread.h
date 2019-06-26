#ifndef __MESSAGE_THREAD_H__
#define __MESSAGE_THREAD_H__


#include <BlockingQueue.h>
#include <thread>


class MessageThread
{
public:
  enum class ThreadReturn {
      SUCCESS,
      ALREADY,
      NOT_AVAILABLE,
      MAX
  };

  enum class ThreadState {
      UNINITED,
      INITED,
      STARTED,
      RUNNING,
      TERMINATED,
      MAX
  };

  class IMsg
  {
  public:
    IMsg() {}
    virtual ~IMsg() {}
  };

public:
    MessageThread(std::function<int(IMsg*)> dispatcher, std::string name = "");
    virtual ~MessageThread();

    ThreadState getState() const;

    ThreadReturn start();
    ThreadReturn suspend();
    ThreadReturn resume();
    ThreadReturn exit();

    void postMessage(IMsg *msg);

    void setMsg(void * value);
    void* getMsg();

protected:
    int run();

private:
    std::string m_name;
    std::function<int(IMsg *)> m_dispatcher;
    ThreadState m_state;

    std::thread m_thread;
    std::mutex m_thread_mutex;
    std::condition_variable m_thread_cond;
    BlockingQueue<void> m_queue;

    void* m_msg;
};


#endif // __MESSAGE_THREAD_H__
