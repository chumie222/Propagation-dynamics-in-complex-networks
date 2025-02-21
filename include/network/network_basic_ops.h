/*
 * network_basic_ops.h
 *
 *  Created on: 2017-7-16
 *      Author: Administrator
 */

#ifndef NETWORK_BASIC_OPS_H_
#define NETWORK_BASIC_OPS_H_

#include "network/network_total.h"

void create(Edge head, int data);
void print(Edge head,char type[]);
int del_Data(Edge head,int data);
int length(Edge head);
int find_Data(Edge head, int data);
void count_Data(int array[],float ct[]);
int Init_queue(Queue *Q);
void Enter_queue(Queue *Q, int data);
int IsEmpty(Queue *Q);
int DeletQueue(Queue *Q);
void init_Node(Node ER[], int network_size);
void save_network_into_file(Node network[], int network_size, char file[]);
//淇濆瓨缃戠粶搴﹀垎甯冩枃浠�
int save_network_degree_distribution(Node network[], int network_size, char file[]);
//浠庢枃浠朵腑璇诲彇缃戠粶
int read_network_from_file(char file_path[], Node network[]);
//鏋勫缓閲嶅缃戠粶
void create_overlapping_network(char file_path[], Node network[]);
//浠庢枃浠朵腑璇诲彇搴﹀簭鍒�
int read_degree_sequence_from_file(char file_path[]);
#endif /* NETWORK_BASIC_OPS_H_ */
