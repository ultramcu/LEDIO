/*
NOTE

HARDWARE : Raspberry PI
IO_LIB : BCM2835 (http://www.open.com.au/mikem/bcm2835/)
AUTHER : MaIII Themd
EMAIL : maiii.themd@gmail.com
COMPILER : gcc version 4.6.3 (Debian 4.6.3-12+rpi1)
SINCE : 15/02/2013

Copyright www.pishared.com


*/



#include <bcm2835.h>
#include <stdint.h>
#include <stdio.h>

#define _NO_OF_LED_ 10
RPiGPIOPin LED[_NO_OF_LED_];

/*
LED brigthness pattern
*/
uint8_t LED_BRIGTH[11][10] = {
 
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,1,1,1,1},
    {0,0,0,0,0,1,1,1,1,1},
    {0,0,0,0,1,1,1,1,1,1},
    {0,0,0,1,1,1,1,1,1,1},
    {0,0,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1}
};


#define _NO_OF_PATTERN_ 73
/*
IN ROW : LED0,LED1,LED2,LED3...LED9,DELAY_IN_uSec
*/
int32_t LED_PATTERN[_NO_OF_PATTERN_][11] = 
    {
        {9,0,0,0,0,0,0,0,0,0,50000},
        {8,9,0,0,0,0,0,0,0,0,50000},
        {7,8,9,0,0,0,0,0,0,0,50000},
        {6,7,8,9,0,0,0,0,0,0,50000},
        {5,6,7,8,9,0,0,0,0,0,50000},
        {4,5,6,7,8,9,0,0,0,0,50000},
        {3,4,5,6,7,8,9,0,0,0,50000},
        {2,3,4,5,6,7,8,9,0,0,50000},
        {1,2,3,4,5,6,7,8,9,0,50000},
        {0,1,2,3,4,5,6,7,8,9,50000},
        {0,0,1,2,3,4,5,6,7,8,50000},
        {0,0,0,1,2,3,4,5,6,7,50000},
        {0,0,0,0,1,2,3,4,5,6,50000},
        {0,0,0,0,0,1,2,3,4,5,50000},
        {0,0,0,0,0,0,1,2,3,4,50000},
        {0,0,0,0,0,0,0,1,2,3,50000},
        {0,0,0,0,0,0,0,0,1,2,50000},
        {0,0,0,0,0,0,0,0,0,1,50000},
        {0,0,0,0,0,0,0,0,0,0,100000},
        {0,0,0,0,0,0,0,0,0,9,50000},
        {0,0,0,0,0,0,0,0,9,8,50000},
        {0,0,0,0,0,0,0,9,8,7,50000},
        {0,0,0,0,0,0,9,8,7,6,50000},
        {0,0,0,0,0,9,8,7,6,5,50000},
        {0,0,0,0,9,8,7,6,5,4,50000},
        {0,0,0,9,8,7,6,5,4,3,50000},
        {0,0,9,8,7,6,5,4,3,2,50000},
        {0,9,8,7,6,5,4,3,2,1,50000},
        {9,8,7,6,5,4,3,2,1,0,50000},
        {8,7,6,5,4,3,2,1,0,0,50000},
        {7,6,5,4,3,2,1,0,0,0,50000},
        {6,5,4,3,2,1,0,0,0,0,50000},
        {5,4,3,2,1,0,0,0,0,0,50000},
        {4,3,2,1,0,0,0,0,0,0,50000},
        {3,2,1,0,0,0,0,0,0,0,50000},
        {2,1,0,0,0,0,0,0,0,0,50000},
        {1,0,0,0,0,0,0,0,0,0,50000},
        {0,0,0,0,0,0,0,0,0,0,100000},
        {1,1,1,1,1,1,1,1,1,1,100000},
        {2,2,2,2,2,2,2,2,2,2,100000},
        {3,3,3,3,3,3,3,3,3,3,100000},
        {4,4,4,4,4,4,4,4,4,4,100000},
        {5,5,5,5,5,5,5,5,5,5,100000},
        {6,6,6,6,6,6,6,6,6,6,100000},
        {7,7,7,7,7,7,7,7,7,7,100000},
        {8,8,8,8,8,8,8,8,8,8,100000},
        {9,9,9,9,9,9,9,9,9,9,100000},
        {0,0,0,0,0,0,0,0,0,0,100000},

        {9,0,9,0,9,0,9,0,9,0,1000000},
        {0,9,0,9,0,9,0,9,0,9,1000000},
        {9,0,9,0,9,0,9,0,9,0,1000000},
        {0,9,0,9,0,9,0,9,0,9,1000000},
        {0,0,0,0,0,0,0,0,0,0,100000},

        {9,0,0,0,0,0,0,0,0,9,100000},
        {8,9,0,0,0,0,0,0,9,8,100000},
        {7,8,9,0,0,0,0,9,8,7,100000},
        {6,7,8,9,0,0,9,8,7,6,100000},
        {5,6,7,8,9,9,8,7,6,5,100000},
        {0,6,7,8,9,9,8,7,6,0,100000},
        {0,0,7,8,9,9,8,7,0,0,100000},
        {0,0,0,8,9,9,8,0,0,0,100000},
        {0,0,0,0,9,9,0,0,0,0,100000},
        {0,0,0,0,0,0,0,0,0,0,100000},
        {0,0,0,0,9,9,0,0,0,0,100000},
        {0,0,0,9,9,9,9,0,0,0,100000},
        {0,0,9,9,9,9,9,9,0,0,100000},
        {0,9,9,9,9,9,9,9,9,0,100000},
        {9,9,9,9,9,9,9,9,9,9,100000},
        {9,9,9,9,0,0,9,9,9,9,100000},
        {9,9,9,0,0,0,0,9,9,9,100000},
        {9,9,0,0,0,0,0,0,9,9,100000},
        {9,0,0,0,0,0,0,0,0,9,100000},
        {0,0,0,0,0,0,0,0,0,0,100000}

    };


