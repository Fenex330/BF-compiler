#include <TXLib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector> 

#define LOG(x) std::cout << x << std::endl

//const size_t CELL_SIZE = 127;


//uniprogram (UTF-8) can be used instead
//q list added for control characters stub


int doProccess (std::ifstream& source)
	{
	typedef int Type;

	if (!source.is_open()) { std::cerr << "error openning file" << std::endl; return 0; }
    	
	std::vector<Type> mem_tape;
	const size_t mem_tape_size = 1024;
	mem_tape.resize (mem_tape_size);

	int mem_pos = 0;
    bool skip = false;
    size_t last_jump = 0;

    std::string line;
    std::string program;

	while (!source.eof())
		{
		getline (source, line);
		program.append (line);
		}


	size_t program_len = program.length();
	for (size_t i = 0; i < program_len; i++)
		{
		if (skip)
			{
			if (program.at (i) != ']') continue;
			skip = false; 
			i++; 
			}

        if ((size_t)mem_pos > mem_tape.size()) mem_tape.resize(mem_pos + 1);
		if (mem_pos < 0) mem_pos = 0;
        
		switch (program.at (i))
			{
			case '>':
				{
				mem_pos++;
				break;
				}
			case '<':
				{
				mem_pos--;
				break;
				}
			case '+':
				{	
				(mem_tape.at(mem_pos))++;
				//(mem_tape.at(mem_pos) > CELL_SIZE) ? mem_tape.at(mem_pos) = 0 : NULL; //forward wrap around
				break;
				}
			case '-':
				{
				(mem_tape.at(mem_pos))--;
				//(mem_tape.at(mem_pos) < 0) ? mem_tape.at(mem_pos) = 0 : NULL;
				break;
				}
			case '.':
				{
				std::cout << static_cast<char>(mem_tape.at(mem_pos));
				break;
				}
			case ',':
				{
				char temp;
				std::cin >> temp;
				mem_tape.at(mem_pos) = static_cast<int>(temp);
				break;
				}
			case '[':
				{
				last_jump = i;
				if (mem_tape.at(mem_pos) == 0) skip = true;
				break;
				}
			case ']':
				{
				if (mem_tape.at(mem_pos) != 0) i = last_jump;
				break;
				}
			default: {;}
				//All characters other than ><+-.,[] should be considered comments and ignored
            	
        	}
    	}
	return 1;	  
	}

int main(int argc, char* argv [])
	{
	if (argc == 1) { LOG("No arguments were passed. At least one expected"); return 0; }
	
	std::string filename;
    filename = argv[1];
    
	std::ifstream source;
    source.open (filename);
	
    return doProccess (source);


    source.close();
	}