/*
 * KeyEventContext.c
 *
 *  Created on: Feb 16, 2020
 *      Author: guoxs
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/select.h>
#include <linux/vt.h>
#include <linux/kd.h>
#include <linux/keyboard.h>
#include <linux/input.h>

#include "KeyEventContext.h"

//#define DEV_INPUT_NODE		"/dev/input/event0"
#define DEV_INPUT_NODE		"/customer/event0"

static int sWakeFds[2] = { -1, -1 };
static on_key_event_callback s_callback;



static void* _event_Loop(void *user) {

	printf("222222222\n");
#if 1
	int kbd = open(DEV_INPUT_NODE, O_RDONLY);
	if (kbd < 0) {
		printf("open %s fail!\n", DEV_INPUT_NODE);
		return NULL;
	}
#endif
	printf("open %s Success!\n", DEV_INPUT_NODE);

	//fd_set fdset;
	//FD_ZERO(&fdset);

	while (1)
	{
			//int i = 0;
		int event=0;
		char bkd_buf[128];
			//printf("[lyj]--->%d\n",i++);
		//printf("[lyj]== %d\n",read(kbd, &event, 4));
#if 1
		//if (read(kbd, &event, 4))
		fgets(bkd_buf,	128,  stdin);
		printf("bkd_buf = %s\n", bkd_buf);
		char choose =  bkd_buf[0];
        if(0)
		{
			printf("111111111111\n");
			if (event)
			{
				printf("event code: %d\n", event);
				event = 0;
				//write(kbd, &event, 4);

			}

			usleep(10);
		}

        switch (choose) {
			case '1':
							printf("menu_up\n");
							if (s_callback) {
												s_callback(1, 1);
											}
							break;
			case '2':
							printf("key_down\n");
							if (s_callback) {
													s_callback(1, 2);
											}
							break;

			case '3':
							printf("key_ok\n");
							if (s_callback) {
							s_callback(1, 3);
							}
							break;

			case '4':
							printf("key_mode\n");
							if (s_callback) {
												s_callback(1, 4);
											}
							break;


			case '5':
					printf("key_return\n");
					if (s_callback) {
					s_callback(1, 5);
					}
										break;
			case '6':
					printf("key_menu\n");
					if (s_callback) {
					s_callback(1, 6);
					}
					break;
			default:
				printf("iput format error!\n");
				break;
		}




#endif




	}
	printf(" while Success!\n");
#if 0
	while (1) {
		FD_SET(kbd, &fdset);
		FD_SET(sWakeFds[0], &fdset);
		if (select(FD_SETSIZE, &fdset, NULL, NULL, NULL) > 0) {
			if (FD_ISSET(kbd, &fdset)) {
				FD_CLR(kbd, &fdset);
				//struct input_event event;
				struct key_event0 event;
				if (read(kbd, &event, sizeof(event)) == sizeof(event)) {
					if (event.type == /*EV_KEY*/1) {
						printf("event code: %d, value: %d\n", event.code, event.value);
						// 和 set_key_event_callback 最好加一下锁，再操作
						if (s_callback) {
							s_callback(event.code, event.value);
						}
					}
				}
			}

			if (FD_ISSET(sWakeFds[0], &fdset)) {
				printf("wait_event wake up ...\n");
				close(sWakeFds[0]);
				sWakeFds[0] = -1;
				break;
			}
		}
	}

#endif

	//close(kbd);

	printf("_event_Loop exit...\n");

	return NULL;
}

int start_key_event_ctx() {
	if (pipe(sWakeFds) < 0) {
		printf("Create pipe error!\n");
		return -1;
	}
	printf("Create pipe success!\n");

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_t thread;
	int ret = pthread_create(&thread, &attr, _event_Loop, NULL);
	pthread_attr_destroy(&attr);

	if (ret || !thread) {
		printf("pthread_create error, erro=%s\n", strerror(errno));
		return -1;
	}
	printf("pthread_create success\n");
	return 0;
}

int stop_key_event_ctx() {
	if (sWakeFds[1] >= 0) {
		printf("Want to wake up wait_event...\n");

		ssize_t nWrite;
		do {
			nWrite = write(sWakeFds[1], "W", 1);
		} while ((nWrite == -1) && (errno == EINTR));

		while (sWakeFds[0] >= 0) {
			usleep(10000);
		}

		close(sWakeFds[1]);
		sWakeFds[1] = -1;
	}

	return 0;
}

void set_key_event_callback(on_key_event_callback cb) {
	s_callback = cb;
}
