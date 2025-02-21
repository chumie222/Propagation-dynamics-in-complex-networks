/*
 * network_basic.cpp
 *
 *  Created on: 2017-7-16
 *      Author: Administrator
 */
#include "total.h"
#include "network/network_basic_ops.h"

void tranverse(Edge head){
    for(edge *ptr=head->next; ptr!=NULL; ptr=ptr->next){
       printf("节点值是:%d, ", ptr->data);
    }
    printf("\n");
}

//给端点的边列表插入新边
void create(Edge head, int data)
{
	edge *s;
	s=(edge *)malloc(sizeof(edge));
	s->overlapping = 1; //开始都设置为重复
	s->data=data;
	s->weight = -1; //开始设置边权重为-1，表示没有分配
	s->isNew = true; //初始设置每个边都是新的
	if(head->next==NULL)
	{
		s->next=head->next;
		head->next=s;
	}
	else{
		//从小到大排序
		while(head->next && head->next->data<data)
		{
			head=head->next;
		}
		s->next=head->next;
		head->next=s;
	}
}

//打印边列表
void print(Edge head,char type[])
{
	FILE *fp;
	edge *p;
	char ch[10];
	strcpy(ch,"Graph_");
	strcat(ch,type);

	fp=fopen(ch,"a");


	p=head->next;
	while(p)
	{
		fprintf(fp,"%10d",p->data);
		p=p->next;
	}
	fprintf(fp,"\n");
	fclose(fp);
}

//从边列表中删除一个边
int del_Data(Edge head,int data)
{
	edge *p,*q;
	int k;

	q=head;
	p=head->next;
	while(p && p->data!=data)
	{
		q=p;
		p=p->next;
	}
	if(p==NULL)
	{
		return -1;
	}
	k=p->data;
	q->next=p->next;

	free(p);
	return k;
}

//计算一个节点所连接的所有边的数目
int length(Edge head)
{
	int count = 0;
	edge *h;
	h = head->next;
	while(h)
	{
		count++;
		h = h->next;
	}
	return count;
}

//检查一个节点是否和另一个标号为data的节点相连
int find_Data(Edge head, int data)
{
	edge *h;
	h=head->next;
	while(h)
	{
		if(h->data==data)
			return 1;
		h=h->next;
	}
	return 0;
}

//统计一数组中各个元素的个数
void count_Data(int array[],float ct[], int M)
{
	int i;
	for(i=0;i<M;i++)
	{
		ct[i]=0;
	}
	for(i=0;i<M;i++)
	{
		ct[array[i]]=ct[array[i]]+1;
	}
}

//初始化队列
int Init_queue(Queue *Q)
{
	Q->front = (edge *)malloc(sizeof(edge));
	if(Q->front != NULL)
	{
		Q->rear = Q->front ;
		Q->front->next = NULL;
        return(1);
     }
  	else
		return(-1);
}

//将节点插入队列
void Enter_queue(Queue *Q, int data)
{
    edge *temp;
    temp = (edge *)malloc(sizeof(edge));
	if(temp == NULL)
		return ;
	else
	{
		temp->data = data;
        temp->next = NULL;
		Q->rear->next = temp;
		Q->rear = temp;
	}
}

//判断队列是否为空
int IsEmpty(Queue *Q)
{
	if(Q->front == Q->rear)
		return(1);
	else
		return(0);
}

//彻底删除队列
int DeletQueue(Queue *Q)
{
	edge *p;
	int data;
	if(Q->front == Q->rear)
	    return(-1);
    p = Q->front->next;
	Q->front->next = p->next ;
	if(Q->rear == p)
		Q->rear = Q->front;
	data=p->data;
	free(p);
    return(data);
}

//初始化节点
void init_Node(Node network[], int network_size)
{
	int i;
	for(i=0; i<network_size; i++)
	{
		network[i].data=i;
		network[i].degree=-1;
		network[i].type='S';
		network[i].active = 0; //开始都认为是保守
		network[i].info_count = 0;
		network[i].next=(edge *)malloc(sizeof(edge));
		network[i].next->next=NULL;
	}
}

