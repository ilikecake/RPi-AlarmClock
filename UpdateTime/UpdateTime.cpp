#include <iostream>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <climits>
#include <unistd.h>
#include <iostream>

#include "SparkFunSX1509.h"
#include "Adafruit_LEDBackpack.h"

#define 	LED_PIN_NUM		7
#define 	BTN_PIN_NUM		8

#define 	LED_PIN_NUM_SUNDAY			1
#define 	LED_PIN_NUM_MONDAY			1
#define 	LED_PIN_NUM_TUESDAY			1
#define 	LED_PIN_NUM_WEDNESDAY		1
#define 	LED_PIN_NUM_THURSDAY		1
#define 	LED_PIN_NUM_FRIDAY			1
#define 	LED_PIN_NUM_SATURDAY		1
#define 	LED_PIN_NUM_AMPM			7
#define 	LED_PIN_NUM_ALARM			1

#define 	BTN_PIN_NUM_SNOOZE			1
#define 	BTN_PIN_NUM_DIMUP			1
#define 	BTN_PIN_NUM_DIMDN			1
#define 	BTN_PIN_NUM_ALARM_ACK		1
#define 	BTN_PIN_NUM_ALARM_STATE		1


#define		IO_INT_PIN		7	//The pin on the GPIO header that is attached to the interrupt signal. Expressed in the wiringPi simplified numbering scheme. (http://wiringpi.com/pins/)

using namespace std;


void HandleButtonPress(void);

char SX1509_Address = 0x3e;
SX1509 io; // Create an SX1509 object
Adafruit_7segment LED_Disp;

int main()
{
	int fd, result;
	int LED_State = LOW;
	unsigned int button_pressed = 0;
	tm TheTime;
	float TimeToWrite;
	bool IsPM;
	
	time_t t = time(0);
	localtime_r(&t, &TheTime);
	
	if(TheTime.tm_hour > 12)
	{
		TimeToWrite = (TheTime.tm_hour-12)+TheTime.tm_min/100.;
		IsPM = true;
	}
	else if(TheTime.tm_hour == 0)
	{
		TimeToWrite = 12+TheTime.tm_min/100.;
		IsPM = true;
	}
	else
	{
		TimeToWrite = TheTime.tm_hour+TheTime.tm_min/100.;
		IsPM = false;
	}
	
	printf("Time: %4.2f", TimeToWrite);
	
	if(IsPM)
	{
		printf(" PM\n");
	}
	else
	{
		printf(" AM\n");
	}
	
	/*if now.hour > 12:
		TimeToPrint = (now.hour-12)+now.minute/100.
		IsPM = True
	elif now.hour == 0:
		TimeToPrint = 12+now.minute/100.
		IsPM = True
	else:
		TimeToPrint = (now.hour)+now.minute/100.
		IsPM = False*/
	
	//printf("%d:%d %d/%d/%d\n", TheTime.tm_hour, TheTime.tm_min, TheTime.tm_mday, TheTime.tm_mon+1, TheTime.tm_year+1900);
	
	wiringPiSetup();
	pinMode(IO_INT_PIN, INPUT);
	pullUpDnControl(IO_INT_PIN, PUD_OFF);
	wiringPiISR(IO_INT_PIN, INT_EDGE_FALLING, &HandleButtonPress);
	
	//SX1509 io; // Create an SX1509 object
	if (!io.begin(SX1509_Address))
	{
		printf("SX1509 Not Found");
	}

	//Basic setup of expander
	io.clock(INTERNAL_CLOCK_2MHZ, 4);
	io.debounceTime(4);	//Sed debounce time to 8ms (I think)
	
	//Set up LED
	io.pinMode(LED_PIN_NUM, OUTPUT);
	io.digitalWrite(LED_PIN_NUM, LOW);
	
	//Set up button
	io.pinMode(BTN_PIN_NUM, INPUT_PULLUP);
	io.debouncePin(BTN_PIN_NUM);
	io.enableInterrupt(BTN_PIN_NUM, FALLING);
	io.interruptSource();
	
	for(int i=0;i<10;i++)
	{
		delay(200);
		io.digitalWrite(LED_PIN_NUM, HIGH);
		delay(200);
		io.digitalWrite(LED_PIN_NUM, LOW);
	}
	
	//Make sure LED is off
	io.digitalWrite(LED_PIN_NUM, LOW);
	
	//Set up the LED display
	LED_Disp.begin(0x70);
	
	LED_Disp.setBrightness(2);
	
	
	LED_Disp.clear();
	LED_Disp.printFloat(12.34);
	LED_Disp.drawColon(true);
	LED_Disp.writeDisplay();
	
	while(1)
	{
	
		//interruptSource(bool clear = true);
	
		/*if (digitalRead(IO_INT_PIN))
		{
			printf("Pin 7 is HIGH\n");
		}
		else
		{
			//Interrupt is triggered
			button_pressed = io.interruptSource();
			printf("Pin 7 is LOW, Source is %u\n", button_pressed);
			button_pressed = 0;
		}*/
		//delay(500);
		sleep(UINT_MAX);
	
		/*if (io.digitalRead(BTN_PIN_NUM) == LOW)
		{
			// If the button is pressed toggle the LED:
			LED_State = !LED_State;
			io.digitalWrite(LED_PIN_NUM, LED_State);
			while (io.digitalRead(BTN_PIN_NUM) == LOW)
				; // Wait for button to release
		}*/
	}

	return 0;
}


void HandleButtonPress(void)
{
	unsigned int button_pressed = 0;

	button_pressed = io.interruptSource();
	printf("Pin 7 is LOW, Source is %u\n", button_pressed);
	fflush(stdout);

	return;
}
