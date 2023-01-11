#ifndef CHASELIGHT_H
# define CHASELIGHT_H
# include <Arduino.h>

typedef	unsigned char myByte;

enum e_setting : myByte {
	LEFT = 0,
	RIGHT = 1,
	LEFT_INVERTED = 2,
	RIGHT_INVERTED = 3,
};

class ChaseLight
{
	public:
		ChaseLight( void );
		~ChaseLight( void );

		int	init( const myByte &size, const myByte *channels, const int &mDelay );
		void	setmDelay( const int &mDelay );

		void	setChannelsD( const myByte &value );
		void	set2Channel( const myByte &first, const myByte &second, const myByte &value, const int &mDelay );
		
		void	flash( int mDelay = 0, const myByte count = 3 );
		void	knightRider( e_setting setTo = LEFT, int mDelay = 0, const myByte &count = 3 );

		void	fillLeft( const int &mDelay = 0, const myByte &count = 3 );
		void	fillRight( const int &mDelay = 0, const myByte &count = 3 );
		void	fillLeftInverted( const int &mDelay = 0, const myByte &count = 3 );
		void	fillRightInverted( const int &mDelay = 0, const myByte &count = 3 );

		void	fillLeftEmptyRight( const int &mDelay = 0, const myByte &count = 3 );

	private:
		void	mainLoop( const myByte *start, const myByte *goal, const int &mDelay, const myByte &value);

		void	fill( int mDelay, const myByte &count, void (ChaseLight::*f)(const int&, const myByte&, const myByte&), const myByte &value );
		void	fillLeftLoop( const int &mDelay, const myByte &x, const myByte &value );
		void	fillRightLoop( const int &mDelay, const myByte &x, const myByte &value );

		void	fillEmpty( int mDelay, const myByte &count, void (ChaseLight::*f)(const int&, const myByte&, const myByte&), const myByte &value );
		void	emptyLeftLoop( const int &mDelay, const myByte &x, const myByte &value);
		void	emptyRightLoop( const int &mDelay, const myByte &x, const myByte &value);


		myByte	_size;
		myByte	*_channels;
		myByte	*_begin;
		myByte	*_end;
		myByte	*_rbegin;
		myByte	*_rend;
		int		_mDelay;

};

#endif