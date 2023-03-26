#ifndef CHASELIGHT_H
# define CHASELIGHT_H
# ifndef DEBUG
#  define DEBUG 0
#  include <Arduino.h>
# endif
# if DEBUG
#  include "debug/ChaseLightDebug.h"
# endif

typedef	unsigned char myByte;

enum e_setting : myByte {
	START_LEFT = 0,
	START_RIGHT = 1,
	START_LEFT_INVERTED = 2,
	START_RIGHT_INVERTED = 3,
};

enum e_setMiddle : myByte {
	START_INSIDE = 0,
	START_OUTSIDE = 1,
	START_INSIDE_INVERTED = 2,
	START_OUTSIDE_INVERTED = 3,
};

enum e_empty : myByte {
	EMPTY_NONE = 0,
	EMPTY_LEFT = 1,
	EMPTY_RIGHT = 3,
};

class ChaseLight
{
	public:
		ChaseLight( void );
		~ChaseLight( void );

		int		init( const myByte &size, const myByte *channels, const int &mDelay );
		void	setmDelay( const int &mDelay );

		void	setAllChannelsD( const myByte &value );
		void	set1Channel( const myByte &first, const myByte &second, const myByte &value, const int &mDelay );
		void	set2Channel( const myByte &first, const myByte &second, const myByte &value, const int &mDelay );
		void	set4Channel( const myByte &firstPrev, const myByte &secondPrev, const myByte &first, const myByte &second,
				const myByte &value, const int &mDelay );

		void	flash( const myByte &count = 3, int mDelay = 0 );
		void	knightRider( const myByte &count = 3, int mDelay = 0, e_setting setTo = START_LEFT );
		void	knightRiderMiddle( const myByte &count = 3, int mDelay = 0, e_setMiddle setTo = START_INSIDE );
		void	fillUp( const myByte &count = 3, int mDelay = 0, e_setting setTo = START_LEFT, e_empty empty = EMPTY_NONE );
		void	fillTo( const myByte &count = 3, int mDelay = 0, e_setting setTo = START_LEFT, e_empty empty = EMPTY_NONE );

	protected:
		void	basicLoop( myByte *start, myByte *goal, const int &mDelay, const myByte &value,
				void ( ChaseLight::*setChannel )( const myByte&, const myByte&, const myByte&, const int& ) );

		myByte	_size;
		myByte	_center;
		myByte	_isEven;
		myByte	*_channels;
		myByte	*_begin;
		myByte	*_end;
		myByte	*_rbegin;
		myByte	*_rend;
		int		_mDelay;

		void	( *myPinMode ) ( myByte channel, myByte value );
		void	( *myDelay ) ( long unsigned int time );
		void	( *myDigitalWrite ) ( myByte channel, myByte value );


};

enum e_state : myByte {
	STOPPED = 0,
	PLAYING = 1,
};

class ChaseLightTime;

class Button
{
	public:
		Button( myByte const & inputPin, void	( ChaseLightTime::*changeState ) ( void ) );
		~Button( void );

		void	check( ChaseLightTime & obj );
		void	( ChaseLightTime::*_changeState ) ( void );

	private:
		myByte						_inputPin;
		bool						_buttonPressed;
		unsigned long				_previousTime;
		static const unsigned long	_DEBOUNCETIME = 25;

		int	( *myDigitalRead ) ( myByte channel );
		unsigned long	( *myMillis ) ( void );

};

class ChaseLightTime : public ChaseLight
{
	public:
		ChaseLightTime( void );
		~ChaseLightTime( void );
		void	loopStep( void );
		void	setOutputs( myByte const & input );

		void	stop( void );
		void	pauseToggle( void );
		void	stopToggle( void );
		void	registerButton( myByte const & inputPin, void	( ChaseLightTime::*changeState ) ( void ) );

	private:
		void	incrementSequence( void );
		void	setOutputs( void );
		friend void	delayReplace( long unsigned int time );
		friend void	digitalWriteReplace( unsigned char channel, unsigned char value );
		void	writeSequence( void );
		void	reallocate( void );

		unsigned long	_previousTime;
		unsigned long	_delayTime;
		unsigned long	( *myMillis ) ( void );

		unsigned int	_sequence;
		unsigned int	_capacity;
		unsigned int	_sequenceSize;
		unsigned int *	_step;
		unsigned int *	_sequenceSteps;
		unsigned int	_lastSequenceStep;

		myByte			_state;
		Button		**	_buttons;
		myByte			_buttonsSize;
		myByte			_buttonPos;
};

void	delayReplace( long unsigned int time );
void	digitalWriteReplace( unsigned char channel, unsigned char value );


#endif