#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIM1 6
#define DIM2 8
#define NAME_LEN 20

#define qsort NOT_ALLOWED


typedef struct Name {
   char first[NAME_LEN+1];
   char last[NAME_LEN+1];
} Name;


// Support functions NameLess, NameGreater, DblLess, and StrLess
int DblLess(const void *a, const void *b) {
   return *(double *)a < *(double *)b;
}

int StrLess(const void *a, const void *b) {
   return strcmp(*(char **)a, *(char **)b) < 0 ? 1 : 0;
}

int NameLess(const void *a, const void *b) {
   Name *nameA = (Name *)a, *nameB = (Name *)b;
   int lastNameComp = strcmp(nameA->last, nameB->last), rtn;

   if (!lastNameComp) 
      rtn = strcmp(nameA->first, nameB->first) < 0 ? 1 : 0;
   else 
      rtn = lastNameComp < 0 ? 1 : 0;

   return rtn;
}

int NameGreater(const void *a, const void *b) {
   Name *nameA = (Name *)a, *nameB = (Name *)b;
   int lastNameComp = strcmp(nameA->last, nameB->last), rtn;

   if (!lastNameComp) 
      rtn = strcmp(nameA->first, nameB->first) > 0 ? 1 : 0;
   else 
      rtn = lastNameComp > 0 ? 1 : 0;

   return rtn;
}

// Function GenInsertSort
void GenInsertSort(void *base, size_t num, size_t size,
 int (*compar)(const void*, const void*)) {
   int i, j;
   char *vals = base, toInsert[size];

   for (i = 1; i < num; i++) {
      memmove(toInsert, vals + i*size, size);
      for (j = i - 1; j >= 0 && compar(toInsert, vals + j*size); j--)
         memmove(vals + (j + 1)*size, vals + j*size, size);

      memmove(vals + (j + 1)*size, toInsert, size);
   }
}

void main() {
   Name names[DIM1] = {{"John", "Smith"}, {"Jane", "Smith"}, {"Bill", "Jones"},
      {"Sue", "Johnson"}, {"Susan", "Johnson"}, {"Jim", "Taylor"}
   };
   double vals[DIM2] = {1.1, -2.2, 3.3, -4.2, 5.5, -6.6, 7.7, -8.8};
   char *words[DIM2]
    = {"alpha", "beta", "gamma", "delta", "epsilon", "pi", "phi", "omega"};
   int i;
   
   GenInsertSort(names, DIM1, sizeof(Name), NameLess);
   for (i = 0; i < DIM1; i++)
      printf("%s %s\n", names[i].first, names[i].last);
     
   GenInsertSort(names, DIM1, sizeof(Name), NameGreater);   
   for (i = 0; i < DIM1; i++)
      printf("%s %s\n", names[i].first, names[i].last);

   GenInsertSort(vals, DIM2, sizeof(double), DblLess);
   for (i = 0; i < DIM2; i++)
      printf("%f ", vals[i]);
   printf("\n");
   
   GenInsertSort(words, DIM2, sizeof(char *), StrLess);
   for (i = 0; i < DIM2; i++)
      printf("%s ", words[i]);
   printf("\n");
}
