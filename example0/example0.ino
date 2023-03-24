#include <ChaseLight.h>

ChaseLight Light;

void	setup(void)
{
	const myByte channels[] = {9, 10, 8, 7, 4, 5, 6, 3, 2, 11, 12, 13};

	if (Light.init(sizeof(channels), channels, 80) == 0)
		Light.flash(50);
}

void	loop(void)
{
	Light.flash(220, 2);
	Light.fillUp(START_LEFT, EMPTY_LEFT, 30, 3);
	Light.fillTo(START_RIGHT, EMPTY_RIGHT, 30, 3);
	Light.knightRider(START_RIGHT, 40, 7);
	Light.knightRiderMiddle(START_INSIDE, 40, 4);
}
