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

class LEDDisplay
{
	public:
		LEDDisplay(int numberOfDigits, int digitFlagPins[], int segmentPins[], int decimalPointPin);
		void displayNumber(int number, int digit, bool showDecimalPoint);
		void displayNumber(int number, int digit);
		void displayDecimalPoint(int digit);
		void clearDisplay();
	private:
		int digitFlagPins[4];
		int segmentPins[8];
		int binaryValueMap[11];
		int decimalPointPin;
		int digitCount;
		int segmentCount;
};