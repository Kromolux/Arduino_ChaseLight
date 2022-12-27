#ifndef CHASELIGHT_H
# define CHASELIGHT_H
# include <Arduino.h>

typedef	unsigned char byte;

class ChaseLight
{
	public:
		ChaseLight (const byte &size, const byte *channels, const int &mDelay );
		~ChaseLight( void );
		void	flash( int mDelay = 0, const byte count = 3 );
		void	knightRiderLeft( const int &mDelay = 0, const byte &count = 3 );
		void	knightRiderRight( const int &mDelay = 0, const byte &count = 3 );
		void	knightRiderLeftInverted( const int &mDelay = 0, const byte &count = 3 );
		void	knightRiderRightInverted( const int &mDelay = 0, const byte &count = 3 );

	private:
		void	setChannelsD( const byte &value );
		void	knightRider( int mDelay, const byte &count, const byte &value, const bool &left);
		void	set2Channel( const byte &first, const byte &second, const byte &value, const int &mDelay );
		byte	_size;
		byte	*_channels;
		int		_mDelay;

};

#endif