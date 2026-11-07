#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

namespace Ignite
{
	enum class TimeOut : uint32_t
	{
		kNoWait = 0,
		kWaitForever = 0xFFFFFFFF
	};

	template <class T>
	class CMsgQueue
	{
		public:
			CMsgQueue (uint32_t msg_count) : _size (msg_count)
			{
			}
			CMsgQueue (const CMsgQueue&) = delete; // disable copying
			CMsgQueue& operator= (const CMsgQueue&) = delete; // disable assignment
			CMsgQueue (CMsgQueue&&) = delete;
			CMsgQueue& operator= (CMsgQueue&&) = delete;

			bool put(const T& msg, TimeOut timeoutTicks = TimeOut::kWaitForever)
			{
				if (_queue.size() == _size && timeoutTicks == TimeOut::kNoWait)
				{
					return false;
				}

				while (_queue.size() >= _size)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}
				std::unique_lock<std::mutex> mlock(_mutex);
				_queue.push(msg);
				mlock.unlock();
				_cond.notify_one();

				return true;
			}

			bool get (T& msg, TimeOut timeoutTicks)
			{
				std::unique_lock<std::mutex> mlock (_mutex);
				while (_queue.empty())
				{
					_cond.wait(mlock);
				}
				msg = _queue.front();
				_queue.pop();
				return true;
			}

			bool reset (void)
			{
				std::queue<T> empty;
				std::swap(_queue, empty);
				return true;
			}

			bool isEmpty (void)
			{
				return _queue.empty();
			}

			bool isFull (void) { return (numVacant() == 0); }

			uint32_t getSize (void) { return _size; }

			uint32_t numQueued (void) { return static_cast<uint32_t>(_queue.size()); }

			uint32_t numVacant (void) { return static_cast<uint32_t>(_size - _queue.size()); }

		private:
			std::queue<T> _queue;
			std::mutex _mutex;
			std::condition_variable _cond;
			const uint32_t _size;
	};
}; // namespace Ignite

