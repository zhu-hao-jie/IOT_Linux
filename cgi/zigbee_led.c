#include <stdio.h> 
#include "cgic.h" 
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "zigbee_cmd.h"


int cgiMain() 
{ 
	key_t key;
	char buf[N];
	char ep_no[2];
	int msgid;
	struct msg msg_buf;
	memset(&msg_buf,0,sizeof(msg_buf));
	
	cgiFormString("led",buf,N);
	cgiFormString("store",ep_no,2);

	if((key = ftok("/app", 'g')) < 0)
	{
		perror("ftok");
		exit(1);
	}

	if((msgid = msgget(key, 0666)) < 0)
	{
		perror("msgget");
		exit(1);
	}

	bzero (msg_buf.text, sizeof (msg_buf.text));
	
	msg_buf.text[0] = born_cmd(ep_no[0],DEVICE_LED,(buf[0]-48));

	msg_buf.type = 1L;
	msg_buf.msgtype = 4L;
	msgsnd(msgid, &msg_buf,sizeof(msg_buf)-sizeof(long),0);

	ep_no[0] -= 48;

	cgiHeaderContentType("text/html\n\n"); 
	fprintf(cgiOut, "<HTML><HEAD>\n"); 
	fprintf(cgiOut, "<TITLE>My CGI</TITLE></HEAD>\n"); 
	fprintf(cgiOut, "<BODY>"); 

	fprintf(cgiOut, "<H2>send sucess</H2>");

	//fprintf(cgiOut, "<a href='.html'>返回</a>"); 
	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../control%d.html\">", ep_no[0]);
	fprintf(cgiOut, "</BODY>\n"); 
	fprintf(cgiOut, "</HTML>\n"); 


	return 0; 
} 
