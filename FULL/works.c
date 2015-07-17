/*
Mario Kart Bluetooth Controlled Game
Written by: Yongxuan Li, Michael Ru, Kevin Huo, Sachin Apiah
Group 5
MTE 100 and GENE 121
*/


bool initialize(int & player);
void displayPlayer(int p);
char readBluetooth();
void convertInput(char input, int speed, bool & canShoot, bool speedUp, bool slowDown);
void setMotor(int mA, int mC);
void launchBall();
void checkColour(int & lap, bool & canShoot, bool & speedUp, bool & slowDown,
								int & blue, int & yellow, int & red);
void checkBump(int & numColl, int & time, int stunTime);
void outputScore(float dis, float time, float speed, int numColl, int b, int y, int r);


bool initialize(int & player) //Yongxuan and Sachin
{
	setBluetoothRawDataMode(); //change bluetooth to read the raw data sent
	while (!bBTRawMode) //loop while the mode has not changed
	{
		wait1Msec(1);
	}

	if (nBTCurrentStreamIndex >= 0)//check that the bluetooth connection has occured
	{
		//PlaySoundFile("Startup.rso");
		//while (bSoundActive);

		//menu stuff
		do
		{
			if (nNxtButtonPressed == 2 && player > 0)
			{
				eraseDisplay();
				player--;
			}
			else if (nNxtButtonPressed == 1 && player < 2)
			{
				eraseDisplay();
				player++;
			}

		 while(nNxtButtonPressed != -1);
			displayPlayer(player);

		} while (nNxtButtonPressed != 3);
			while(nNxtButtonPressed != -1);

			eraseDisplay();
		return true;
	}
	else
	{
		//PlaySoundFile("Whoops.rso");
		//while (bSoundActive);
		return false;
	}
}

/*
Players:
0-Peach: Increased boost time, decreased banana slow time
1-Mario: Increased base speed
2-Bowser: Decreased bump stun time
*/
void displayPlayer(int p)
{
	if (p == 0) //peach
	{
		nxtDisplayCenteredTextLine(0, "PEACH");
		nxtDisplayCenteredTextLine(2, "+ mushroom boost");
		nxtDisplayCenteredTextLine(3, "- banana slow");

		///right arrow
		nxtDrawLine(90, 20, 75, 20);
		nxtDrawLine(90, 20, 85, 25);
		nxtDrawLine(90, 20, 85, 15);
	}
	else if (p == 1) //mario
	{
		nxtDisplayCenteredTextLine(0, "MARIO");
		nxtDisplayCenteredTextLine(2, "+ base speed");

		//left arrow
		nxtDrawLine(10, 20, 25, 20);
		nxtDrawLine(10, 20, 15, 25);
		nxtDrawLine(10, 20, 15, 15);

		///right arrow
		nxtDrawLine(90, 20, 75, 20);
		nxtDrawLine(90, 20, 85, 25);
		nxtDrawLine(90, 20, 85, 15);
	}
	else
	{
		nxtDisplayCenteredTextLine(0, "BOWSER");
		nxtDisplayCenteredTextLine(2, "- stun time");

		//left arrow
		nxtDrawLine(10, 20, 25, 20);
		nxtDrawLine(10, 20, 15, 25);
		nxtDrawLine(10, 20, 15, 15);
	}

}

char readBluetooth()// Jerry
{
	ubyte receive[1];
	nxtReadRawBluetooth(receive, 1);
	return (char)receive[0];
}

