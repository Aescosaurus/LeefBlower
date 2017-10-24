#include <conio.h>
#include <fstream>

#include "Database.h"

namespace aesc
{
	void print( char* str )
	{
		for( ; *str != 0; ++str )
		{
			_putch( *str );
		}
		str = 0;
	}
	// TODO: Read and write from and to files, respectively.
}

int main()
{
	// aesc::print( "hi" );
	Database db;
	db.Add( "nItems : 12;" );
	db.Add( "isOutsideScreen : x,y,w,h {" );
	db.Add( "++nItems;" );
	db.Add( "}" );

	db.Print();

	db.DeleteShit();
	while( !_kbhit() );
	return 0;
}