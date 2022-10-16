#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#define MAX 4096

int main(void)
{
	char c;
	const char *nombre = "/ObjCompartido";
	int shm_fd;
	void *puntero;

   sem_t *semaforo;
   
   if ((semaforo = sem_open("/semaforo", O_CREAT, 0700, 0)) == SEM_FAILED){
	perror("Error al crear semaforo");
	return -1;
	}

   shm_fd = shm_open (nombre, O_CREAT | O_RDWR, 0666);

   ftruncate(shm_fd, MAX);

   puntero = mmap(0, MAX, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
   
   if (puntero == MAP_FAILED){
	perror("Error al mapear objeto compartido");
	return -1;
   }

	while (1){
   		c = getchar();
		sprintf(puntero++, "%c", c);
		sem_post(semaforo);
	if (c == EOF){
		break;
		}
}

	return 0;
}
