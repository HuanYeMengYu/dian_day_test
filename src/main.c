#include "stdio.h"
#include "stdlib.h"
#include "./sh/logger.h"

int main(void)
{
    Log(DEBUG,"this is debug");
    Log(INFO,"this is info");
    Log(ERROR,"this is error");
    Log(WARNING,"this is warn");
    Log(FATAL,"this is fatal");

    return 0;
}