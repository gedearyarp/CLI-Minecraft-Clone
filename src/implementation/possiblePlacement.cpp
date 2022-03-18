#include "../header/craft.hpp"
#include "../header/item.hpp"

#include <map>

using namespace std;


vector<vector<string>> makePossibleRecipePlacement1x1(string a, int position) 
{
    vector<vector<string>> newMatrix;

    int count = 0;
    for (int i=0; i<3;i++) {
        vector<string> temp;
        for (int j = 0;j<3; j++) {
            if (count == position) {
                temp.push_back(a);
            } else {
                temp.push_back("");
            }
        }
        newMatrix.push_back(temp);
    }
    
    return newMatrix;
}