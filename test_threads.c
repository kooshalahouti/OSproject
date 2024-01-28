#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#include "x86.h"

#define SLEEP_TIME 100

volatile int counter = 0;

lock_t* lock;

void thread1_func(void* arg1, void* arg2) 
{
  int num = *(int*)arg1;
  if (num) lock_acquire(lock);
  {
    counter++;
    printf(1, "1. First thread : %d \n", counter );
  }  
  sleep(SLEEP_TIME);
  if (num) lock_release(lock);
  exit();
}

void thread2_func(void* arg1, void* arg2) 
{
  int num = *(int*)arg1;
  if (num) lock_acquire(lock);
  {
    counter++;
    printf(1, "2. Second Thread: %d \n", counter );
  }
  sleep(SLEEP_TIME);
  if (num) lock_release(lock);
  exit();
}

void thread3_func(void* arg1, void* arg2) 
{
  int num = *(int*)arg1;
  if (num) lock_acquire(lock);
  {
    counter++;
    printf(1, "3. Third Thread: %d \n", counter );
  }
  sleep(SLEEP_TIME);
  if (num) lock_release(lock);
  exit();
}

int
main(int argc, char *argv[])
{
  lock_init(lock);
  int arg1 = 1, arg2 = 1;

  thread_create(&thread1_func, (void *)&arg1, (void *)&arg2);
  thread_create(&thread2_func, (void *)&arg1, (void *)&arg2);
  thread_create(&thread3_func, (void *)&arg1, (void *)&arg2);
  thread_join();
  thread_join();
  thread_join();
  
  exit();
}