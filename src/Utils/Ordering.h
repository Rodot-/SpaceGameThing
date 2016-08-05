//library of functions and macros built around ordering lists, arrays, vectors, etc

#ifndef ORDERING_H
#define ORDERING_H


#define MAX(X,Y) (X < Y) ? Y : X //get max of X and Y
#define MIN(X,Y) (X > Y) ? Y : X //get min of X and Y

#define SORT2(X, Y) { (X < Y) ? X, Y : Y, X } //sort two items

#define ARGMAX(X, Y, AX, AY) (AX < AY) ? Y : X //get Y if AX < AY otherwise get X
#define ARGMIN(X, Y, AX, AY) (AX > AY) ? Y : X //get X if AX < AY otherwise get Y

#define ARGSORT2(X, Y, AX, AY) { (AX < AY) ? X, Y : Y, X } //argsort two items

#endif
