#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iconv.h>
#include <sys/types.h>
#include <sys/wait.h>


int cgiMain()
{
	DIR *dir;
	struct dirent *dirp;

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"https://github.com/zhu-hao-jie?tab=repositories\">\n");
	fprintf(cgiOut, " <html xmlns=\"https://github.com/zhu-hao-jie?tab=repositories\"><head>\n");
	fprintf(cgiOut, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n");
	fprintf(cgiOut, "<link rel=\"stylesheet\" href=\"../images/style.css\" type=\"text/css\" />	<title>history Picture</title></head>\n");
	fprintf(cgiOut, "<body>\n");
	fprintf(cgiOut, "<H1 align=\"left\">history Picture:<H1>\n");
	fprintf(cgiOut, "<li><a href=\"/main2.html\">return to main</a></li>\n");
	fprintf(cgiOut, "<li><a href=\"/cgi-bin/delete.cgi\">delete all the pictures</a></li>\n");

	if((dir = opendir("../pice/")) == NULL)
	{
		perror("fail to opendir");
		return -1;
	}

	if(dir != NULL)
	{
		while((dirp = readdir(dir)) != NULL)
		{
			if(dirp->d_name[0] == '.') continue;
			fprintf(cgiOut, "<div align=\"center\">");
			fprintf(cgiOut,"%s",dirp->d_name);
			fprintf(cgiOut, "</div>");
			fprintf(cgiOut, "<div align=\"center\"><img src=\"../pice/%s\" width=\"320\" height=\"240\" />",dirp->d_name);
			fprintf(cgiOut, "</div>");
		}
	}

	fprintf(cgiOut, "</BODY></HTML>");
	

	return 0;
}
