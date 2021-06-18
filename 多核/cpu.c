#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <process.h>
#include "cpu.h"
/***************************全局变量的定义*****************************************/
HANDLE hMutex;//内存互斥 
HANDLE hMu;//Put_Reg函数和Output函数互斥，防止printf被打断

short* memory;//主存
/***************************全局变量的定义*****************************************/

int main()
{
	memory = Init();//初始化内存
	ReadCmdFile();//读入指令序列

	//Outmemory(memory);
	HANDLE hThread1;//创建线程 1 
	HANDLE hThread2;//创建线程 2 

	hMutex = CreateMutex(NULL, FALSE, NULL);//互斥对象 
	hMu = CreateMutex(NULL, FALSE, NULL);//互斥对象 


	hThread1 = (HANDLE)_beginthreadex(NULL, 0, Cpu1, NULL, 0, NULL);//核1
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, Cpu2, NULL, 0, NULL);//核2

	WaitForSingleObject(hThread1, INFINITE);//等待两个线程执行完毕
	WaitForSingleObject(hThread2, INFINITE);

	Outmemory();//输出代码段和数据段
	free(memory);
	return 0;
}
