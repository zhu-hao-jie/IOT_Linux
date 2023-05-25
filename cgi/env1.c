#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#include <unistd.h>
#include "sem.h"
#include "cgic.h"
#include "data_global.h"

#define N 32

#define STO_NO 1

char status[2][6] = {"Close", "Open"};
char fan_status[4][6] = {"Close", "One", "Two", "Three"};

struct shm_addr
{
	char cgi_status;
	char qt_status;
	struct env_info_array zg_status;
};

int cgiMain()
{
	key_t key;
	int shmid,semid;
	struct shm_addr *shm_buf;
	
	
	if((key = ftok("/app",'i')) <0)
	{
		perror("ftok");
		exit(1);
	}
	printf("key = %x\n",key);

	if((semid  = semget(key, 1, 0666)) < 0)
	{
		perror("semget");
		exit(1);
	}

	if((shmid = shmget(key, N, 0666 )) == -1)
	{
			perror("shmget");
			exit(1);
	}

	if((shm_buf = (struct shm_addr*)shmat(shmid, NULL, 0)) == (void*)-1 )
	{
		perror("shmat");
		exit(1);
	}

	sem_p(semid,0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<head><meta http-equiv=\"refresh\" content=\"1\"><style><!--body{line-height:50%}--></style></head>");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<BODY bgcolor=\"#666666\">\n");
	fprintf(cgiOut, "<h1><font color=\"#FF0000\">ENDPOINT  #%d</font></H2>\n ", STO_NO);
	if (shm_buf->zg_status.env_no[STO_NO].storage_status == 1)
	{
		fprintf(cgiOut, "<h2><font face=\"Broadway\"><font color=\"#FFFAF0\">Real-time information environment</font></font></H2>\n ");	
		fprintf(cgiOut, "<h4>Temperature:\t%0.2f</H4>\n ", shm_buf->zg_status.env_no[STO_NO].temperature);
	//	fprintf(cgiOut, "<h4>Humidity:\t%0.2f</H4>\n ", shm_buf->zg_status.env_no[STO_NO].humidity);
		fprintf(cgiOut, "<h4>Light:\t%d</H4>\n ", shm_buf->zg_status.env_no[STO_NO].illumination);
		fprintf(cgiOut, "<h4>Gas:\t%d</H4>\n ", shm_buf->zg_status.env_no[STO_NO].gas);
	//	fprintf(cgiOut, "<h4>Adc:\t%0.2f</H4>\n ", shm_buf->zg_status.env_no[STO_NO].adc);
		// 红外
		if(shm_buf->zg_status.env_no[STO_NO].hongwai == 1)
		{
			fprintf(cgiOut, "<h4>有人\t</H4>\n ");
		}else{			
			fprintf(cgiOut, "<h4>无人\t</H4>\n "); 
		}
	}
	else
	{
		fprintf(cgiOut, "<h2><font face=\"Broadway\"><font color=\"#FFFAF0\">Close!</font></font></H2>\n ");	
	}
//	fprintf(cgiOut, "<h3>:</H3>\n ");	
	fprintf(cgiOut, "</BODY></HTML>\n");	
	sem_v (semid, 0);
	return 0;
}
