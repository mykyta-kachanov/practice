#include <stdlib.h>
#include <time.h>
#include <string.h>

void generatelicense(int arr[]) {
	int targetSum = 15;
	int size = 5;
	int sum = 0;
	// Initialize the random number generator
	srand(time(NULL));

	// Generate first 4 random numbers and calculate their sum
	for (int i = 0; i < size - 1; i++) {
		arr[i] = rand() % (targetSum + 1);
		sum += arr[i];
	}

	// Set the last element to make the sum equal to targetSum
	arr[size - 1] = targetSum - sum;

	// Adjust elements if the last element is out of bounds (not a digit)
	while (arr[size - 1] < 0 || arr[size - 1] > 9) {
		int index = rand() % (size - 1);
		sum -= arr[index];
		arr[index] = rand() % (targetSum + 1);
		sum += arr[index];
		arr[size - 1] = targetSum - sum;
	}
}

int count_set_bits(int n) {
	int count = 0;
	while (n) {
		count += n & 1;
		n >>= 1;
	}
	return count;
}

/**
* @return 1 - valid license
* @return 0 - invalid license
*/
int checklicense(int key[]) {
	int length = 5;
	int expected_bit_sum = 11; 
	int bit_sum = 0;

	for (int i = 0; i < length; i++) {
		bit_sum += count_set_bits(key[i]);
	}

	if (bit_sum == expected_bit_sum) {
		return 1;
	}
	else {
		return 0;
	}
}
