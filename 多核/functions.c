/*********************初始化和输出等函数定义***************************/
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <process.h>
#include "cpu.h"

unsigned __stdcall Cpu1()//核1
{
	int stop = 0;//用于停机指令
	Register Reg1;//寄存器
	InitReg(&Reg1);
	Reg1.id = 1;
	while (!stop)
	{
		Getcmd(&Reg1);
		stop = State_trans(&Reg1);
	}
}
unsigned __stdcall Cpu2()//核2
{
	int stop = 0;//用于停机指令
	Register Reg2;//寄存器
	InitReg(&Reg2);
	Reg2.id = 2;
	Reg2.ip = 256;//核2的代码段从256开始
	while (!stop)
	{
		Getcmd(&Reg2);
		stop = State_trans(&Reg2);
	}
}

short* Init()
{
	int i = 0;
	short* p = (short*)malloc(sizeof(short) * MEM_SIZE);
	for (i = 0; i < MEM_SIZE; i++)
	{
		p[i] = 0;
	}
	p[ONEADDR] = 10;//规定16384地址处的值为100
	return p;
}
void InitReg(Register* Reg)//寄存器初始化
{
	int i = 0;
	Reg->flag = 0;
	for (i = 0; i < 9; i++)
	{
		Reg->genReg[i] = 0;
	}
	Reg->ip = 0;
	Reg->ir[0] = 0;
	Reg->ir[1] = 0;
	Reg->numReg = 0;
}
short byte_to_short(char* s, int start)//把从start处后8位得字符串翻译成short型整数
{
	int i = 0, j = 7;
	short sum = 0;
	for (i = start; i < start + 8; i++)
	{
		sum += (s[i] - '0') * pow(2, j);
		j--;
	}
	return sum;
}
void ReadCmdFile()
{
	FILE* fp = fopen("dict.dic", "r");
	if (fp == NULL)
		printf("open file error!\n");
	char s[CMD_LEN + 1] = "";
	int i = 0, j = 256;
	while (fscanf(fp, "%s", s))//把读出的指令序列分别存储到地址0开始和地址256开始的代码段中
	{
		if (feof(fp))
			break;
		memory[i++] = byte_to_short(s, 0);
		memory[j++] = memory[i - 1];

		memory[i++] = byte_to_short(s, 8);
		memory[j++] = memory[i - 1];

		memory[i++] = byte_to_short(s, 16);
		memory[j++] = memory[i - 1];

		memory[i++] = byte_to_short(s, 24);
		memory[j++] = memory[i - 1];
	}
}
void Getcmd(Register* Reg)//取指令
{
	Reg->ir[0] = memory[Reg->ip];
	Reg->ir[1] = memory[Reg->ip + 1];
	if (memory[Reg->ip + 2] >= 128)//立即数有可能是负数
		Reg->numReg = (memory[Reg->ip + 2] - 256) * EIGHTBYTE + memory[Reg->ip + 3];
	else Reg->numReg = memory[Reg->ip + 2] * EIGHTBYTE + memory[Reg->ip + 3];
	Reg->ip += 4;
}
short State_trans(Register* Reg)
{
	int type = Reg->ir[0];
	int stopflag = 0;
	switch (type)
	{
	case 0://停机
		stopflag = 1;
		break;
	case 1:
		Data_transfer(Reg);
		break;
	case 2:
		Arith_add(Reg);
		break;
	case 3:
		Arith_sub(Reg);
		break;
	case 4:
		Arith_multiply(Reg);
		break;
	case 5:
		Arith_div(Reg);
		break;
	case 6:
		And_oper(Reg);
		break;
	case 7:
		Or_oper(Reg);
		break;
	case 8:
		Not_oper(Reg);
		break;
	case 9:
		Compare(Reg);
		break;
	case 10:
		Jump(Reg);
		break;
	case 11:
		Input(Reg);
		break;
	case 12:
		Output(Reg);
		break;
	case 13://请求锁住内存的互斥对象
		WaitForSingleObject(hMutex, INFINITE);
		break;
	case 14:
		ReleaseMutex(hMutex);
		break;
	case 15:
		Sleep(Reg->numReg);
		break;
	}
	PutReg(Reg);
	if (stopflag)
		return 1;
	else return 0;
}
void PutReg(Register* Reg)
{
	WaitForSingleObject(hMu, INFINITE);
	printf("id = %d\n", Reg->id);
	printf("ip = %hd\n", Reg->ip);
	printf("flag = %hd\n", Reg->flag);
	printf("ir = %hd\n", Reg->ir[0] * EIGHTBYTE + Reg->ir[1]);
	printf("ax1 = %hd ax2 = %hd ax3 = %hd ax4 = %hd\n", Reg->genReg[1], Reg->genReg[2], Reg->genReg[3], Reg->genReg[4]);
	printf("ax5 = %hd ax6 = %hd ax7 = %hd ax8 = %hd\n", Reg->genReg[5], Reg->genReg[6], Reg->genReg[7], Reg->genReg[8]);
	ReleaseMutex(hMu);
}
void Outmemory()
{
	int i, j, count = 0, sum;
	printf("\ncodeSegment :\n");
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 8; j++)
		{
			sum = memory[count] * 16777216 + memory[count + 1] * 65536 + memory[count + 2] * 256 + memory[count + 3];
			printf("%d ", sum);
			count += 4;
		}
		printf("\n");
	}
	printf("\ndataSegment :\n");
	count = 16384;
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			sum = memory[count] + memory[count + 1] * 256;//特别诡异的地方
			printf("%d ", sum);
			count += 2;
		}
		printf("\n");
	}
}

/*********************函数定义***************************/