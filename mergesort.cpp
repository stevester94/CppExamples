//Works except for uneven splitting

#include <iostream>

#include <assert.h>

using namespace std;

int* mergeSort(int* inAr, int length) {
    if(length > 2) {
    	// Split and recurse
    	int length1 = (length/2);
    	int length2 = length - length1;

    	int* ar1 = mergeSort(inAr, length1);
    	int* ar2 = mergeSort(&(inAr[length1]), length2);

    	// Merge together
    	int* merged = new int[length];
    	int* currentMerged = merged;
    	int currentAr1 = 0;
    	int currentAr2 = 0;

    	for(int i = 0; i < length; i++) {
    		if(ar1[currentAr1] > ar2[currentAr2] && currentAr2 < length2) {
    			currentMerged[i] = ar2[currentAr2];
    			currentAr2++;
    		} else {
    			currentMerged[i] = ar1[currentAr1];
    			currentAr1++;
    		}
    	}

    	return merged;
    } else {
    	int* retAr = new int[2];
    	retAr[0] = inAr[0] > inAr[1] ? inAr[1] : inAr[0];
    	retAr[1] = inAr[0] < inAr[1] ? inAr[1] : inAr[0];

    	return retAr;
    }
}


int main() {
    int sizeArray = 16;
    int* ar = new int[sizeArray];
    int* sorted;
    

    for(int i = 0; i < sizeArray; i++) {
        ar[i] = sizeArray - i;
    }
    
    sorted = mergeSort(ar, sizeArray);
    
    for(int i = 0; i < sizeArray; i++) {
        cout << sorted[i] << endl;
    }
}























