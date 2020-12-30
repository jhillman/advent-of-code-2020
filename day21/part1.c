/* Day 21, part 1 = 1815 */

#include <stdio.h>
#include "allergens.h"

int main() {
    struct AllergenData *data = readAllergenData();

    if (data) {
        int notAllergenIngredientCount = 0;
        bool notAllergenIngredient = true;

        for (int i = 0; i < data->ingredientListsCount; i++) {
            for (int j = 0; j < data->ingredientLists[i].count; j++) {
                notAllergenIngredient = true;

                for (int k = 0; notAllergenIngredient && k < data->allergenCount; k++) {
                    if (strcmp(*data->minimizedAllergenGroups[k].ingredientList.ingredients, data->ingredientLists[i].ingredients[j]) == 0) {
                        notAllergenIngredient = false;
                    }
                }

                if (notAllergenIngredient) {
                    ++notAllergenIngredientCount;
                }
            }
        }

        freeAllergenData(data);

        printf("%d", notAllergenIngredientCount);
    }

    return 0;
}
