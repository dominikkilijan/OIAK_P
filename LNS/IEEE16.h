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
	//IEEE16(IEEE32 initNumber)
	{
		//this->sign = initNumber.sign;
		//this->exponent = initNumber.exponent - 112;
		//this->mantissa = initNumber.mantissa / 8192;
		this->sign = 0;
		this->exponent = 0;
		this->mantissa = 0;
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



