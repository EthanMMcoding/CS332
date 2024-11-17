#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/* compile with -lpthread */

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

typedef struct data{
  double *double_arr; /* a */
  double sum;
  long tid;
  int num_elements;   /* N  */
  int size;
}Data;

void *compute(void *args) {
  Data *info = (Data *)args;

  int myStart, myEnd, myN, i;

  myN = info->num_elements/info->size;
  myStart = info->tid * myN;
  myEnd = myStart + myN;

  if(info->tid == (info->size-1)) myEnd = info->num_elements;

  for(i = myStart; i < myEnd; i++)
    info->sum += info->double_arr[i];

  for(int x = myStart; x < myEnd; x++){
    printf("double_arr[%d]: %f\n", x, info->double_arr[x]);
  }

  printf("myN: %d, myStart: %d, myEnd: %d\n", myN, myStart, myEnd);
  printf("mySum = %f\n", info->sum);

  return NULL;
}

int main(int argc, char **argv){
  long i;
  pthread_t *tid;
  Data *thread_data;
  int num_threads;
  int N;
  double *a;
  double sum = 0.0;

  if (argc != 3){
    printf("Usage: %s <# of elements> <# of threads>\n", argv[0]);
    exit(-1);
  }

  N = atoi(argv[1]);
  num_threads = atoi(argv[2]);
  thread_data = (Data *)malloc(sizeof(Data)*num_threads);
  tid = (pthread_t*)malloc(sizeof(pthread_t)*num_threads);
  a = (double *)malloc(sizeof(double)*N);

  for (i=0; i<N; i++)
    a[i] = (double)(i + 1);

  for(i = 0; i < num_threads; i++){
    thread_data[i].tid = i;
    thread_data[i].num_elements = N;
    thread_data[i].size = num_threads;
    thread_data[i].double_arr = a;
    thread_data[i].sum = 0.0;
    pthread_create(&tid[i], NULL, compute, (void *) &thread_data[i]);
  }

  for ( i = 0; i < num_threads; i++)
    pthread_join(tid[i], NULL);

  for(i = 0; i < num_threads; i++){
    sum += thread_data[i].sum;
  }

  printf("The total is %g, it should be equal to %g\n", 
           sum, ((double)N*(N+1))/2);

  return 0;
}