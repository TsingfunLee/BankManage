// XunHuanDuiLie.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <iostream>
using namespace std;

const int MAXQUEUESIZE = 4;
int  g_iNum = 0;
enum SERTYTLE             //服务类型
{
	CUNKUAN=0,
	QUKUAN=1,
	KAIHU=2
};
typedef struct BANKGUEST     //定义银行客户结构体
{
	int iNum;
	SERTYTLE sertytle ;
}BANKGUEST;

typedef struct queue
{
	int queuesize;   //数组的大小
	int head, tail;  //队列的头和尾下标
	BANKGUEST  *q;          //数组头指针
	//int count;
}Queue;

int  help();
void InitQueue(Queue *queue);
void EnQueue(Queue *queue, BANKGUEST *guest);
void DeQueue(Queue *queue);
int  IsQueueFull(Queue *queue);
int  IsQueueEmpty(Queue *queue);
void PrintSertytle(SERTYTLE sertytle);

int IsQueueEmpty(Queue *queue)           //队列是否为空
{
	if (queue->head==queue->tail) /* 队列空的标志 */
		return 1;
	else
		return 0;
}

int IsQueueFull(Queue *queue)         //队列是否已满
{
	if ((queue->tail + 1) % (queue->queuesize)==queue->head)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void InitQueue(Queue *queue)         //初始化队列
{
	queue->queuesize = MAXQUEUESIZE;
	queue->q = (BANKGUEST *)malloc(sizeof(int)*queue->queuesize);
	queue->tail = 0;
	queue->head = 0;
	//queue->count = 0;
}

void EnQueue(Queue*queue, BANKGUEST guest)       //进队列
{
	int tmp = (queue->tail+1)%queue->queuesize;
	if (IsQueueFull(queue))
	{
			cout << "队列已满！" << endl;

	}
	else
	{
		queue->q[queue->tail].sertytle= guest.sertytle;
		queue->q[queue->tail].iNum =g_iNum+ 1;
		g_iNum += 1;
		queue->tail = tmp;
		
		//queue->count += 1;
	}
}

void DeQueue(Queue*queue)           //出队列
{
	int tmp;
	if (IsQueueEmpty(queue))
	{
		cout << "队列为空！" << endl;

	}
	else
	{
		tmp = queue->head;
		queue->head = (tmp + 1) % queue->queuesize;
		cout << queue->q[tmp].iNum << " ";
		PrintSertytle(queue->q[tmp].sertytle);
		cout << "已离队！" << endl;
		//queue->count -= 1;
	}
}

void VisitQueue(Queue*queue)             //输出队列
{
	int j = queue->head;
	if (queue->head==queue->tail)
	{
		cout << "队列为空！\n" << endl;
	}
	if (queue->head<queue->tail)
	{
		for (; j < queue->tail; j++)
		{
			cout << queue->q[j].iNum << " ";
			PrintSertytle(queue->q[j].sertytle);
			//cout << endl;
		}
	}
	else if (queue->head>queue->tail)
	{
		for (; j <queue->queuesize;)
		{
			cout << queue->q[j].iNum << " ";
			PrintSertytle(queue->q[j].sertytle);
			//cout << endl;
			j = j + 1;
		}
		for (j = 0; j < queue->tail;j++)
		{
			cout << queue->q[j].iNum << " ";
			PrintSertytle(queue->q[j].sertytle);
			//cout << endl;
		}
	}
	cout << endl;
}

void PrintSertytle(SERTYTLE sertytle)
{
	switch (sertytle)
	{
	case CUNKUAN:
		cout << "存款" << endl;
		break;
	case QUKUAN:
		cout << "取款" << endl;
		break;
	case KAIHU:
		cout << "开户" << endl;
		break;
	default:
		cout << "操作错误！" << endl;
		break;
	}
}

int main()
{
	char command;
	BANKGUEST guest;
	int input;
	Queue *queue=(Queue *)malloc(sizeof(Queue));
	//队列初始化 
	InitQueue(queue);
	help();
	cout << "请输入选择的选项（ASCII值）：" << endl;
	cin >> command;

	while (command)
	{
		switch (command)
		{
		case 63:
		{
			help();
		}break;//?帮助
		case 97:
		{
            printf("请输入操作：0存款，1取款，2开户\n");
			cin >> input;
			guest.sertytle = (SERTYTLE)input;
			guest.iNum = g_iNum;
			if (!IsQueueFull(queue))
			{
				EnQueue(queue, guest);
				printf("当前队列：\n");
				VisitQueue(queue);
			}
			else
			{
				printf("队列已满！\n");
			}
			
		}break;//a增加记录
		case 100:
		{
			printf("离队\n");
			if (!IsQueueEmpty(queue))
			{
				DeQueue(queue);
				printf("当前队列：\n");
				VisitQueue(queue);
			}
			else
			{
				printf("队列已空！\n");
			}
		}break;//d删除记录
		//case 102:
		//	{
		//		printf("查找记录\n");
		//	}break;//f查找记录
		//case 108:
		//	{
		//		printf("读盘\n");
		//	}break;//l读盘
		case 112:
		{
			printf("当前队列\n");
			VisitQueue(queue);
		}break;//p列出记录
		case 113:
		{
			printf("退出\n");
			return -1;
		}break;//q退出
		//case 115:
		//	{
		//		printf("存盘\n");
		//	}break;//s存盘
		default:
			printf("错误的命令!\n");//报错
		}

		help();
		cout << "请输入选择的选项（ASCII值）：" << endl;
		cin >> command;
	}
	return 1;
}

////////////////////////////////////////////////////////////////////
int help()//帮助模块
{
	printf("/----------------程序使用说明---------------\\\n");
	printf("|--------------------------------------------|\n");
	printf("|指令|   功能     |           说明           |\n");
	printf("| ?  | 取得帮助   |显示本帮助信息            |\n");
	printf("| a  | 取号       |向队列中添加记录          |\n");
	printf("| d  | 离开       |删除队列中队尾的记录      |\n");
	//printf("| f  | 查找记录 |按学号或姓名查找表中的记录|\n");
	printf("| p  | 当前队列情况 |显示队列中全部记录      |\n");
	//printf("| l  | 读取文件 |读入磁盘文件              |\n");
	//printf("| s  | 存为文件 |将当前工作保存为文件      |\n");
	printf("| q  | 退出程序   |退出本系统                |\n");
	printf("\\-------------------------------------------/\n");
	return(0);
}