void convertInput(char input, int speed, bool & canShoot, bool speedUp, bool slowDown) // Michael and Jerry
{
	if (speedUp)
		speed += 20;
	if (slowDown)
		speed -= 20;

		nxtDisplayString(0,"***%c***",input);

	if (input == 'z')
		setMotor(0, 0);
	else if (input == 'p' && canShoot)
	{
		launchBall();
		canShoot = false;
	}
	switch(input)
	{
		case '0':
			setMotor(30,70);
			nxtDisplayString(1,"0");
			break;
		case '1':
			setMotor(40,60);
			nxtDisplayString(1,"1");
			break;
		case '2':
			setMotor(50,50);
			nxtDisplayString(1,"2");
			break;
		case '3':
			setMotor(60,40);
			nxtDisplayString(1,"3");
			break;
		case '4':
			setMotor(70,30);
			nxtDisplayString(1,"4");
			break;
		case '5':
			setMotor(-30,-70);
			nxtDisplayString(1,"5");
			break;
		case '6':
			setMotor(-40,-60);
			nxtDisplayString(1,"0");
			break;
		case '7':
			setMotor(-50,-50);
			break;
		case '8':
			setMotor(-60,-40);
			break;
		case '9':
			setMotor(-70,-30);
			break;
	}

	/*else
	{
		string s = input;
		int num = atoi(s);

		if (num <= 4)
		{
			num -= 2;
		}
		else
		{
			num -= 7;
			speed *= -1;
		}

		if (num < 0)
			setMotor(speed + num * 15, speed - num * 15);
		else
			setMotor(speed - num * 15, speed + num * 15);
	}*/
}

void setMotor(int mA, int mC) //Sachin
{
	motor[motorA] = mA;   //Left Motor
	motor[motorC] = mC;   //Right Motor
}

void launchBall() //Sachin
{
	nMotorEncoder[motorB] = 0;

	motor[motorB] = 50;
	while (nMotorEncoder[motorB] < 360);  //shooting a ball in every revolution of the Motor
	motor[motorB] = 0;

}

void checkColour(int & lap, bool & canShoot, bool & speedUp, bool & slowDown,
	int & blue, int & yellow, int & red) //Michael
{
	int senValue = SensorValue[S1];
	if (senValue != 1 && senValue != 6)
	{
		wait1Msec(50);
		if (SensorValue[S1] == senValue)
		{
			if (senValue == 2) //blue - speedboost
			{
				speedUp = true;
				time1[T2] = 0; //reset timer
				nxtDisplayString(0,"BLUE");
				blue++;
			}

			else if (SensorValue[S1] == 3) //green - finish line
			{
				lap += 1;
				nxtDisplayString(1, "GREEN");

			}

			else if (SensorValue[S1] == 4) //yellow - banana
			{
				slowDown = true;
				time1[T3] = 0; //reset timer
				nxtDisplayString(2,"YELLOW");
				yellow++;
			}

			else //red - ballshooter
			{
				canShoot = true;
				nxtDisplayString(3, "RED");
				red++;
			}
		}
	}
}


void checkBump(int & numColl, int & time, int stunTime) //Kevin
{
	if(SensorValue[S3] == 1 || SensorValue[S4] == 1)
	{
		time += time10[T1];

		motor[motorA] = 0;
		motor[motorC] = 0;
		wait1Msec(stunTime);

		time1[T1] = 0;
		numColl++;
	}
}

