#include "cgic.h"
#include <stdlib.h>

//删除
int cgiMain()
{
	system("rm /www/pice/*");

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<HTML><HEAD>\n");
	fprintf(cgiOut, "<TITLE>logining</TITLE></HEAD>\n");
	fprintf(cgiOut, "<BODY>");
	fprintf(cgiOut, "<H1>%s<Hi>","delete pictures successfully,skipping...");		
	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"0;url=/cgi-bin/picture1.cgi\">");
	return 0;
}
