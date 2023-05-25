#include "link_list.h"
#include "data_global.h"

extern int dev_uart_fd;

extern linklist envlinkHead;
extern pthread_mutex_t mutex_linklist;
extern pthread_cond_t cond_refresh;


//struct termios  
//{  
//    unsigned short c_iflag; /* 输入模式标志*/  
//    unsigned short c_oflag; /* 输出模式标志*/  
//    unsigned short c_cflag; /* 控制模式标志*/  
//    unsigned short c_lflag; /*区域模式标志或本地模式标志或局部模式*/  
//    unsigned char c_line; /*行控制line discipline */  
//    unsigned char c_cc[NCC]; /* 控制字符特性*/  
//};

//终端初始化
void serial_init(int fd)
{
	struct termios options;
	tcgetattr(fd, &options);//获取终端介质 fd 的初始值，并将其值赋值给 options
	options.c_cflag |= ( CLOCAL | CREAD );
	options.c_cflag &= ~CSIZE;
	options.c_cflag &= ~CRTSCTS;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CSTOPB; 
	options.c_iflag |= IGNPAR;
	options.c_iflag &= ~(ICRNL | IXON);
	options.c_oflag = 0;
	options.c_lflag = 0;

	cfsetispeed(&options, B115200);//设置输入波特率
	cfsetospeed(&options, B115200);//设置输出波特率
	tcsetattr(fd,TCSANOW,&options);//设置与终端相关的参数，TCSANOW:改变立即发生
}

//zigbee 接收数据线程
void *pthread_zigbee_rcv (void *arg)
{
	int i = 0, len;
	char flag = 0, check;
	link_datatype buf;

	envlinkHead = CreateEmptyLinklist ();
#if 1
	if ((dev_uart_fd = open (DEV_ZIGBEE, O_RDWR)) < 0)
	{
		perror ("open ttyUSB0 fail");
	}
	serial_init (dev_uart_fd);//初始化 ttyUSB0 

	printf ("pthread_transfer is ok\n");

#endif
	while (1)
	{
		memset (&buf, 0, sizeof (link_datatype));
		read (dev_uart_fd, &check, 1);
 /*       if (check == 'c')
        {
            sendMsgQueue(MSG_ZIGBEE,MSG_CONNECT_SUCCESS);
        }*/
		if (check == 's')
		{
			check = 0;
			read (dev_uart_fd, &check, 1);
			if (check == 't')
			{
				check = 0;
				read (dev_uart_fd, &check, 1);
				if (check == ':')
				{
					check = 0;
					read (dev_uart_fd, &check, 1);
					if (check == 'e')
					{
						buf.msg_type = 'e';
						usleep(1);
						if ((len = read (dev_uart_fd, buf.text, LEN_ENV)) != LEN_ENV)
						{
							for (i = len; i < LEN_ENV; i++)
							{
								read (dev_uart_fd, buf.text+i, 1);
							}
						}
						flag = 1;
					}			
				}
			}
		}
		
		if (flag==1)
		{
			pthread_mutex_lock (&mutex_linklist);
			//接收到的数据加入到链表中
			if ((InsertLinknode (buf)) == -1)
			{
				pthread_mutex_unlock (&mutex_linklist);
				printf ("NONMEM\n");
			}
			pthread_mutex_unlock (&mutex_linklist);
			flag = 0;
			pthread_cond_signal (&cond_refresh);
		}
		
	}
	return 0;
}
