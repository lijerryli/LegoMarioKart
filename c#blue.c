task main()
{
   string str1 = "";
   const int kMaxSizeOfMessage = 56;
   ubyte nReceiveBuffer[kMaxSizeOfMessage];

   setBluetoothRawDataMode();  // set Bluetooth to "raw mode"
   while (!bBTRawMode)         // while the Bluecore is still NOT in raw mode (bBTRawMode == false):
   {
     wait1Msec(1);               // wait for Bluecore to enter raw data mode
   }

   while(nNxtButtonPressed != 3){
      if(nBTCurrentStreamIndex >= 0)  // if there is currently an open Bluetooth connection:
      {
        nxtDisplayTextLine(1,"Success");
         nxtReadRawBluetooth(nReceiveBuffer, 6);
         string as = (char)nReceiveBuffer[0];
         nxtDisplayString(6,"%s",as);

         if(as == "q") wait1Msec(2000);
         /*int length = (int)nReceiveBuffer[0] - 1;
         nxtReadRawBluetooth(nReceiveBuffer, length);
         for(int i = 0; (byte)nReceiveBuffer[i] != 0; i++){
            str1 = (char)nReceiveBuffer[0];
         }
         nxtDisplayTextLine(2,"%s",str1);
         length = 0;
         str1 = "";*/
      }
      else{
         nxtDisplayTextLine(1,"Fail");
         nxtDisplayTextLine(5,"%3d, %3d",cCmdBTCheckStatus(nBTCurrentStreamIndex));
      }

      wait1Msec(20);

   }
   wait1Msec(10);
   btDisconnectAll();
   wait1Msec(10);
}
