#include "../header/craft.hpp"

#include "readRecipe.cpp"
#include "possiblePlacement.cpp"

#include <map>

using namespace std;

bool isBlockTheSame(string wordInRecipe, string wordInTable)
{
    ItemConfig temp = ItemConfig("./config", "item.txt");
    bool isWordAType = temp.isType(wordInRecipe); // return apakah wordInRecipe merupakan type atau bukan // STONE, LOG
    if (!isWordAType)
    {
        return wordInRecipe == wordInTable;
    }
    else
    {
        // berisi semua item dengan tipe wordInrRecipe
        vector<string> listOfItemString = temp.listOfItemWithType(wordInRecipe);
        for (int i = 0; i < listOfItemString.size(); i++)
        {
            if (listOfItemString[i] == wordInTable)
            {
                return true;
            }
        }
        return false;
    }
    return false;
}

CraftingTable::CraftingTable()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->Table[i][j] = new Item();
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
            if (this->Table[i][j]->getName() != "-")
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
            this->Table[i][j] = new Item();
        }
    }
}

Item CraftingTable::getSlot(int slotKe) const
{
    return *this->Table[slotKe / 3][slotKe % 3];
}

void CraftingTable::setSlot(int slotKe, Item *item)
{
    this->Table[slotKe / 3][slotKe % 3] = item;
}

Item *&CraftingTable::slotItem(int slotKe)
{
    return this->Table[slotKe / 3][slotKe % 3];
}

void CraftingTable::showCraftingTable()
{
    cout << "Crafting Table: " << endl;
    int idx = 0;
    for (int i = 0; i < 3; i++)
    {
        cout << "[ ", idx, ": ";
        for (int j = 0; j < 3; j++)
        {
            string name = Table[i][j]->getName();
            int quantity = Table[i][j]->getQuantity();
            cout << "[C " << name << " " << quantity;
            if (Table[i][j]->getCategory().compare(0, 4, "TOOL", 0, 4) == 0)
            {
                cout << " " << Table[i][j]->getDurability();
            }
            cout << " ]";
            if (j != 2)
            {
                cout << " ";
            }
            idx++;
        }
        cout << " ]" << endl;
    }
}

bool CraftingTable::itemInTableSameAsRecipePlacement(vector<vector<string>> recipePlacement)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!isBlockTheSame(recipePlacement[i][j], this->Table[i][j]->getName()))
            {
                return false;
            }
        }
    }
    return true;
};

map<string, int> CraftingTable::craft()
{
    int nItem = this->countItemOnTable();
    if (nItem == 0)
    {
        cout << "No item on table" << endl;
        return map<string, int>();
    }

    // check for increasing durability of TOOL ITEM
    bool isToolItem = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->Table[i][j]->getCategory() == "TOOL")
            {
                isToolItem = true;
            }
        }
    }

    if (isToolItem)
    {
        bool thereIsNonToolItem = false;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (this->Table[i][j]->getCategory() == "NONTOOL")
                {
                    thereIsNonToolItem = true;
                }
            }
        }

        if (thereIsNonToolItem)
        {
            cout << "Cannot craft with tool and non-tool item" << endl;
            return map<string, int>();
        }
        else
        {
            bool isToolNameSame = false;
            string toolName = "";
            bool done = false;
            int countDurability = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (!done)
                    {
                        toolName = this->Table[i][j]->getName();
                        countDurability += this->Table[i][j]->getDurability();
                        done = true;
                    }
                    else
                    {
                        if (toolName == this->Table[i][j]->getName())
                        {
                            countDurability += this->Table[i][j]->getDurability();
                        }
                        else
                        {
                            isToolNameSame = true;
                        }
                    }
                }
            }

            if (!isToolNameSame)
            {
                cout << "Tool name is not the same" << endl;
                return map<string, int>();
            }
            else
            {
                cout << "Increase Tool " << toolName << " with durability: " << countDurability << endl;
                this->clearTable();
                return map<string, int>{{"ADD_DURABILITY " + toolName, countDurability}};
            }
        }
    }
    else
    {
        ItemConfig readItemConfigs = ItemConfig("./config", "item.txt");
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
                            positions = {1, 2, 3};
                        }
                        // 1x3
                        else if (recipeRow == 1 && recipeCol == 3)
                        {
                            positions = {1, 4, 7};
                        }
                        // 2x3
                        else if (recipeRow == 2 && recipeCol == 3)
                        {
                            positions = {1, 4};
                        }
                        // 3x2
                        else if (recipeRow == 3 && recipeCol == 2)
                        {
                            positions = {1, 2};
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
            this->clearTable();
            return map<string, int>{{resultRecipe.getItemResultName(), resultRecipe.getItemResultQuantity()}};
        }
        else
        {
            cout << "No recipe match with item on crafting table" << endl;
            return map<string, int>{{"-", 0}};
        }
    }
}
