#include <iostream>

bool majorityElement(const int arr[], int& majority, int sz){
	//accepts an array of int, a reference of an int, the size of array
	//returns true if there is a majority element and pass the value to int& majority
	int count = 1;
	int* dupArr = new int[sz];

	//copy the array
	for (int i = 0; i < sz; i++){
		dupArr[i] = arr[i];
	}

	//count the numbers of each element
	for (int i = 0; i < sz - 1; i++){
		for (int j = i + 1; j < sz; j++){
			if (dupArr[i] == dupArr[j]){
				count++;
			}
		}

		//if count is bigger than sz/2, pass the value, free the memory, return true
		if (count >(sz / 2)){
			majority = dupArr[i];
			delete dupArr;
			return true;
		}

		count = 1;
	}

	//otherwise, free the memory, return false
	delete dupArr;
	return false;
}

bool candidate(int array[], int& one_candidate, int sz){
	//accepts an array of int, a reference of an int, the size of array
	//returns true if there is a majority element and pass the value to int& majority
	bool isEven = sz % 2 == 0 ? true : false;
	int count = 0, leftover;
	int* newArray;

	//if sz is odd number, keep the last element
	if (!isEven){
		leftover = array[sz - 1];
	}

	//compare a pair of elements and count if they are same
	for (int i = 0; i < sz - 1; i += 2){
		if (array[i] == array[i + 1])
			count++;
	}

	//if count is bigger than 0, create a new array, call the candidate function
	if (count > 0){
		newArray = new int[count];

		for (int i = 0; i < sz - 1; i += 2){
			if (array[i] == array[i + 1]){
				newArray[i / 2] = array[i];
			}
		}

		if (candidate(newArray, one_candidate, count)){
			delete newArray;
			return true;
		}
		else{
			//if candidate returns false, check if the array has odd number of elements
			//if it has, pass the value to the reference, return true
			if (!isEven){
				one_candidate = leftover;
				delete newArray;
				return true;
			}
			//otherwise, return false
			else{
				delete newArray;
				return false;
			}
		}
	}
	else{
		//if count is 0, check if the array has odd number of elements
		//if it has, pass the value to the reference, return true
		if (!isEven){
			one_candidate = leftover;
			return true;
		}
		//otherwise, return false
		else{
			return false;
		}
	}
}