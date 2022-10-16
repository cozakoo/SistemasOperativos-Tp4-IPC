#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int connection_handler(int connection_fd)

{
	int nbytes;
	char buffer[256];

  
	while((nbytes = read(connection_fd, buffer, 256)))

	{

        buffer[nbytes] = 0;

        if(index(buffer, EOF) != NULL) break;
		printf("Mensaje del prog_a: %s\n", buffer);

	}

	close(connection_fd);
	return 0;
}

int main(void)

{
	struct sockaddr_un address;
	int socket_fd, connection_fd;
	socklen_t address_length;

	socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		printf("Falla en socket\n");
		return 1;
	}

	unlink("./socket");

	memset(&address, 0, sizeof(struct sockaddr_un));

	address.sun_family = AF_UNIX;
	
	sprintf(address.sun_path, "./socket");

	if(bind(socket_fd,
		      (struct sockaddr *) &address,
			      sizeof(struct sockaddr_un)) != 0)
	{
		perror("Error al hacer bind)");
		return 1;
	}

	if(listen(socket_fd, 1) != 0)
	{
		perror("Error al intentar escuchar:");
		return 1;
	}
	if((connection_fd = accept(socket_fd,
			                            (struct sockaddr *) &address,
			                            &address_length)) > -1)
	{
		connection_handler(connection_fd);
		close(connection_fd);
	}

	close(socket_fd);
	unlink("./socket");
	return 0;
}
