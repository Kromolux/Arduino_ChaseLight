#include <ChaseLight.h>

ChaseLight Light;

void	setup( void )
{
	const myByte channels[] = { 9, 10, 8, 7, 4, 5, 6, 3, 2, 11, 12, 13 };

	if ( Light.init( sizeof( channels ), channels, 80 ) == 0 )
		Light.flash( 3, 50 );
}

void	loop( void )
{
	Light.flash( 2, 220 );
	Light.fillUp( 3, 30, START_LEFT, EMPTY_LEFT );
	Light.fillTo( 3, 30, START_RIGHT, EMPTY_RIGHT );
	Light.knightRider( 7, 40, START_RIGHT );
	Light.knightRiderMiddle( 4, 40, START_INSIDE );
}
