#ifndef LOCK_H
#define LOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

namespace Lock {

#define Bprintf printf

#define brwlock_init     pthread_rwlock_init
#define brwlock_destroy  pthread_rwlock_destroy
#define brwlock_rdlock   pthread_rwlock_rdlock
#define brwlock_wrlock   pthread_rwlock_wrlock
#define brwlock_unlock   pthread_rwlock_unlock

typedef enum
{
    B_RLOCK = 0,
    B_WLOCK = 1
}RWLockOpt;


class BMutex
{
public:
    BMutex();
    ~BMutex();

    void lock();
    void unlock();

private:
    BMutex(const BMutex&);
    BMutex operator = (const BMutex&);

    pthread_mutex_t _mutex;
};

class BLockGuard
{
public:
    explicit BLockGuard(BMutex &m) : _m(m) {
        _m.lock();
    }

    ~BLockGuard() {
        _m.unlock();
    }

private:
    BLockGuard();
    BLockGuard(const BLockGuard&);
    BLockGuard& operator = (const BLockGuard&);

    BMutex& _m;
};

class BRWLock
{
public:
    BRWLock();
    ~BRWLock();

    void read_lock();
    void write_lock();

    void unlock();

private:
    BRWLock(const BRWLock&);
    BRWLock operator = (const BRWLock&);

    pthread_rwlock_t _lock;
};

class BRWLockGuard
{
public:
    BRWLockGuard(BRWLock &l, RWLockOpt opt) : _lock(l) {
        if (B_RLOCK == opt) {
            _lock.read_lock();
        }
        else {
            _lock.write_lock();
        }
    }

    ~BRWLockGuard() {
        _lock.unlock();
    }

private:
    BRWLockGuard();
    BRWLockGuard(const BRWLockGuard&);
    BRWLockGuard operator = (const BRWLockGuard&);

    BRWLock& _lock;
};

} // namespace Lock

#endif // LOCK_H
