#include <stdio.h>
#include <pthread.h>

#define N_THREADS 5

static int exited;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void thr_exit() {
  pthread_mutex_lock(&mutex);

  /* YOUR CODE HERE */
  exited++;
  pthread_cond_signal(&cond);

  pthread_mutex_unlock(&mutex);
}

void thr_join() {
  pthread_mutex_lock(&mutex);

  while (exited < N_THREADS) 
    pthread_cond_wait(&cond, &mutex);/* YOUR CODE HERE */

  pthread_mutex_unlock(&mutex);
}

void *child_func(void *arg) {
  int thr_id = *(int*)arg + 1; /* YOUR CODE HERE */
  printf("child %d created and exited\n", thr_id);
  thr_exit();
  return NULL;
}

int main() {
  pthread_t p[N_THREADS];
  int thr_idx[N_THREADS];
  void *arg;
  int i;

  exited = 0; /* YOUR CODE HERE */

  puts("parent: begin");

  for (i = 0; i < N_THREADS; i++) {
    thr_idx[i] = i;
    arg = &thr_idx[i];

    pthread_create(&p[i], NULL, child_func, arg); /* YOUR CODE HERE */
  }

  thr_join();

  puts("parent: end");

  return 0;
}
