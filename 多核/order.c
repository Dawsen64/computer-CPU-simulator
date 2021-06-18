#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <process.h>
#include "cpu.h"
/************************15条指令的函数实现*********************************/
void Data_transfer(Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0)//立即数->R
	{
		Reg->genReg[Dreg] = Reg->numReg;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->genReg[Dreg] = memory[Reg->genReg[Sreg]];
	}
	else if (Sreg >= 5 && Dreg >= 5)//M->M
	{
		memory[Reg->genReg[Dreg]] = memory[Reg->genReg[Sreg]];
	}
	else if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->genReg[Dreg]] = Reg->genReg[Sreg];
	}
	else if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->genReg[Dreg] = Reg->genReg[Sreg];
	}
}
void Arith_add(Register* Reg)//加法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->genReg[Dreg] += Reg->numReg;
	}
	else if (Sreg == 0 && Dreg >= 5)//立即数->M
	{
		memory[Reg->genReg[Dreg]] += Reg->numReg;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->genReg[Dreg] += memory[Reg->genReg[Sreg]];
	}
	else if (Sreg >= 5 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] += memory[Reg->genReg[Sreg]];
	}
	else if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->genReg[Dreg]] += Reg->genReg[Sreg];
	}
	else if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->genReg[Dreg] += Reg->genReg[Sreg];
	}
}
void Arith_sub(Register* Reg)//减法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->genReg[Dreg] -= Reg->numReg;
	}
	else if (Sreg == 0 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] -= Reg->numReg;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->genReg[Dreg] -= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg >= 5 && Dreg >= 5)//M->M
	{
		memory[Reg->genReg[Dreg]] -= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->genReg[Dreg]] -= Reg->genReg[Sreg];
	}
	else if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->genReg[Dreg] -= Reg->genReg[Sreg];
	}
}
void Arith_multiply(Register* Reg)//乘法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->genReg[Dreg] *= Reg->numReg;
	}
	else if (Sreg == 0 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] *= Reg->numReg;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->genReg[Dreg] *= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg >= 5 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] *= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->genReg[Dreg]] *= Reg->genReg[Sreg];
	}
	else if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->genReg[Dreg] *= Reg->genReg[Sreg];
	}
}
void Arith_div(Register* Reg)//除法
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数->R
	{
		Reg->genReg[Dreg] /= Reg->numReg;
	}
	else if (Sreg == 0 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] /= Reg->numReg;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M->R
	{
		Reg->genReg[Dreg] /= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg >= 5 && Dreg >= 5)
	{
		memory[Reg->genReg[Dreg]] /= memory[Reg->genReg[Sreg]];
	}
	else if (Sreg <= 4 && Dreg >= 5)//R->M
	{
		memory[Reg->genReg[Dreg]] /= Reg->genReg[Sreg];
	}
	else if (Sreg <= 4 && Dreg <= 4)//R->R
	{
		Reg->genReg[Dreg] /= Reg->genReg[Sreg];
	}
}
void And_oper(Register* Reg)//与
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数 && R
	{
		if (Reg->genReg[Dreg] && Reg->numReg)
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
	else if (Sreg == 0 && Dreg >= 5)//立即数 && M
	{
		if (memory[Reg->genReg[Dreg] && Reg->numReg])
			memory[Reg->genReg[Dreg]] = 1;
		else memory[Reg->genReg[Dreg]] = 0;
	}
	else if (Sreg >= 5 && Dreg <= 4)//M && R
	{
		if (Reg->genReg[Dreg] && memory[Reg->genReg[Sreg]])
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
	else if (Sreg >= 5 && Dreg >= 5)//M && M
	{
		if (memory[Reg->genReg[Dreg]] && memory[Reg->genReg[Sreg]])
			memory[Reg->genReg[Dreg]] = 1;
		else memory[Reg->genReg[Dreg]] = 0;
	}
	else if (Sreg <= 4 && Dreg >= 5)
	{
		if (memory[Reg->genReg[Dreg]] && Reg->genReg[Sreg])
			memory[Reg->genReg[Dreg]] = 1;
		else memory[Reg->genReg[Dreg]] = 0;
	}
	else if (Sreg <= 4 && Dreg <= 4)//R && R
	{
		if (Reg->genReg[Dreg] && Reg->genReg[Sreg])
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
}
void Or_oper(Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)//立即数 && R
	{
		if (Reg->genReg[Dreg] || Reg->numReg)
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
	else if (Sreg == 0 && Dreg >= 5)//立即数 && M
	{
		if (memory[Reg->genReg[Dreg] || Reg->numReg])
			memory[Reg->genReg[Dreg]] = 1;
		else memory[Reg->genReg[Dreg]] = 0;
	}
	else if (Sreg >= 5)//M && R
	{
		if (Reg->genReg[Dreg] || memory[Reg->genReg[Sreg]])
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
}
void Not_oper(Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0)//
	{
		if (!Reg->genReg[Dreg])
			Reg->genReg[Dreg] = 1;
		else Reg->genReg[Dreg] = 0;
	}
	else if (Sreg >= 5)
	{
		if (!memory[Reg->genReg[Sreg]])
			memory[Reg->genReg[Sreg]] = 1;
		else memory[Reg->genReg[Sreg]] = 0;
	}
}
void Compare(Register* Reg)
{
	short Sreg = Reg->ir[1] % 16;
	short Dreg = Reg->ir[1] / 16;
	if (Sreg == 0 && Dreg <= 4)
	{
		if (Reg->genReg[Dreg] == Reg->numReg)
			Reg->flag = 0;
		else if (Reg->genReg[Dreg] > Reg->numReg)
			Reg->flag = 1;
		else if (Reg->genReg[Dreg] < Reg->numReg)
			Reg->flag = -1;
	}
	else if (Sreg == 0 && Dreg >= 5)
	{
		if (memory[Reg->genReg[Dreg]] == Reg->numReg)
			Reg->flag = 0;
		else if (memory[Reg->genReg[Dreg]] > Reg->numReg)
			Reg->flag = 1;
		else Reg->flag = -1;
	}
	else if (Sreg >= 5)
	{
		if (Reg->genReg[Dreg] == memory[Reg->genReg[Sreg]])
			Reg->flag = 0;
		else if (Reg->genReg[Dreg] > memory[Reg->genReg[Sreg]])
			Reg->flag = 1;
		else if (Reg->genReg[Dreg] < memory[Reg->genReg[Sreg]])
			Reg->flag = -1;
	}
	else if (Sreg <= 4)
	{
		if (Reg->genReg[Dreg] == Reg->genReg[Sreg])
			Reg->flag = 0;
		else if (Reg->genReg[Dreg] > Reg->genReg[Sreg])
			Reg->flag = 1;
		else  Reg->flag = -1;
	}
}
void Jump(Register* Reg)
{
	int state = Reg->ir[1];
	if (state == 0)//无条件跳转
	{
		Reg->ip += Reg->numReg - 4;
	}
	else if (state == 1)
	{
		if (Reg->flag == 0)
			Reg->ip += Reg->numReg - 4;
	}
	else if (state == 2)
	{
		if (Reg->flag == 1)
			Reg->ip += Reg->numReg - 4;
	}
	else if (state == 3)
	{
		if (Reg->flag == -1)
			Reg->ip += Reg->numReg - 4;
	}
}
void Input(Register* Reg)
{
	short Dreg = Reg->ir[1] / 16;
	printf("in:\n");
	if (Dreg <= 4)
		scanf("%hd", &Reg->genReg[Dreg]);
	else scanf("%hd", &memory[Reg->genReg[Dreg]]);
}
void Output(Register* Reg)
{
	WaitForSingleObject(hMu, INFINITE);
	short Dreg = Reg->ir[1] / 16;
	printf("id = %d  ", Reg->id);
	printf("out: ");
	if (Dreg <= 4)
		printf("%hd\n", Reg->genReg[Dreg]);
	else printf("%hd\n", memory[Reg->genReg[Dreg]]);
	ReleaseMutex(hMu);
}