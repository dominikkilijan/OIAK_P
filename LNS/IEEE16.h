#pragma once
#include "IEEE32.h"
class IEEE16
{
public:

		struct
		{
			unsigned int mantissa : 10;
			unsigned int exponent : 5;
			unsigned int sign : 1;
		};

	IEEE16()
	{
		this->sign = 0;
		this->exponent = 0;
		this->mantissa = 0;
	}
	IEEE16(IEEE32 initNumber)
	{
		this->setValue(initNumber);
	}
	void setValue(IEEE32 setNumber)
	{
		this->sign = setNumber.sign;
		this->exponent = setNumber.exponent - 112;
		this->mantissa = setNumber.mantissa / 8192;
	}
	void printNumber();
	IEEE16 mul(IEEE16, IEEE16);
	IEEE16 mulLNS(IEEE16, IEEE16);
	IEEE16 mulLNS2(IEEE16, IEEE16);

	IEEE16 div(IEEE16, IEEE16);
	IEEE16 divLNS(IEEE16, IEEE16);

	void sr();
	void srLNS();

	void isr();
	void isrLNS();

};



