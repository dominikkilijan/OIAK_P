#pragma once
class IEEE16
{
public:
	union
	{
		short fValue;

		struct
		{
			unsigned int mantissa : 10;
			unsigned int exponent : 5;
			unsigned int sign : 1;
		};
	};

	IEEE16(short value)
	{
		fValue = value;
	}
	void printNumber();
};


