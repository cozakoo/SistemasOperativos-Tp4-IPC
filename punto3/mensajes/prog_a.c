#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>
#define MAX 5


int main (){

	mqd_t cola_mensajes;
	
	struct mq_attr atributos;
	
//definimos los atributos de la cola de mensajes
/*
	atributos.mq_flags = 0;
	atributos.mq_maxmsg = 15;
	atributos.mq_msgsize = MAX;
	atributos.mq_curmsgs = 0;

*/
	
	if((cola_mensajes = mq_open("/mq_so", O_CREAT | O_RDWR, 0660, NULL)) == -1){
		perror("No se pudo crear cola de mensajes");
		return 1;
	}

	char c;
	char c_buffer[MAX];


	while(1){
		c = getchar();
		sprintf(c_buffer, "%c", c);
		if(mq_send(cola_mensajes, c_buffer, MAX, 0) == -1){
			perror("No se pudo enviar el mensaje");
			return -1;
		}

		if(c == EOF) break;
	}

	mq_close(cola_mensajes);
}
