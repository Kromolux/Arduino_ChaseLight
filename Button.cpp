#include "ChaseLight.h"

Button::Button( void )
{
	this->_changeState = NULL;
	this->_inputPin = 0;
	this->_buttonPressed = false;
	this->_previousTime = 0;
}

Button::Button( myByte const & inputPin, void	( ChaseLightTime::*changeState ) ( void ) )
: _changeState( changeState ), _inputPin( inputPin ), _buttonPressed( false ), _previousTime( 0 )
{
	pinMode( inputPin, INPUT_PULLUP );
}

Button::~Button( void ) {}

void	Button::check( ChaseLightTime & obj )
{
	unsigned long currentTime = millis();

	if ( ( currentTime - this->_previousTime ) >= this->_DEBOUNCETIME)
	{
		if (this->_buttonPressed == false && digitalRead( this->_inputPin ) == LOW )
		{
			this->_previousTime = currentTime;
			this->_buttonPressed = true;
			(obj.*_changeState)();
		}
		else if (this->_buttonPressed == true && digitalRead( this->_inputPin ) == HIGH)
		{
			this->_previousTime = 0;
			this->_buttonPressed = false;
		}
	}
}
