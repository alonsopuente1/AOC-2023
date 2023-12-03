#include <iostream>
#include <array>
#include <fstream>
#include <vector>

using std::array, std::string, std::cout;

#define NUMLINES 140	// Number of lines in the puzzle input
#define NUMCHARS 140	// Number of characters in each line of puzzle input

array<array<char, NUMCHARS>, NUMLINES> puzzleinput;

void loadpuzzle()
{
	std::ifstream file("puzzleinput.txt");

	if(!file.is_open())
	{
		cout << "Failed to open file\n";
		return;
	}

	array<char, NUMCHARS> arr;
	
	int i = 0;
	while(!file.eof())
	{
		file.getline(arr.data(), NUMCHARS + 1);  
		puzzleinput[i++] = arr;
	}
}

string getnumber(int lineindex, int characterindex)
{
	string strnum;
	for(int i = characterindex; i < puzzleinput[lineindex].size(); i++)
		if(isdigit(puzzleinput[lineindex][i]))
			strnum += puzzleinput[lineindex][i];
		else
			break;
	return strnum; 
}

int ispartnumber(int lineindex, int characterindex)
{
	string 	strnum = getnumber(lineindex, characterindex);
	int 	intnum = std::stoi(strnum);
	bool 	checkabove;
	bool	checkbelow;
	int 	endindex = characterindex + strnum.length() - 1;

	checkabove = lineindex != 0;

	checkbelow = lineindex != NUMLINES - 1;

	if(characterindex != 0)
	{
		if(puzzleinput[lineindex][characterindex - 1] != '.')
			return intnum;
	
		if(checkabove && puzzleinput[lineindex - 1][characterindex - 1] != '.')
			return intnum;
		
		if(checkbelow && puzzleinput[lineindex + 1][characterindex - 1] != '.')
			return intnum;
	}

	if(endindex != NUMCHARS - 1)
	{
		if(puzzleinput[lineindex][endindex + 1] != '.')
			return intnum;
		
		if(checkabove && puzzleinput[lineindex - 1][endindex + 1] != '.')
			return intnum;
		
		if(checkbelow && puzzleinput[lineindex + 1][endindex + 1] != '.')
			return intnum;
	}
	for(int i = 0; i < strnum.length(); i++)
	{
		if(	(checkabove && puzzleinput[lineindex - 1][characterindex + i] != '.') || 
			(checkbelow && puzzleinput[lineindex + 1][characterindex + i] != '.'))
		{
			return intnum; 
		}
	}

	return 0;
}

int main()
{
	loadpuzzle();

	int totalpartnumbers = 0;
	for(int j = 0; j < NUMLINES; j++)
	{
		for(int i = 0; i < NUMCHARS; i++)
		{
			// file[j] is the current line
			if(!isdigit(puzzleinput[j][i]))
				continue;
			
			if(int num = ispartnumber(j, i))
			{
				totalpartnumbers += num;
			}
			i += getnumber(j, i).length() - 1;
		}
	}

	cout << totalpartnumbers;

	return 0;
}