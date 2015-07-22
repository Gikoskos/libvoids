#include "alghead.h"

int main (int argc, char* argv[])
{

	int arrInt[ARRAY_SIZE], choice;

	fillArray(&arrInt[0]);
	printf("Randomly generated array:\n");
	printArray(&arrInt[0], NO_WALL);
	printf("Choose your sorting method: ");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		insertionSort(arrInt);
		break;
	case 2:
		selectionSort(arrInt);
		break;
	default:
		return 1;
	}
	return 0;
}
