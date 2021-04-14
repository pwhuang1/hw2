#include "mbed.h"
#include "uLCD_4DGL.h"
 


AnalogOut aout(D7);
AnalogIn ain(A3);
uLCD_4DGL uLCD(D1, D0, D2);
DigitalIn up(A0);
DigitalIn down(A1);
DigitalIn confirm(A2);


/*
int main(void)
{
   while (1) {
      // change the voltage on the digital output pin by 0.1 * VCC
      //  and print what the measured voltage should be (assuming VCC = 3.3v)


      //float f = 3.0;
      for (float i = 0.0; i < 3.0; i += 0.001) {
            aout = i;
            if (i == 1.0)
               break;

            //printf("aout = %f volts\n", aout.read() * 3.0f);
            // turn on the led if the voltage is greater than 0.5f * VCC
            //dout = (aout > 0.5f) ? 1 : 0;
            //ThisThread::sleep_for(1s);
      }

      for (float i = 1.0; i > 0.0 ; i -= 0.000001) {
            aout = i;
            if (i == 0.0)
               break;
      }
   }
}
*/


float i;
int j;
int l;
int freq = 720;
int x;
int y;
float T = 1000/freq;
float ADCdata[128];
int conf = 0;
int main(void)
{
    uLCD.text_width(4);
    uLCD.text_height(4);
    uLCD.locate(1,2);
    uLCD.printf("%d\n", freq);
    
    while(1){
        if(up==1){
            if(freq < 970)
                freq = freq + 50;
            else
                freq = freq; 
            uLCD.text_width(4);
            uLCD.text_height(4);
            uLCD.locate(1,2);
            uLCD.printf("%d\n", freq);
        }
        if(down==1){
            if(freq > 120)
                freq = freq - 50;
            else
                freq = freq;
            uLCD.text_width(4);
            uLCD.text_height(4);
            uLCD.locate(1,2);
            uLCD.printf("%d\n", freq);
        }
        if(confirm==1){
            conf = 1;
            T = 1000 / freq;
            uLCD.text_width(4);
            uLCD.text_height(4);
            uLCD.locate(1,2);
            uLCD.printf("%d\n", freq);
        }
        
        x = 105;
        y = 70;
        
        
        for (i = 0; i < 0.9; i +=  T / x) {
            aout = i;
        }
        for (i = 0.9; i > 0; i -=  T / y) {
            aout = i;
        }
        
        if(conf==1){
            for(j = 0; j < 128; j++){
                ADCdata[j] = ain;
                ThisThread::sleep_for(1000ms/freq);
            }
            if(j == 127){
                printf("%d\r\n", freq);
                for(l=0; l<128; l++){
                    printf("%f\r\n", ADCdata[l]);
                    ThisThread::sleep_for(1000ms/freq);
                }
                j = 0;
            }
            conf = 0;
        }
    }
}


