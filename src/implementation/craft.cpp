#include "../header/craft.hpp"
#include "../header/item.hpp"

#include "readRecipe.cpp"
#include "possiblePlacement.cpp"

#include <map>

using namespace std;

bool isBlockTheSame(string wordInRecipe, string wordInTable)
{
    Item temp;
    bool isWordAType = temp.isType(wordInRecipe);
    if (!isWordAType)
    {
        return wordInRecipe == wordInTable;
    }
    else
    {
        vector<string> listOfItemString = temp.listOfItemWithType(wordInRecipe);
        for (int i = 0; i < listOfItemString.size(); i++)
        {
            if (listOfItemString[i] == wordInTable)
            {
                return true;
            }
        }
    }
    return false;
}

CraftingTable::CraftingTable()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->Table[i][j] = Item();
        }
    }
    this->recipes = ReadRecipesFromConfigToRecipesClass();
};

int CraftingTable::countItemOnTable()
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->Table[i][j].getName() != "-")
            {
                count++;
            }
        }
    }
    return count;
};

void CraftingTable::clearTable()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->Table[i][j] = Item();
        }
    }
}

Item CraftingTable::getSlot(int slotKe) const
{
    return this->Table[slotKe / 3][slotKe % 3];
}

void CraftingTable::setSlot(int slotKe, Item item)
{
    this->Table[slotKe / 3][slotKe % 3] = item;
}

void CraftingTable::showCraftingTable()
{
    cout << "Crafting Table" << endl;
    int idx = 0;
    for (int i = 0; i < 3; i++)
    {
        cout << "[ C", idx, ": ";
        for (int j = 0; j < 3; j++)
        {
            string name = Table[i][j].getName();
            int quantity = Table[i][j].getQuantity();
            cout << name << " - " << quantity << " ]";
            if (j != 2)
            {
                cout << " ";
            }
            idx++;
        }
        cout << endl;
    }
}

bool CraftingTable::itemInTableSameAsRecipePlacement(vector<vector<string>> recipePlacement)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!isBlockTheSame(recipePlacement[i][j], this->Table[i][j].getName()))
            {
                return false;
            }
        }
    }
    return true;
};

void CraftingTable::craft(Inventory inventory)
{
    int nItem = this->countItemOnTable();
    if (nItem == 0)
    {
        cout << "No item on table" << endl;
    }

    ItemConfig readItemConfigs = ItemConfig("../../config", "item.txt");
    map<int, vector<string>> mapOfRecipe = MapRecipesFromRecipesClass(this->recipes);

    auto it = mapOfRecipe.find(nItem);
    vector<string> stringOfPossibleRecipe = it->second;

    vector<SingleRecipe> recipesList = this->recipes.getRecipesList();

    Item itemTemp;
    bool found = false;
    SingleRecipe resultRecipe;
    int count = 0;
    while (!found && count < stringOfPossibleRecipe.size())
    {
        for (string possibleRecipe : stringOfPossibleRecipe)
        {
            for (SingleRecipe recipe : recipesList)
            {
                if (possibleRecipe == recipe.getItemResultName())
                {
                    // ini berarti "recipe" udah merupakan recipe yang ada di possibleRecipe
                    int recipeRow = recipe.getNRowRecipe();
                    int recipeCol = recipe.getNColRecipe();

                    SingleRecipe mirrorRecipe = recipe.getItemMirroredInPlacement();
                    bool sameMatrixAsOriginal = recipe.isOriginalRecipeSameAsMirroredRecipe(mirrorRecipe);

                    vector<int> positions;

                    // 1x1
                    if (recipeRow == 1 && recipeCol == 1)
                    {
                        positions = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                    }
                    // 3x3
                    else if (recipeRow == 3 && recipeCol == 3)
                    {
                        positions = {1};
                    }
                    // 2x1
                    else if (recipeRow == 2 && recipeCol == 1)
                    {
                        positions = {1, 2, 3, 4, 5, 6};
                    }
                    // 1x2
                    else if (recipeRow == 1 && recipeCol == 2)
                    {
                        positions = {1, 2, 4, 5, 7, 8};
                    }
                    // 3x1
                    else if (recipeRow == 3 && recipeCol == 1)
                    {
                        positions = {1, 2, 3, 4, 5, 6};
                    }
                    // 1x3
                    else if (recipeRow == 1 && recipeCol == 3)
                    {
                        positions = {1, 2, 3, 4, 5, 6};
                    }
                    // 2x3
                    else if (recipeRow == 2 && recipeCol == 3)
                    {
                        positions = {1, 4, 7};
                    }
                    // 3x2
                    else if (recipeRow == 3 && recipeCol == 2)
                    {
                        positions = {1, 2, 3};
                    }
                    // 2x2
                    else if (recipeRow == 2 && recipeCol == 2)
                    {
                        positions = {1, 2, 4, 5};
                    }
                    else
                    {
                        positions = {};
                    }

                    vector<vector<string>> recipePossiblePlacement;
                    for (int position : positions)
                    {
                        recipePossiblePlacement = makeNewMatrix(position, recipe.getItemPlacement());
                        if (itemInTableSameAsRecipePlacement(recipePossiblePlacement))
                        {
                            found = true;
                            resultRecipe = recipe;
                            break;
                        }
                    }

                    if (!found && !sameMatrixAsOriginal)
                    {
                        for (int position : positions)
                        {
                            recipePossiblePlacement = makeNewMatrix(position, mirrorRecipe.getItemPlacement());
                            if (itemInTableSameAsRecipePlacement(recipePossiblePlacement))
                            {
                                found = true;
                                resultRecipe = mirrorRecipe;
                                break;
                            }
                        }
                    }
                }
            }
            count++;
        }
    }

    if (found)
    {
        cout << "Crafting success" << endl;
        cout << "Created : " << resultRecipe.getItemResultQuantity() << " " << resultRecipe.getItemResultName() << endl;
        inventory.give(resultRecipe.getItemResultName(), resultRecipe.getItemResultQuantity());
        this->clearTable();
    }
    else
    {
        cout << "No recipe match with item on crafting table" << endl;
    }
}
