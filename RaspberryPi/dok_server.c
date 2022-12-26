#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

char device[] = "/dev/ttyACM0";

int serial;
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
		printf("%c", newChar);
		fflush(stdout);
	}
}

int main() {
	setup();
	while(1) loop();
	return 0;
}
