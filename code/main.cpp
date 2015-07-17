#include <iostream>
#include <conio.h>
#include "nxt.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
	
	Connection *connection = new Bluetooth();  
	Sensor *sensor1 = new Touch(IN_1, connection);  
	Motor *motorA = new Motor(OUT_A, connection); 
	Motor *motorC = new Motor(OUT_C, connection);
	Brick *brick = new Brick(connection);
	
int main(int argc, char** argv) {

try{
	cout << "Try to connect to the NXT" << endl;  
    connection->connect(40);  
    cout << "Connected" << endl;  
	
	while(true)
	{
		char a = getch();
		cout << a;
		switch(a)
		{	
					
			case 'k':
				motorA->on(50);
				motorC->on(50);
				break;
				
			case 'q':
				motorA->on(-80);
				motorC->on(-20);
				break;
				
			case 'w':
				motorA->on(-70);
				motorC->on(-30);
				break;
				
			case 'e':
				motorA->on(-60);
				motorC->on(-40);
				break;
				
			case 'r':
				motorA->on(-100);
				motorC->on(-100);
				if(character == mario)
				{
					speed +=5
				}
				break;
				
			case 't':
				motorA->on(-40);
				motorC->on(-60);
				break;
				
			case 'y':
				motorA->on(-30);
				motorC->on(-70);
				break;
				
			case 'u':
				motorA->on(-20);
				motorC->on(-80);
				break;
			case 'z':
				motorA->off();
				motorC->off();
				break;
			default:
				motorA->off();
				motorC->off();
				break;
		}
		
		if(sensor1->print() == "Pressed")
		{
			cout << "stopping";
			while(true)
			{
				motorA->off();
				motorC->off();
			}
		}
		
	}
	
}
    
catch(int e){
	
}

    connection->disconnect();  
	
	
	return 0;
}
