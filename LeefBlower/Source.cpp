#include <conio.h>
#include <string>

#include "Database.h"
#include "Aesc.h"

int main()
{
	// aesc::print( "hi" );
	Database db;
	// db.Add( "nItems : 12;" );
	// db.Add( "isOutsideScreen : x,y,w,h {" );
	// db.Add( "++nItems;" );
	// db.Add( "}" );
	// db.Print();

	std::ifstream in( "Main.leef" );
	char line[69];
	for( ; in.getline( line,69,'\n' ); )
	{
		db.Add( line );
	}

	// Fix this someday b0ss
	// int curOffset = 0;
	// bool done = false;
	// while( !done )
	// {
	// 	char next[69];
	// 	int offsetAdd = aesc::read_file_offset( next,"Main.leef",69,curOffset );
	// 	if( offsetAdd < 6969 )
	// 	{
	// 		curOffset += offsetAdd;
	// 	}
	// 	else
	// 	{
	// 		done = true;
	// 	}
	// 	db.Add( next );
	// }

	db.JSCode( "leef.js" );

	db.DeleteShit();

	while( !_kbhit() );
	return 0;
}