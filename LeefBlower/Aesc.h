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