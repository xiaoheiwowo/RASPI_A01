#include "Macro.h"
#include "Public.h"

uint CountAvg_Advalue(uint *ADV,uchar Times){
    /* 去掉一个最大值，一个最小值，然后求平均值 */
    
	uchar i;
	uint Min,Max;
	Min=ADV[0];
	Max=Min;
	for(i=0;i<Times;i++) 
	{
		 if(ADV[i]<Min) Min=ADV[i];			//统计最小值
		 if(ADV[i]>Max) Max=ADV[i];			//统计最大值
	}
	uint CountAll=0;
	uint Avg=0;
	for(i=0;i<Times;i++) CountAll=CountAll+ADV[i]; 		//统计总数
	CountAll=CountAll-Min-Max;				//去掉最大值，去掉最小值
	Avg=CountAll/(Times-2);					//求平均值
	return Avg;
}

int read_bit(uint x, uchar index) {
    /* 读取一个unsigned int类型二级制形式的某一位 */
    return (x & 1 << index) >> index;
    //算术运算 > 移位运算 > 位运算 > 逻辑运算 > 赋值运算（+=）   
    //例：1 << 3 + 2 && 7等价于 (1 << (3 + 2))&&7
    
}

uint set_bit(uint * x, uchar index) {
    /* 将一个unsigned int类型的二进制的某一位置为1 */
    *x |= 1 << index;
    return *x;
}

uint clear_bit(uint * x, uchar index) {
    /* 将一个unsigned int类型的二进制的某一位置为0 */
    *x &= ~ (1 << index);
    return *x;
}