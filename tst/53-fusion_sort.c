#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "thread.h"

// tri fusion

typedef struct interval{
  int a;
  int b;
} interval;


void fusion(int d, int m, int f){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}

void fusion(int dest[], sub_list A, sub_list B) {
    int i = 0, j = 0, k = 0;

    while (i < A.n && j < B.n) {
        if (A.l[i] <= B.l[j]) {
            dest[k] = A.l[i];
            i++;
        } else {
            dest[k] = B.l[j];
            j++;
        }
        k++;
    }

    while (i < A.n) {
        dest[k] = A.l[i];
        i++;
        k++;
    }

    while (j < B.n) {
        dest[k] = B.l[j];
        j++;
        k++;
    }
}

//Liste buffer pour les calculs (de fusion)
int *buffer = NULL;

static void * fusion_sort(void *_value)
{
  thread_t th1, th2;
  int err;
  interval I = *((interval*) _value);
  int a = I.a, b = I.b;
  int n = b-a+1;

  /* on passe un peu la main aux autres pour eviter de faire uniquement la partie gauche de l'arbre */
  thread_yield();

  if (value < 3)
    return (void*) 1;

  err = thread_create(&th, fibo, (void*)(value-1));
  assert(!err);
  err = thread_create(&th2, fibo, (void*)(value-2));
  assert(!err);

  err = thread_join(th, &res);
  assert(!err);
  err = thread_join(th2, &res2);
  assert(!err);

  return (void*)((unsigned long) res + (unsigned long) res2);



  if (n <= 1) {
    return NULL;
  }

  int mid = n / 2;
  int* left = L.l;
  int* right = L.l + mid;

  int left[mid];
  int right[size - mid];

    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }



    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(arr, left, mid, right, size - mid);
}

unsigned long is_list_sorted(int *l, size_t n)
{
  if(n <= 1) return 1;

  for(size_t i=0; i < n-1; i++){
    if(l[i] > l[i+1]) return 0;
  }

  return 1;
}

int main(int argc, char *argv[])
{
  unsigned long n;
  struct timeval tv1, tv2;
  double s;
  int *list = NULL;

  if (argc < 2) {
    printf("argument manquant: entier n pour la longueur de liste à trier\n");
    return -1;
  }

  n = atoi(argv[1]);
  list = malloc(n*sizeof(int));
  buffer = malloc(n*sizeof(int));
  if (!list || !buffer) { perror("malloc"); return -1; }

  srand(0); //Seed de la génération pseudo-aléatoire, peut être modifiée.
  printf("Liste Initiale : [ ");
  for(size_t i=0; i < n; i++){
    list[i] = (rand() % (2*n+1)) - n; //Les entiers générés sont compris entre [-n,n]
    printf("%d ", list[i]);
  }
  printf("]\n");

  interval I = {0, n-1};

  gettimeofday(&tv1, NULL);
  fusion_sort(&I);
  gettimeofday(&tv2, NULL);
  s = (tv2.tv_sec-tv1.tv_sec) + (tv2.tv_usec-tv1.tv_usec) * 1e-6;

  printf("Liste Finale : [ ");
  for(size_t i=0; i < n; i++) printf("%d ", list[i]);
  printf("]\n");
  
  if ( !is_list_sorted(list, n) ) {
    printf("Fusion sort (FAILED)\nLa liste finale n'est pas triée !!!\n");
    free(list);
    return EXIT_FAILURE;
  } else {
    printf("Fusion sort (SUCCESS)\nLa liste finale a été triée en %e s\n", s);
    free(list);
    return EXIT_SUCCESS;
  }
}
