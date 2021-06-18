#ifndef _CPU_H_
#define _CPU_H
/********************************宏定义****************************************/
#define CMD_LEN 32
#define MEM_SIZE 32768
#define REG_LEN 2
#define CODE_GROUP 4
#define DATA_GROUP 2
#define OUT_LINES 16
#define CODE_LINE 8
#define DATA_LINE 16
#define EIGHTBYTE 256
#define ONEADDR 16384
/********************************宏定义****************************************/

/*****************************寄存器************************************/
typedef struct reg
{
	int id;//核心id
	short genReg[9];//寄存器1到8
	short ir[2];//指令寄存器
	short ip;//程序计数器
	short flag;//标志寄存器
	short numReg;//立即数寄存器
}Register;
/*****************************寄存器************************************/


/***************************全局变量的声明*****************************************/
extern HANDLE hMutex;//内存互斥 
extern HANDLE hMu;//Put_Reg函数与Output函数互斥 
extern short* memory;//主存
/***************************全局变量的声明*****************************************/


/*****************************函数声明**************************/
short* Init();//主存初始化
void InitReg(Register* Reg);//寄存器初始化
void ReadCmdFile();//读入指令序列
short byte_to_short(char* s, int start);//把从start处后8位得字符串翻译成short型整数
void Getcmd(Register* Reg);//取指令
short State_trans(Register* Reg);

void Data_transfer(Register* Reg);
void Arith_add(Register* Reg);//加法
void Arith_sub(Register* Reg);//减法
void Arith_multiply( Register* Reg);//乘法
void Arith_div(Register* Reg);//除法
void And_oper(Register* Reg);//与
void Or_oper(Register* Reg);
void Not_oper(Register* Reg);
void Compare(Register* Reg);
void Jump(Register* Reg);
void Input(Register* Reg);
void Output(Register* Reg);

void PutReg(Register* Reg);
void Outmemory();
unsigned __stdcall Cpu1();//核1
unsigned __stdcall Cpu2();//核2
/***************************************函数声明*****************************************/

#endif // !_CPU_H_
