// Copyright (C) 2013 rastating
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.

#ifndef LEDDisplay_h
#define LEDDisplay_h

#include "Arduino.h"
#include "LEDDisplay.h"

LEDDisplay::LEDDisplay(int numberOfDigits, int digitFlagPins[], int segmentPins[], int decimalPointPin)
{		
	this->decimalPointPin = decimalPointPin;
	this->binaryValueMap[0] = B00111111;
	this->binaryValueMap[1] = B00000110;
	this->binaryValueMap[2] = B01011011;
	this->binaryValueMap[3] = B01001111;
	this->binaryValueMap[4] = B01100110;
	this->binaryValueMap[5] = B01101101;
	this->binaryValueMap[6] = B01111101;
	this->binaryValueMap[7] = B00000111;
	this->binaryValueMap[8] = B01111111;
	this->binaryValueMap[9] = B01101111;
	this->binaryValueMap[10] = B10000000;
		
	// Initialise all the pins and clear the display.
	this->digitCount = numberOfDigits;
	for (int i = 0; i < this->digitCount; i++)
	{
		this->digitFlagPins[i] = digitFlagPins[i];
		pinMode(this->digitFlagPins[i], OUTPUT);
		digitalWrite(this->digitFlagPins[i], 0);
	}
	
	this->segmentCount = 8;
	for (int i = 0; i < this->segmentCount; i++)
	{
		this->segmentPins[i] = segmentPins[i];
		pinMode(this->segmentPins[i], OUTPUT);
		digitalWrite(this->segmentPins[i], 1);
	}
}

void LEDDisplay::clearDisplay()
{
	for (int i = 0; i < this->segmentCount; i++)
	{
		digitalWrite(this->segmentPins[i], 1);
	}
}

void LEDDisplay::displayNumber(int number, int digit, bool showDecimalPoint)
{
	// Clear all the segments to avoid background flickering.
	this->clearDisplay();
	
	// As we can only show a single number, ensure the number passed
	// to the method is between 0 and 9.		
	if (number >= 0 && number <= 9)
	{
		// Set the digit we want to write to.
		for (int i = 0; i < this->digitCount; i++)
		{
			digitalWrite(this->digitFlagPins[i], i == digit ? 1 : 0);
		}
		
		/* 
			Loop through each segment pin, and if the matching bit is set
			in the binary map then light it up!
		   
			Example: the value 1 is mapped to B00000110, which means we have to light up pins 2 and 3 
			Remember, we are counting backwards in binary, so the last digit is actually the first.
			Hence the two 1s in the value are pins 2 and 3.
		*/
		for (int i = 0; i < this->segmentCount; i++)
		{
			if (bitRead(this->binaryValueMap[number], i) == 1)
			{
				digitalWrite(this->segmentPins[i], 0);
			}
			else
			{
				digitalWrite(this->segmentPins[i], 1);
			}
		}
		
		// Show the decimal point if specified.
		if (showDecimalPoint)
		{
			digitalWrite(this->decimalPointPin, 0);
		}
	}
}

void LEDDisplay::displayNumber(int number, int digit)
{
	this->displayNumber(number, digit, false);
}

void LEDDisplay::displayDecimalPoint(int digit)
{
	// Set the digit we want to write to.
	for (int i = 0; i < this->digitCount; i++)
	{
		digitalWrite(this->digitFlagPins[i], i == digit ? 1 : 0);
	}
	
	// Show the decimal point.
	digitalWrite(this->decimalPointPin, 0);
}

#endif