uint8_t LED_MAP[_NO_OF_LED_];


int led_play()
{
    int pt = 0;
    int no_led = 0;
    int blink_pattern = 0;


    while(1)
    {
        for(pt = 0; pt < _NO_OF_PATTERN_; pt++)
        {
            for(blink_pattern = 0; blink_pattern < _NO_OF_LED_; blink_pattern++)
            {
                for(no_led = 0; no_led < _NO_OF_LED_; no_led++)
                {
                    if(LED_BRIGTH[LED_PATTERN[pt][no_led]][blink_pattern] == 1)
                    {
                        bcm2835_gpio_write(LED[no_led], LOW);
                    }
                    else
                    {
                        bcm2835_gpio_write(LED[no_led], HIGH); 
                    }
                    usleep(50);
                }
            }
            usleep(LED_PATTERN[pt][10]);
        }
    }

}


int main()
{
    uint8_t i = 0;

    LED[0] = RPI_GPIO_P1_11;
    LED[1] = RPI_GPIO_P1_15;
    LED[2] = RPI_GPIO_P1_16;
    LED[3] = RPI_GPIO_P1_18;
    LED[4] = RPI_GPIO_P1_19;
    LED[5] = RPI_GPIO_P1_21;
    LED[6] = RPI_GPIO_P1_22;
    LED[7] = RPI_GPIO_P1_23;
    LED[8] = RPI_GPIO_P1_24;
    LED[9] = RPI_GPIO_P1_26;


    if (!bcm2835_init())
    {
        return 1;
    }

    for(i = 0; i < _NO_OF_LED_; i++)
    {
        bcm2835_gpio_fsel(LED[i], BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_write(LED[i], HIGH);
        LED_MAP[i] = 0;
    }
    
    led_play();


    return 0;
}



//eof
