/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

 ******************************************************************************/
#ifndef SYNCQUEUE_H_
#define SYNCQUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SyncQueue {
  public:

    SyncQueue()
    {
        RequestToEnd = false;
        EnqueueData = true;
    }
    void Enqueue(const T& data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (EnqueueData) {
            m_queue.push(data);
            m_cond.notify_one();
        }

    }


    bool TryDequeue(T& result)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        while (m_queue.empty() && (!RequestToEnd)) {
            m_cond.wait(lock);
        }

        if (RequestToEnd) {
            DoEndActions();
            return false;
        }

        result = m_queue.front(); m_queue.pop();

        return true;
    }

    void StopQueue()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        RequestToEnd =  true;
        m_cond.notify_one();
    }

    int Size()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size();

    }

  private:

    void DoEndActions()
    {
        EnqueueData = false;

        while (!m_queue.empty()) {
            m_queue.pop();
        }
    }



    std::queue<T> m_queue;            // Use STL queue to store data
    std::mutex m_mutex;               // The mutex to synchronise on
    std::condition_variable m_cond;   // The condition to wait for

    bool RequestToEnd;
    bool EnqueueData;
};


#endif