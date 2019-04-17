#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

#include "Logger.h"

using namespace std;

int main(int argc, char *argv[])
{
    SimpleLogger("SimpleLogger test");

    LoggerTag(__FUNCTION__, DEBUG, "LogerrTag test, consistting of tag and content");

    LoggerTimeTag(__FUNCTION__, DEBUG, "LogerrTag test, consistting of tag and content");

    Logger(__FUNCTION__, __LINE__, DEBUG, "LogerrTag test, consistting of tag and content");

    MyLogger(__FUNCTION__, __LINE__, ERROR, "Content test value: %d", 1);
    return 0;
}
