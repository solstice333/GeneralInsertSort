#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 5

int DblLess(const void *a, const void *b) {
   return *(double *)a < *(double *)b;
}

int StrLess(const void *a, const void *b) {
   return strcmp(*(char **)a, *(char **)b) < 0 ? 1 : 0;
}

void GenInsertSort(void *base, size_t num, size_t size, 
 int (*compar)(const void*, const void*)) {
   int i, j;
   char *vals = base;
   char *toInsert = (char *)malloc(size); 

   for (i = 1; i < num; i++) {
      memmove(toInsert, vals + i*size, size);
      for (j = i - 1; j >= 0 && compar(toInsert, vals + j*size); j--) 
         memmove(vals + (j + 1)*size, vals + j*size, size); 
      memmove(vals + (j + 1)*size, toInsert, size);
   }
   free(toInsert);
}

void printDbl(double *base, size_t num) {
   int i;
   for (i = 0; i < num; i++) 
      printf("index[%d]: %.2lf\n", i, base[i]);
}

void printStr(char *base[], size_t num) {
   int i;
   for (i = 0; i < num; i++) 
      printf("index[%d]: %s\n", i, base[i]);
}

int main() {
   double vals[] = {3.3, 4.5, 1.2, 8.9, -1.7};
   char *str[] = {"Ariana", "Anna", "Andrea", "Abigail", "Meghan"};
   printf("Before insertion sort: \n");
   printDbl(vals, DIM);
   printf("\n");
   printStr(str, DIM);
   printf("\n");

   GenInsertSort(vals, DIM, sizeof(double), DblLess);
   GenInsertSort(str, DIM, sizeof(char *), StrLess);
   printf("After insertion sort: \n");
   printDbl(vals, DIM);
   printf("\n");
   printStr(str, DIM);
   printf("\n");

   return 0;
}
