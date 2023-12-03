#include <iostream>
#include <vector>

using std::string;

std::vector<string> split(const string &in, const string& token)
{
    std::vector<string> out;
    
    out.clear();
    
    string temp;
    
    for (int i = 0; i < int(in.size()); i++)
    {
        string test = in.substr(i, token.size());
    
        if (test == token)
        {
            if (!temp.empty())
            {
                out.push_back(temp);
                temp.clear();
                i += (int)token.size() - 1;
            }
            else
            {
                out.push_back("");
            }
        }
        else if (i + token.size() >= in.size())
        {
            temp += in.substr(i, token.size());
            out.push_back(temp);
            break;
        }
        else
        {
            temp += in[i];
        }
    }

    return out;
}