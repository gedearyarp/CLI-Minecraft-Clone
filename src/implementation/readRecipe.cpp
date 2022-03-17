#include "../header/recipes.hpp"
#include <bits/stdc++.h>
#include <cstdio>
#include <cerrno>
#include <dirent.h>
#include <map>
#include <fstream>
#include <cstring>

using namespace std;

void SingleRecipeVisualization(SingleRecipe single)
{
    int Row = single.getNRowRecipe();
    int Col = single.getNColRecipe();
    string resultName = single.getItemResultName();
    int resultQuantity = single.getItemResultQuantity();
    string filename = single.getFilename();
    vector<vector<Item>> iPlacement = single.getItemPlacement();

    cout << "filename: " << filename << endl;
    cout << "Row & Column:" << Row << " " << Col << endl;
    cout << "Result Item: " << resultName << endl;
    cout << "Result Qty: " << resultQuantity << endl;
    cout << "iPlacement: " << endl;

    for (int j = 0; j < Row; j++)
    {
        for (int k = 0; k < Col; k++)
        {
            Item el = iPlacement[j][k];
            cout << el.getName() << " ";
        }
        cout << endl;
    }

    cout << endl;
}

int countItemInSingleRecipe(SingleRecipe single)
{
    int Row = single.getNRowRecipe();
    int Col = single.getNColRecipe();
    vector<vector<Item>> iPlacement = single.getItemPlacement();
    int countItem = 0;

    for (int j = 0; j < Row; j++)
    {
        for (int k = 0; k < Col; k++)
        {
            Item el = iPlacement[j][k];
            if (el.getName() != "-") {
                countItem++;
            }
        }
    }
    return countItem;
}

map<int, vector<string>> MapRecipesFromRecipesClass(Recipes recipes)
{
    map<int, vector<string>> recipesMapping;
    vector<SingleRecipe> RecipesList = recipes.getRecipesList();

    for (int i = 0; i < recipes.getTotalRecipe(); i++)
    {
        SingleRecipe single = RecipesList[i];
        int countItem = countItemInSingleRecipe(single);
        recipesMapping[countItem].push_back(single.getFilename());
    }

    // // visualization 
    // for (const auto &elem : recipesMapping)
    // {
    //     cout << elem.first << " : "
    //          << "[";
    //     for (const auto &elem2 : elem.second)
    //     {
    //         cout << elem2 << " ";
    //     }
    //     cout << "]" << endl;
    // }

    return recipesMapping;
}

Recipes ReadRecipesFromConfigToRecipesClass()
{
    Recipes newRecipes;
    struct dirent **namelist;
    int n = scandir("../../config/recipe", &namelist, NULL, alphasort);
    if (n < 0)
        perror("scandir");
    else
    {
        int totalRecipe = 0;
        while (n > 0)
        {
            string filename = namelist[n - 1]->d_name;
            if (filename != "." && filename != "..")
            {
                ifstream file("../../config/recipe/" + filename);

                // inizialize all config for single recipe
                SingleRecipe newSingleRecipe;
                int count = 0;
                int NRow = 0;
                int NCol = 0;
                string itemResultName = "";
                string itemResultQuantity = "0";
                vector<vector<Item>> itemPlacement;

                string line;

                // get row and column
                getline(file, line);
                stringstream ss(line);
                string word;
                ss >> word;
                NRow = stoi(word);
                ss >> word;
                NCol = stoi(word);

                // get item placement
                for (int i = 0; i < NRow; i++)
                {
                    getline(file, line);
                    stringstream ss(line);
                    string word;
                    vector<Item> temp;
                    for (int j = 0; j < NCol; j++)
                    {
                        ss >> word;
                        // TODO ITEMNYA GABISA CONSTRUCT DARI STRING
                        temp.push_back(Item());
                    }
                    itemPlacement.push_back(temp);
                }

                // get item result name & quantity
                getline(file, line);
                stringstream ss2(line);
                ss2 >> word;
                itemResultName = word;
                ss2 >> word;
                itemResultQuantity = word;

                newSingleRecipe = SingleRecipe(filename, NRow, NCol, itemResultName, stoi(itemResultQuantity), itemPlacement);

                newRecipes.AddNewSingleRecipe(newSingleRecipe);
            }

            delete namelist[n - 1];
            n--;
        }

        delete namelist;
    }
    return newRecipes;
}

int main()
{
    Recipes newRecipes = ReadRecipesFromConfigToRecipesClass();
    vector<SingleRecipe> RecipesList = newRecipes.getRecipesList();

    for (int i = 0; i < newRecipes.getTotalRecipe(); i++)
    {
        SingleRecipe single = RecipesList[i];
        SingleRecipeVisualization(single);
    }

    map<int, vector<string>> newMapping = MapRecipesFromRecipesClass(newRecipes);
    return 0;
}