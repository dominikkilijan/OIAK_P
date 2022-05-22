#pragma once
class IEEE32
{
public:
	union
	{
		float fValue;

		struct
		{
			unsigned int mantissa : 23;
			unsigned int exponent : 8;
			unsigned int sign : 1;
		};
	};

	IEEE32(float value)
	{
		fValue = value;
	}
	IEEE32()
	{
		fValue = 0;
	}
	void printNumber();
	IEEE32 mul(IEEE32, IEEE32);
	IEEE32 mulLNS(IEEE32, IEEE32);

	IEEE32 div(IEEE32, IEEE32);
	IEEE32 divLNS(IEEE32, IEEE32);

	void sr();
	void srLNS();

	void isr();
	void isrLNS();

};

