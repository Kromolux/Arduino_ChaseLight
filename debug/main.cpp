#include "../ChaseLight.h"
#include <iostream>
#include <cstring>

// typedef struct sequence {
// 	unsigned int capacity;
// 	unsigned int size;
// 	unsigned int * step;
// 	unsigned int * sequenceSteps;
// 	unsigned int lastSequence;
// } t_sequence;

const myByte channels[] = {9, 10, 8, 7, 4, 5, 6, 3, 2, 11, 12, 13};
std::string output(sizeof(channels), ' ');
unsigned int sequence = 0;
// t_sequence actualSequence;

void	pinMode( unsigned char channel, unsigned char value)
{
	( void ) channel;
	( void ) value;
	std::cout << "<pinMode> channel: " << std::to_string(channel) << " value: " << std::to_string(value) << "\n";
}

void	delay( long unsigned int time)
{
	( void ) time;
	std::cout << output << " sequence: " << sequence << "\n";

}

void	digitalWrite( unsigned char channel, unsigned char value )
{
	myByte pos = 0;
	while (channels[pos] != channel)
		++pos;
	output[pos] = static_cast<myByte>(value + '0');

	unsigned int bitMask = static_cast<unsigned int>( ( 1 << pos ) );
	if (value == 0)
		sequence = sequence & ~bitMask; // set bit to 0
	else
		sequence = sequence | bitMask; // set bit to 1
}

int	main(void)
{
	ChaseLight Light;



	Light.init(sizeof(channels), channels, 80);
	std::cout << "\n";
	//Light.fillTo(START_LEFT, EMPTY_RIGHT, 80, 1);
	//Light.knightRiderMiddle(START_INSIDE, 80, 1);
	std::cout << "\n";
	Light.fillUp(START_RIGHT, EMPTY_LEFT, 80, 1);

	unsigned int *itE = &actualSequence.sequenceSteps[actualSequence.size];
	for (unsigned int * it = actualSequence.sequenceSteps; it != itE; ++it)
	{
		for (myByte i = 0; i < 16; ++i)
		{
			std::cout << ( (*it >> i) & 1);
		}
		std::cout << " " << *it << "\n";
	}
	std::cout << "size: " << actualSequence.size << "\n";
	delete [] actualSequence.sequenceSteps;
	return (0);
}
