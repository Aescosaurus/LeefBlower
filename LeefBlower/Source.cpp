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
	void read_file( char* str,char* fileName,int maxLen )
	{
		int curChar = 0;
		std::ifstream in( fileName );
		for( char c = in.get(); in.good() && curChar + 1 < maxLen; c = in.get() )
		{
			str[curChar++] = c;
		}
		str[curChar] = 0;
	}
	void write_file( char* str,char* fileName )
	{
		std::ofstream out( fileName );
		for( char c = *str; *str != 0; ++str,c = *str )
		{
			out.put( c );
		}
	}
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

	char text[69];
	aesc::read_file( text,"hi.txt",69 );

	aesc::write_file( "These are the words that I say today!","a.txt" );

	aesc::print( text );

	db.DeleteShit();
	while( !_kbhit() );
	return 0;
}