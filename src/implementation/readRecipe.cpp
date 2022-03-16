#include <bits/stdc++.h>
#include <cstdio>
#include <cerrno>
#include <dirent.h>
#include <map>
#include <fstream>

using namespace std;

map<int, vector<string>> ReadRecipes(void)
{
    map<int, vector<string>> recipes;
    struct dirent **namelist;
    int n = scandir("../config/recipe", &namelist, NULL, alphasort);
    if (n < 0)
        perror("scandir");
    else
    {
        while (n > 0)
        {
            string filename = namelist[n - 1]->d_name;
            ifstream file("../config/recipe/" + filename);
            string line;
            getline(file, line);

            int firstInteger = int(line[0]) - 48;
            int secondInteger = int(line[2]) - 48;
            if (firstInteger > 0 && secondInteger > 0)
            {
                recipes[firstInteger * secondInteger].push_back(filename);
            }

            delete namelist[n - 1];
            n--;
        }

        delete namelist;
    }
    
    for (const auto &elem : recipes)
    {
        cout << elem.first << " : " << "[";
        for (const auto &elem2 : elem.second)
        {
            cout << elem2 << " ";
        }
        cout << "]" << endl;
    }
    return recipes;
}