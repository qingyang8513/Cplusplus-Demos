#include <iostream>
#include <sys/time.h>
#include "Lock.h"

using namespace std;

Lock::BMutex bmutex;

Lock::BRWLock brwLock;

int sum_nolock = 0;
int sum_bmutex = 0;
int sum_brwlock = 0;

void *addTest(void *userData)
{
    int *testTpye = (int *)userData;
    cout << "****** Test type value: " << *testTpye << " ******" << endl; fflush(stdout);
    for (int i = 0; i < 1000000; ++i) {
        if (*testTpye == 1) {
            Lock::BLockGuard block_guard(bmutex);
            sum_bmutex++;
        }
        else if (*testTpye == 2) {
            Lock::BRWLockGuard wrLockGuard(brwLock, Lock::RWLockOpt::B_WLOCK);
            sum_brwlock++;
        }
        else {
            sum_nolock++;
        }
    }
}

int main()
{
    cout << "Lock Demo Test" << endl;

    pthread_t ptid1, ptid2;
    int testType;
    struct timeval timeStart, timeEnd;
    double runTime = 0.0;

    /// Test Case 1
    testType = 0;
    gettimeofday(&timeStart, NULL);
    pthread_create(&ptid1, NULL, addTest, &testType);
    pthread_create(&ptid2, NULL, addTest, &testType);

    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);

    gettimeofday(&timeEnd, NULL);
    runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;

    cout << "NoLock sum result: " << sum_nolock << endl;
    cout << "NoLock run time: " << runTime << endl << endl;

    /// Test Case 2
    testType = 1;
    gettimeofday(&timeStart, NULL);
    pthread_create(&ptid1, NULL, addTest, &testType);
    pthread_create(&ptid2, NULL, addTest, &testType);

    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);

    gettimeofday(&timeEnd, NULL);
    runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;

    cout << "BMutex sum result: " << sum_bmutex << endl;
    cout << "BMutex run time: " << runTime << endl << endl;


    /// Test Case 3
    testType = 2;
    gettimeofday(&timeStart, NULL);
    pthread_create(&ptid1, NULL, addTest, &testType);
    pthread_create(&ptid2, NULL, addTest, &testType);

    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);

    gettimeofday(&timeEnd, NULL);
    runTime = (timeEnd.tv_sec - timeStart.tv_sec ) + (double)(timeEnd.tv_usec -timeStart.tv_usec)/1000000;

    cout << "BRWLock sum result: " << sum_brwlock << endl;
    cout << "BRWLock run time: " << runTime << endl << endl;

    return 0;
}
