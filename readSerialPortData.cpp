/*
This code was created based on the examples from https://learn.microsoft.com/en-us/previous-versions/ff802693(v=msdn.10)?redirectedfrom=MSDN#reading-and-writing.
By: Kithmi N.D. Widanage
University of Sussex
Date: March 21 2025

Developed for Windows OS.
Tested with Windows 10, GCC compiler with MINGW64 5.4 toolchain on CLion environment.

COM port number should be modified based on the COM port to which the Serial data is being written.
Baud rate should also be updated based on the baud rate of the Serial communication (from the microcontroller)
  */

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

void PrintCommState(DCB dcb)
{
    //  Print some of the DCB structure values
    _tprintf( TEXT("\nBaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d\n"),
              dcb.BaudRate,
              dcb.ByteSize,
              dcb.Parity,
              dcb.StopBits );
}


int _tmain( int argc, TCHAR *argv[] )
{
   DCB dcb;
   HANDLE hCom;
   BOOL fSuccess;

   auto pcCommPort = "\\\\.\\COM5"; // update based on the COM port

   //  Open a handle to the specified com port.
   hCom = CreateFile( pcCommPort,
                      GENERIC_READ | GENERIC_WRITE,
                      0,      //  must be opened with exclusive-access
                      NULL,   //  default security attributes
                      OPEN_EXISTING, //  must use OPEN_EXISTING
                      0,      //  not overlapped I/O
                      NULL ); //  hTemplate must be NULL for comm devices

   if (hCom == INVALID_HANDLE_VALUE)
   {
      //  Handle the error.
      printf ("CreateFile failed with error %d.\n", GetLastError());
      return (1);
   }

   //  Initialize the DCB structure.
   SecureZeroMemory(&dcb, sizeof(DCB));
   dcb.DCBlength = sizeof(DCB);

   //  Build on the current configuration by first retrieving all current
   //  settings.
   fSuccess = GetCommState(hCom, &dcb);

   if (!fSuccess)
   {
      //  Handle the error.
      printf ("GetCommState failed with error %d.\n", GetLastError());
      return (2);
   }

   PrintCommState(dcb);       //  Output to console

   //  Fill in some DCB values and set the com state:
   //  9600 baud rate, 8 data bits, no parity, and 1 stop bit.
   dcb.BaudRate = 9600;          //  baud rate (update based on the serial communication from microcontroller)
   dcb.ByteSize = 8;             //  data size, xmit and rcv
   dcb.Parity   = NOPARITY;      //  parity bit
   dcb.StopBits = ONESTOPBIT;    //  stop bit

   fSuccess = SetCommState(hCom, &dcb);

   if (!fSuccess)
   {
      //  Handle the error.
      printf ("SetCommState failed with error %d.\n", GetLastError());
      return (3);
   }

   //  Get the comm config again.
   fSuccess = GetCommState(hCom, &dcb);

   if (!fSuccess)
   {
      //  Handle the error.
      printf ("GetCommState failed with error %d.\n", GetLastError());
      return (2);
   }

   PrintCommState(dcb);       //  Output to console

   _tprintf (TEXT("Serial port %s successfully reconfigured.\n"), pcCommPort);

   char TempChar; //Temporary character used for reading
   char SerialBuffer[256];//Buffer for storing Rxed Data
   DWORD NoBytesRead;
   int i = 0;
   std::string tempString = "";
   double xData, yData;
   bool isX = true;

   do
   {
      ReadFile( hCom,           //Handle of the Serial port
                &TempChar,       //Temporary character
                sizeof(TempChar),//Size of TempChar
                &NoBytesRead,    //Number of bytes read
                NULL);

      SerialBuffer[i] = TempChar;// Store Tempchar into buffer
      if (SerialBuffer[i] == '\n')
      {
         
         yData = strtod(tempString.c_str(),NULL);
         std::cout<<"x: "<<xData<<"    ";
         std::cout<<"y: "<<yData<<std::endl;
         
         tempString = "";
         i = -1;
         isX = true;
      }
      else
      {
         if (SerialBuffer[i] == ' ')
         {
            xData = strtod(tempString.c_str(),NULL);
            tempString = "";
            isX = false;
         }
         tempString = tempString + SerialBuffer[i];

      }


      i++;
   }

   while (NoBytesRead > 0);

   return (0);
}
