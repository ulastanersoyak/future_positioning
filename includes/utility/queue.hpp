#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename contained> class queue
{
  std::queue<contained> q{};
  mutable std::mutex mtx{};
  std::condition_variable cv{};

public:
  void
  push (const contained &cont) noexcept
  {
    std::lock_guard<std::mutex> lock (this->mtx);
    q.push (cont);
    cv.notify_one ();
  }

  contained
  pop () noexcept
  {
    std::unique_lock<std::mutex> lock (this->mtx);
    this->cv.wait (lock, [this] { return !q.empty (); });
    contained item = std::move (q.front ());
    q.pop ();
    return item;
  }

  [[nodiscard]] std::size_t size() const noexcept{
      return q.size();
  }
};

#endif // !QUEUE_HPP
