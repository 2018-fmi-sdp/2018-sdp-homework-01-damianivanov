// Dom.SPD1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class String
{
private:
	char*s;
	unsigned int size;
public:
	String ()
	{
		size = 0;
		s = new char[size];

	}
	String ( const String& other )
	{
		stringcopy ( other );
	}
	String ( char* str )
		{
			int i = 0;
			while ( str[i] != '\0' )
			{
				i++;
			}
			s = new char[i + 1];
			for ( int j = 0; j < i; j++ )
			{
				s[j] = str[j];
			}
			s[i] = '\0';
		}
	const char& operator[] ( unsigned int i )
	{
		return s[i];
	}
	/*int sizee ( String& str )
	{
		int i = 0;
		while ( str[i] != '\0' )
			i++;
		return i;
	}*/
	void stringcopy ( const String& other )
	{
		size = other.size;
		s = new char[size + 1];
		strcpy_s ( s , other.size , other.s );
	}
	char gets ()
	{
		return *s;
	}
	String& operator = ( const String& other )
	{
		if ( this == &other )
			return *this;

		deletethis ();
		stringcopy ( other );
		return *this;
	}
	String& operator = (char* str )
	{
		deletethis ();
		int i = 0;
		while ( str[i] != '\0' )
		{
			i++;
		}
		s = new char[i + 1];
		for ( int j = 0; j < i; j++ )
		{
			s[j] = str[j];
		}
		s[i] = '\0';
		return *this;

	}
	int stringlen ()
	{
		int i = 0;
		while ( s[i] != '\0' )
		{
			i++;
		}
		return i;
	}
	char operator [] (int i ) 
	{
		char* newch;
		newch = s;
		return newch[i];
	}
	friend ostream& operator<<	( ostream& cout , String& str )
	{
			cout << str.s;
		return cout;
	}
	friend istream& operator>> ( istream& cin , String& str )
	{
		char* inp = new char[400];
		cin.getline ( inp , 400 );
		int i = 0;
		while ( inp[i] != '\0' )
			i++;
		str.size = i + 1;
		delete[]str.s;
		str.s = new char[i + 1];
		for ( int j = 0; j < i; j++ )
		{
			str.s[j] = inp[j];
		}
		str.s[i] = '\0';
		delete[] inp;
		return cin;
	}
	bool operator==( String& other )
	{

		if ( size != other.size )
			return false;
		for ( int i = 0; i < size; i++ )
		{
			if ( s[i] != other.s[i] )
				return false;
		}
		return true;
	}
	bool operator==( const char* str ) const
	{
		return strcmp ( s, str ) == 0;
	}
	void deletethis ()
	{
		delete[]s;
		size = 0;
		s = NULL;

	}
	bool substring ( const char* cha )
	{
		int stringsize = 0;
		while ( s[stringsize] != '\0' )
		{
			stringsize++;
		}
		int charsize = 0;
		while ( cha[charsize] != '\0' )
		{
			charsize++;
		}
		int j = 0;
		if ( stringsize < charsize )
			return false;
		while ( s[j] == cha[j] )
		{
			j++;
		}
		if ( j == charsize )
			return true;
		else
			return false;
	}
	void clear ()
	{
		int i = 0;
		while ( s[i] != '\0' )
		{
			s[i] = '\0';
			i++;
		}
	}
	~String ()
	{
		deletethis ();
	}
};
class Command
{
public:
	///////////////////////////////////////////////////////
	virtual bool match ( String& line ) = 0;
	virtual bool execute (String& line) = 0;
	virtual String& getName () = 0;
	~Command () {};
};
struct Interpretercfg {
	bool extra;
};
class Quit : public Command
{
private:
	String _namecmd;
public:

