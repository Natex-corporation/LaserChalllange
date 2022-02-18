#include <iostream>
#include<string>
#include<stdlib.h>
#include"SerialPort.h"
using namespace std;


char output[MAX_DATA_LENGHT];
char* port = "\\\\.\\COM4";
CHAR INCOMING[MAX_DATA_LENGHT];
int main() {

	SerialPort arduino(port);

	if (arduino.isConected()) {
		cout << "conected" << endl;
	}
	else() {
		cout << "error" << endl;
	}
	while (arduino.isConected()) {
		arduino.readSerialPort(output, MAX_DATA_LENGHT);
		cout << output << endl;
	}
	return 0;
}