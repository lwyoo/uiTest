#include <MessageThread.h>


//static const char * const DLT_TAG = "MessageThread";


MessageThread::MessageThread(std::function<int(IMsg *)> dispatcher, std::string name)
  : m_name(name)
  , m_state(ThreadState::UNINITED)
  , m_dispatcher(dispatcher)
  //, m_thread
  //, m_thread_mutex
  //, m_thread_cond
  , m_queue()
{
}

MessageThread::~MessageThread()
{
    if (m_thread.joinable())
    {
        exit();
        m_thread.join();
    }
}

MessageThread::ThreadState MessageThread::getState() const
{
    return m_state;
}

MessageThread::ThreadReturn MessageThread::start()
{
    ThreadReturn ret = ThreadReturn::ALREADY;

    std::lock_guard<std::mutex> lock(m_thread_mutex);

    if (ThreadState::UNINITED == m_state)
    {
        m_state = ThreadState::STARTED;
        m_thread = std::thread([=]{run();});
        ret = ThreadReturn::SUCCESS;
    }
    else if (ThreadState::TERMINATED == m_state)
    {
        ret = ThreadReturn::NOT_AVAILABLE;
    }

    return ret;
}

MessageThread::ThreadReturn MessageThread::suspend()
{
    ThreadReturn ret = ThreadReturn::NOT_AVAILABLE;

    if (ThreadState::TERMINATED != m_state)
    {
        m_queue.setSuspendMode(true);
        ret = ThreadReturn::SUCCESS;
    }

    return ret;
}

MessageThread::ThreadReturn MessageThread::resume()
{
    ThreadReturn ret = ThreadReturn::NOT_AVAILABLE;

    if (ThreadState::TERMINATED != m_state)
    {
        m_queue.setSuspendMode(false);
        ret = ThreadReturn::SUCCESS;
    }

    return ret;
}

MessageThread::ThreadReturn MessageThread::exit()
{
    ThreadReturn ret = ThreadReturn::ALREADY;

    if (ThreadState::TERMINATED != m_state)
    {
        m_state = ThreadState::TERMINATED;
        m_queue.setBypass(true);

        ret = ThreadReturn::SUCCESS;
    }

    return ret;
}

void MessageThread::postMessage(IMsg *msg)
{
    m_queue.enqueue(msg);
}

void MessageThread::setMsg(void *value)
{
    m_msg = value;
}

void *MessageThread::getMsg()
{
    return m_msg;
}

int MessageThread::run()
{

    int res = 0;

    m_state = ThreadState::RUNNING;

    void *msg = m_queue.dequeue();
    while (m_state != ThreadState::TERMINATED)
    {
        if (nullptr != msg)
        {
            // (note) do m_queue.setSuspend(true) here or
            // let m_handler(msg) do it on her decision
            res = m_dispatcher((IMsg*)msg);
            if (0 != res)
            {
                // log : ERROR
            }
        }
        msg = m_queue.dequeue();
        setMsg(msg);
    }
    // note: msg could have not-handled message

    // TODO : clear m_queue
    //while (nullptr != msg)
    //{
    //    msg = m_queue.dequeue(); // m_queue should be in bypass mode
    //}

    return res;
}
