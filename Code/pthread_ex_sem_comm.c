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

int shared_var = 0;

void *body1(void *arg)
{
  int i;
  for (i=0; i<1000000; i++);
  shared_var = 11;
  sem_post(&semaforo);
  return NULL;
}

void *body2(void* arg)
{
  sem_wait(&semaforo);
  printf("shared_var is %d\n", shared_var);
  return NULL;
}

int main()
{
  pthread_t t1,t2;
  pthread_attr_t myattr;
  int err;
  
  // Init
  sem_init(&semaforo, 0, 1);

  //printf("I am inside \"main\", before creating the PThreads\n");
  
  pthread_attr_init(&myattr);
  err = pthread_create(&t1, &myattr, body1, (void *)".");
  err = pthread_create(&t2, &myattr, body2, (void *)"#");
  pthread_attr_destroy(&myattr);
  
  //printf("I am inside \"main\", after creating but before joining the PThreads\n");

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  
  sem_destroy(&semaforo);
  
  //printf("I am inside \"main\", after joining the PThreads\n");

  printf("\n");

  return 0;
}
