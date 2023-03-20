#ifndef CHASELIGHTDEBUG_H
# define CHASELIGHTDEBUG_H
# include <cstddef>
# define LOW 0
# define HIGH 1
# define OUTPUT 100

void	pinMode( unsigned char channel, unsigned char value );
void	delay( long unsigned int time );
void	digitalWrite( unsigned char channel, unsigned char value );

#endif