/* Day 21, part 2 = kllgt,jrnqx,ljvx,zxstb,gnbxs,mhtc,hfdxb,hbfnkq */

#include <stdio.h>
#include "allergens.h"

int main() {
    struct AllergenData *data = readAllergenData();

    if (data) {
        int notAllergenIngredientCount = 0;

        for (int i = 0; i < data->allergenCount; i++) {
            printf("%s", *data->minimizedAllergenGroups[i].ingredientList.ingredients);
            
            if (i < data->allergenCount - 1) {
                printf(",");
            }
        }

        freeAllergenData(data);
    }

    return 0;
}
