#include "ChaseLight.h"

ChaseLight::ChaseLight( void )
{
	this->_size = 0;
	this->_mDelay = 0;
	this->_channels = new myByte[1];
	this->_channels[0] = 0;
	this->_begin = NULL;
	this->_end = NULL;
	this->_rbegin = NULL;
	this->_rend = NULL;
	this->_isEven = 0;
}

ChaseLight::~ChaseLight( void )
{
	delete [] this->_channels;
}

/**
	@brief Initialize the member variables and allocates memory for the channel array.
	@param size Number of output channels 0 = no output channel - max 255.
	@param channels Array of output channels in order left to right.
	@param mDelay Delay in miliseconds for switching lights.
	@return 0 if memory allocation was successfull otherwise 1.
*/
int	ChaseLight::init( const myByte &size, const myByte *channels, const int &mDelay )
{
	this->_size = size;
	this->_mDelay = mDelay;
	delete [] this->_channels;
	this->_channels = new myByte[_size];
	if ( this->_channels == NULL )
		return ( 1 );
	for ( myByte i = 0; i < _size; ++i )
	{
		this->_channels[i] = channels[i];
		pinMode( this->_channels[i], OUTPUT );
		digitalWrite( this->_channels[i], LOW );
	}
	this->_begin = this->_channels;
	this->_end = this->_channels + this->_size;
	this->_rbegin = this->_end - 1;
	this->_rend = this->_begin - 1;
	if ( this->_size % 2 == 0 )
		this->_isEven = 1;
	this->_center = static_cast<myByte>( _size / 2 );
	return ( 0 );
}

/**
	@brief Set the this->mDelay for all internal ChaseLight delays.
	@param mDelay Delay in miliseconds for switching lights.
	@return Nothing.
*/
void	ChaseLight::setmDelay( const int &mDelay )
{	this->_mDelay = mDelay;	}

/**
	@brief Irgnores first channel and sets second channel to !value. Delays afterwards.
	@param first Ignored.
	@param second Channel to value. Has to be the output pin.
	@param mDelay Delay in miliseconds after digitalWrite.
	@param value LOW = 0 turned off - HIGH = 1 turned on.
	@return Nothing.
*/
void	ChaseLight::set1Channel( const myByte &first, const myByte &second, const myByte &value, const int &mDelay )
{
	(void) first;
	digitalWrite( second, !value );
	delay( mDelay );
}

/**
	@brief Set first channel to value and second to !value. Delays afterwards.
	@param first Channel to value. Has to be the output pin.
	@param second Channel to !value. Has to be the output pin.
	@param mDelay Delay in miliseconds after digitalWrite.
	@param value LOW = 0 turned off - HIGH = 1 turned on.
	@return Nothing.
*/
void	ChaseLight::set2Channel( const myByte &first, const myByte &second, const myByte &value, const int &mDelay )
{
	digitalWrite( first, value );
	digitalWrite( second, !value );
	delay( mDelay );
}

/**
	@brief Set firstPrev and secondPrev channel to value and first and second to !value. Delays afterwards.
	@param firstPrev Channel to value. Has to be the output pin.
	@param secondPrev Channel to value. Has to be the output pin.
	@param first Channel to value. Has to be the output pin.
	@param second Channel to value. Has to be the output pin.
	@param mDelay Delay in miliseconds after digitalWrite.
	@param value LOW = 0 turned off - HIGH = 1 turned on.
	@return Nothing.
*/
void	ChaseLight::set4Channel( const myByte &firstPrev, const myByte &secondPrev,
		const myByte &first, const myByte &second, const myByte &value, const int &mDelay )
{
	digitalWrite( firstPrev, value );
	digitalWrite( secondPrev, value );
	digitalWrite( first, !value );
	digitalWrite( second, !value );
	delay( mDelay );
}

/**
	@brief Set all channels to value.
	@param value LOW = 0 turned off - HIGH = 1 turned on.
	@return Nothing.
*/
void	ChaseLight::setAllChannelsD( const myByte &value )
{
	for ( myByte *it = this->_begin; it != this->_end; ++it )
		digitalWrite( *it, value );
}

void	ChaseLight::mainLoop( myByte *start, myByte *goal, const int &mDelay, const myByte &value,
		void (ChaseLight::*setChannel)( const myByte&, const myByte&, const myByte&, const int& ) )
{
	signed char step = 1;
	if ( start > goal )
		step = -1;

	for ( myByte *it = start, *previous = start; it != goal; previous = it, it += step )
		(this->*setChannel)( *previous, *it, value, mDelay );
}

