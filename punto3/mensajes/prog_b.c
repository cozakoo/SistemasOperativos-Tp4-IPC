
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#define MAX 5

int main (){

	mqd_t cola_mensajes;
	//char c_buffer[MAX+1];
	char* c_buffer;
	struct mq_attr atributos;
	
//definimos los atributos de la cola de mensajes
/*
	atributos.mq_flags = 0;
	atributos.mq_maxmsg = 15;
	atributos.mq_msgsize = MAX;
	atributos.mq_curmsgs = 0;

*/	
	//if((cola_mensajes = mq_open("/colaMensajes", O_RDONLY, &atributos)) == -1){
	if((cola_mensajes = mq_open("/mq_so", O_RDWR)) == -1){
		perror("No se pudo leer cola de mensajes");
		return 1;
	}



	while(1){

		printf("HOLA");
		if(mq_receive(cola_mensajes, c_buffer, MAX, NULL) == -1){
			perror("No se pudo recibir el mensaje");
			return -1;
		}

		//if(*c_buffer == EOF) break;
		
		//printf("%c", *c_buffer);
		printf("%s", c_buffer);
	}

	mq_close(cola_mensajes);
}
