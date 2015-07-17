using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace robotBlue
{
    class Program
    {
        static void Main(string[] args)
        {
            SerialPort BluetoothConnection = new SerialPort();
            BluetoothConnection.PortName = "COM40";
            // Replace this COM port by the appropriate one on your computer
            Console.WriteLine("Connecting");
            try
            {
                BluetoothConnection.Open();
                BluetoothConnection.ReadTimeout = 1500;
            }
            catch (Exception e)
            {
                Environment.Exit(0);
            }
            Console.WriteLine("Connected");
            string last = "";
            while (true)
            {
                
      
                string a = Console.ReadKey(true).KeyChar.ToString();

                if (a != "z" || last != "z")
                {
                    Console.Write(a);
                    BluetoothConnection.Write(a);
                    last = a;
                }

                //SendMsg(Console.ReadLine(), false, 0, BluetoothConnection);
            }
            BluetoothConnection.Close();
        }
        public static void SendMsg(string message, bool reply, int inbox, SerialPort BluetoothConnection)
        {
            byte[] command;
            int length = message.Length;
            command = new byte[length + 7];

            int i = 0;

            if (length + 6 > 55)
            {
                length = 49;
            }
            command[0] = (byte)(length + 5);  //command length
            command[1] = 0x00;
            if (reply)
            {
                command[2] = 0x00;
            }
            else
            {
                command[2] = 0x80;
            }
            command[3] = 0x09;
            if (inbox > 9)
            {
                inbox = 9;
            }
            command[4] = (byte)inbox;
            command[5] = (byte)(length + 1);
            while (i < length)
            {
                command[i + 6] = (byte)message[i];
                i++;
            }
            command[i + 6] = (byte)'\0';
            BluetoothConnection.Write(command, 0, length + 6);
        }   
    }
}
