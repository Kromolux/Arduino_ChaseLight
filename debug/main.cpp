#include "../ChaseLight.h"
#include <iostream>

const myByte channels[] = {9, 10, 8, 7, 4, 5, 6, 3, 2, 11, 12, 13};
std::string output(sizeof(channels), ' ');

void	pinMode( unsigned char channel, unsigned char value)
{
	( void ) channel;
	( void ) value;
	std::cout << "<pinMode> channel: " << std::to_string(channel) << " value: " << std::to_string(value) << "\n";
}

void	delay( long unsigned int time)
{
	( void ) time;
	std::cout << output << "\n";
}

void	digitalWrite( unsigned char channel, unsigned char value )
{
	myByte pos = 0;
	while (channels[pos] != channel)
		++pos;
	output[pos] = static_cast<myByte>(value + '0');
}

int	main(void)
{
	ChaseLight Light;

	Light.init(sizeof(channels), channels, 80);

	Light.fillTo();
	return (0);
}
