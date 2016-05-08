// XunHuanDuiLie.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include <iostream>
using namespace std;

const int MAXQUEUESIZE = 4;
int  g_iNum = 0;
enum SERTYTLE             //��������
{
	CUNKUAN=0,
	QUKUAN=1,
	KAIHU=2
};
typedef struct BANKGUEST     //�������пͻ��ṹ��
{
	int iNum;
	SERTYTLE sertytle ;
}BANKGUEST;

typedef struct queue
{
	int queuesize;   //����Ĵ�С
	int head, tail;  //���е�ͷ��β�±�
	BANKGUEST  *q;          //����ͷָ��
	//int count;
}Queue;

int  help();
void InitQueue(Queue *queue);
void EnQueue(Queue *queue, BANKGUEST *guest);
void DeQueue(Queue *queue);
int  IsQueueFull(Queue *queue);
int  IsQueueEmpty(Queue *queue);
void PrintSertytle(SERTYTLE sertytle);

int IsQueueEmpty(Queue *queue)           //�����Ƿ�Ϊ��
{
	if (queue->head==queue->tail) /* ���пյı�־ */
		return 1;
	else
		return 0;
}

int IsQueueFull(Queue *queue)         //�����Ƿ�����
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

void InitQueue(Queue *queue)         //��ʼ������
{
	queue->queuesize = MAXQUEUESIZE;
	queue->q = (BANKGUEST *)malloc(sizeof(int)*queue->queuesize);
	queue->tail = 0;
	queue->head = 0;
	//queue->count = 0;
}

void EnQueue(Queue*queue, BANKGUEST guest)       //������
{
	int tmp = (queue->tail+1)%queue->queuesize;
	if (IsQueueFull(queue))
	{
			cout << "����������" << endl;

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

void DeQueue(Queue*queue)           //������
{
	int tmp;
	if (IsQueueEmpty(queue))
	{
		cout << "����Ϊ�գ�" << endl;

	}
	else
	{
		tmp = queue->head;
		queue->head = (tmp + 1) % queue->queuesize;
		cout << queue->q[tmp].iNum << " ";
		PrintSertytle(queue->q[tmp].sertytle);
		cout << "����ӣ�" << endl;
		//queue->count -= 1;
	}
}

void VisitQueue(Queue*queue)             //�������
{
	int j = queue->head;
	if (queue->head==queue->tail)
	{
		cout << "����Ϊ�գ�\n" << endl;
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
		cout << "���" << endl;
		break;
	case QUKUAN:
		cout << "ȡ��" << endl;
		break;
	case KAIHU:
		cout << "����" << endl;
		break;
	default:
		cout << "��������" << endl;
		break;
	}
}

int main()
{
	char command;
	BANKGUEST guest;
	int input;
	Queue *queue=(Queue *)malloc(sizeof(Queue));
	//���г�ʼ�� 
	InitQueue(queue);
	help();
	cout << "������ѡ���ѡ�ASCIIֵ����" << endl;
	cin >> command;

	while (command)
	{
		switch (command)
		{
		case 63:
		{
			help();
		}break;//?����
		case 97:
		{
            printf("�����������0��1ȡ�2����\n");
			cin >> input;
			guest.sertytle = (SERTYTLE)input;
			guest.iNum = g_iNum;
			if (!IsQueueFull(queue))
			{
				EnQueue(queue, guest);
				printf("��ǰ���У�\n");
				VisitQueue(queue);
			}
			else
			{
				printf("����������\n");
			}
			
		}break;//a���Ӽ�¼
		case 100:
		{
			printf("���\n");
			if (!IsQueueEmpty(queue))
			{
				DeQueue(queue);
				printf("��ǰ���У�\n");
				VisitQueue(queue);
			}
			else
			{
				printf("�����ѿգ�\n");
			}
		}break;//dɾ����¼
		//case 102:
		//	{
		//		printf("���Ҽ�¼\n");
		//	}break;//f���Ҽ�¼
		//case 108:
		//	{
		//		printf("����\n");
		//	}break;//l����
		case 112:
		{
			printf("��ǰ����\n");
			VisitQueue(queue);
		}break;//p�г���¼
		case 113:
		{
			printf("�˳�\n");
			return -1;
		}break;//q�˳�
		//case 115:
		//	{
		//		printf("����\n");
		//	}break;//s����
		default:
			printf("���������!\n");//����
		}

		help();
		cout << "������ѡ���ѡ�ASCIIֵ����" << endl;
		cin >> command;
	}
	return 1;
}

////////////////////////////////////////////////////////////////////
int help()//����ģ��
{
	printf("/----------------����ʹ��˵��---------------\\\n");
	printf("|--------------------------------------------|\n");
	printf("|ָ��|   ����     |           ˵��           |\n");
	printf("| ?  | ȡ�ð���   |��ʾ��������Ϣ            |\n");
	printf("| a  | ȡ��       |���������Ӽ�¼          |\n");
	printf("| d  | �뿪       |ɾ�������ж�β�ļ�¼      |\n");
	//printf("| f  | ���Ҽ�¼ |��ѧ�Ż��������ұ��еļ�¼|\n");
	printf("| p  | ��ǰ������� |��ʾ������ȫ����¼      |\n");
	//printf("| l  | ��ȡ�ļ� |��������ļ�              |\n");
	//printf("| s  | ��Ϊ�ļ� |����ǰ��������Ϊ�ļ�      |\n");
	printf("| q  | �˳�����   |�˳���ϵͳ                |\n");
	printf("\\-------------------------------------------/\n");
	return(0);
}




