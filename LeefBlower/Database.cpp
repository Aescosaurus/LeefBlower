#include "Database.h"

#include <conio.h>

void Database::Print() const
{
	for( int i = 0; i < curEntry; ++i )
	{
		entries[i].Print();
		_putch( ' ' );
		entries[i].PrintJS();
		_putch( '\n' );
	}
}

void Database::Add( char* term_in )
{
	// char temp[69];
	// int curTemp = 0;
	// for( ; term_in != 0; ++term_in )
	// {
	// 	temp[curTemp++] = *term_in;
	// }
	entries[curEntry++] = { term_in };
}

Database::Entry::Entry( char* term_in )
{
	char firstTerm = *term_in;
	char secTerm = *( term_in + 1 );
	bool includesColon = false;
	bool includesSemicolon = false;
	for( ; *term_in != 0; ++term_in )
	{
		term[curTerm++] = *term_in;
		if( *term_in == ':' )
		{
			includesColon = true;
		}
		if( *term_in == ';' )
		{
			includesSemicolon = true;
		}
	}
	term_in = 0;

	// Check what it is and set enum appropriately.
	if( includesColon ) // Definition.
	{
		if( includesSemicolon ) // Not a function or object!
		{
			if( firstTerm == 'n' )
			{
				keywordType = Term::IntD;
			}
			else if( firstTerm == 'i' && secTerm == 's' )
			{
				keywordType = Term::BoolD;
			}
			else
			{
				keywordType = Term::FloatD;
			}
		}
		else // Functions and objects.
		{
			if( firstTerm < 94 ) // Caps, so objects.
			{
				keywordType = Term::ObjD;
			}
			else // No caps, no objects.
			{
				if( firstTerm == 'n' )
				{
					keywordType = Term::IFuncD;
				}
				else if( firstTerm == 'i' && secTerm == 's' )
				{
					keywordType = Term::BFuncD;
				}
				else
				{
					keywordType = Term::FFuncD;
				}
			}
		}
	}
	else // Use.
	{
		// Don't really need to write anything for js, it works anyway.
	}
	ConvertToJS();
}

void Database::Entry::ConvertToJS()
{
	bool var = false;
	bool func = false;
	bool obj = false;
	int t = 0;
	// TODO: Make this prettier with methods.
	if( keywordType == Term::IntD || keywordType == Term::BoolD || keywordType == Term::FloatD )
	{ // var
		var = true;
		jsTerm[t++] = 'v'; jsTerm[t++] = 'a'; jsTerm[t++] = 'r';
	}
	else if( keywordType == Term::IFuncD || keywordType == Term::BFuncD || keywordType == Term::FFuncD )
	{ // function
		func = true;
		jsTerm[t++] = 'f'; jsTerm[t++] = 'u'; jsTerm[t++] = 'n'; jsTerm[t++] = 'c';
		jsTerm[t++] = 't'; jsTerm[t++] = 'i'; jsTerm[t++] = 'o'; jsTerm[t++] = 'n';
	}
	else
	{ // function, but this time it's an object.
		obj = true;
		jsTerm[t++] = 'f'; jsTerm[t++] = 'u'; jsTerm[t++] = 'n'; jsTerm[t++] = 'c';
		jsTerm[t++] = 't'; jsTerm[t++] = 'i'; jsTerm[t++] = 'o'; jsTerm[t++] = 'n';
	}

	jsTerm[t++] = ' ';

	for( int i = 0; i < curTerm; ++i )
	{
		jsTerm[t] = term[i];

		if( term[i] == ':' )
		{
			if( var )
			{
				jsTerm[--t] = '=';
				++i;
			}
			else // obj or func
			{
				jsTerm[--t] = '(';
				++i; // Deals with unnecessary spaces.
			}
		}

		++t;
	}
	// for( int i = 0 + t; i < 69 + t; ++i )
	// {
	// 	jsTerm[i] = term[i - t];
	// 	if( term[i - t] == ':' )
	// 	{
	// 		if( var )
	// 		{
	// 			jsTerm[i] = '=';
	// 		}
	// 		else if( func || obj )
	// 		{
	// 			jsTerm[i] = '(';
	// 		}
	// 	}
	// 	// ++t;
	// }
	if( func || obj )
	{
		jsTerm[t] = ')';
	}
}

void Database::Entry::Print() const
{
	for( int i = 0; i < curTerm; ++i )
	{
		_putch( term[i] );
	}
}

void Database::Entry::PrintType() const
{
	if( keywordType == Term::BFuncD )
	{
		_putch( 'i' );
	}
}

void Database::Entry::PrintJS() const
{
	for( int i = 0; i < 69 * 2; ++i )
	{
		// TODO: Fix this using null terminator lol.
		if( jsTerm[i] == -52 )
		{
			break;
		}
		_putch( jsTerm[i] );
	}
}
