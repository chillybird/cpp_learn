#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(size_t numThreads) : stop(false) {
        // 创建指定数量的工作线程
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                // 循环从任务队列中取出任务并执行
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mutex);
                        // 等待任务队列不为空或者线程池停止
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
                        // 如果线程池停止且任务队列为空，则退出循环
                        if (stop && tasks.empty()) {
                            return;
                        }
                        // 取出一个任务
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    // 执行任务
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mutex);
            // 设置线程池停止标志
            stop = true;
        }
        // 唤醒所有线程以使它们可以退出循环
        condition.notify_all();
        // 等待所有线程完成
        for (std::thread& worker : workers) {
            worker.join();
        }
    }

    // 提交任务到线程池
    template <typename Func, typename... Args>
    void submit(Func&& func, Args&&... args) {
        // 创建一个绑定了函数和参数的任务，并加入任务队列
        std::function<void()> task = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(mutex);
            tasks.emplace(std::move(task));
        }
        // 唤醒一个等待的线程来执行任务
        condition.notify_one();
    }

private:
    std::vector<std::thread> workers;                // 工作线程集合
    std::queue<std::function<void()>> tasks;         // 任务队列
    std::mutex mutex;                                // 互斥量用于保护任务队列
    std::condition_variable condition;               // 条件变量用于线程同步
    bool stop;                                       // 线程池停止标志
};

// 测试代码
void printNumber(int number) {
    std::cout << "Thread ID: " << std::this_thread::get_id() << ", Number: " << number << std::endl;
}

int main() {
    ThreadPool threadPool(4);  // 创建包含4个线程的线程池

    // 提交10个任务到线程池执行
    for (int i = 0; i < 10; ++i) {
        threadPool.submit(printNumber, i);
    }

    // 等待一段时间以观察输出结果
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
