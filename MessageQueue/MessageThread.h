#ifndef MESSAGETHREAD_H
#define MESSAGETHREAD_H

#include <BlockingQueue.h>
#include <thread>


enum class MessageThreadReturn {
    SUCCESS,
    ALREADY,
    MAX
};

enum class MessageThreadState {
    UNINITED,
    INITED,
    STARTED,
    RUNNING,
    STOPPED,
    SUSPEND,
    TERMINATED,
    MAX
};


class MessageThread {
public:
    MessageThread(std::function<int(void *)> handler, std::string name = "");
    virtual ~MessageThread();

    void setState(const MessageThreadState state);
    MessageThreadState getState() const;

    MessageThreadReturn start();
    MessageThreadReturn resume();
    MessageThreadReturn stop();
    MessageThreadReturn exit();

    void putMessage(void *msg);

protected:
    int run();

private:
    std::string m_name;
    MessageThreadState m_state;
    std::thread m_thread;

    std::mutex m_thread_mutex;
    std::condition_variable m_thread_cond;

    BlockingQueue<void> m_queue;
    std::function<int(void *)> m_handler;
};

#endif // MESSAGETHREAD_H
