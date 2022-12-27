#ifndef CHASELIGHT_H
# define CHASELIGHT_H
# include <Arduino.h>

typedef	unsigned char byte;

class ChaseLight
{
	public:
		ChaseLight( void );
		~ChaseLight( void );

		void	init( const byte &size, const byte *channels, const int &mDelay );
		
		void	setmDelay( const int &mDelay );

		void	flash( int mDelay = 0, const byte count = 3 );
		
		void	knightRiderLeft( const int &mDelay = 0, const byte &count = 3 );
		void	knightRiderRight( const int &mDelay = 0, const byte &count = 3 );
		void	knightRiderLeftInverted( const int &mDelay = 0, const byte &count = 3 );
		void	knightRiderRightInverted( const int &mDelay = 0, const byte &count = 3 );

		void	fillLeft( const int &mDelay = 0, const byte &count = 3 );
		void	fillRight( const int &mDelay = 0, const byte &count = 3 );

	private:
		void	fill( int mDelay, const byte &count, void (ChaseLight::*f)(const int&, const byte&) );
		void	fillLeftLoop( const int &mDelay, const byte &x );
		void	fillRightLoop( const int &mDelay, const byte &x );

		void	setChannelsD( const byte &value );
		void	knightRider( int mDelay, const byte &count, const byte &value, const bool &left);
		void	set2Channel( const byte &first, const byte &second, const byte &value, const int &mDelay );
		
		byte	_size;
		byte	*_channels;
		int		_mDelay;

};

#endif