/*****************************************************
Chip type               : ATmega32
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32.h>
#include <delay.h>

int i;

unsigned char num_code[15]={0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,
                   0x07,0x7F,0x6F,0x80,0x31,0x31,0x79,0x40};

unsigned char shpins[4]={0x70,0xE0,0xB0,0xD0};

void disp_err(void)
{
   for(i=0;i<3;i++)
     {
        PORTC=num_code[i+11];
        PORTB=shpins[i];
        delay_us(500);
     }
     PORTB=0xF0;
}

void ss_s(int num)
{
   int t,l,c=0;
   bit g=1;
   t=num;
   if(num>9999 || num<0)
   {
      disp_err();
   }
   else
   {                     
     while(t!=0 || g)
     {
        t=t/10;
        l=num-t*10;
        num=num/10;
        PORTC=num_code[l];
        PORTB=shpins[c];
        delay_us(500);
        PORTB=0xF0;
        c++;
        g=0;
     }
   }
}

void main(void)
{
DDRC=0xFF;
PORTC=0x4F;
DDRB=0xF0;

while (1)
      {
        ss_s(1188);
        delay_ms(19);
      }
}
