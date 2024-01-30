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

void first_thread(void* arg1, void* arg2) 
{
  int num = *(int*)arg1;
  if (num) lock_acquire(lock);
  {
    counter++;
    printf(1, "First one is: %d \n", counter );
  }  
  sleep(SLEEP_TIME);
  if (num) lock_release(lock);
  exit();
}

void second_thread(void* arg1, void* arg2) 
{
  int num = *(int*)arg1;
  if (num) lock_acquire(lock);
  {
    counter++;
    printf(1, "Second one is: %d \n", counter );
  }
  sleep(SLEEP_TIME);
  if (num) lock_release(lock);
  exit();
}

void third_thread(void* arg1, void* arg2) 
{
  int num = *(int*)arg1;
  if (num) lock_acquire(lock);
  {
    counter++;
    printf(1, "Third one is: %d \n", counter );
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

  thread_create(&first_thread, (void *)&arg1, (void *)&arg2);
  thread_create(&second_thread, (void *)&arg1, (void *)&arg2);
  thread_create(&third_thread, (void *)&arg1, (void *)&arg2);
  thread_join();
  thread_join();
  thread_join();
  
  exit();
}