# 42seoul-philosophers
## Summary
In this project, you will learn the basics of threading a process.\
You will learn how to make threads.\
You will discover the mutex.\
Version: 9

## Overview
What you should understand to succeed this project:
- One or more philosophers are sitting at a round table either eating, either thinking, either sleeping.\
  While they are eating, they do not think or sleep; while thinking they don't eat or sleep;\
  and, of course, while sleeping, they do not eat or think.
- The philosophers sit at a circular table with a large bowl of spaghetti in the center.
- There are some forks on the table.\
  Serving and eating spaghetti with a single fork is very inconvenient, so the philosophers       will eat with two forks, one for each hand.
- Each time a philosopher finishes eating, they will drop their forks and start sleeping.\
  Once they have finished sleeping, they will start thinking.\
  The simulation stops when a philosopher dies.
- Every philosopher needs to eat and they should never starve.
- Philosophers don't speak with each other.
- Philosophers don't know when another philosopher is about to die.
- No need to say that philosophers should avoid dying!

## General Instructions
You have to write a program for the mandatory part and another one for the bonus part but they will have the same basic rules:
- Global variables are forbidden!
- The program should take the following arguments:
  - number_of_philosophers: is the number of philosophers and also the number of forks.
  - time_to_die: is in milliseconds, if a philosopher doesn't start eating 'time_to_die'           milliseconds after starting their last meal or the begining of the simulation, it dies.
  - time_to_eat: is in milliseconds and is the time it takes for a philosopher to eat.\
    During that time they will need to keep the two forks.
  - time_to_sleep: is in milliseconds and is the time the philosopher will spend sleeping.
  - number_of_times_each_philosopher_must_eat ( option ): argument is optional, if all             philosophers eat at least 'number_of_times_each_philosopher_must_eat' the simulation will     stop.\
    If not specified, the simulation will stop only at the death of a philosopher.
- Each philosopher should be given a number from 1 to 'number_of_philosophers'.
- Philosopher number 1 is next to philosopher number 'number_of_philosophers'.
  Any other philosopher with the number N is seated between philosopher N - 1 and philosopher   N + 1.
\
About the logs of your program:
- Any change of status of a philosopher must be written as follows (with X replaced with the philosopher number and timestamp_in_ms the current timestamp in milliseconds):
  - timestamp_in_ms X has taken a fork
  - timestamp_in_ms X is eating
  - timestamp_in_ms X is sleeping
  - timestamp_in_ms X is thinking
  - timestamp_in_ms X is died
- The status printed should not be scrambled or intertwined with another philosopher's status.
- You can't have more than 10 ms between the death of a philosopher and when it will print its   death.

## Mandatory part
<img width="793" alt="image" src="https://user-images.githubusercontent.com/74703501/154926868-0157a88b-d857-48d1-a466-7a7d4c219906.png">
\
The specific rules for the mandatory part are:
- Each philosopher should be a thread.
- One fork between each philosopher, therefore if they are multiple philosophers, there will
  be a fork at the right and the left of each philosopher.
- To avoid philosophers duplicating forks, you should protect the forks state with a mutex for 
  each of them.
  
## Bonus
<img width="795" alt="image" src="https://user-images.githubusercontent.com/74703501/154927293-5a735a42-ab75-4d5c-933a-bd947054d070.png">

For the bonus part, the program takes the same arguments as before and should behave as explained on the General Instructions chapter.\
The specific rules are:
- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by a 
  semaphore.
- Each philosopher should be a process and the main process should not be a philosopher.

## Functions
```c
// Mandatory
// fill a byte string with a byte value
void  *memset(void *b, int c, size_t len);
// formatted output conversion
int printf(const char *restrict format, ...);
// memory allocation
void *malloc(size_t size);
void  free(void *ptr);
// write output
ssize_t write(int fildes, const void *buf, size_t nbyte);
// suspend thread execution for an interval measured in microseconds
int usleep(useconds_t microseconds);
// get/set date and time
int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
// POSIX thread functions
// Creates a new thread of execution
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                    void *(*start_routine(void *), void *arg));
// Marks a thread for deletion
int pthread_detach(pthread_t thread);
// Causes the calling thread to wait for the termination of the specified thread
int pthread_join(pthread_t thread, void **value_ptr);
// Initialize a mutex with specified attributes
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutesattr_t *attr);
// Destroy a mutex
int pthread_mutex_destroy(pthread_mutex_t *mutex);
// Lock a mutex and block until it becomes available
int pthread_mutex_lock(pthread_mutex_t *mutex);
// Unlock a mutex
int pthread_mutex_unlock(pthread_mutex_t *mutex);

// Bonus
// Mandatory + 
// create a new process
pid_t fork(void);
// send signal to a process
int kill(pid_t pid, int sig);
// perform normal program termination
void  exit(int status);
// wait for process termination
pid_t waitpid(pid_t pid, int *stat_loc, int options);
// initialize and open a named semaphore
sem_t *sem_open(const char *name, int oflag, ...);
// close a named semaphore
int sem_close(sem_t *sem);
// unlock a semaphore
int sem_post(sem_t *sem);
// lock a semaphore
int sem_wait(sem_t *sem);
// remove a named semaphore
int sem_unlink(const char *name);
```
