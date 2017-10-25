#include "Database.h"

#include <conio.h>

void Database::Print() const
{
	for( int i = 0; i < numEntries; ++i )
	{
		entries[i].Print();
		_putch( '\t' ); _putch( '|' ); _putch( '\t' );
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
	entries[numEntries++] = { term_in };
}

void Database::JSCode( char* fileName )
{
	aesc::clear_file( fileName );
	for( int i = 0; i < numEntries; ++i )
	{
		entries[i].JSCode( fileName );
	}
}

void Database::DeleteShit()
{
	delete[] entries;
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
		// Don't really need to write anything for statements, they works anyway.
	}
	ConvertToJS();
}

void Database::Entry::ConvertToJS()
{
	bool var = false;
	bool func = false;
	bool obj = false;

	bool hasPlacedParenthesis = false;

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
	else if( keywordType == Term::ObjD )
	{ // function, but this time it's an object.
		obj = true;
		jsTerm[t++] = 'f'; jsTerm[t++] = 'u'; jsTerm[t++] = 'n'; jsTerm[t++] = 'c';
		jsTerm[t++] = 't'; jsTerm[t++] = 'i'; jsTerm[t++] = 'o'; jsTerm[t++] = 'n';
	}
	else
	{
		// Do nothing. :>
	}

	jsTerm[t++] = ' ';

	for( int i = 0; i < curTerm; ++i )
	{
		if( term[i] != ' ' )
		{
			jsTerm[t] = term[i];
		}
		else
		{
			--t;
		}

		if( term[i] == ':' )
		{
			if( var )
			{
				// TODO: Deal with spaces in a separate minifier, not here.
				// jsTerm[--t] = '=';
				// ++i;
				jsTerm[t] = '=';
			}
			else if( func || obj )
			{
				// jsTerm[--t] = '(';
				// ++i; // Deals with unnecessary spaces.
				jsTerm[t] = '(';
			}
		}
		else if( term[i] == '{' )
		{
			jsTerm[t++] = ')';
			jsTerm[t] = '{';
			hasPlacedParenthesis = true;
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
	if( ( func || obj ) && !hasPlacedParenthesis )
	{
		jsTerm[t++] = ')';
	}

	jsTerm[t] = 0;
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
	for( int i = 0; jsTerm[i] != 0; ++i )
	{
		_putch( jsTerm[i] );
	}
}

void Database::Entry::JSCode( char* fileName )
{
	aesc::write_file( jsTerm,fileName );
}
