#ifndef __CCOS_BLOCKING_QUEUE_H__
#define __CCOS_BLOCKING_QUEUE_H__


#include <mutex>
#include <queue>
#include <condition_variable>


template <class TYPE>
class BlockingQueue {
public:
    BlockingQueue()
    : m_suspend(false) // non suspend mode
    , m_bypass(false)  // non bypass mode
    {
    }
    virtual ~BlockingQueue() {
        // TODO : clear queue
    }

public:
    void wake_up() {
        m_cond.notify_one();
    }

    // set BlockingQueue in bypass mode
    // : dequeue() would not wait even if in suspend mode
    void setBypass(bool bBypassMode) { // it wake up dequeue() from waiting
        std::lock_guard<std::mutex> lock(m_mutex);
        m_bypass = bBypassMode;
        m_cond.notify_one();
    }

    // set BlockingQueue in suspend mode
    // : dequeue() will wait once even if empty
    // : dequeue() will not retrieve message from the queue
    void setSuspendMode(bool bSuspendMode) { // it wake up dequeue() from waiting
        std::lock_guard<std::mutex> lock(m_mutex);
        m_suspend = bSuspendMode;
        m_cond.notify_one();
    }

    void enqueue(TYPE *msg) {
        if (msg != nullptr) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_msgQueue.push(msg);
            m_cond.notify_one();
        }
    }

    TYPE * dequeue() {
        std::unique_lock<std::mutex> uniqLock(m_mutex);

        TYPE *msg = nullptr;
        if (!m_bypass)
        {
            if (m_suspend || m_msgQueue.empty()) {
                m_cond.wait(uniqLock);
            }
        }
        if (!m_suspend && !m_msgQueue.empty()) {
            msg = m_msgQueue.front();
            m_msgQueue.pop();
        }
        return msg;
    }

    int getSize() {
        std::unique_lock<std::mutex> uniqLock(m_mutex);
        return m_msgQueue.size();
    }

private:
    std::queue<TYPE *> m_msgQueue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    bool m_suspend;
    bool m_bypass;
};


#endif // __CCOS_BLOCKING_QUE_H__
