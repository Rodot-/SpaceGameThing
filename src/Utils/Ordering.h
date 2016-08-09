//library of functions and macros built around ordering lists, arrays, vectors, etc

#ifndef ORDERING_H
#define ORDERING_H

#include <stdio.h>
#include <stdlib.h> //for rand
#include <time.h> //for seed

//srand (time(NULL)); //random seed

#define MAX(X,Y) (X < Y) ? Y : X //get max of X and Y
#define MIN(X,Y) (X > Y) ? Y : X //get min of X and Y

#define SORT2(X, Y) { (X < Y) ? X, Y : Y, X } //sort two items

#define ARGMAX(X, Y, AX, AY) (AX < AY) ? Y : X //get Y if AX < AY otherwise get X
#define ARGMIN(X, Y, AX, AY) (AX > AY) ? Y : X //get X if AX < AY otherwise get Y

#define ARGSORT2(X, Y, AX, AY) { (AX < AY) ? X, Y : Y, X } //argsort two items

#define SWAP(X, Y) X ^= Y; Y ^= X; X ^= Y

template <typename T>
void SORT(T* begin, T* end) {

	if (begin < end) {
		T* test = begin;
		T* low = begin;
		T temp;
		for (test; test != (end-1); ++test) {
			if (*test < *(end-1)) {
					temp = *test;
					*test = *low;
					*low = temp;
					low++;
			}
		}
		temp = *(end-1);
		*(end-1) = *low;
		*low = temp;
		SORT(begin, low);
		SORT(low+1, end);
	}
};



#endif
