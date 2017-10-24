#pragma once

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
		ObjU
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
	private:
		char term[69];
		char jsTerm[69 * 2];
		int curTerm = 0;
		Term keywordType;
		bool isConst = false;
	};
public:
	void Print() const;
	void Add( char* term );
	void DeleteShit()
	{
		delete entries;
	}
private:
	Entry* entries = new Entry[6969];
	int curEntry = 0;
};
