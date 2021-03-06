#ifndef __COMMAND_H__
#define __COMMAND_H__

#define SQLCMD_SIZE 256	//数据库命令
#define ACCMSG_SIZE 10	//账户信息(用户名密码)
#define VDOPIC_SIZE 204800  //客户端视频传递

//用户操作码
#define GETENV	1   //获取环境参数
#define GETCAM 	2   //打开摄像头
#define CTRLM0 	3   //M0相关控制
#define SIGNUP 	4   //用户注册
#define SIGNIN 	5   //用户登录
//#define BYE

//M0设备码
#define LED	1   //LED
#define BUZZ	2   //蜂鸣器
#define FAN	3   //风扇

//M0控制码
#define  LEDON	    1	//开LED灯
#define  LEDOFF	    2	//关LED灯
#define	 FANON	    3	//开风扇
#define  FANOFF	    4	//关风扇
#define  BUZZON	    5	//开蜂鸣器
#define  BUZZOFF    6	//关蜂鸣器

//自动处理阈值
#define TMPUPPERLIMIT	55  //温度上限值
#define TMPLOWERLIMIT	10  //温度下限值

#define HUMUPPERLIMIT	100 //湿度上限值
#define HUMLOWERLIMIT	100 //湿度下限值

#define LIGUPPERLIMIT	100 //亮度上限值
#define LIGLOWERLIMIT	100 //亮度下限值

//接收客户端数据
typedef struct client_2_server
{
    int cmd;
    int dev;
    int ctl;
    char name[ACCMSG_SIZE];
    char passwd[ACCMSG_SIZE];
}C2S;

//发送给客户端数据
typedef struct server_2_client
{
    int tem;
    int hum;
    int light;
    int loc_x;
    int loc_y;
    int loc_z;
    char sure[10];
}S2C;

//sql数据库
sqlite3 *account;    //数据库
char *errmsg;	//sql错误信息
char **resultp;
int nrow, ncolumn;

//int fd;
C2S cli_msg;	//接收cli数据
S2C svr_msg;	//svr发出数据

//注册登录
int signup();	//帐号注册
int signin();	//帐号登录

//客户端操作
void get_env_m0(int e_fd, Display display);  //获取m0环境参数
void get_vdo_cam(int v_fd); //获取cam视频

#endif	//__COMMAND_H__
