/*--------------------------------------------------
注意：部分源程序给出如下。请勿改动主函数main和其它
      函数中的任何内容，仅在函数的花括号中填入所编
      写的若干语句。
-------------------------------------------------------*/
#include <iostream>
#include <cmath>
using namespace std;

int selfhold(long number);

int main()
{

        long number;
        for(number=0;number<200000;number++)
        {
                if(selfhold(number)==1)
                {
                        cout<<number<<endl;
                }
        }

        return 0;
}


int selfhold(long number) /*判断数number是否是一个自守数*/
{
/**********Program**********/                
        long _pow = number * number, _number=number, wei=0;
        int count=0;
        while (_number){
                _number/=10;
                count++;
        }
        wei = _pow % (long)pow(10,count);
        if (wei == number)
                return 1;
        else
                return 0;
/**********Program**********/                
}