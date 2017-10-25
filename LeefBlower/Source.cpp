#include <conio.h>

#include "Database.h"
#include "Aesc.h"

int main()
{
	// aesc::print( "hi" );
	Database db;
	db.Add( "nItems : 12;" );
	db.Add( "isOutsideScreen : x,y,w,h {" );
	db.Add( "++nItems;" );
	db.Add( "}" );

	db.Print();

	db.JSCode( "leef.js" );

	db.DeleteShit();

	while( !_kbhit() );
	return 0;
}