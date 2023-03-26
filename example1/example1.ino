#include <ChaseLight.h>

ChaseLightTime Light;

void	setup( void )
{
	const myByte channels[] = { 9, 10, 8, 7, 4, 5, 6, 3, 2, 11, 12, 13 };
	Light.init( sizeof( channels ), channels, 80 );
	//Light.fillTo();
	//Light.flash(50);
	Light.fillUp( 1, 30, START_LEFT, EMPTY_LEFT );
	Light.registerButton( 0, &ChaseLightTime::pauseToggle );
	Light.registerButton( 1, &ChaseLightTime::stopToggle );
}

void	loop( void )
{
	Light.loopStep();
}
