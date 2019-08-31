#ifndef __TPOOL_H__
#define __TPOOL_H__

#include <stdbool.h>
#include <stddef.h>


struct thread_pool;
typedef struct thread_pool thread_pool_t;

typedef void (*thread_func_t)(void *arg);

thread_pool_t *create_thread_pool(size_t num);
void threadpool_destroy(thread_pool_t *tm);

// bool threadpool_add_work(thread_pool_t *tm, void (*func), void *arg);
bool threadpool_add_work(thread_pool_t *tm, thread_func_t func, void *arg);

void threadpool_wait(thread_pool_t *tm);

typedef struct thread_worker thread_worker_t;


#endif


// struct thread_pool {
//     thread_worker_t    *work_first;
//     thread_worker_t    *work_last;
//     pthread_mutex_t  pool_mutex; // used for all locking
//     pthread_cond_t   end_cond;  // signals the thread that work needs to be done
//     pthread_cond_t   working_cond; //signals when there is an available thread
//     size_t           working_cnt; // how many threads are actively processing
//     size_t           thread_cnt; // Track how many threads are alive
//     bool             stop;
// };
// struct thread_worker {
//     thread_func_t      func;
//     void              *args;
//     struct thread_worker *next;
// };
