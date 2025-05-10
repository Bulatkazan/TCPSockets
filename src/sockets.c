#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define IP "142.250.150.94" /* www.google.se*/
#define PORT 80 /*http port*/

int main(){
    int s;
    struct sockaddr_in sock;
    char buf[512];
    char *data;
    data = "HEAD / HTTP/1.0\n\n";

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0 ) {
        printf("socket() error\n");
        return -1;
    } else {
        sock.sin_addr.s_addr = inet_addr(IP);
        sock.sin_port = htons(PORT);
        sock.sin_family = AF_INET;
        int result = connect(s, (struct sockaddr*)&sock, sizeof(struct sockaddr_in));
        if (result != 0){
            printf("connect() error\n");
            close(s);
            return -1;
        } else {
            write(s, data, strlen(data));
            read(s, buf, 511);
            close(s);
            printf("\n%s\n", buf);
            return 0;
        }
    }


}