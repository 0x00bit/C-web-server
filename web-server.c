#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <stdlib.h>

int sv_port = 0;
int ip_addr = 0;

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

int web_server()
{
        int s = socket(AF_INET, SOCK_STREAM, 0);

        //int sv_port = 8080;
        //int ip = 0;

        struct sockaddr_in addr = {0};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(sv_port);
        addr.sin_addr.s_addr = ip_addr;

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
        return 0;
}

int menu()
{
	int choice;

	puts(
	"[1] set server port (default 8080) \n"
	"[2] set server ip addr \n"
	"[3] run server \n"
	);

	printf("please, select an option: \n");
	scanf("%d", &choice);
	//printf("selected option: %d\n", choice);
	
	switch(choice){
	    case 1:
	        printf("type server port number: \n");
		scanf("%d",&sv_port);
		printf("port defined: %d\n",sv_port);
		menu();
		printf("\n");
		break;


	    case 2:
                printf("type server ip addr: \n");
                scanf("%d",&ip_addr);
                printf("ip defined: %d\n",ip_addr);
		printf("\n");
	    	menu();
		break;

	    case 3:
		web_server();
		break;
	    
	    default:
		printf("please select an valid option");

	}
	return 0;
}

int main()
{
    banner();
    menu();
    return 0;
}

