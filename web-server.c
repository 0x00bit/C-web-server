#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>

/* hello, this is my first programm made in C language
 * this project  was make based in the video: Making
 * Minimalist Web Server in C on Linux so... credits for
 * Nir Lichtman, thanks!
 * made by magnstr
 */


/*menu selector*/

/*void menu()
{

}*/

void main()
{
	
	int s = socket(AF_INET, SOCK_STREAM, 0);
	
	//char* sv_port = "0x901f";
	//int ip = 0;

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = 0;
	
	bind(s, (struct sockaddr *)&addr, sizeof(addr));

	listen(s, 10);

	int client_fd = accept(s, 0, 0);

	char buffer[256] = {0};
	recv(client_fd, buffer, 256, 0);

	char* f = buffer + 5;
	*strchr(f, ' ') = 0;
	int opened_fd = open(f, O_RDONLY);
	sendfile(client_fd, opened_fd, 0, 256);
	close(opened_fd);
	close(client_fd);
	close(s);

}