void save_network_into_file(Node network[], int network_size, char file[]){
	FILE *fp;
	if((fp=fopen(file,"w"))==NULL) {
	    printf("network_into File %s cannot be opened\n", file);
	}else{
//		printf("File opened for writing\n");
		//写出每一条边的端点对
		//写入网络大小
//		fprintf(fp, "%d\n", network_size);
        for (int i=0; i<network_size; i++){
        	if (network[i].next->next != NULL){
        		fprintf(fp, "%d", i);
        		for (edge *pGuard=network[i].next->next; pGuard!=NULL; pGuard=pGuard->next){
					fprintf(fp, " %d", pGuard->data);
				}
        		fprintf(fp, "\n");
        	}
        }
	}
	fclose(fp);
}

int save_network_degree_distribution(Node network[], int network_size, char file[]){
	FILE *fp;
	int degree[network_size] = {0};
	float ct[network_size] = {0};			//用来表示每个度节点的个数,用来表示度分布
    int max_degree = 0;
	if((fp=fopen(file,"w"))==NULL) {
		    printf("degree File cannot be opened\n");
	}else{
		for(int i = 0 ; i < network_size ; i++)
		{
			degree[i] = length(network[i].next);
			network[i].degree = degree[i];
			if (max_degree < network[i].degree){
				max_degree = network[i].degree;
			}
		}

		//计算每个度的个数
		count_Data(degree, ct, network_size);
		//计算每个度出现的概率
		for(int i = 0 ; i <= max_degree ; i++)
		{
			ct[i] = ct[i]/network_size;
			//在文件中只写入分布到最大度
			fprintf(fp , "%d %f\n" , i , ct[i]);
		}
	}

	fclose(fp);
	return max_degree;
}

void create_overlapping_network(char file_path[], Node network[]){
	FILE *fp;
	char line[1000];
	int vertex1 = 0;
	int vertex2 = 0;
	const char *d = " \n";
	char *pp;
//	int count = 0;
	//打开文件,以读的方式
	if((fp=fopen(file_path,"r"))==NULL) {
		printf("network File cannot be opened\n");
	}else{
		while(fgets(line,100, fp)){    //读入每行数据
			//从一行中首先读出一个端点编号
			pp = strtok(line,d);
			vertex1 = atoi(pp);
//			count = 0;
			//开始处理另一头的端点
			pp = strtok(NULL,d);
			vertex2 = atoi(pp);

			create(network[vertex1].next, vertex2);
			if (network[vertex1].degree == -1){
				network[vertex1].degree = 1;
			}else{
				network[vertex1].degree++;
			}

//			printf("(%d, %d), %d degree is %d\n", vertex1, vertex2, vertex1, network[vertex1].degree);
//			printf("degree of node %d is %d\n", vertex1, count);
		}
	}
	fclose(fp);
}

//从文件中读出网络数据
int read_network_from_file(char file_path[], Node network[]){
    //首先从文件路径，建立文件指针
	int totoal_edges = 0;
	FILE *fp;
	char line[1000];
	int vertex1 = 0;
	int vertex2 = 0;
	const char *d = " \n";
	char *pp;
	int count = 0;
	//打开文件,以读的方式
	if((fp=fopen(file_path,"r"))==NULL) {
		printf("network File： %s cannot be opened\n", file_path);
	}else{
        while(fgets(line,1000,fp)){    //读入每行数据
            //从一行中首先读出一个端点编号
        	pp = strtok(line,d);
        	vertex1 = atoi(pp);
        	count = 0;
        	//开始处理另一头的端点
        	pp = strtok(NULL,d);
			while(pp)
			{
				vertex2 = atoi(pp);
				count++;
				totoal_edges++;
				create(network[vertex1].next, vertex2);
				pp=strtok(NULL,d);
			}
			network[vertex1].degree = count;
//			printf("degree of node %d is %d\n", vertex1, count);
	    }
	}
	fclose(fp);
	return totoal_edges/2;
}

int read_degree_sequence_from_file(char file_path[]){
	FILE *fp;
	char line[1000];
	int vertex1 = 0;
	float vertex2 = 0;
	const char *d = " \n";
	char *pp = NULL;
	int count = 0;
	//打开文件,以读的方式
	if((fp=fopen(file_path,"r"))==NULL) {
		printf("network File cannot be opened\n");
	}else{
		while(fgets(line,1000,fp)){    //读入每行数据
			//得到度值
			pp = strtok(line,d);
			vertex1 = atoi(pp);
			//得到度分布
			pp = strtok(NULL,d);
			vertex2 = atof(pp);
		}
	}
	fclose(fp);
	return vertex1;
}
