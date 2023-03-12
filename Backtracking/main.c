/*
Patikrinti, ar iš duotos skaičių aibės gali būti išrinktas netuščias poaibis, kurio skaičių suma būtų 0
*/

#include <stdio.h>
#include <stdlib.h>

static int isSumZero = 0;

void generateSubsets(int* set, int index, int size, int sum, int flag);

int main(){

    int set[] = {1, 2, 3, -50, 5};

    int size = sizeof(set)/sizeof(int);

    generateSubsets(set, 0, size, 0, 0);

    if(isSumZero){
        printf("There is subset with sum 0!");
    }
    else{
        printf("There is no subset with sum 0!");
    }

    return 0;
}

void generateSubsets(int* set, int index, int size, int sum, int flag){
    
    if(flag > 0 && sum == 0){
        isSumZero = 1;
        return;
    }

    if(index == size){
        return;
    }

    generateSubsets(set, index+1, size, sum + set[index], flag+1);
    generateSubsets(set, index+1, size, sum, flag);
}
