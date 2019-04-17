#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

#include "Logger.h"

using namespace std;

int main(int argc, char *argv[])
{
    MyLogger(__FUNCTION__, __LINE__, DEBUG, "Content test value: %d", 1);
    return 0;
}
