#include <iostream>
using namespace std;

void insertionSort(int* inAr, int lenAr) {
  int j, temp;
  for(int i = 1; i < lenAr; i++) {
    j = i - 1;
    while(j >= 0 && inAr[j+1] < inAr[j]) {
      temp = inAr[j];
      inAr[j] = inAr[j+1];
      inAr[j+1] = temp;
      j--;
    }
  }
}



int main() {
  int sizeAr = 100000;
  int* ar = new int[sizeAr];
  for(int i = 0; i < sizeAr; i++) {
    ar[i] = sizeAr - i;
  }

  insertionSort(ar, sizeAr);

  for(int i = 0; i < sizeAr; i++) {
    cout << ar[i] << endl;
  }
}
