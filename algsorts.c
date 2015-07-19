#include "alghead.h"

void printArray(int *arrayPtr,int wall){
	for(i = 0; i < ARRAY_SIZE; i++){
		printf("%d ", *arrayPtr++);
		if(wall == i+1) printf("\b|");
	}
	printf("\n\n");
}

void fillArray(int *arrayPtr){
	srand (time(NULL));
	for(i = 0; i < ARRAY_SIZE; i++)
		*arrayPtr++ = RANDOM_INT(30);
}

void insertionSort(int array[]){
	int curr, index, wall;
	
	for(wall = 1; wall < ARRAY_SIZE; wall++){
		curr = array[wall];
		index = wall - 1;
		while(index >= 0 && curr < array[index]){
			array[index+1] = array[index];
			index--;
		}
		array[index + 1] = curr;
		printArray(&array[0],wall);
	}
}

void selectionSort(int array[]){
	int min, index, wall, c;
	
	for(wall = 0; wall < ARRAY_SIZE-1; wall++){
		min = array[wall];
		index = wall + 1;
		while(index < ARRAY_SIZE){
			if(min > array[index]){
				min = array[index];
				c = index;
			}
			index++;
		}
		if(min != array[wall]){
			array[c] = array[wall];
			array[wall] = min;
		}
		printArray(&array[0],wall + 1);
	}
}