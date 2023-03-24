#include "ChaseLight.h"

ChaseLightTime *globalChaseLightTimeObject = NULL;

ChaseLightTime::ChaseLightTime( void )
{
	this->_sequence = 0;
	this->_sequenceSteps = new unsigned int [16];
	this->_sequenceSteps[0] = 0;
	this->_step = this->_sequenceSteps;
	this->_capacity = 16;
	this->_sequenceSize = 0;
	this->_lastSequenceStep = 0;
	this->_delayTime = 50;
	this->myMillis = &millis;
	this->myDelay = &delayReplace;
	this->myDigitalWrite = &digitalWriteReplace;
	this->_previousTime = this->myMillis();
	globalChaseLightTimeObject = this;
	this->_state = STOPPED;
	this->_buttons = NULL;
	this->_buttonPos = 0;
	this->_buttonsSize = 2;
}

ChaseLightTime::~ChaseLightTime( void )
{
	delete [] this->_sequenceSteps;
	if ( this->_buttons != NULL )
		delete [] this->_buttons;
}

void	ChaseLightTime::loopStep( void )
{
	// implement buttons
	if (this->_buttons != NULL)
	{
		for ( myByte i = 0; i < _buttonPos; ++i)
		this->_buttons[i]->check( *this );
	}

	unsigned long currentTime = myMillis();
	if ( this->_state == PLAYING && ( currentTime - this->_previousTime ) >= this->_delayTime )
	{
		this->_previousTime = currentTime;
		this->incrementSequence();
		this->setOutputs();
	}
}

void	ChaseLightTime::incrementSequence( void )
{
	++this->_step;
	if ( this->_step >= &this->_sequenceSteps[this->_sequenceSize] )
		this->_step = &this->_sequenceSteps[0];
}

void	ChaseLightTime::setOutputs( void )
{
	unsigned int pos = 0;
	for ( myByte *it = this->_begin; it != this->_end; ++it, ++pos )
		digitalWrite(*it, ( ( *this->_step >> pos ) & 1 ) );
}

void	ChaseLightTime::setOutputs( myByte const & input )
{
	unsigned int pos = 0;
	for ( myByte *it = this->_rbegin; it != this->_rend; --it, ++pos )
		digitalWrite(*it, ( ( input >> pos ) & 1 ) );
}

void	delayReplace( long unsigned int time )
{
	( void ) time;
	globalChaseLightTimeObject->writeSequence();
}

void	digitalWriteReplace( unsigned char channel, unsigned char value )
{
	unsigned int pos = 0;
	while ( globalChaseLightTimeObject->_channels[pos] != channel )
		++pos;

	unsigned int bitMask = ( 1 << pos );
	if ( value == 0 )
		globalChaseLightTimeObject->_sequence &= ~bitMask; // set bit at pos to 0
	else
		globalChaseLightTimeObject->_sequence |= bitMask; // set bit at pos to 1
}

void	ChaseLightTime::writeSequence( void )
{
	if ( this->_sequenceSize == this->_capacity )
		this->reallocate();
	*this->_step = this->_sequence;
	++this->_step;
	++this->_sequenceSize;
}

void	ChaseLightTime::reallocate( void )
{
	this->_capacity *= 2;
	unsigned int * tmp = new unsigned int [this->_capacity];
	memmove( ( void* ) tmp, ( void* ) this->_sequenceSteps, sizeof( unsigned int ) * this->_sequenceSize );
	delete [] this->_sequenceSteps;
	this->_sequenceSteps = tmp;
	this->_step = &this->_sequenceSteps[this->_sequenceSize];
}

void	ChaseLightTime::stop( void )
{
	this->_step = this->_sequenceSteps;
	this->myDigitalWrite = &digitalWrite;
	this->setAllChannelsD( LOW );
	this->myDigitalWrite = &digitalWriteReplace;
	this->_state = STOPPED;
}

void	ChaseLightTime::pauseToggle( void )
{
	this->_state = !this->_state;
}

void	ChaseLightTime::stopToggle( void )
{
	if (this->_state == STOPPED)
		this->_state = PLAYING;
	else
		this->stop();
}

void	ChaseLightTime::registerButton( myByte const & inputPin, void	( ChaseLightTime::*changeState ) ( void ) )
{
	if ( this->_buttons == NULL )
	{
		this->_buttons = new Button *[_buttonsSize];
		this->_buttons[0] = new Button( inputPin, changeState );
		++_buttonPos;
	}
	else if (_buttonPos < 2) // can only hold two buttons at the moment. realloc needed when more buttons registered
	{
		this->_buttons[1] = new Button( inputPin, changeState );
		++_buttonPos;
	}
	
}
