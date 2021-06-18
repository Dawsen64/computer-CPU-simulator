#ifndef _CPU_H_
#define _CPU_H
/********************************�궨��****************************************/
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
/********************************�궨��****************************************/

/*****************************�Ĵ���************************************/
typedef struct reg
{
	int id;//����id
	short genReg[9];//�Ĵ���1��8
	short ir[2];//ָ��Ĵ���
	short ip;//���������
	short flag;//��־�Ĵ���
	short numReg;//�������Ĵ���
}Register;
/*****************************�Ĵ���************************************/


/***************************ȫ�ֱ���������*****************************************/
extern HANDLE hMutex;//�ڴ滥�� 
extern HANDLE hMu;//Put_Reg������Output�������� 
extern short* memory;//����
/***************************ȫ�ֱ���������*****************************************/


/*****************************��������**************************/
short* Init();//�����ʼ��
void InitReg(Register* Reg);//�Ĵ�����ʼ��
void ReadCmdFile();//����ָ������
short byte_to_short(char* s, int start);//�Ѵ�start����8λ���ַ��������short������
void Getcmd(Register* Reg);//ȡָ��
short State_trans(Register* Reg);

void Data_transfer(Register* Reg);
void Arith_add(Register* Reg);//�ӷ�
void Arith_sub(Register* Reg);//����
void Arith_multiply( Register* Reg);//�˷�
void Arith_div(Register* Reg);//����
void And_oper(Register* Reg);//��
void Or_oper(Register* Reg);
void Not_oper(Register* Reg);
void Compare(Register* Reg);
void Jump(Register* Reg);
void Input(Register* Reg);
void Output(Register* Reg);

void PutReg(Register* Reg);
void Outmemory();
unsigned __stdcall Cpu1();//��1
unsigned __stdcall Cpu2();//��2
/***************************************��������*****************************************/

#endif // !_CPU_H_
