#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H


#include <mutex>
#include <queue>
#include <condition_variable>

#include <QQueue>
#include <QDebug>

#include <sstream>
#include <iostream>

#include "popuptypes.h"

template <class TYPE>
class BlockingQueue {
public:
    BlockingQueue() {
    }
    virtual ~BlockingQueue() {
    }

public:
    void wake_up() {
        m_cond.notify_one();
    }

    void enqueue(TYPE *msg) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_msgQueue.push_back(msg); // all data input( [Full/Middle] + [Mini] + [Utile] )


        m_cond.notify_one();
    }

    TYPE *dequeue() {
        // thread work ...
        std::lock_guard<std::mutex> lock(m_mutex);
        //        TYPE *msg = m_msgQueue.front();
        //        m_msgQueue.pop();

        TYPE *msg = m_msgQueue.front();
        m_msgQueue.pop_front();
        return msg;
    }
    //    TYPE *dequeue() {
    //        // thread work ...
    //        std::lock_guard<std::mutex> lock(m_mutex);
    //        //tuning
    ////        큐에 있는 정보를 확인
    ////        필여한 정보만 선별하기

    //        TYPE *msg = m_msgQueue.back();
    //        m_msgQueue.clear();
    //        return msg;
    //    }

    TYPE *obtain() {

        if (0 == m_msgQueue.size()) {
            std::unique_lock<std::mutex> uniqLock(m_mutex);
            m_cond.wait(uniqLock);
        }

        TYPE *msg = dequeue();

        //        std::stringstream strS;
        //        strS << msg;
        //        qDebug() << Q_FUNC_INFO << "MessageQueue index address" << strS.str().c_str();

        return msg;
    }

    int getSize() {
        return m_msgQueue.size();
    }

private:
    //    std::queue<TYPE *> m_msgQueue;
    QQueue<TYPE *> m_msgQueue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    int checkCount = 0;
};

#endif // BLOCKINGQUEUE_H
