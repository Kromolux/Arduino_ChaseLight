# MyKro_ChaseLight
A simple ChaseLight library for Arduino. It should be easy to use for everyone even without any coding experience. All member functions can be called without any argument.
Since the delay function is used in the code, the microcontroller can't do anything else then the chaselight. I will create another library for this case.

## How to use this library?
1. Download the .zip file from GitHub.

2. Insert the library into your Arduino IDE.
    * Sketch -> Include Library -> Add .ZIP Library...

3. Include the header in your project .ino file.
```C
#include <ChaseLight.h>
```

4. Create a global class object.
```C
ChaseLight Light;
```

5. In the Setup function create an array with the output pins in the order from left to right. The size variable is optional, but you need it for the init function. the init functions needs the size of the array, the array itself and the default delay.
```C
int		init( const myByte &size, const myByte *channels, const int &mDelay );
```

```C
void setup(void)
{
	const myByte size = 9;
	const myByte channels[size] = {9, 10, 8, 7, 4, 5, 6, 3, 2};

	Light.init(size, channels, 150)
}
```

6. In the loop function call one of the chaselight member functions.
```C
void loop(void)
{
  Light.flash();
  Light.knightRider();
  Light.knightRiderMiddle();
  Light.fillUp();
  Light.fillTo();
}
```

## What is inside?
* flash
* knightRider
* knightRiderMiddle
* fillUp
* fillTo
