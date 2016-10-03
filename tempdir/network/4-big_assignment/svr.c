#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define RC_SIZE 16
#define SD_SIZE 4096
#define RD_SIZE 4096

typedef struct stat Stat;

int FilePropertiesView(char *filename);

int main()
{
    int sr_fd;	//server
    int cl_fd;	//client
    int so_fd; //source
    int b_ret;	//bind
    int l_ret;	//listen
    int f_size;	//file size
    ssize_t s_ret;  //send
    ssize_t r_ret;  //recv
    ssize_t rd_ret; //read

    struct sockaddr_in sr_addr;
    struct sockaddr_in cl_addr;
    int s_len = sizeof(struct sockaddr_in);
    int c_len = sizeof(struct sockaddr_in);
    char rc_buf[RC_SIZE] = "";
    char sd_buf[SD_SIZE] = "";
    char rd_buf[RD_SIZE] = "";

    //zeor setting
    bzero(&sr_addr, s_len);
    bzero(&cl_addr, c_len);

    //assignment
    sr_addr.sin_family = AF_INET;
    sr_addr.sin_port = htons(9527);
    inet_pton(AF_INET, "127.0.0.1", &sr_addr.sin_addr);

    //sokcet
    sr_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sr_fd)
    {
	printf("socket failed!\n"); 
	return -1;
    }

    //bind
    b_ret = bind(sr_fd, (struct sockaddr *)&sr_addr, s_len);
    if(0 != b_ret)
    {
	printf("bind failed!\n");
	return -1; 
    }

    //listen
    l_ret = listen(sr_fd, 5);
    if(-1 == l_ret)
    {
	printf("listen failed!\n"); 
	return -1;
    }

    while(1)
    {
	//accept
	cl_fd = accept(sr_fd, (struct sockaddr *)&cl_addr, &c_len);
	if(-1 == cl_fd)
	{
	    printf("accept failed!\n");	
	    return -1;
	}
#if 1	//这部分之后要放到并发调用函数中
	//recv
	r_ret = recv(cl_fd, rc_buf, RC_SIZE, 0); 
	if(-1 == r_ret)
	{
	    printf("recv failed!\n"); 
	    return -1;
	}

	//检查文件是否存在
	f_size = FilePropertiesView(rc_buf);
	if(-1 == f_size)
	{
	    printf("file not exist.\n");	
	    send(cl_fd , "file not exist", SD_SIZE, 0);
	    continue;
	}
	printf("%d\n", f_size);

	//获得原始文件的大小
	

	//从原始文件中读取数据
	so_fd = open(rc_buf, O_RDONLY, 0666);
	if(so_fd < 0)
	{
	    printf("open source failed.\n");
	    return -1; 
	}

	rd_ret = read(so_fd, rd_buf, RD_SIZE);
	if(-1 == rd_ret)
	{
	    printf("read file failed.\n");	
	    return -1;
	}
	//printf("rd_buf:%s\n", rd_buf);

	//将读到的数据拷贝并发送给client
	strcpy(sd_buf, rd_buf);
	s_ret = send(cl_fd, sd_buf, SD_SIZE, 0);
	if(-1 == s_ret)
	{
	    printf("send filename failed!\n"); 
	    return -1;
	}
#endif
    }
    return 0;
}

int FilePropertiesView(char *filename)
{
    DIR *dir = opendir(".");
    if(!dir)
    {
	printf("open failure\n"); 
	return; 
    }

    Stat *file_info;
    struct dirent *rf = NULL;

    memset(file_info, 0, sizeof(stat));
    printf("%s\n", filename);
    while(rf = readdir(dir))
    {
	//使用stat函数将文件名和结构体关联
	stat(rf->d_name, file_info);

	//当前文件夹中是否存在客户端指定的文件，并判断是否为常规文件
	if((!strcmp(filename, rf->d_name))  && S_ISREG(file_info->st_mode))
	{
	    printf("file %s exist.\n", filename);	
	    return (int)file_info->st_size;
	}
    }
    return -1; 
}
