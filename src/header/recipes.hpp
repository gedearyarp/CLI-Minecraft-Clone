#ifndef RECIPES_HPP
#define RECIPES_HPP

#include "item.hpp"

#include <string>
#include <vector>

using namespace std;

class SingleRecipe {
    private:
        string filename;
        int NRowRecipe;
        int NColRecipe;
        string ItemResultName;
        int ItemResultQuantity;
        vector<vector<string>> ItemPlacement;
        
    public:
        SingleRecipe();
        SingleRecipe(string filename, int NrowRecipe, int NcolRecipe, string ItemResultName, int ItemResultQuantity, vector<vector<string>> ItemPlacement);
        
        // getters
        string getFilename();
        int getNRowRecipe();
        int getNColRecipe();
        string getItemResultName();
        int getItemResultQuantity();
        vector<vector<string>> getItemPlacement();

        // mirror of itemplacement;
        SingleRecipe getItemMirroredInPlacement();

        // checking if mirrored matrix have the same recipe as the recipe
        bool isOriginalRecipeSameAsMirroredRecipe(SingleRecipe mirroredRecipe);

        void showItemPlacement();

};

class Recipes {
    private:
        vector<SingleRecipe> recipesList;
        int totalRecipe;
    public:
        Recipes();

        int getTotalRecipe();
        void setTotalRecipe(int totalRecipe);
        vector<SingleRecipe> getRecipesList();

        void AddNewSingleRecipe(SingleRecipe newSingleRecipe);
};

#endif