#include <iostream>
#include <thread>
#include <vector>

void foo(const std::vector<std::thread::id>& thread_ids) {
    if (std::this_thread::get_id() == thread_ids[0]) {
        std::cout << "foo() was called by high priority thread, with id: " << std::this_thread::get_id() << std::endl;
    }
    if (std::this_thread::get_id() == thread_ids[1]) {
        std::cout << "foo() was invoked by low priority thread, with id: " << std::this_thread::get_id() << std::endl;
    }
}

void EntryPoint(const std::vector<std::thread::id>& thread_ids) {
    foo(thread_ids); // Passing thread_ids to foo
}

int main() {
    // Placeholder threads to capture their IDs
    std::thread placeholder1, placeholder2;

    // Capture thread IDs, index represents thread priority, lower index is higher priority
    std::vector<std::thread::id> thread_ids{placeholder1.get_id(), placeholder2.get_id()};

    // Create actual threads and pass thread_ids using a lambda
    std::thread t1 ([&thread_ids]() { EntryPoint(thread_ids); });
    std::thread t2 ([&thread_ids]() { EntryPoint(thread_ids); });

    // Join threads
    t1.join();
    t2.join();

    return 0;
}