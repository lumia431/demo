#pragma once
#include <iostream>
#include <pthread.h>

// 定义互斥锁和条件变量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// 定义future和promise
template <typename T>
class Future {
public:
    Future() : m_value(), m_ready(false) {}

    T get() {
        // 加锁
        pthread_mutex_lock(&mutex);
        // 如果值未准备好，则等待条件变量
        while (!m_ready) {
            pthread_cond_wait(&cond, &mutex);
        }
        // 解锁
        pthread_mutex_unlock(&mutex);
        // 返回值
        return m_value;
    }

    void set(T value) {
        // 加锁
        pthread_mutex_lock(&mutex);
        // 设置值
        m_value = value;
        m_ready = true;
        // 发送条件变量信号
        pthread_cond_signal(&cond);
        // 解锁
        pthread_mutex_unlock(&mutex);
    }

private:
    T m_value;
    bool m_ready;
};

template <typename T>
class Promise {
public:
    Promise() : m_future() {}

    Future<T>& get_future() {
        return m_future;
    }

    void set_value(T value) {
        m_future.set(value);
    }

private:
    Future<T> m_future;
};

void* thread_func(void* arg)
{
    Promise<int>* promise = (Promise<int>*)arg;
    // 计算1 + 2，并将结果设置到promise中
    promise->set_value(1 + 2);
    return NULL;
}

int main()
{
    Promise<int> promise;
    Future<int>& future = promise.get_future();

    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, (void*)&promise);

    // 等待future的值，并输出结果
    std::cout << "Result: " << future.get() << std::endl;

    pthread_join(thread, NULL);

    return 0;
}

