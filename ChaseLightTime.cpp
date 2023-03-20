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
}

ChaseLightTime::~ChaseLightTime( void )
{
	delete [] this->_sequenceSteps;
}

void	ChaseLightTime::loopStep( void )
{
	unsigned long currentTime = myMillis();
	if ( ( currentTime - this->_previousTime ) >= this->_delayTime )
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
		globalChaseLightTimeObject->_sequence = globalChaseLightTimeObject->_sequence & ~bitMask; // set bit at pos to 0
	else
		globalChaseLightTimeObject->_sequence = globalChaseLightTimeObject->_sequence | bitMask; // set bit at pos to 1
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
