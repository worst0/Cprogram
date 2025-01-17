/*************************************************************************
	> File Name: head.h
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年07月26日 星期日 18时37分15秒
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

//my-self
#include "color.h"
#include "common.h"


// chat-project
/*
#include "chat.h"
#include "thread_pool.h"
*/
//#include "datatype.h"

//#include "file_transfer.h"



//system
#include <math.h>
#include <dirent.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include "head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <semaphore.h>


//json
#include <cjson/cJSON.h>
#include "parse_conf.h"
//#include "cJSON.h"



#ifdef _D
#define DBG(fmt, args...); printf(fmt, ##args);
#else
#define DBG(fmt, args...);
#endif

#endif
//DBG("In while");
