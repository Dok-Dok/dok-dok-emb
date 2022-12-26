#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

char device[] = "/dev/ttyACM0";

int serial;
int isOpen = 0; // 0: close / 1: open 
int count = 0;
char str[10];
unsigned long baud = 9600;
unsigned long time = 0;

int main(void);
void loop(void);
void setup(void);

void setup() {
	printf("%s \n", "Start Raspberry!");
	fflush(stdout);
	
	if ((serial = serialOpen(device, baud)) <0) {
		fprintf(stderr, "Unable to open serial device : %s\n", strerror(errno));
		exit(1);
	}
	
	if (wiringPiSetup() == -1) {
		fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
		exit(1);
	}
}

void loop() {
	if(serialDataAvail(serial)) {
		char newChar = serialGetchar(serial);
		if(newChar != '\n') {
			str[count++] = newChar;
		} else {
			count = 0;
			int num = atoi(str);
			if(num > 15) {
				// 문이 열렸을 경우
				printf("%d open\n", num);
				if(isOpen == 0) {
					isOpen = 1;
					// 문에 변화가 생긴 것. TODO. 안드로이드에 open 사실 알리기
				}
			} else {
				// 문이 닫혔을 경우
				printf("%d close\n", num);
				if(isOpen == 1) {
					isOpen = 0;
					// 문에 변화가 생긴 것. TODO. 안드로이드에 close 사실 알리기
				}
			}
			for(int i = 0; i < 10; i++) {
				str[i] = '\0';
			}
		}
		//printf("%c", newChar);
		fflush(stdout);
	}
}

int main() {
	setup();
	while(1) loop();
	return 0;
}
