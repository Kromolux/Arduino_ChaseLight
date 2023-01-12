#ifndef CHASELIGHT_H
# define CHASELIGHT_H
# include <Arduino.h>

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

		void	setChannelsD( const myByte &value );
		void	set2Channel( const myByte &first, const myByte &second, const myByte &value, const int &mDelay );
		void	set4Channel( const myByte &firstPrev, const myByte &secondPrev, const myByte &first, const myByte &second, const myByte &value, const int &mDelay );

		void	flash( int mDelay = 0, const myByte count = 3 );
		void	knightRider( e_setting setTo = START_LEFT, int mDelay = 0, const myByte &count = 3 );
		void	knightRiderMiddle( e_setMiddle setTo = START_INSIDE, int mDelay = 0, const myByte &count = 3 );
		void	fillUp( e_setting setTo = START_LEFT, e_empty empty = EMPTY_NONE, int mDelay = 0, const myByte &count = 3);

	private:
		void	mainLoop( const myByte *start, const myByte *goal, const int &mDelay, const myByte &value);

		myByte	_size;
		myByte	_center;
		myByte	_isEven;
		myByte	*_channels;
		myByte	*_begin;
		myByte	*_end;
		myByte	*_rbegin;
		myByte	*_rend;
		int		_mDelay;

};

#endif