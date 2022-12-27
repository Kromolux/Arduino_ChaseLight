#include "ChaseLight.h"

ChaseLight::ChaseLight( void )
{
	this->_size = 0;
	this->_mDelay = 0;
	this->_channels = new byte[1];
	this->_channels[0] = 0;
}

ChaseLight::~ChaseLight( void )
{
	delete [] this->_channels;
}

void	ChaseLight::init( const byte &size, const byte *channels, const int &mDelay )
{
	this->_size = size;
	this->_mDelay = mDelay;
	delete [] this->_channels;
	this->_channels = new byte[_size];
	for (byte i = 0; i < _size; ++i)
	{
		this->_channels[i] = channels[i];
		pinMode(this->_channels[i], OUTPUT);
		digitalWrite(this->_channels[i], HIGH);
	}
}

void	ChaseLight::setmDelay( const int &mDelay )
{	this->_mDelay = mDelay;	}

void	ChaseLight::flash( int mDelay = 0, const byte count = 3 )
{
	if (mDelay == 0)
		mDelay = this->_mDelay;

	for (byte i = 0; i < count; ++i)
	{
		setChannelsD(LOW);
		delay(mDelay);
		setChannelsD(HIGH);
		delay(mDelay);
	}
	setChannelsD(LOW);
}

void	ChaseLight::setChannelsD(const byte &value)
{
	for (byte i = 0; i < this->_size; ++i)
		digitalWrite(this->_channels[i], value);
}

void	ChaseLight::knightRiderLeft( const int &mDelay = 0, const byte &count = 3 )
{	this->knightRider(mDelay, count, LOW, true);	}

void	ChaseLight::knightRiderRight( const int &mDelay = 0, const byte &count = 3 )
{	this->knightRider(mDelay, count, LOW, false);	}

void	ChaseLight::knightRiderLeftInverted( const int &mDelay = 0, const byte &count = 3 )
{	this->knightRider(mDelay, count, HIGH, true);	}

void	ChaseLight::knightRiderRightInverted( const int &mDelay = 0, const byte &count = 3 )
{	this->knightRider(mDelay, count, HIGH, false);	}

void	ChaseLight::knightRider( int mDelay, const byte &count, const byte &value, const bool &left)
{
	if (mDelay == 0)
		mDelay = this->_mDelay;
	setChannelsD(value);

	if (left == true)
		digitalWrite(_channels[0], !value);
	else
		digitalWrite(_channels[_size - 1], !value);
	delay(mDelay);

	for (byte total = 0; total < count; ++total)
	{
		if (left == true)
		{
			for (byte i = 1, j = 0; i < this->_size; j = i, ++i)
				set2Channel(_channels[j], _channels[i], value, mDelay);

			for (byte i = 1, j = 0, pos = this->_size - 1; i < this->_size; j = i, ++i)
				set2Channel(_channels[pos - j], _channels[pos - i], value, mDelay);
		}
		else
		{
			for (byte i = 1, j = 0, pos = this->_size - 1; i < this->_size; j = i, ++i)
				set2Channel(_channels[pos - j], _channels[pos - i], value, mDelay);

			for (byte i = 1, j = 0; i < this->_size; j = i, ++i)
				set2Channel(_channels[j], _channels[i], value, mDelay);
		}
	}
	setChannelsD(!value);
}

void	ChaseLight::set2Channel(const byte &first, const byte &second, const byte &value, const int &mDelay)
{
	digitalWrite(first, value);
	digitalWrite(second, !value);
	delay(mDelay);
}

void	ChaseLight::fillLeft( const int &mDelay = 0, const byte &count = 3 )
{	fill(mDelay, count, &ChaseLight::fillLeftLoop);	}

void	ChaseLight::fillRight( const int &mDelay = 0, const byte &count = 3 )
{	fill(mDelay, count, &ChaseLight::fillRightLoop);	}

void	ChaseLight::fill( int mDelay, const byte &count, void (ChaseLight::*f)(const int&, const byte&))
{
	if (mDelay == 0)
		mDelay = this->_mDelay;
	
	for (byte total = 0; total < count; ++total)
	{
		for (byte i = 0; i < _size; ++i)
			(this->*f)(mDelay, i);
		delay(mDelay);
		setChannelsD(LOW);
		delay(mDelay);
	}
}

void	ChaseLight::fillLeftLoop( const int &mDelay, const byte &x )
{
	for (byte i = 0, j = 0; i < _size - x; j = i, ++i)
		set2Channel(_channels[j], _channels[i], LOW, mDelay);
}

void	ChaseLight::fillRightLoop( const int &mDelay, const byte &x)
{
	for (byte i = 0, j = 0, pos = this->_size - 1; i < _size - x; j = i, ++i)
		set2Channel(_channels[pos - j], _channels[pos - i], LOW, mDelay);
}
