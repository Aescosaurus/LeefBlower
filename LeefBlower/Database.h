#pragma once

#include "Aesc.h"

class Database
{
public:
	enum class Term
	{
		IntD, // Definition.
		IntU, // Use.
		BoolD,
		BoolU,
		FloatD,
		FloatU,
		IFuncD,
		IFuncU,
		BFuncD,
		BFuncU,
		FFuncD,
		FFuncU,
		ObjD,
		ObjU,
		Other
	};
	class Entry
	{
	public:
		Entry() = default;
		Entry( char* term_in );
		void ConvertToJS();
		void Print() const;
		void PrintType() const;
		void PrintJS() const;
		void JSCode( char* fileName );
	private:
		char term[69];
		char jsTerm[69 * 2];
		int curTerm = 0;
		Term keywordType = Term::Other;
		bool isConst = false;
		bool isComment = false;
	};
public:
	void Print() const;
	void Add( char* term );
	void JSCode( char* fileName );
	void DeleteShit();
private:
	Entry* entries = new Entry[69 * 100];
	int numEntries = 0;
};
