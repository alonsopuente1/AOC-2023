#include <iostream>
#include <fstream>
#include <string>

using std::cout, std::cerr;

int isstrdigit(const std::string& str)
{
	struct strnums
	{
		std::string str;
		int 		num;
	};

    strnums nums[] = {
        {"one", 	1},
        {"two", 	2},
        {"three", 	3},
        {"four", 	4},
        {"five", 	5},
        {"six", 	6},
        {"seven", 	7},
        {"eight", 	8},
        {"nine", 	9}
    };

    for(int i = 0; i < 10; i++)
    	if(str.substr(0, nums[i].str.length()) == nums[i].str)
			return nums[i].num;
    
    return 0;
}


int extractnums(const std::string& str)
{
    int firstnum = -1;
    int secondnum = -1;

    cout << str << " : ";

    for(int i = 0; i < str.length(); i++)
    {
        if(firstnum > -1 && secondnum > -1)
        {
            break;
        }
        
        if(firstnum < 0)
        {
			if(isdigit(str[i]))
            	firstnum = static_cast<int>(str[i]) - 0x30;
			else if(int num = isstrdigit(str.substr(i)))
				firstnum = num;
        }
        if(secondnum < 0)
        {
			if(isdigit(str[str.length() - i - 1]))
            	secondnum = static_cast<int>(str[str.length() - i - 1]) - 0x30;
			else if(int num = isstrdigit(str.substr(str.length() - i - 1)))
				secondnum = num;
        }
    }

    cout << (firstnum * 10) + secondnum << "\n"; 
    
    return (firstnum * 10) + secondnum;
}

int main()
{
    std::ifstream file("puzzleinput.txt");

    if(!file.is_open())
    {
        cerr << "Failed to open file";
        return -1;
    }
    else
        cout << "File opened!\n";

    int total = 0;
    while(!file.eof())
    {
        char buffer[64];
        file.getline(buffer, 64);
        total += extractnums(std::string(buffer));
    }

    cout << total << "\n";

    file.close();

    return 0;
}