#include <iostream>
#include <fstream>
#include <vector>

#define ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))

using std::cout, std::cerr, std::string;

struct diceinfo {
	string  col;
	int     num;
};

extern std::vector<string> split(const string &in, const string& token);

diceinfo extractinfo(const string& str)
{
	std::vector<string> arr = split(str, " ");

	return {arr[1], std::stoi(arr[0])};
}

int extractid(const string& str)
{
	return std::stoi(str.substr(5, str.find(':') - 5));
}

bool meetsreq(const string& str)
{
	std::vector<string> arr = split(str, ": ");

	arr = split(arr[1], "; ");

	for(int i = 0; i < arr.size(); i++)
	{
		std::vector<string> temp = split(arr[i], ", ");
		std::vector<diceinfo> set;
		for(const string& s : temp)
			set.push_back(extractinfo(s));

		for(const diceinfo& di : set)
		{
			if( (di.col == "green" && di.num > 13) || 
				(di.col == "blue" && di.num > 14) || 
				(di.col == "red" && di.num > 12))
				return false;
		}
	}

	return true;
}

int getpower(const string& str)
{
	std::vector<string> arr = split(str, ": ");

	arr = split(arr[1], "; ");

	std::vector<diceinfo> di;

	for(const string& temp : arr)
	{
		std::vector<string> set = split(temp, ", ");
		for(const string& setstr : set)
		{
			di.push_back(extractinfo(setstr));
		}
	}

	int red = 0, green = 0, blue = 0;

	for(const diceinfo& i : di)
	{
		if(i.col == "red" && i.num > red)
			red = i.num;
		if(i.col == "green" && i.num > green)
			green = i.num;
		if(i.col == "blue" && i.num > blue)
			blue = i.num;
	}

	return red * green * blue;
}

int main()
{
	std::fstream file("puzzleinput.txt");

	if(!file.is_open())
	{
		cerr << "Failed to open file";
		return -1;
	}

	char buffer[256];

	int total 		= 0;
	int powertotal 	= 0;
	while(!file.eof())
	{
		file.getline(buffer, ARRAYSIZE(buffer));

		if(meetsreq(string(buffer)))			// Solution to first problem
			total += extractid(string(buffer));

		powertotal += getpower(string(buffer));	// Solution to second
	}

	cout << powertotal;

	file.close();

	return 0;
}