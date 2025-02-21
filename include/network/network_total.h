/*
 * network_total.h
 *
 *  Created on: 2017-7-16
 *      Author: Administrator
 */

#ifndef NETWORK_TOTAL_H_
#define NETWORK_TOTAL_H_

#include "total.h"

//杈瑰畾涔�
typedef struct edge{
	int data; //杈硅繛鎺ョ殑涓�涓畾鐐圭紪鍙�
	bool isNew; //鏍囧織杩欐潯杈规槸鍚︽槸鏈�缁堢殑鏂拌竟
	unsigned char overlapping; //鏍囧織杩欐潯杈规槸閲嶅彔杈硅繕鏄笉閲嶅彔杈癸紝0琛ㄧず涓嶉噸鍙狅紝1琛ㄧず閲嶅彔
	char transmit;
	float weight; //边权重
	struct edge *next;//边链表指针
}edge,*Edge;


//队列
typedef struct Queue{
	edge *front;
	edge *rear;
}Queue;


//鑺傜偣缁撴瀯
typedef struct Node{
	int data;
	int degree;		//
	char type;		//SIR
	int info_count; //
	unsigned char active; //
	edge *next;
}Node;

typedef struct Infect{
	int data;
	char type;
}Infect;

typedef struct edge_element{
   int from; //璧峰绔偣鍙�
   int to;   //缁堟绔偣鍙�
   struct edge_element * pre; //鍓嶉┍鎸囬拡
   struct edge_element * next; //鍚庣户鎸囬拡
}edge_element_t;

typedef struct node_element{
    int id; //鑺傜偣缂栧彿
    char type;		//鑺傜偣鎰熸煋绫诲瀷,SIR
    int newID;
    struct node_element *next;
}node_element_t;

typedef struct time_step_element{
	node_element_t * head;
	node_element_t * tail;
	int size;
	struct time_step_element * next;
}time_step_element_t;

typedef struct status_node_list{
	time_step_element_t * head;
	time_step_element_t * tail;
	int size;
}status_node_list_t;

typedef struct edge_layer_elem{
    int from;
    int layer1;
    int to;
    int layer2;
    struct edge_layer_elem* next;
}edge_layer_elem_t;

typedef struct edge_layer_list{
	edge_layer_elem_t *head;
	edge_layer_elem_t *tail;
    int size;
}edge_layer_list_t;

#endif /* NETWORK_TOTAL_H_ */
