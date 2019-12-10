/*------------------------------------------------------*/
/* Skeleton for the synchronization Lab .   assignment 	*/
/*------------------------------------------------------*/
/* Note:						                        */
/* -----						                        */
/* 1. E = Elephant					                    */
/* 2. D = Dog						                    */
/* 3. C = Cat					                    	*/
/* 4. M = Mouse						                    */
/* 5. P = Parrot					                    */
/*------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define  CHILD		0       /* Return value of child proc from fork call */

int main()
{
    sem_t * ele_mou, * cat_dog, * par_cat, * mou_par,  * cat_mou; 
  
    int pid;		/* Process id after fork call */
    int i;		/* Loop index. */
    int N;		/* Number of requests to process */
    int status;  	/* Exit status of child process. */
    int type;           /* Type of animal */


    /*   Initialization of the semaphores   */
    if ((ele_mou = sem_open("/ele_mou", O_CREAT, 0644, 1)) == SEM_FAILED) {
      perror("Failed to open ele_mou.");
      exit(-1);
    }
  
    if ((cat_dog = sem_open("/cat_dog", O_CREAT, 0644, 1)) == SEM_FAILED) {
      perror("Failed to open dog_cat.");
      exit(-1);
    }
	
    if ((par_cat = sem_open("/par_cat", O_CREAT, 0644, 1)) == SEM_FAILED) {
      perror("Failed to open par_cat.");
      exit(-1);
    }
	
    if ((mou_par = sem_open("/mou_par", O_CREAT, 0644, 1)) == SEM_FAILED) {
      perror("Failed to open mou_par.");
      exit(-1);
    }
  
    if ((cat_mou = sem_open("/cat_mou", O_CREAT, 0644, 1)) == SEM_FAILED) {
      perror("Failed to open cat_mou.");
      exit(-1);
    }
     
    printf("How many requests to be processed: \n");
    scanf("%d",&N);

    for (i=1; i<=N; i++) {
        printf("Who wants in (E=1)(D=2)(C=3)(M=4)(P=5): \n");
        fflush(stdout);
        scanf("%d",&type);
        if ((pid = fork()) == -1) {
   	        /* Fork failed! */
	        perror("fork");
	        exit(1);
        }
        
        if (pid == CHILD) {
          pid = getpid();
          switch (type) {

            case 1: /* Elephant code*/
                        printf("     Elephant process with pid %d wants in.\n",pid);
                        fflush(stdout);
                        sem_wait(ele_mou);
                        printf("     Elephant process with pid %d is in.\n",pid);
                        fflush(stdout);
                        sleep(rand()%10);
                        printf("     Elephant process with pid %d is out.\n",pid);
                        fflush(stdout); 
                        sem_post(ele_mou);
                        break;

            case 2:  /*Dog code*/
                        printf("     Dog process with pid %d wants in.\n",pid);
                        fflush(stdout);
                        sem_wait(cat_dog);
                        printf("     Dog process with pid %d is in.\n",pid);
                        fflush(stdout);
                        sleep(rand()%10);
                        printf("     Dog process with pid %d is out.\n",pid);
                        fflush(stdout);
                        sem_post(cat_dog);
                        break;

            case 3: /*Cat Code*/
                        printf("     Cat process with pid %d wants in.\n",pid);
                        fflush(stdout);
                        sem_wait(cat_dog);
                        sem_wait(par_cat);
                        sem_wait(cat_mou);
                        printf("     Cat process with pid %d is in.\n",pid);
                        fflush(stdout);
                        sleep(rand()%10);
                        printf("     Cat process with pid %d is out.\n",pid);
                        fflush(stdout);
                        sem_post(cat_dog);
                        sem_post(par_cat);
                        sem_post(cat_mou);
                        break;

            case 4: /*Mouse code*/
                        printf("     Mouse process with pid %d wants in.\n",pid);
                        fflush(stdout);
                        sem_wait(mou_par);
                        sem_wait(ele_mou);
                        sem_wait(cat_mou);
                        printf("     Mouse process with pid %d is in.\n",pid);
                        fflush(stdout);
                        sleep(rand()%10);
                        printf("     Mouse process with pid %d is out.\n",pid);
                        fflush(stdout); 
                        sem_post(mou_par);
                        sem_post(ele_mou);
                        sem_post(cat_mou);
                        break;

            case 5: /*Parrot  Code*/
                        printf("     Parrot process with pid %d wants in.\n",pid);
                        fflush(stdout);
                        sem_wait(mou_par);
                        sem_wait(par_cat);
                        printf("     Parrot process with pid %d is in.\n",pid);
                        fflush(stdout);
                        sleep(rand()%10);
                        printf("     Parrot process with pid %d is out.\n",pid);
                        fflush(stdout);
                        sem_post(mou_par);
                        sem_post(par_cat);
                        break;
          }
          exit(0);
       }
    }
    
    /* Now wait for the child processes to finish */
    for (i=1; i<=N; i++) {
        pid = wait(&status);
        printf("Child (pid = %d) exited with status %d.\n", pid, status);
        fflush(stdout);
    }
}
