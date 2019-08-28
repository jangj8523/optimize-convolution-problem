
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "thread_pool.h"
#include <pthread.h>


// Unused
// const signed char filter [3] = {-1, 0, 1};

//tpool_work => thread_worker
//tpool => thread_pool

struct thread_worker {
    thread_func_t      func;
    void              *args;
    struct thread_worker *next;
};

struct thread_pool {
    thread_worker_t    *work_first;
    thread_worker_t    *work_last;
    pthread_mutex_t  pool_mutex; // used for all locking
    pthread_cond_t   end_cond;  // signals the thread that work needs to be done
    pthread_cond_t   working_cond; //signals when there are no threads processing
    size_t           working_cnt; // how many threads are actively processing
    size_t           thread_cnt; // Track how many threads are alive
    bool             stop;
};

static thread_worker_t *get_thread_worker (thread_pool_t *t_pool)
{
  thread_worker_t *next_worker;
  next_worker = t_pool->work_first;
  if (next_worker == NULL)
  {
    printf ("this was null\n");
    return NULL;
  }

  if (next_worker->next == NULL)
  {
    t_pool->work_first = NULL;
    t_pool->work_last = NULL;
  } else {
    t_pool->work_first = next_worker->next;
  }
  return next_worker;
}

static void free_thread_worker(thread_worker_t *worker)
{
  if (worker != NULL) {
    free(worker);
  }
}



static void *thread_function(void *tm)
{
  thread_pool_t* tp = (thread_pool_t*) tm;
  thread_worker_t *next_worker;
  while (true)
  {
    pthread_mutex_lock(&(tp->pool_mutex));
    if (tp->stop)
      break;

    if (tp->work_first == NULL)
      pthread_cond_wait(&(tp->working_cond), &(tp->pool_mutex));
    tp->working_cnt += 1;
    pthread_mutex_unlock(&(tp->pool_mutex));

    next_worker = get_thread_worker(tp);
    if (next_worker != NULL)
    {
      (*next_worker->func)(next_worker->args);
      free_thread_worker(next_worker);
    }

    pthread_mutex_lock(&(tp->pool_mutex));
    tp->working_cnt -= 1;
    if (tp->working_cnt == 0 && tp->work_first == NULL)
      pthread_cond_signal(&(tp->end_cond));
    pthread_mutex_unlock(&(tp->pool_mutex));

  }
  tp->thread_cnt-=1;
  if (tp->thread_cnt == 0)
    pthread_cond_broadcast(&(tp->end_cond));
  pthread_mutex_unlock(&(tp->pool_mutex));

}


// Waits for all task in the thread_pool to finish
void threadpool_wait(thread_pool_t *t_pool)
{
  pthread_mutex_lock(&(t_pool->pool_mutex));
  while(true) {
    if ((!t_pool->stop && t_pool->working_cnt == 0 && t_pool->work_first == NULL) || (t_pool->stop && t_pool->thread_cnt == 0) )
      break;
    pthread_cond_wait(&(t_pool->end_cond), &(t_pool->pool_mutex));
  }
  pthread_mutex_unlock(&(t_pool->pool_mutex));

}


// Add new work to the threadpool
bool threadpool_add_work(thread_pool_t *t_pool, void (*new_func), void *args)
{
  thread_worker_t *new_worker = malloc(sizeof(thread_worker_t));
  new_worker->func = new_func;
  new_worker->args = args;
  new_worker->next = NULL;

  pthread_mutex_lock(&(t_pool->pool_mutex));

  thread_worker_t *first_worker = t_pool->work_first;
  thread_worker_t *last_worker = t_pool->work_last;
  if (first_worker == NULL)
  {
    t_pool->work_first = new_worker;
    t_pool->work_last = new_worker;
    printf ("creating\n");
  }
  else
  {
    last_worker->next = new_worker;
    last_worker = new_worker;
  }
  pthread_cond_signal(&(t_pool->working_cond));
  pthread_mutex_unlock(&(t_pool->pool_mutex));
  return true;
}


// Destroy threadpool
void threadpool_destroy(thread_pool_t* t_pool)
{
  pthread_mutex_lock(&(t_pool->pool_mutex));
  t_pool->stop = true;
  thread_worker_t *worker = t_pool->work_first;
  while (worker != NULL) {
    thread_worker_t *tmp_worker = worker->next;
    free(worker);
    worker = tmp_worker;
  }
  pthread_cond_broadcast(&(t_pool->working_cond));
  pthread_mutex_unlock(&(t_pool->pool_mutex));
  threadpool_wait(t_pool);

  pthread_mutex_destroy(&(t_pool->pool_mutex));
  pthread_cond_destroy(&(t_pool->working_cond));
  pthread_cond_destroy(&(t_pool->end_cond));
  free(t_pool);
}

// initialize threadpool
thread_pool_t *create_thread_pool(size_t num)
{
  thread_pool_t *t_pool;
  pthread_t single_thread;
  t_pool = malloc(sizeof(thread_pool_t));
  pthread_mutex_init(&t_pool->pool_mutex, NULL);
  pthread_cond_init(&t_pool->working_cond, NULL);
  pthread_cond_init(&t_pool->end_cond, NULL);
  t_pool->working_cnt = 0;
  t_pool->thread_cnt = num;
  t_pool->work_first = NULL;
  t_pool->work_last = NULL;
  t_pool->stop = false;

  thread_worker_t *prev= NULL;
  for (size_t i = 0; i < num; i++)
  {
    pthread_create(&single_thread, NULL, thread_function, t_pool);
    pthread_detach(single_thread);
  }
  return t_pool;
}
