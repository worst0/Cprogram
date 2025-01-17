/*************************************************************************
	> File Name: select.c
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年08月10日 星期一 17时48分46秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    fd_set rfds;
    struct timeval tv;
    int retval;

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
        char buff[512] = {0};
        ssize_t nread;
        if ((nread = read( 0, buff, sizeof(buff))) < 0) {
            perror("read(");
            exit(1);
        }
        printf("Data is available now.\n");
        //scanf("%s", buff);
        printf("%s", buff);
    }
        /* FD_ISSET(0, &rfds) will be true. */
    else
        printf("No data within five seconds.\n");

    exit(EXIT_SUCCESS);
}


