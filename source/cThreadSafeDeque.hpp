///************************* OUTS HOMEWORK ****************************************
#ifndef CTHREADSAFEDEQUE_HPP
#define CTHREADSAFEDEQUE_HPP

#include <deque>
#include <mutex>
#include <condition_variable>

template <typename T>
class TThreadSafeDeque
{
public:
	TThreadSafeDeque() {}

	void push_back(const T& item)
	{
		{
			std::unique_lock<std::mutex> lock(mutex_);
			deque_.push_back(item);
		}
		cond_.notify_one();
	}

	bool pop_front(T& item)
	{
		std::unique_lock<std::mutex> lock(mutex_);
		if (deque_.empty()) {
			return false;
		}
		item = deque_.front();
		deque_.pop_front();
		return true;
	}

	bool empty() const {
		std::unique_lock<std::mutex> lock(mutex_);
		return deque_.empty();
	}

	size_t size() const
	{
		std::unique_lock<std::mutex> lock(mutex_);
		return deque_.size();
	}

	// Wait until deque is not empty
	void wait_for_data()
	{
		std::unique_lock<std::mutex> lock(mutex_);
		cond_.wait(lock, [this]() { return !deque_.empty(); });
	}

	// Wait with timeout
	template<typename Rep, typename Period>
	bool wait_for_data(const std::chrono::duration<Rep, Period>& timeout)
	{
		std::unique_lock<std::mutex> lock(mutex_);
		return cond_.wait_for(lock, timeout, [this]() { return !deque_.empty(); });
	}

protected:
	std::deque<T> deque_;
	mutable std::mutex mutex_;
	std::condition_variable cond_;
};

#endif //#ifndef CTHREADSAFEDEQUE_HPP
