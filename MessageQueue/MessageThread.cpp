#include <MessageThread.h>
#include <QDebug>


MessageThread::MessageThread(std::function<int(void *)> handler, std::string name) {
    m_name    = name;
    m_handler = handler;
    setState(MessageThreadState::UNINITED);
    //    m_state   = MessageThreadState::UNINITED;
}

MessageThread::~MessageThread() {
    exit();
    m_thread.join();
}

void MessageThread::setState(const MessageThreadState state) {

    m_state = state;

    QString temp;
    switch (m_state) {
    case MessageThreadState::UNINITED  : temp = "UNINITED,  " ;break;
    case MessageThreadState::INITED    : temp = "INITED,    " ;break;
    case MessageThreadState::STARTED   : temp = "STARTED,   " ;break;
    case MessageThreadState::RUNNING   : temp = "RUNNING,   " ;break;
    case MessageThreadState::STOPPED   : temp = "STOPPED,   " ;break;
    case MessageThreadState::SUSPEND   : temp = "SUSPEND,   " ;break;
    case MessageThreadState::TERMINATED: temp = "TERMINATED," ;break;
    case MessageThreadState::MAX       : temp = "MAX        " ;break;

    }
    //    qDebug() << Q_FUNC_INFO << "state : " << temp;
}

MessageThreadState MessageThread::getState() const {
    return m_state;
}

MessageThreadReturn MessageThread::start() {
    MessageThreadReturn ret = MessageThreadReturn::ALREADY;
    std::lock_guard<std::mutex> lock(m_thread_mutex);
    if (MessageThreadState::UNINITED == m_state) {
        m_thread  = std::thread([=]{run();});
        setState(MessageThreadState::STARTED);
        //        m_state = MessageThreadState::STARTED;
        ret = MessageThreadReturn::SUCCESS;
    }

    return ret;
}

MessageThreadReturn MessageThread::resume() {
    MessageThreadReturn ret = MessageThreadReturn::ALREADY;
    std::lock_guard<std::mutex> lock(m_thread_mutex);
    if (MessageThreadState::RUNNING != m_state) {
        setState(MessageThreadState::RUNNING);
        //        m_state = MessageThreadState::RUNNING;
        m_thread_cond.notify_one();
        ret = MessageThreadReturn::SUCCESS;
    } else {
        //        m_state = MessageThreadState::SUSPEND;
        ////        m_thread_cond.notify_one();
        //        ret = MessageThreadReturn::SUCCESS;
    }

    return ret;
}

MessageThreadReturn MessageThread::stop() {
    MessageThreadReturn ret = MessageThreadReturn::ALREADY;
    std::lock_guard<std::mutex> lock(m_thread_mutex);
    if (MessageThreadState::STOPPED != m_state) {
        setState(MessageThreadState::STOPPED);
        //        m_state = MessageThreadState::STOPPED;
        ret = MessageThreadReturn::SUCCESS;
    }

    return ret;
}

MessageThreadReturn MessageThread::exit() {
    MessageThreadReturn ret = MessageThreadReturn::ALREADY;
    m_queue.wake_up();
    std::lock_guard<std::mutex> lock(m_thread_mutex);
    if (MessageThreadState::TERMINATED != m_state) {
        setState(MessageThreadState::TERMINATED);
        //        m_state = MessageThreadState::TERMINATED;
        ret = MessageThreadReturn::SUCCESS;
        m_thread_cond.notify_one();
    }

    return ret;
}

void MessageThread::putMessage(void *msg) {
    m_queue.enqueue(msg);
}


int MessageThread::run() {

    void *msg = nullptr;
    int res = 0;

    //    m_state = MessageThreadState::RUNNING;
    setState(MessageThreadState::RUNNING);

    while (MessageThreadState::TERMINATED != m_state) {
        msg = m_queue.obtain();

        if (MessageThreadState::RUNNING != m_state) {
            std::unique_lock<std::mutex> lock(m_thread_mutex);
            m_thread_cond.wait(lock);
            setState(MessageThreadState::RUNNING);
            lock.unlock();
        }

        if (nullptr == msg) {
            // critical ERROR log
            continue;
        }

        res = m_handler(msg);
        if (0 != res) {
            // ERROR log
        }
    }

    return res;
}