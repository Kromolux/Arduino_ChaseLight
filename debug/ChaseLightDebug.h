#ifndef CHASELIGHTDEBUG_H
# define CHASELIGHTDEBUG_H
# include <cstddef>
# include <sys/time.h>
# include <string.h>
# define LOW 0
# define HIGH 1
# define OUTPUT 100
# define INPUT 0
# define INPUT_PULLUP 2

void	pinMode( unsigned char channel, unsigned char value );
void	delay( long unsigned int time );
void	digitalWrite( unsigned char channel, unsigned char value );
unsigned long	millis( void );
int	digitalRead( unsigned char channel );

#endif