// #include "../header/craft.hpp"
// #include "../header/item.hpp"

#include <bits/stdc++.h>

#include <map>

using namespace std;

void visualizeMatrix(vector<vector<string>> matrix)
{

    for (int j = 0; j < matrix.size(); j++)
    {
        for (int k = 0; k < matrix[j].size(); k++)
        {
            cout << matrix[j][k] << " ";
        }
        cout << endl;
    }
}

vector<vector<string>> makeNewMatrix(int position, vector<vector<string>> matrixPlacement)
{
    vector<vector<string>> newMatrix = vector<vector<string>>(0, vector<string>(0));

    int count = 1;
    int indexIPosition = 0;
    int indexJPosition = 0;
    for (int i = 0; i < 3; i++)
    {
        vector<string> temp;
        for (int j = 0; j < 3; j++)
        {
            temp.push_back("-");
            if (count == position)
            {
                indexIPosition = i;
                indexJPosition = j;
            }
            count++;
        }
        newMatrix.push_back(temp);
    }


    int tempI = indexIPosition;
    for (int i = 0; i < matrixPlacement.size(); i++)
    {
        int tempJ = indexJPosition;
        for (int j = 0; j < matrixPlacement[i].size(); j++)
        {
            newMatrix[tempI][tempJ] = matrixPlacement[i][j];
            tempJ++;
        }
        tempI++;
    }
    return newMatrix;
}

vector<vector<string>> makePossibleRecipePlacement1x1(string a, int position)
{
    vector<vector<string>> newMatrix;

    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        vector<string> temp;
        for (int j = 0; j < 3; j++)
        {
            if (count == position)
            {
                temp.push_back(a);
            }
            else
            {
                temp.push_back("");
            }
        }
        newMatrix.push_back(temp);
    }

    return newMatrix;
}
