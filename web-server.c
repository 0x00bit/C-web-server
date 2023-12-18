#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <stdlib.h>
/* hello, this is my first programm made in C language
 * this project  was make based in the video: Making
 * Minimalist Web Server in C on Linux so... credits for
 * Nir Lichtman, thanks!
 * made by magnstr
 */



void banner()
{

    char *buf;
    buf=(char*)malloc(100*sizeof(char));
    getcwd(buf,100);

    puts(                
"		  .88888888:.\n"
"                88888888.88888.\n"
"              .8888888888888888.\n"
"              888888888888888888\n"
"              88' _`88'_  `88888\n"
"              88 88 88 88  88888\n"
"              88_88_::_88_:88888\n"
"              88:::,::,:::::8888\n"
"              88`:::::::::'`8888\n"
"             .88  `::::'    8:88.\n"
"            8888            `8:888.\n"
"          .8888'             `888888.\n"
"         .8888:..  .::.  ...:'8888888:.\n"
"        .8888.'     :'     `'::`88:88888\n"
"       .8888        '         `.888:8888.\n"
"      888:8         .           888:88888.\n"
"    .888:88        .:           888:88888:\n"
"    8888888.       ::           88:888888\n"
"    `.::.888.      ::          .88888888\n"
"   .::::::.888.    ::         :::`8888'.:.\n"
"  ::::::::::.888   '         .::::::::::::\n"
"  ::::::::::::.8    '      .:8::::::::::::.\n"
" .::::::::::::::.        .:888:::::::::::::\n"
" :::::::::::::::88:.__..:88888:::::::::::'\n"
"  `'.:::::::::::88888888888.88:::::::::'\n"
"        `':::_:' -- '' -'-' `':_::::'`\n"

"------------------------------------------------\n"
"Little Web Server\n"
);
printf("server is listening on port 8080, in path %s\n",buf);
}
void main()
{
	banner();	
	int s = socket(AF_INET, SOCK_STREAM, 0);
	
	int sv_port = 8080;
	int ip = 0;

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(sv_port);
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


