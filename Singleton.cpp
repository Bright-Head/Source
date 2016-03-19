#include <iostream>
#include <Windows.h>
using namespace std;
template<class TCount = TCountOn, class TThreads = TThreadWithoutLock>
class TSingletonDestroyer;

class IThreadStrategy
{
public:
	virtual ~IThreadStrategy() {};
	virtual void lock() = 0;
	virtual void unlock() = 0;
};
class TThreadLock : public IThreadStrategy
{
private:
  CRITICAL_SECTION cs;
public:
	virtual ~TThreadLock() {};
	TThreadLock() {};
	virtual void lock() { EnterCriticalSection(&cs); cout << "EnterCriticalSection" << endl; };
	virtual void unlock() { LeaveCriticalSection(&cs); cout << "LeaveCriticalSection" << endl; };
};
class TThreadWithoutLock : public IThreadStrategy
{
public:
	virtual ~TThreadWithoutLock() {};
	virtual void lock() { cout << "TThreadWithoutLock lock()" << endl; };
	virtual void unlock() { cout << "TThreadWithoutLock unlock()" << endl; };
};
class ICountStrategy
{
public:
	virtual ~ICountStrategy() {};
	virtual int onIncrement() = 0;
	virtual int onDecrement() = 0;
};
class TCountOn : public ICountStrategy
{
public:
	virtual ~TCountOn() {};
	TCountOn() { count = 0; };
	virtual int onIncrement() { ++count; cout << count << endl; return count; };
	virtual int onDecrement() { --count; cout << count << endl; return count; };
private:
	int count;
};
class TCountOff : public ICountStrategy
{
public:
	virtual ~TCountOff() {};
	TCountOff() { count = -1; };
	virtual int onIncrement() { cout << "CountOff Inc"; cout << count << endl; return count; };
	virtual int onDecrement() { cout << "CountOff Dec"; cout << count << endl; return count; };
private:
	int count;
};

template<class TCount = TCountOn, class TThreads = TThreadWithoutLock>
class TSingleton
{
public:
	static TSingleton<TCount, TThreads>* GetInstance();
	TSingleton() { cout << "Singleton()\n"; }
	friend class TSingletonDestroyer<TCount, TThreads>;
protected:
	~TSingleton();
private:
	static TSingleton<TCount, TThreads>* ref;
	static TThreads* ptr_threadStrategy;
	static TCount ptr_countStrategy;
	static TSingletonDestroyer<TCount, TThreads> destroyer;
};

template<class TCount, class TThreads> TSingleton<TCount, TThreads>* TSingleton<TCount, TThreads>::ref = 0;
template<class TCount, class TThreads> TThreads* TSingleton<TCount, TThreads>::ptr_threadStrategy = new TThreads();
template<class TCount, class TThreads> TCount TSingleton<TCount, TThreads>::ptr_countStrategy;
template<class TCount, class TThreads> TSingletonDestroyer<TCount, TThreads> TSingleton<TCount, TThreads>::destroyer;

template<class TCount, class TThreads>
TSingleton<TCount, TThreads>* TSingleton<TCount, TThreads>::GetInstance()
{
	if (!ptr_threadStrategy)
		ptr_threadStrategy = new TThreads();
	if (!ref)
	{
		ptr_threadStrategy->lock();
		if (!ref)
		{
			ref = new TSingleton<TCount, TThreads>();
		}
		ptr_threadStrategy->unlock();
	}
	ptr_countStrategy.onIncrement();
	return ref;
}

template<class TCount, class TThreads>
TSingleton<TCount, TThreads>::~TSingleton() {
	ref = NULL;
	cout << "~Singleton\n";
}

template<class TCount = TCountOn, class TThreads = TThreadWithoutLock>
class TSingletonDestroyer
{
private:
	static TSingleton<TCount, TThreads>* instance;
public:
	~TSingletonDestroyer()
	{
		if (instance->ptr_countStrategy.onDecrement() == 0)
		{
			delete instance->ptr_threadStrategy;
			instance->ptr_threadStrategy = NULL;
			delete instance;
			instance = NULL;
		}
	};
	TSingletonDestroyer(TSingleton<TCount, TThreads>* _ins) { instance = _ins; };
};

template <class TCount = TCountOn, class TThreads = TThreadWithoutLock> TSingleton<TCount, TThreads>* TSingletonDestroyer<TCount, TThreads>::instance;

typedef TCountOff TCount;
typedef TThreadLock TThreads ;

int main()
{
	{
		TSingletonDestroyer<TCount, TThreads> singleton(TSingleton<TCount, TThreads>::GetInstance());
	}
	{
		TSingletonDestroyer<TCount, TThreads> singleton2(TSingleton<TCount, TThreads>::GetInstance());
	}
	TSingletonDestroyer<TCount, TThreads> singleton1(TSingleton<TCount, TThreads>::GetInstance());
	return 0;
}