void outputScore(float dis, float time, float speed, int numColl, int b, int y, int r) // Kevin
{

	while(nNxtButtonPressed == -1);
	while (nNxtButtonPressed != -1);

	//PlaySoundFile("   .rso");
	//while(bSoundActive);
	nxtDisplayString(0, "Crashes: %d", numColl);
	wait10Msec(20);

	//PlaySoundFile("   .rso");
	//while(bSoundActive);
	nxtDisplayString(1, "Bananas: %d", y);
	wait10Msec(20);

	//PlaySoundFile("   .rso");
	//while(bSoundActive);
	nxtDisplayString(2, "Mushrooms: %d", b);
	wait10Msec(20);

	//PlaySoundFile("   .rso");
	//while(bSoundActive);
	nxtDisplayString(3, "Green Shells: %d", r);
	wait10Msec(20);

	nxtDisplayString(7, "PRESS BUTTON TO CONTINUE");
	while (nNxtButtonPressed == -1);
	while (nNxtButtonPressed != -1);
	eraseDisplay();

	//PlaySoundFile("   .rso");
	//while(bSoundActive);
	nxtDisplayString(0, "Total Time Taken:");
	nxtDisplayString(1, "%.2f s", time);
	wait10Msec(20);

	//PlaySoundFile("   .rso");
	//while(bSoundActive);
	nxtDisplayString(2, "Total Distance:");
	nxtDisplayString(3, "%.2f m", dis);
	wait10Msec(20);

	//PlaySoundFile("   .rso");
	//while(bSoundActive);
	nxtDisplayString(5,"Average Speed:");
	nxtDisplayString(6,"%.2f cm/s",speed);
	wait10Msec(20);

	nxtDisplayString(7, "PRESS BUTTON TO CONTINUE");
	while (nNxtButtonPressed == -1);
	while (nNxtButtonPressed != -1);
	eraseDisplay();

	//PlaySoundFile("   .rso");
	//while(bSoundActive);
	nxtDisplayCenteredBigTextLine(4,"TALLYING SCORE...");
	wait10Msec(100);

	//PlaySoundFile("   .rso");
	//while(bSoundActive);
	nxtDisplayCenteredBigTextLine(3,"TOTAL SCORE:");
	nxtDisplayCenteredBigTextLine(4,"%,2f", speed + b + r - y - numColl);
	nxtDisplayCenteredTextLine(6, "Thanks for Playing!");
	nxtDisplayCenteredTextLine(7, "Made by Group5Games");

	while(nNxtButtonPressed == -1);
}

/*
Players:
0-Peach: Increased boost time, decreased banana slow time
1-Mario: Increased base speed
2-Bowser: Decreased bump stun time
*/


task main()
{

	int blue = 0, yellow = 0, red = 0, numColl = 0, ; //keep track of how many colours and collisions hit
	int lap = 1, player = 1;//default to mario
	int bananaSlow = 2000, speedBoost = 1500, stunTime = 1500; //timings for special events
	int defaultSpeed = 50;

	float totDis = 0, totTime = 0;
	float avgSpeed = 0;

	bool canShoot = false, speedUp = false, slowDown = false;

	SensorType[S1] = sensorCOLORFULL;
	SensorType[S3] = sensorTouch;
	SensorType[S4] = sensorTouch;

	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorB] = 0;

	time1[T1] = 0; //for total race length
	time1[T2] = 0; //for speedup
	time1[T3] = 0; //for slowdown

	if (initialize(player))
	{
		//setup each player's abilities

		if (player == 0)//peach
		{
			bananaSlow -= 500;
			speedBoost += 500;
		}
		else if (player == 1)//mario
			defaultSpeed = 60;
		else //bowser
			stunTime -= 500;

		do
		{
			if (time1[T2] > speedBoost)
				speedUp = false;
			if (time1[T3] > bananaSlow)
				slowDown = false;

			if (time10[T1] > 32000)
			{
				totTime += time10[T1]/100.0;
				time10[T1] = 0;
			}

			if (nMotorEncoder[motorA] > 32000)
			{
				totDis += (8.2 * PI / 360.0) * nMotorEncoder[motorA];
				nMotorEncoder[motorA] = 0;
			}

			//game loop
			convertInput(readBluetooth(), defaultSpeed, canShoot, speedUp, slowDown);

			checkColour(lap, canShoot, speedUp, slowDown, blue, yellow, red);

			checkBump(numColl, totTime, stunTime);


		} while (true);//(lap <= 3);

		setMotor(0, 0);

		totTime += time10[T1]/100;
		totDis += (8.2 * PI / 360.0) * nMotorEncoder[motorA];
		avgSpeed = (float)totDis / totTime;

		nxtDisplayString(0, "Click to show score!");
		while (nNxtButtonPressed == -1);
		while (nNxtButtonPressed != -1);
		eraseDisplay();

		outputScore(totDis, totTime, avgSpeed, numColl, blue, yellow, red);
		wait10Msec(100);
	}

	else
	{
		nxtDisplayString(4, "No Connection");
		while(nNxtButtonPressed == -1);
		while(nNxtButtonPressed != -1);
	}
}
