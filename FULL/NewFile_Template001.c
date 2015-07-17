
task main()
{
	nMotorEncoder[motorA]= 0;
	motor[motorA] = 50;
	motor[motorC] = 50;
	while(nMotorEncoder[motorA] < 360);
	motor[motorA] = 0;
	motor[motorC] = 0;


}
