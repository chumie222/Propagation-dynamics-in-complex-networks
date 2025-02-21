/*
 * ER_network.h
 *
 *  Created on: 2017-7-16
 *      Author: Administrator
 */

#ifndef ER_NETWORK_H_
#define ER_NETWORK_H_

#include "network/network_total.h"
#define ER_NETWORK_SIZE 4// 10000
/*******************************************
 * 生成ER网络
 * Node ER[]:要生成的ER网络节点集合
 * float p:ER网络边的生成概率
 * int network_size:网络节点数
 * char ch[]:字节数组
 * edge_element_t *edge_list:存储的单向边列表
 *******************************************/
int ER_Model(Node ER[], float p, int network_size,  edge_element_t **edge_list);
/*******************************************
 * 生成ER网络,返回所有边的列表（单向的），同时返回1-Q比例的不重复的边
 * 生成的边数最多是(N*(N-1)/2)*p
 * Node ER[]:要生成的ER网络节点集合
 * float p:ER网络边的生成概率
 * int network_size:网络节点数
 * char ch[]:字节数组
 * edge_element_t **edge_list:存储的单向边列表的地址，指针的指针
 * float Q:网络边重复比例
 * edge_element_t **non_existent_edge_list:未连接的边链表，长度为(N*(N-1)/2)*p
 *******************************************/
int ER_Model_with_Q(Node ER[], float p, int network_size, char ch[], edge_element_t **edge_list, float Q, edge_element_t **non_existent_edge_list);

#endif /* ER_NETWORK_H_ */
