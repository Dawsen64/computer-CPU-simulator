#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <process.h>
#include "cpu.h"
/***************************ȫ�ֱ����Ķ���*****************************************/
HANDLE hMutex;//�ڴ滥�� 
HANDLE hMu;//Put_Reg������Output�������⣬��ֹprintf�����

short* memory;//����
/***************************ȫ�ֱ����Ķ���*****************************************/

int main()
{
	memory = Init();//��ʼ���ڴ�
	ReadCmdFile();//����ָ������

	//Outmemory(memory);
	HANDLE hThread1;//�����߳� 1 
	HANDLE hThread2;//�����߳� 2 

	hMutex = CreateMutex(NULL, FALSE, NULL);//������� 
	hMu = CreateMutex(NULL, FALSE, NULL);//������� 


	hThread1 = (HANDLE)_beginthreadex(NULL, 0, Cpu1, NULL, 0, NULL);//��1
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, Cpu2, NULL, 0, NULL);//��2

	WaitForSingleObject(hThread1, INFINITE);//�ȴ������߳�ִ�����
	WaitForSingleObject(hThread2, INFINITE);

	Outmemory();//�������κ����ݶ�
	free(memory);
	return 0;
}
