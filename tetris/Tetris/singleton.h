#pragma once

#include <memory>
#include <mutex>

template<class T>
class TypeAllocator {
public:
	static T* createInstance() {
		return new T();
	}
};

template <class T, class Allocator = TypeAllocator<T>>
class Singleton
{
public:
	Singleton(Singleton<T, Allocator> const&) = delete;
	Singleton(Singleton&&) = delete;                  // Move construct
	Singleton& operator=(Singleton const&) = delete;  // Copy assign
	Singleton& operator=(Singleton &&) = delete;      // Move assign

public:
	static T& instance()
	{
		std::call_once(onceFlag_, [] {instance_.reset(Allocator::createInstance()); });
		return *instance_.get();
	}

private:

	static std::unique_ptr<T> instance_;
	static std::once_flag onceFlag_;
};

template<class T, class Allocator> std::unique_ptr<T> Singleton<T, Allocator>::instance_;
template<class T, class Allocator> std::once_flag Singleton<T, Allocator>::onceFlag_;