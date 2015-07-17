//Bluetooth Code

bool initialize(int & player)
{
	setBluetoothRawDataMode(); //change bluetooth to read the raw data sent
  while (!bBTRawMode) //loop while the mode has not changed
  {
    wait1Msec(1);
  }

 	if(nBTCurrentStreamIndex >=0)//check that the bluetooth connection has occured
 	{
   	PlaySoundFile("Startup.rso");
   	while(bSoundActive);

   	//menu stuff

   	return true;
 	}
 	else
 	{
 		PlaySoundFile("Whoops.rso");
 		while(bSoundActive);
 		return false;
 	}
}


char readBluetooth()
{
	ubyte receive[1];
	nxtReadRawBluetooth(receive, 1)
	return (char)receive[0];
}


task main()
{
	int player = 0;
	initialize(player);
	while(true)
	{
		string in = readBluetooth();
		nxtDisplayString(0, "%s", in);
		}

}
