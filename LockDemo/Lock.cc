#include "Lock.h"

namespace Lock {

BMutex::BMutex()
{
    int32_t ret = pthread_mutex_init(&_mutex, NULL);
    if (0 != ret) {
        Bprintf("[BMutex::BMutex][errno = %d], init mutex failed", ret);
        abort();
    }
}

BMutex::~BMutex()
{
    int32_t ret = pthread_mutex_destroy(&_mutex);
    if (0 != ret) {
        Bprintf("[BMutex::~BMutex][errno = %d], destory mutex failed", ret);
        abort();
    }
}

void BMutex::lock()
{
    int32_t ret = pthread_mutex_lock(&_mutex);
    if (0 != ret) {
        Bprintf("[BMutex::lock][errno = %d], lock failed", ret);
        abort();
    }
}

void BMutex::unlock()
{
    int32_t ret = pthread_mutex_unlock(&_mutex);
    if (0 != ret) {
        Bprintf("[BMutex::unlock][errno = %d], unlock failed", ret);
        abort();
    }
}

BRWLock::BRWLock()
{
    int32_t ret = brwlock_init(&_lock, NULL);
    if (0 != ret) {
        Bprintf("[BRWLock::BRWLock][errno = %d], init rwlock failed", ret);
        abort();
    }
}

BRWLock::~BRWLock()
{
    int32_t ret = brwlock_destroy(&_lock);
    if (0 != ret) {
        Bprintf("[BRWLock::~BRWLock][errno = %d], destory rwlock failed", ret);
        abort();
    }
}

void BRWLock::read_lock()
{
    int32_t ret = brwlock_rdlock(&_lock);
    if (0 != ret) {
        Bprintf("[BRWLock::read_lock][errno = %d], rwlock rdlock failed", ret);
        abort();
    }
}

void BRWLock::write_lock()
{
    int32_t ret = brwlock_wrlock(&_lock);
    if (0 != ret) {
        Bprintf("[BRWLock::write_lock][errno = %d], rwlock wrlock failed", ret);
        abort();
    }
}

void BRWLock::unlock()
{
    int32_t ret = brwlock_unlock(&_lock);
    if (0 != ret) {
        Bprintf("[BRWLock::unlock][errno = %d], unlock failed", ret);
        abort();
    }
}


} // namespace Lock
