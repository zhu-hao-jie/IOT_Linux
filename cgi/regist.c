#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cgic.h"
#include "sqlite3.h"


//注册sqlite
int cgiMain()
{
	char userbuf[10], pwbuf[10]; 
	char sql[1024], **result, *errmsg;
	int nrow, ncolumn;
	sqlite3 *db;
	if(sqlite3_open("user.db",&db) != 0)
	{
		printf("open user.db failed!\n");
		exit(-1);
	}
	cgiFormString("username",userbuf,10);
	cgiFormString("userpass",pwbuf,10);

	sprintf(sql,"insert into user values('%s','%s');",userbuf,pwbuf);


	if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != 0)
	{
		perror("sqlite3_exec()\n");
		cgiHeaderContentType("text/html");
		fprintf(cgiOut, "<HTML>\n");
		fprintf(cgiOut, "<HTML><HEAD>\n");
		fprintf(cgiOut, "<TITLE>logining</TITLE></HEAD>\n");
		fprintf(cgiOut, "<BODY>");
		fprintf(cgiOut, "<H1>%s<Hi>","username or password is not right,please try again");		
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
	}
	else{
		cgiHeaderContentType("text/html");
//		fprintf(cgiOut,"<request.seCharcterEncoding(%s);>",buf);
		fprintf(cgiOut, "<HTML>\n");
		fprintf(cgiOut, "<HTML><HEAD>\n");
		fprintf(cgiOut, "<TITLE>regist</TITLE></HEAD>\n");
		fprintf(cgiOut, "<BODY>");
		fprintf(cgiOut, "<H1>%s<Hi>","regist successfully,skipping...");		
		fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"1;url=../index.html\">");
	}
	return 0;
}
