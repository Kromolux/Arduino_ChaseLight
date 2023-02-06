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
int	init( const myByte &size, const myByte *channels, const int &mDelay );
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
```C
void	flash( int mDelay = 0, const myByte count = 3 );
void	knightRider( e_setting setTo = START_LEFT, int mDelay = 0, const myByte &count = 3 );
void	knightRiderMiddle( e_setMiddle setTo = START_INSIDE, int mDelay = 0, const myByte &count = 3 );
void	fillUp( e_setting setTo = START_LEFT, e_empty empty = EMPTY_NONE, int mDelay = 0, const myByte &count = 3 );
void	fillTo( e_setting setTo = START_LEFT, e_empty empty = EMPTY_NONE, int mDelay = 0, const myByte &count = 3 );
```

## flash
```C
void	flash( int mDelay = 0, const myByte count = 3 );
```
> All connected lights will light up in a loop - turned on and off. <br>
`mDelay` Delay in miliseconds for switching lights - default = this->mDelay. <br>
`count` Number of total loops - default = 3. <br>
`return` Nothing.

`Light.flash();`


![](https://user-images.githubusercontent.com/104884267/214869100-840b565c-0999-4e3a-b979-75b090cc14d5.gif)


## knightRider
```C
void	knightRider( e_setting setTo = START_LEFT, int mDelay = 0, const myByte &count = 3 );
```
> One light moving in a loop. Can be customized with first argument setTo. <br>
`START_LEFT` = light starts left and moves to the right. <br>
`START_RIGHT` = light starts right and moves to the left. <br>
`START_LEFT_INVERT` = one light turned off and moves from left to the right. <br>
`START_RIGHT_INVERT` = one light turned off and moves from left to the right. <br>
`setTo` Setting for changing direction and invert lights default = LEFT. <br>
`mDelay` Delay in miliseconds for moving lights - default = this->mDelay. <br>
`count` Number of total loops - default = 3. <br>
`return` Nothing.

`Light.knightRider( START_LEFT );`

![](https://user-images.githubusercontent.com/104884267/215150591-8efd4a71-1d09-4079-b13f-20db8cf68965.gif)

![](https://user-images.githubusercontent.com/104884267/214862362-963fd9f8-c422-4906-bf14-a538ad6dcf37.gif)


`Light.knightRider( START_RIGHT );`


![](https://user-images.githubusercontent.com/104884267/214863874-53d6a5fa-fc4e-40ab-b010-68b18ab2a53a.gif)


`Light.knightRider( START_LEFT_INVERTED );`


![](https://user-images.githubusercontent.com/104884267/214865326-fbbc56ea-36c2-4be5-91c6-51ee3dbbdccf.gif)


`Light.knightRider( START_RIGHT_INVERTED );`


![](https://user-images.githubusercontent.com/104884267/214865975-707b07e6-25cc-4600-bf0c-e04fd9d769d8.gif)


## knightRiderMiddle
```C
void	knightRiderMiddle( e_setMiddle setTo = START_INSIDE, int mDelay = 0, const myByte &count = 3 );
```
> Two lights moving from the inside to the outside and then returning back to the inside. <br>
Can be customized with first argument setTo. <br>
`START_INSIDE` = start in the middle moves to the ends. <br>
`START_OUTSIDE` = start at the ends and moves to the middle. <br>
`START_MIDDLE_INVERTED` = start in the middle moves to the ends inverted lights. <br>
`START_INSIDe_INVERTED` = start at the ends and moves to the middle inverted lights. <br>
`setTo` Setting for changing direction and invert lights default = START_MIDDLE. <br>
`mDelay` Delay in miliseconds for moving lights - default = this->mDelay. <br>
`count` Number of total loops - default = 3. <br>
`return` Nothing.

`Light.knightRiderMiddle( START_INSIDE );`


![](https://user-images.githubusercontent.com/104884267/214870961-50bec0dc-b326-4410-9702-03d24272190f.gif)


`Light.knightRiderMiddle( START_OUTSIDE );`


![](https://user-images.githubusercontent.com/104884267/214871554-aff474a3-46b6-4dda-9793-cf428b1a60da.gif)


`Light.knightRiderMiddle( START_INSIDE_INVERTED );`


![](https://user-images.githubusercontent.com/104884267/214879289-d1362ac2-7d12-4745-b13d-d13d6585dd6d.gif)

`Light.knightRiderMiddle( START_OUTSIDE_INVERTED );`


![](https://user-images.githubusercontent.com/104884267/214883310-aef81adc-79ca-47a7-b50f-da9872c1f996.gif)



## fillUp
```C
void	fillUp( e_setting setTo = START_LEFT, e_empty empty = EMPTY_NONE, int mDelay = 0, const myByte &count = 3 );
```

> One light moving and filling up till all lights turned to !value. Can be customized with first argument setTo and second argument setEmpty. <br>
`START_LEFT` = light starts left and moves to the right. <br>
`START_RIGHT` = light starts right and moves to the left. <br>
`START_LEFT_INVERT` = one light turned off and moves from left to the right. <br>
`START_RIGHT_INVERT` = one light turned off and moves from left to the right. <br>
`EMPTY_NONE` = will not be emptied. <br>
`EMPTY_LEFT` = lights will be emptied moving left. <br>
`EMPTY_RIGHT` = lights will be emptied moving right. <br>
`setTo` Setting for changing direction and invert lights default = START_LEFT. <br>
`setEmpty` Setting for emptying the filled lights. default = EMPTY_NONE. <br>
`mDelay` Delay in miliseconds for moving lights - default = this->mDelay. <br>
`count` Number of total loops - default = 3. <br>
`return` Nothing.

### EMPTY_NONE
`Light.fillUp( START_LEFT, EMPTY_NONE );`

![](https://user-images.githubusercontent.com/104884267/214897561-c069aaed-9fa5-4b10-817f-3eac08d3f07b.gif)


`Light.fillUp( START_RIGHT, EMPTY_NONE );`

![](https://user-images.githubusercontent.com/104884267/214897615-07e4fd0a-c5e7-432b-9b1c-2c5deca76aa6.gif)

`Light.fillUp( START_LEFT_INVERTED, EMPTY_NONE );`

![](https://user-images.githubusercontent.com/104884267/214900929-d2d9a5d3-9451-44ba-9612-95fe7d97d17a.gif)


`Light.fillUp( START_RIGHT_INVERTED, EMPTY_NONE );`

![](https://user-images.githubusercontent.com/104884267/214901017-78361af7-e10b-4df7-973b-0689f11f264c.gif)

### EMPTY_LEFT
`Light.fillUp( START_LEFT, EMPTY_LEFT );`

![](https://user-images.githubusercontent.com/104884267/214907446-6fa7e2b2-effd-4111-8588-c5ac613a2181.gif)


`Light.fillUp( START_RIGHT, EMPTY_LEFT );`

![16fillUp_cropped](https://user-images.githubusercontent.com/104884267/216934412-7da42d36-1196-45be-9e01-5e07347c0424.gif)


`Light.fillUp( START_LEFT_INVERTED, EMPTY_LEFT );`

![17fillUp_cropped](https://user-images.githubusercontent.com/104884267/216934324-f2cee624-9449-4174-b987-a94847717f53.gif)


`Light.fillUp( START_RIGHT_INVERTED, EMPTY_LEFT );`

![18fillUp_cropped](https://user-images.githubusercontent.com/104884267/216934271-1cfd080b-48e0-4bca-b01b-e7954c581c6f.gif)


### EMPTY_RIGHT
`Light.fillUp( START_LEFT, EMPTY_RIGHT );`

![19fillUp_cropped](https://user-images.githubusercontent.com/104884267/216934185-9b6b9a6e-703c-46dc-afb6-539b5e5288d9.gif)


`Light.fillUp( START_RIGHT, EMPTY_RIGHT );`

![20fillUp_cropped](https://user-images.githubusercontent.com/104884267/216933656-150848e5-47fc-4398-a4f7-f824d5889228.gif)


`Light.fillUp( START_LEFT_INVERTED, EMPTY_RIGHT );`

![21fillUp_cropped](https://user-images.githubusercontent.com/104884267/216933587-8721f940-f8d7-4606-be70-7566de4f7edd.gif)


`Light.fillUp( START_RIGHT_INVERTED, EMPTY_RIGHT );`

![22fillUp_cropped](https://user-images.githubusercontent.com/104884267/216933505-26a4745a-5211-44f3-a655-5758213fe08a.gif)

## fillTo
```C
void	fillTo( e_setting setTo = START_LEFT, e_empty empty = EMPTY_NONE, int mDelay = 0, const myByte &count = 3 );
```

> One light after another turing to !value till all lights turned to !value. <br>
Can be customized with first argument setTo and second argument setEmpty. <br>
`START_LEFT` = light starts left and fills to the right. <br>
`START_RIGHT` = light starts right and fills to the left. <br>
`START_LEFT_INVERT` = one light turned off and empties from left to the right. <br>
`START_RIGHT_INVERT` = one light turned off and empties from left to the right. <br>
`EMPTY_NONE` = will not be emptied. <br>
`EMPTY_LEFT` = lights will be emptied from left. <br>
`EMPTY_RIGHT` = lights will be emptied from right. <br>
`setTo` Setting for changing direction and invert lights default = START_LEFT. <br>
`setEmpty` Setting for emptying the filled lights. default = EMPTY_NONE.  <br>
`mDelay` Delay in miliseconds for moving lights - default = this->mDelay. <br>
`count` Number of total loops - default = 3. <br>
`return` Nothing.


`Light.fillTo( START_LEFT, EMPTY_NONE );`

`Light.fillTo( START_RIGHT, EMPTY_NONE );`

`Light.fillTo( START_LEFT_INVERTED, EMPTY_NONE );`

`Light.fillTo( START_RIGHT_INVERTED, EMPTY_NONE );`


`Light.fillTo( START_LEFT, EMPTY_LEFT );`

`Light.fillTo( START_RIGHT, EMPTY_LEFT );`

`Light.fillTo( START_LEFT_INVERTED, EMPTY_LEFT );`

`Light.fillTo( START_RIGHT_INVERTED, EMPTY_LEFT );`



`Light.fillTo( START_LEFT, EMPTY_RIGHT );`

`Light.fillTo( START_RIGHT, EMPTY_RIGHT );`

`Light.fillTo( START_LEFT_INVERTED, EMPTY_RIGHT );`

`Light.fillTo( START_RIGHT_INVERTED, EMPTY_RIGHT );`

