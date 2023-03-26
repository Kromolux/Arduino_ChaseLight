#include <ChaseLight.h>

ChaseLight Light;

void	setup( void )
{
	const myByte channels[] = { 9, 10, 8, 7, 4, 5, 6, 3, 2, 11, 12, 13 };

	if ( Light.init( sizeof( channels ), channels, 50 ) == 0 )
		Light.flash( 3, 25 );
}

void	loop( void )
{
	Light.flash( 2, 220 );
	Light.moveFillUp( 3, 30, START_LEFT, EMPTY_LEFT );
	Light.fillTo( 3, 30, START_RIGHT, EMPTY_RIGHT );
	Light.knightRider( 7, 40, START_RIGHT );
	Light.knightRiderMiddle( 4, 40, START_INSIDE );
	Light.move(3, 25, START_RIGHT );
}
