#include <ChaseLight.h>

ChaseLightTime Light;

void	setup(void)
{
	const myByte channels[] = {9, 10, 8, 7, 4, 5, 6, 3, 2, 11, 12, 13};

	Light.init(sizeof(channels), channels, 80);
	//Light.fillTo();
	//Light.flash(50);
	Light.fillUp(START_LEFT, EMPTY_LEFT, 30, 1);
}

void	loop(void)
{
	Light.loopStep();
}
