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


task main()
{
		int player = 1;
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
		nxtDisplayString(0,"%d", player);
wait1Msec(6000);
}
