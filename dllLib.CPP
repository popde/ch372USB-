#include "stdafx.h"
#include "doDll.h"
#include "CH375DLL.h"
#pragma comment(lib,"CH375DLL")  //隐式调用库文件
 
 
bool OPenSuccess = false;
unsigned int CH375_Index = 0;
 
DODLL_API bool usbInit(int index=0)
{
    CH375_Index = index;
    if (OPenSuccess == false) {
        OPenSuccess = (CH375OpenDevice(CH375_Index) != INVALID_HANDLE_VALUE);
    }
     
    return OPenSuccess;
}
 
DODLL_API bool usbClose(void)
{
    if (OPenSuccess == true)
    {
        CH375CloseDevice(CH375_Index);
        OPenSuccess = false;
    }
    return true;
}
 
DODLL_API long usbWrite(INT unEndPoint, unsigned char* pSendBytes, ULONG unSendLength)
{
    ULONG len = unSendLength;
    if (OPenSuccess == true)
    {
        BOOL ret = CH375WriteData(CH375_Index, pSendBytes, &len);
        if (ret == TRUE)
        {
            return len;
        }
        else {
            return -1;
        }
    }
    return -1;
}
 
DODLL_API long usbRead(INT unEndPoint, unsigned char* pRecBytes, ULONG unSendLength)
{
    ULONG len = unSendLength;
    if (OPenSuccess == true)
    {
        BOOL ret = CH375ReadData(CH375_Index, pRecBytes, &len);
        if (ret == TRUE)
        {
            return len;
        }
        else {
            return -1;
        }
    }
    return -1;
}
