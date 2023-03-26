#include "../ChaseLight.h"
#include <iostream>
#include <cstring>

template<typename T>
void	setBit( T & input, unsigned char & bitNr )
{
	input |= ( 1 << bitNr );
}

template<typename T>
void	unsetBit( T & input, unsigned char & bitNr )
{
	input &= ~( 1 << bitNr );
}

template<typename T>
void	toggleBit( T & input, unsigned char & bitNr )
{
	if ( ( 1 << bitNr ) & input )
		unsetBit( input, bitNr );
	else
		setBit( input, bitNr );
}

template<typename T>
void	printBits( T & input )
{
	size_t itE = sizeof( input ) * 8;
	for (size_t it = 0; it < itE; ++it)
		std::cout << (( input >> it ) & 1);
	std::cout << "\n";
}

template<typename T>
void	printBitsValue( T & input)
{
	size_t itE = sizeof( input ) * 8 - 1;
	for (size_t it = 0; it < itE; --itE)
		std::cout << (( input >> itE ) & 1);
	std::cout << ( input & 1);
	std::cout << "\n";
}

const myByte channels[] = {9, 10, 8, 7, 4, 5, 6, 3, 2, 11, 12, 13};
std::string output(sizeof(channels), ' ');
unsigned int sequence = 0;

// replacement of arduino function
void	pinMode( unsigned char channel, unsigned char value)
{
	( void ) channel;
	( void ) value;
	std::cout << "<pinMode> channel: " << std::to_string(channel) << " value: " << std::to_string(value) << "\n";
}

// replacement of arduino function
void	delay( long unsigned int time)
{
	( void ) time;
	std::cout << output << " sequence: " << sequence << "\n";
	//printBits( sequence );
}

// replacement of arduino function
void	digitalWrite( unsigned char channel, unsigned char value )
{
	myByte pos = 0;
	while (channels[pos] != channel)
		++pos;
	output[pos] = static_cast<myByte>(value + '0');

	if (value == 0)
		unsetBit(sequence, pos);
	else
		setBit(sequence, pos);
}

// replacement of arduino function
unsigned long	millis( void )
{
	return (0);
}

// replacement of arduino function
int	digitalRead( unsigned char channel )
{
	( void ) channel;
	return (false);
}

int	main(void)
{
	ChaseLight Light;

	Light.init( sizeof( channels ), channels, 80 );
	std::cout << "\n";
	//Light.fillTo( 1, 80, START_LEFT, EMPTY_RIGHT );
	Light.move( 2 );
	//Light.knightRiderMiddle(START_INSIDE, 80, 1);
	std::cout << "\n";
	Light.move( 2, 0, START_RIGHT );
	//Light.fillUp(START_RIGHT, EMPTY_LEFT, 80, 1);

	struct timeval actualTime;
	gettimeofday(&actualTime, NULL);
	std::cout << "sec: " << actualTime.tv_sec << " usec: " << actualTime.tv_usec << "\n";
	return (0);
}