/**
	@brief All connected lights will light up in a loop - turned on and off.
	@param mDelay Delay in miliseconds for switching lights - default = this->mDelay.
	@param count Number of total loops - default = 3.
	@return Nothing.
*/
void	ChaseLight::flash( int mDelay, const myByte count )
{
	if ( mDelay == 0 )
		mDelay = this->_mDelay;

	for (myByte i = 0; i < count; ++i )
	{
		setAllChannelsD( LOW );
		delay( mDelay );
		setAllChannelsD( HIGH );
		delay( mDelay );
	}
	setAllChannelsD( LOW );
}

/**
	@brief One light moving in a loop. Can be customized with first argument setTo.
	START_LEFT = light starts left and moves to the right.
	START_RIGHT = light starts right and moves to the left.
	START_LEFT_INVERT = one light turned off and moves from left to the right.
	START_RIGHT_INVERT = one light turned off and moves from left to the right.
	@param setTo Setting for changing direction and invert lights default = LEFT.
	@param mDelay Delay in miliseconds for moving lights - default = this->mDelay.
	@param count Number of total loops - default = 3.
	@return Nothing.
*/
void	ChaseLight::knightRider( e_setting setTo, int mDelay, const myByte &count )
{
	const myByte value = setTo & 0x2;
	const myByte direction = setTo & 0x1;

	if ( mDelay == 0 )
		mDelay = this->_mDelay;
	setAllChannelsD( value );

	if ( direction == START_LEFT )
	{
		for ( myByte total = 0; total < count; ++total )
		{
			mainLoop( _begin, _end, mDelay, value, &ChaseLight::set2Channel );
			digitalWrite( *_rbegin, value );
			mainLoop( (_rbegin -1) , _begin, mDelay, value, &ChaseLight::set2Channel );
			digitalWrite( *(_begin + 1), value );
		}
		set2Channel( *_begin + 1, *_begin, value, mDelay );
	} else {
		for ( myByte total = 0; total < count; ++total )
		{
			mainLoop( _rbegin, _rend, mDelay, value, &ChaseLight::set2Channel );
			digitalWrite( *_begin, value );
			mainLoop( (_begin + 1), _rbegin, mDelay, value, &ChaseLight::set2Channel );
			digitalWrite( *(_rbegin - 1), value );
		}
		set2Channel( *_rbegin - 1, *_rbegin, value, mDelay );
	}
}

/**
	@brief Two lights moving from the inside to the outside and then returning back to the inside.
	Can be customized with first argument setTo.
	START_INSIDE = start in the middle moves to the ends.
	START_OUTSIDE = start at the ends and moves to the middle.
	START_MIDDLE_INVERTED = start in the middle moves to the ends inverted lights.
	START_INSIDe_INVERTED = start at the ends and moves to the middle inverted lights.
	@param setTo Setting for changing direction and invert lights default = START_MIDDLE.
	@param mDelay Delay in miliseconds for moving lights - default = this->mDelay.
	@param count Number of total loops - default = 3.
	@return Nothing.
*/
void	ChaseLight::knightRiderMiddle( e_setMiddle setTo, int mDelay, const myByte &count )
{
	const myByte value = setTo & 0x2;
	const myByte direction = setTo & 0x1;

	if ( mDelay == 0 )
		mDelay = this->_mDelay;
	setAllChannelsD( value );

	myByte *itLeft = &_channels[_center - _isEven];
	myByte *itLeftPrev = itLeft;
	myByte *itRight = &_channels[_center];
	myByte *itRightPrev = itRight;
	myByte *itMiddle = &_channels[_center - _isEven];

	if ( direction == START_LEFT )
	{
		for ( myByte total = 0; total < count; ++total )
		{
			for ( ; itRight != _end; itLeftPrev = itLeft, --itLeft, itRightPrev = itRight, ++itRight )
				set4Channel( *itLeftPrev, *itRightPrev, *itLeft, *itRight, value, mDelay );

			itLeftPrev = ++itLeft;
			itRightPrev = --itRight;
			++itLeft;
			--itRight;

			for ( ; itLeft != itMiddle; itLeftPrev = itLeft, ++itLeft, itRightPrev = itRight, --itRight )
				set4Channel( *itLeftPrev, *itRightPrev, *itLeft, *itRight, value, mDelay );
		}
	} else {
		itLeftPrev = itLeft = _begin;
		itRightPrev = itRight = _rbegin;

		for ( myByte total = 0; total < count; ++total )
		{
			for ( ; itLeft != itMiddle; itLeftPrev = itLeft, ++itLeft, itRightPrev = itRight, --itRight )
				set4Channel( *itLeftPrev, *itRightPrev, *itLeft, *itRight, value, mDelay );

			for ( ; itRight != _rbegin; itLeftPrev = itLeft, --itLeft, itRightPrev = itRight, ++itRight )
				set4Channel( *itLeftPrev, *itRightPrev, *itLeft, *itRight, value, mDelay );
		}
	}
	set4Channel( *itLeftPrev, *itRightPrev, *itLeft, *itRight, value, mDelay );
	setAllChannelsD( value );
}