	Quit () {
		_namecmd= "quit";
	}
	bool match (String& line ) override
	{
		return (line == "quit");
	} 
	bool execute (String& line)  override
	{
		return false;
	}
	String& getName () override {
		return _namecmd;
	}
	/*~Quit ()
	{
		delete this;
	}*/
};
class extraline: public Command
{
private: 
	Interpretercfg _cfg;
	String _namecmd;
public:
	extraline (){
		_namecmd = "extraline";
	}
	bool match (String& line ) override
	{
		return (line == "extraline");
	}
	bool execute ( String& line ) override
	{
		cout << endl;
		return true;
	}
	String& getName ()override {
		return _namecmd; 
	}
	/*~extraline () {
		delete this;
	}*/
};
class cmdprompt : public Command 
{
private:
	String _namecmd;
	
public:
	char*newprompt;
	cmdprompt () {
	
		_namecmd = "cmdprompt";
	}
	bool match (String& line ) override {
		return line.substring ( "cmdprompt" );
	}
	bool execute (String& line ) override{
		int linesize = 0;
		while ( line[linesize] != ' ') { linesize++;}
		linesize++;
		int j = 0;
		newprompt = new char[line.stringlen () - linesize+1];
		while ( line[linesize] != '\0' )
		{
			newprompt[j] = line[linesize];
			j++;
			linesize++;
		}
		newprompt[j++] = '\0';
		return true;
	}
	String& getName () override {
		return _namecmd;
	}
	char* getnewprompt ()
	{
		return newprompt;
	}
	~cmdprompt ()
	{
		delete newprompt;
	}
};
class help : public Command
{
private:
	String _namecmd;
public:
	help () {
		_namecmd = "help";
	}
	bool match ( String& line ) override {
		return (line == "help");
	}
	void printcmds ( Command* cmds[], unsigned size )
	{
		for ( int i = 0; i < size; i++ )
		{
			cout << "-";
			cout << cmds[i]->getName () << endl;
		}
	}
	bool execute ( String& line ) override {

		return true;
	}
	String& getName () override {
		return _namecmd;
	}
	
};
int arr[10] = { 0 };
class asmregset : public Command
{
private:
	String _namecmd;
public:
	asmregset ()
	{
		_namecmd = "asm.reg.set";
	}
	bool match ( String& line ) override
	{
		return line .substring("asm.reg.set ");
	}
	bool execute ( String& line ) override
	{
		int i = 12; //12 e duljivanata na asm.reg.set + space
		if ( line[i + 1] != ' ' )
		{
			cout << "ne validen index[0;10]" << endl;
			return true;
		}
		int index = int ( line[i] - 48 ); // -48 защото цифрите в ASCII таблицата започват от 48
		i += 2;
		int pozicianaminus = i;
		int j = 10;
		int g = i;
		while ( line[g] != '\0' )
		{
			g++;
		}
		char* val = new char[(g-i)+ 1];
		int z = 0;
		
		for ( int k = g-i; k < g; k++ )
		{
			val[z] = line[i];
			z++;
			i++;
		}
		val[(g - i) + 1]='\0';
		int value = atoi ( val );
		arr[index] = value;
		cout << "OK" << endl;
		delete val;
		return true;
	}
	String& getName () override {
		return _namecmd;
	}

};
class asmregadd : public Command 
{
private:
	String _namecmd;
public:
	asmregadd()
	{
		_namecmd = "asm.reg.add";
	}
	bool match ( String& line ) override
	{
		return line.substring ( "asm.reg.add " );

	}
	bool execute ( String& line ) override
	{
		int i = 12;
		if ( line[i + 1] != ' ' && line[i + 3] != ' ' && line[i + 5] != ' ' )
		{
			cout << "Ne korektni indexi" << endl;
			return true;
		}
		char* tmp = new char[1];
		tmp[0] = line[i];
		int dest = atoi ( tmp );
		tmp[0] = line[i + 2];
		int source1 = atoi ( tmp );
		tmp[0] = line[i + 4];
		int source2 = atoi ( tmp );
		if ( arr[source1] + arr[source2] > 100 || arr[source1] + arr[source2] < -100 )
		{
			cout << "ERROR" << endl;
			return true;
		} else
			cout << "OK" << endl;
		arr[dest] = arr[source1] + arr[source2];
		delete tmp;
		return true;
	}
	String& getName () override {
		return _namecmd;
	}
};
class asmregdbg : public Command {
private:
	String _namecmd;
public:
	asmregdbg ()
	{
		_namecmd = "asm.reg.dbg ";
	}
	bool match ( String& line ) override
	{
		return line == "asm.reg.dbg" ;
	}
	bool execute ( String& line )override
	{
		for ( int i = 0; i < 10; i++ )
		{
			cout << "REG_" << i << " = " << arr[i] << endl;
		}
		return true;
	}
	String& getName () override { return _namecmd; }
};
class cmdinterpreter
{
private:
	Command **_cmds;
	unsigned _size;
	Interpretercfg*  _cfg;

public:
	cmdinterpreter ( Command* cmds[] , unsigned size , Interpretercfg *cfg ) :
		_cmds ( cmds ) , _size ( size ) , _cfg ( cfg ) {}

	void repl ()
	{
		
		String line;
		bool flag = true;
		char* prompt = ">";
		while ( flag )
		{
			cout << prompt;
			cin >> line;
			Command *found = NULL;
			
			int j = 0;
			for ( int i = 0; i < _size; i++ )
			{
					if ( _cmds[i]->match ( line ) )
					{
						found = _cmds[i];
						break;
					}
			}
			cmdprompt *foundcmd = dynamic_cast<cmdprompt *>(found); //god bless stackoverflow
			help *helpcmd = dynamic_cast <help *>(found);
			
			if ( found != NULL )
			{
				bool result = found->execute ( line );
				if ( foundcmd )
				{
					prompt = foundcmd->getnewprompt ();
				}
				if ( helpcmd ) 
				{
					helpcmd->printcmds(_cmds,_size);
				}
				if ( !result )
					break;
			}

			else if (found == NULL)
			cout << " UKNOW COMMAND " << endl;
		}
	}
};
void swap ( const char* newprompt , const char* oldprompt )
{
	oldprompt = newprompt;
}
int main()
{
	Interpretercfg cfg;
	Quit q;
	extraline ex;
	cmdprompt cmd;
	help help;
	asmregset ars;
	asmregadd ara;
	asmregdbg ard;
	Command* commands[] = {&q,&ex,&cmd,&help,&ars,&ara,&ard};
	cmdinterpreter ci ( commands , 7 , &cfg );
	ci.repl ();
    return 0;
}

