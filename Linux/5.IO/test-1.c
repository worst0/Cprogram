/*************************************************************************
	> File Name: test-1.c
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年08月08日 星期六 20时38分21秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

int main(void){
    fd_set rfds;
    struct timeval tv;
    int retval;
    int nread;
    /* Watch stdin (fd 0) to see when it has input. */

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    /* Wait up to five seconds. */

    tv.tv_sec = 5;
    tv.tv_usec = 0;

    retval = select(1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */

    if (retval == -1)
        perror("select()");
    else if (retval) {
        char buffer[512];
        /*
        if ((nread = read(0,buffer,sizeof(buffer))) == -1) {
            perror("read()");
            exit(1);
        }
        buffer[nread] = 0;
        printf("read <%d> : %s", nread, buffer); 
        */
        scanf("%s", buffer);
        printf("%s\n", buffer);
        printf("Data is available now.\n");
    }
        /* FD_ISSET(0, &rfds) will be true. */
    else
        printf("No data within five seconds.\n");

    exit(EXIT_SUCCESS);
}


