/*
 * Semaphore demo 
 *
 * Copyright (C) 2002 by Paolo Gai
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaforo;
pthread_mutex_t mutex;

void *body(void *arg)
{
  int i, j;
  char * mychar = (char*) arg;
  //printf("Hello World, I am inside \"body\", and mychar is %s\n", mychar);
  
  // Here, you can use either mutex or sem, because it's for sure the same thread
  
  //pthread_mutex_lock(&mutex);
  //sem_wait(&semaforo);
  for (j=0; j<10; j++)
  {
    //sem_wait(&semaforo);
	pthread_mutex_lock(&mutex);
	
    for (i=0; i<1000000; i++); // Wait some time
    for (i=0; i<4; i++)
	{
		fprintf(stderr, mychar);
	}
	
	pthread_mutex_unlock(&mutex);
	//sem_post(&semaforo);
  }
  //pthread_mutex_unlock(&mutex);
  //sem_post(&semaforo);
  
  return NULL;
}

int main()
{
  pthread_t t1,t2,t3;
  pthread_attr_t myattr;
  int err;
  
  // Init sem and/or mutex
  sem_init(&semaforo, 0, 1);

  pthread_mutexattr_t mymutexattr;
  pthread_mutexattr_init(&mymutexattr);
  pthread_mutex_init(&mutex, &mymutexattr);
  pthread_mutexattr_destroy(&mymutexattr);
  
  //printf("I am inside \"main\", before creating the PThreads\n");
  
  pthread_attr_init(&myattr);
  err = pthread_create(&t1, &myattr, body, (void *)".");
  err = pthread_create(&t2, &myattr, body, (void *)"#");
  err = pthread_create(&t3, &myattr, body, (void *)"o");
  pthread_attr_destroy(&myattr);
  
  //printf("I am inside \"main\", after creating but before joining the PThreads\n");

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  
  sem_destroy(&semaforo);
  
  //printf("I am inside \"main\", after joining the PThreads\n");

  printf("\n");

  return 0;
}
