/*
 * KeyEventContext.h
 *
 *  Created on: Feb 16, 2020
 *      Author: guoxs
 */

#ifndef _KEY_EVENT_CONTEXT_H_
#define _KEY_EVENT_CONTEXT_H_

extern int videoCarema;// lyj add
extern int RecCapKey;
#define REC_FLAG 1;
#define CAP_FLAG 2;
typedef void (*on_key_event_callback)(int keyCode, int keyStatus);

typedef enum{

	keyup =1,
	keydown=2,
	keyOk=3,
	keyMode=4,
	keyReturn=5,
	keyMenu=6,
}KeyVal;




int start_key_event_ctx();
int stop_key_event_ctx();
void set_key_event_callback(on_key_event_callback cb);

#endif /* _KEY_EVENT_CONTEXT_H_ */
