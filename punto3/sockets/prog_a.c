#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <errno.h> 

int main(void){

struct sockaddr_un address;

	int  socket_fd, nbytes;
	char buffer[256];

	socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);

	if(socket_fd < 0)
	{
		perror("Error al crear socket");
		return 1;
	}

	memset(&address, 0, sizeof(struct sockaddr_un));

	address.sun_family = AF_UNIX;
	sprintf(address.sun_path, "./socket");

	if(connect(socket_fd, (struct sockaddr *) &address,
		                sizeof(struct sockaddr_un)) != 0)
	{
		perror("Error de conexión");
		return 1;
	}
    char c;
	while(1)

	{

        nbytes = 0;
        while((c = getchar()) != '\n'){

            buffer[nbytes++] = c;

        }

        buffer[nbytes] = 0;

		if(strncmp(buffer, "quit", 4) == 0)
			break;
		write(socket_fd, buffer, nbytes);

	}

	close(socket_fd);

	return 0;
}
	
