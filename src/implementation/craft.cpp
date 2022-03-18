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
            return isBlockTheSame(recipePlacement[i][j], this->Table[i][j].getName());
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
    // INFINITE LOOP ?! :<
    int count = 0;
    while (!found)
    {
        for (string possibleRecipe : stringOfPossibleRecipe)
        {
            for (SingleRecipe recipe : recipesList)
            {
                if (possibleRecipe == recipe.getItemResultName())
                {
                    // TODO
                    // ini berarti "recipe" udah merupakan recipe yang ada di possibleRecipe
                    int recipeRow = recipe.getNRowRecipe();
                    int recipeCol = recipe.getNColRecipe();

                    // 1x1
                    if (recipeRow == 1 && recipeCol == 1)
                    {
                        for (int i = 1; i <= 9; i++)
                        {
                            vector<vector<string>> recipePlacement = makePossibleRecipePlacement1x1(recipe.getItemResultName(), i);
                            found = this->itemInTableSameAsRecipePlacement(recipePlacement);
                            resultRecipe = recipe;
                        }
                    }
                    // 3x3
                    else if (recipeRow == 3 && recipeCol == 3)
                    {
                        vector<vector<string>> recipePlacement = recipe.getItemPlacement();
                        found = this->itemInTableSameAsRecipePlacement(recipePlacement);
                        if (!found)
                        {
                            SingleRecipe mirrorRecipe = recipe.getItemMirroredInPlacement();
                            bool sameMatrixAsOriginal = recipe.isOriginalRecipeSameAsMirroredRecipe(mirrorRecipe);
                            if (sameMatrixAsOriginal)
                            {
                                found = this->itemInTableSameAsRecipePlacement(mirrorRecipe.getItemPlacement());
                            }
                        }
                    }
                    // 2x1
                    else if (recipeRow == 2 && recipeCol == 1)
                    {
                    }
                    // 1x2
                    else if (recipeRow == 1 && recipeCol == 2)
                    {
                    }
                    // 3x1
                    else if (recipeRow == 3 && recipeCol == 1)
                    {
                    }
                    // 1x3
                    else if (recipeRow == 1 && recipeCol == 3)
                    {
                    }
                    // 2x3
                    else if (recipeRow == 2 && recipeCol == 3)
                    {
                    }
                    // 3x2
                    else if (recipeRow == 3 && recipeCol == 2)
                    {
                    }
                    // 2x2
                    else if (recipeRow == 2 && recipeCol == 2)
                    {
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