/**
	@brief One light moving and filling up till all lights turned to !value. Can be customized with first argument setTo and second argument setEmpty.
	START_LEFT = light starts left and moves to the right.
	START_RIGHT = light starts right and moves to the left.
	START_LEFT_INVERT = one light turned off and moves from left to the right.
	START_RIGHT_INVERT = one light turned off and moves from left to the right.
	EMPTY_NONE = will not be emptied.
	EMPTY_LEFT = lights will be emptied moving left.
	EMPTY_RIGHT = lights will be emptied moving right.
	@param setTo Setting for changing direction and invert lights default = START_LEFT.
	@param setEmpty Setting for emptying the filled lights. default = EMPTY_NONE. 
	@param mDelay Delay in miliseconds for moving lights - default = this->mDelay.
	@param count Number of total loops - default = 3.
	@return Nothing.
*/
void	ChaseLight::fillUp( e_setting setTo, e_empty setEmpty, int mDelay, const myByte &count )
{
	const myByte value = setTo & 0x2;
	const myByte direction = setTo & 0x1;
	const myByte empty = setEmpty & 0x1;
	const myByte directionEmpty = setEmpty & 0x2;

	if ( mDelay == 0 )
		mDelay = this->_mDelay;
	
	setAllChannelsD( value );

	for ( myByte total = 0; total < count; ++total )
	{
		if ( direction == START_LEFT)
		{
			for ( myByte i = 0; i < _size; ++i )
				mainLoop( _begin, _end - i, mDelay, value, &ChaseLight::set2Channel );
		} else {
			for ( myByte i = 0; i < _size; ++i )
				mainLoop( _rbegin, _rend + i, mDelay, value, &ChaseLight::set2Channel );
		}
		if ( empty == EMPTY_NONE)
		{
			setAllChannelsD( value );
			delay( mDelay );
		}
		else if ( directionEmpty == 0 )
		{
			for ( myByte i = 0; i < _size; ++i )
			{
				mainLoop( _begin + i, _rend, mDelay, value, &ChaseLight::set2Channel );
				digitalWrite( *_begin, value );
				delay( mDelay );
			}
		} else {
			for ( myByte i = 0; i < _size; ++i )
			{
				mainLoop( _rbegin - i , _end, mDelay, value, &ChaseLight::set2Channel );
				digitalWrite( *_rbegin, value );
				delay( mDelay );
			}
		}
	}
}

/**
	@brief One light after another turing to !value till all lights turned to !value.
	Can be customized with first argument setTo and second argument setEmpty.
	START_LEFT = light starts left and fills to the right.
	START_RIGHT = light starts right and fills to the left.
	START_LEFT_INVERT = one light turned off and empties from left to the right.
	START_RIGHT_INVERT = one light turned off and empties from left to the right.
	EMPTY_NONE = will not be emptied.
	EMPTY_LEFT = lights will be emptied from left.
	EMPTY_RIGHT = lights will be emptied from right.
	@param setTo Setting for changing direction and invert lights default = START_LEFT.
	@param setEmpty Setting for emptying the filled lights. default = EMPTY_NONE. 
	@param mDelay Delay in miliseconds for moving lights - default = this->mDelay.
	@param count Number of total loops - default = 3.
	@return Nothing.
*/
void	ChaseLight::fillTo( e_setting setTo, e_empty setEmpty, int mDelay, const myByte &count )
{
	const myByte value = setTo & 0x2;
	const myByte direction = setTo & 0x1;
	const myByte empty = setEmpty & 0x1;
	const myByte directionEmpty = setEmpty & 0x2;

	if ( mDelay == 0 )
		mDelay = this->_mDelay;
	
	setAllChannelsD( value );

	for ( myByte total = 0; total < count; ++total )
	{
		if ( direction == START_LEFT)
			mainLoop( _begin, _end, mDelay, value, &ChaseLight::set1Channel );
		else
			mainLoop( _rbegin, _rend, mDelay, value, &ChaseLight::set1Channel );

		if ( empty == EMPTY_NONE )
		{
			setAllChannelsD( value );
			delay( mDelay );
		}
		else if ( directionEmpty == 0 )
			mainLoop( _begin, _end, mDelay, !value, &ChaseLight::set1Channel );
		else
			mainLoop( _rbegin, _rend, mDelay, !value, &ChaseLight::set1Channel );
	}
}
