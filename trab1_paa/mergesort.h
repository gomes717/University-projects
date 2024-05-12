#ifndef __MERGESORT__
#define __MERGESORT__

#define X_AXIS 0
#define Y_AXIS 1

void merge(Points* vec, int start,  int mid,  int end, int axis);

void mergesort(Points* vec, int start, int end, int axis);

#endif 