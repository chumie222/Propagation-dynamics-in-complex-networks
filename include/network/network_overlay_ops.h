/*
 * network_overlay_ops.h
 *
 *  Created on: 2017-7-16
 *      Author: Administrator
 */

#ifndef NETWORK_OVERLAY_OPS_H_
#define NETWORK_OVERLAY_OPS_H_

#include "network/network_total.h"

void traverse_node_edges(Node jiedian);


void traverse_all_nodes(Node all_nodes[], int network_size);

/********************************
 * 将原始边重新随机排序
 * edge_element_t* all_edge_alist:原始边形成的边链表
 * int edge_count:原始生成的边的数目
 * edge_element_t** rearranged_edge_list_head:重新排序的边链表的指针，是指针的指针
 ********************************/
void randomize_all_edges(edge_element_t* all_edge_alist, int edge_count, edge_element_t** rearranged_edge_list_head);

void randomize_self_all_edges(edge_element_t** all_edge_alist, int edge_count);
/*************
 * 对原始网络深拷贝
 * Node ori_network[]:初始生成的原始网络
 * Node duplicate_network[]:深拷贝生成的一模一样的网络
 * int network_size:网络节点数
 ************************/
void copy_network(Node ori_network[], Node duplicate_network[], int network_size);
/*********************
 * create_duplicate_network创建一个网络的有Q比例重复边的网络
 * 输入:
 * edge_element_t* rearranged_edge_list_head:经过重新排序的边链表
 * int edge_count:网络边的总数目
 * Node duplicate_network[]:生成的有重复比例的网络
 * int network_size:网络节点数
 * float Q:边重复比例
 * char[] ori_non_overlay_file_name:原始网络不重复部分文件名
 * char[] dup_non_overlay_file_name:重复网络不重复部分文件名
 *********************/
void create_duplicate_network(edge_element_t* rearranged_edge_list_head, int edge_count, Node duplicate_network[], int network_size, float Q, edge_element_t* non_edge_list_head, char ori_non_overlay_file_name[], char dup_non_overlay_file_name[]);
#endif /* NETWORK_OVERLAY_OPS_H_ */
