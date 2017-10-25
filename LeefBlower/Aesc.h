#pragma once

#include <conio.h>
#include <fstream>

class aesc // Similar to a namespace but that broke obj files... :(
{
public:
	static void print( char* str )
	{
		for( ; *str != 0; ++str )
		{
			_putch( *str );
		}
		str = 0;
	}
	static void read_file( char* str,char* fileName,int maxLen )
	{
		int curChar = 0;
		std::ifstream in( fileName );
		for( char c = in.get(); in.good() && curChar + 1 < maxLen; c = in.get() )
		{
			str[curChar++] = c;
		}
		str[curChar] = 0;
	}
	static int read_file_offset( char* str,char* fileName,int maxLen,int offset )
	{
		// TODO: Say an error if you get to the end of the loop without a \n.
		int curChar = 0;
		std::ifstream in( fileName );
		in.seekg( offset );
		for( char c = in.get(); in.good() && curChar + 1 < maxLen; c = in.get() )
		{
			if( curChar == '\n' )
			{
				break;
			}
			str[curChar++] = c;
		}
		if( !in.good() )
		{
			return 6969;
		}
		str[curChar++] = 0;
		return curChar;
	}
	static void write_file( char* str,char* fileName )
	{
		std::ofstream out( fileName,std::ios::app );
		// out.seekp( position );
		for( char c = *str; *str != 0; ++str,c = *str )
		{
			out.put( c );
		}
	}
	static void clear_file( char* fileName )
	{
		std::ofstream out( fileName );
		out.clear();
	}
};