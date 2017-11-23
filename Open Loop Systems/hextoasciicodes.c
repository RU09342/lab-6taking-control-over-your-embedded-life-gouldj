#include <stdio.h>
#include <stdlib.h>

//converts asci to hex
void converthex(char *data, unsigned int a); //declaration
char buffer[100];
char RecvData[64] = "474F4420426C65737320416D657269636121";

int main(int argc, char *argv[])
{
  int x = 25;
  char temp[10];
  converthex(temp, x);
  printf("%d is converted into %s \n ", x, temp);
  system("PAUSE");	
  return 0;
}


void converthex(char *data, unsigned int a) //definition
{
   unsigned int temp =a;
   int digits = 0 , set;
   int i=0;
   unsigned int x;
   unsigned int mask;
   mask=0x0f;
   while(temp!=0)
   {
        temp=temp/16;
        digits++;
        if(digits>1) mask = mask << 4;
   }
   set=digits;
   set--;
  
   data[i]='0';
   i++;
   data[i]='x';
   i++;
   temp=a;
   while(digits!=0)
   { 
        x=(temp&mask);
        x=x>>(set*4);
        if(x<=9)data[i]=0x30+x;
        else
        {
            data[i]=0x41+(x-10);
        }
        digits--;
        i++;
        temp=temp<<4;  
   }
    data[i]='\0';
}





void converthex(char *data, unsigned int a) //definition
{
	char *ptrBuffer = &buffer[0];

	for (int i = 0; i < sizeof(RecvData); i += 2)
	{
		int	firstvalue = RecvData[i] - '0';
		int	secondvalue;
		//if RecvData[i+1] is a letter convert it to integer, otherwise use it.
		switch (RecvData[i + 1])
		{
		case 'A':
		{
			secondvalue = 10;

		}break;
		case 'B':
		{
			secondvalue = 11;

		}break;
		case 'C':
		{
			secondvalue = 12;

		}break;
		case 'D':
		{
			secondvalue = 13;

		}break;
		case 'E':
		{
			secondvalue = 14;

		}break;
		case 'F':
		{
			secondvalue = 15;

		}break;
		default:
			secondvalue = RecvData[i + 1] - '0';
			break;
		}

		int newval;

		//convert the two values into decimal form
		newval = 16 * firstvalue + secondvalue;

		//change newval into a character
		*ptrBuffer = char(newval);

		//increment ptrBuffer
		cout << ptrBuffer;

		ptrBuffer++;
	}
}
