/*
 * network_tools.cpp
 *
 *  Created on: 2017-7-16
 *      Author: Administrator
 */
#include "total.h"
#include "network/network_total.h"
#include "network/network_overlay_ops.h"
#include "network/network_basic_ops.h"
#include "utils/random_util.h"

/*************
 * 对原始网络深拷贝
 * Node ori_network[]:初始生成的原始网络
 * Node duplicate_network[]:深拷贝生成的一模一样的网络
 * int network_size:网络节点数
 ************************/
void copy_network(Node ori_network[], Node duplicate_network[], int network_size){
	edge * temp_ptr = NULL; //初始化头指针为NULL
	edge * list_tail = NULL; //链表尾指针
    for (int i=0; i<network_size; i++){
        //深度拷贝每个节点
    	duplicate_network[i].data = ori_network[i].data;
    	duplicate_network[i].degree = ori_network[i].degree;
    	duplicate_network[i].type = ori_network[i].type;
    	duplicate_network[i].next=(edge *)malloc(sizeof(edge));
    	duplicate_network[i].next->next = NULL;
//    	printf("节点号是:%d,节点度是:%d,节点类型是%c\n",duplicate_network[i].data,duplicate_network[i].degree,duplicate_network[i].type);
    	//拷贝节点的连边链表
        for (edge * pGuard=ori_network[i].next->next; pGuard!=NULL; pGuard=pGuard->next){
        	//建立所有边（端点对）的数组，为重排序做准备
        	temp_ptr = NULL;
        	temp_ptr = (edge *)malloc(sizeof(edge));
        	temp_ptr->data = pGuard->data;
        	temp_ptr->isNew = pGuard->isNew;
        	if (duplicate_network[i].next->next == NULL){
                //若这时节点的连边链表还没有一个连边
        		duplicate_network[i].next->next = temp_ptr;
        		list_tail = temp_ptr;
        		list_tail->next = NULL;
        	}else{
        		//若节点的连边链表已经有连边了
        		list_tail->next = temp_ptr;
        		list_tail = temp_ptr;
        		temp_ptr->next = NULL;
        	}
        }
    }
}

/********************************
 * 将原始边重新随机排序
 * edge_element_t* all_edge_alist:原始边形成的边链表
 * int edge_count:原始生成的边的数目
 * edge_element_t** rearranged_edge_list_head:重新排序的边链表的指针，是指针的指针
 ********************************/
void randomize_all_edges(edge_element_t* all_edge_alist, int edge_count, edge_element_t** rearranged_edge_list_head){
	//将原始边链表存成指针数组
	edge_element_t* edge_ptr_array[edge_count];
	int ptr_pos = 0;
    for(edge_element_t *pGuard=all_edge_alist; pGuard!=NULL; pGuard=pGuard->next){
    	edge_ptr_array[ptr_pos] = pGuard;
//    	printf("from %d, to %d\n",pGuard->from,pGuard->to);
    	ptr_pos++;
    }
    //将边随机重排
	int a[edge_count] = {0};
	random_permutation(edge_count, a);
//	printf("随机数是:");
//	for(int i=0; i<edge_count; i++){
//		printf("%d ",a[i]);
//	}
//	printf("\n");
	//这个地方生成双向链表
    for (int i=edge_count-1; i>=0; i--){
    	//按照重排的顺序重新排列链表，逆序前插
        if (*rearranged_edge_list_head == NULL){
        	edge_ptr_array[a[i]]->next = NULL; //后继是空
        	edge_ptr_array[a[i]]->pre = NULL; //前驱是空
        	*rearranged_edge_list_head = edge_ptr_array[a[i]];
        }else{
        	edge_ptr_array[a[i]]->next = *rearranged_edge_list_head; //设置新节点的后继
        	(*rearranged_edge_list_head)->pre = edge_ptr_array[a[i]]; //设置 原节点的前驱
        	*rearranged_edge_list_head = edge_ptr_array[a[i]];
        }
    }
}

/********************************
 * 将原始边重新随机排序,直接修改链表本身
 * edge_element_t** all_edge_alist:原始边形成的边链表
 * int edge_count:原始生成的边的数目
 ********************************/
void randomize_self_all_edges(edge_element_t** all_edge_alist, int edge_count){
	//将原始边链表存成指针数组
	edge_element_t* edge_ptr_array[edge_count];
	int ptr_pos = 0;
    for(edge_element_t *pGuard(*all_edge_alist); pGuard!=NULL; pGuard=pGuard->next){
    	edge_ptr_array[ptr_pos] = pGuard;
//    	printf("from %d, to %d\n",pGuard->from,pGuard->to);
    	ptr_pos++;
    }
    //将边随机重排
	int a[edge_count] = {0};
	random_permutation(edge_count, a);
//	printf("随机数是:");
//	for(int i=0; i<edge_count; i++){
//		printf("%d ",a[i]);
//	}
//	printf("\n");
	//这个地方生成双向链表
	*all_edge_alist = NULL;
    for (int i=edge_count-1; i>=0; i--){
    	//按照重排的顺序重新排列链表，逆序前插
        if (*all_edge_alist == NULL){
        	edge_ptr_array[a[i]]->next = NULL; //后继是空
        	edge_ptr_array[a[i]]->pre = NULL; //前驱是空
        	*all_edge_alist = edge_ptr_array[a[i]];
        }else{
        	edge_ptr_array[a[i]]->next = *all_edge_alist; //设置新节点的后继
        	(*all_edge_alist)->pre = edge_ptr_array[a[i]]; //设置 原节点的前驱
        	*all_edge_alist = edge_ptr_array[a[i]];
        	(*all_edge_alist)->pre = NULL; //最前边的前驱永远是NULL
        }
    }
}

/*****************
 * 检验边是否重复
 * duplicate_network:需要最终生成和对比检查的网络
 * edge_nodes:组成边的点对
 *****************/
bool check_repetition(Node duplicate_network[], int edge_nodes[]){
    //首先检查第一条边是否存在
	for(edge *pGuard=duplicate_network[edge_nodes[0]].next->next; pGuard!=NULL; pGuard=pGuard->next){
        if (pGuard->data == edge_nodes[1]){
           //说明这条边存在
//        	printf("出现重复!\n");
        	return true;
        }
	}

	return false;
}

/*********************************
 * 检查新组合的边是否是环，是否和网络中的边重复：包括原有的边和后来添加的边,如果不重复则将新边双向添加进网络，否则返回检检查有效为假
 * Node duplicate_network[]:要参照的和最后生成的网络
 * edge_element_t * first_ptr:原始要重构第一个边指针
 * edge_element_t * second_ptr:原始要重构第二个边指针
 * int new_edge1_nodes[]:新生成的第一个边的节点对
 * int new_edge2_nodes[]:新生成的第二个边的节点对
 ***********************************/
bool check_valid_and_insert(Node duplicate_network[], edge_element_t *first_ptr, edge_element_t *second_ptr, int new_edge1_nodes[], int new_edge2_nodes[]){
	edge* temp_edge_ptr = NULL; //指示两个边
    bool return_value1 = 0;
    bool return_value2 = 0;
	//判断边是否有环，是否重复
	if (new_edge1_nodes[0]==new_edge1_nodes[1] || new_edge2_nodes[0]==new_edge2_nodes[1]){
//		printf("loop comes out!\n");
		//出现环
		return false;
	}else{
//		printf("loop does not exist!\n");
        //若无环，则检查是否有重边
//		printf("检查第一条边:(%d,%d)\n",new_edge1_nodes[0],new_edge1_nodes[1]);
		return_value1 = check_repetition(duplicate_network, new_edge1_nodes);
//		printf("检查第二条边:(%d,%d)\n",new_edge2_nodes[0],new_edge2_nodes[1]);
		return_value2 = check_repetition(duplicate_network, new_edge2_nodes);
//		printf("两条边检查完毕!\n");
		if (return_value1 || return_value2){
			//假如出现重复
//			printf("Repetition exists!\n");
			return false;
		}else{
//			printf("Repetition does not exists!\n");
//			printf("原始第一条边:(%d,%d),第二条边:(%d,%d),交换后的第一条边:(%d,%d),第二条边:(%d,%d)\n",first_ptr->from,first_ptr->to,second_ptr->from,second_ptr->to,new_edge1_nodes[0],new_edge1_nodes[1],new_edge2_nodes[0],new_edge2_nodes[1]);
			//既无环又无重边,将新边添加进去，修改边的新旧属性
			//修改原边新旧属性
			//修改第一条边
			//先修改正向
			for(temp_edge_ptr=duplicate_network[first_ptr->from].next; temp_edge_ptr!=NULL; temp_edge_ptr=temp_edge_ptr->next){
			   if (temp_edge_ptr->data == first_ptr->to){
				   temp_edge_ptr->isNew = false; //把这个边设置成旧边
			   }
			}
			//再修改反向
			for(temp_edge_ptr=duplicate_network[first_ptr->to].next; temp_edge_ptr!=NULL; temp_edge_ptr=temp_edge_ptr->next){
				if (temp_edge_ptr->data == first_ptr->from){
				   temp_edge_ptr->isNew = false; //把这个边设置成旧边
				}
			}
			//修改第二条边
			//先修改正向
			for(temp_edge_ptr=duplicate_network[second_ptr->from].next; temp_edge_ptr!=NULL; temp_edge_ptr=temp_edge_ptr->next){
			   if (temp_edge_ptr->data == second_ptr->to){
				   temp_edge_ptr->isNew = false; //把这个边设置成旧边
			   }
			}
			//再修改反向
			for(temp_edge_ptr=duplicate_network[second_ptr->to].next; temp_edge_ptr!=NULL; temp_edge_ptr=temp_edge_ptr->next){
				if (temp_edge_ptr->data == second_ptr->from){
				   temp_edge_ptr->isNew = false; //把这个边设置成旧边
				}
			}
			//插入新边
			create(duplicate_network[new_edge1_nodes[0]].next, new_edge1_nodes[1]);
			create(duplicate_network[new_edge1_nodes[1]].next, new_edge1_nodes[0]);
			create(duplicate_network[new_edge2_nodes[0]].next, new_edge2_nodes[1]);
			create(duplicate_network[new_edge2_nodes[1]].next, new_edge2_nodes[0]);
//			printf("insert new edges!\n");
			return true;
		}
	}
}

/*********************************************
 * 从链表中删除两个节点，倒着删除，先删除第二个，再删除第一个
 *edge_element_t * first_prior_ptr:重新排序的边列表
 *edge_element_t * first_ptr:要删除的第一个边节点
 *edge_element_t * second_prior_ptr:要删除的第二个节点的前驱节点
 *edge_element_t * second_ptr:要删除的第二个边节点
 *********************************************/
void  delete_edge_nodes_and_move_ptr(edge_element_t ** first_ptr, edge_element_t ** second_ptr, edge_element_t ** head){
    //先删除后边第二个节点
	edge_element_t *precursor = NULL;
	edge_element_t *successor = NULL;
	//先处理第二个节点
	precursor = (*second_ptr)->pre;
	successor = (*second_ptr)->next;

	if (precursor != NULL){
		precursor->next = successor;
	}

	if (successor != NULL){
		successor->pre = precursor;
	}

	free(*second_ptr);
	*second_ptr = successor;

	//处理第一个节点
	precursor = (*first_ptr)->pre;
	successor = (*first_ptr)->next;

	if (successor != NULL){
		successor->pre = precursor;
	}

	if (precursor != NULL){
		precursor->next = successor;
	}else{
        //说明这个是第一个节点
		*head = successor;
	}

	free(*first_ptr);
	*first_ptr = successor;


	//后移结束，两个指针有可能变成一样
	if (*first_ptr==*second_ptr && *first_ptr!=NULL){
		//如果两个一样，则第二个指针再后移一个
		*second_ptr = (*second_ptr)->next;
	}
}

void delete_non_edge(edge_element_t **non_edge_list_head, int new_edge_nodes[]){
	edge_element_t *first_pGuard = *non_edge_list_head;
	edge_element_t *precursor = NULL;
	edge_element_t *successor = NULL;
	bool find_first = false;
	for (first_pGuard = *non_edge_list_head; first_pGuard!=NULL; first_pGuard=first_pGuard->next){
		if((first_pGuard->from==new_edge_nodes[0] && first_pGuard->to==new_edge_nodes[1])
			|| (first_pGuard->from==new_edge_nodes[1] && first_pGuard->to==new_edge_nodes[0]) ){
			find_first = true;
			break;
		}
	}

	if (find_first){
//		printf("不存在边找到了\n");
		precursor = first_pGuard->pre;
		successor = first_pGuard->next;
		if (successor != NULL){
			successor->pre = precursor;
		}

		if (precursor != NULL){
			precursor->next = successor;
		}else{
			//说明这个是第一个节点
			*non_edge_list_head = successor;
		}

		free(first_pGuard);
	}

}

void tranverse_double_link_list(edge_element_t * rearranged_edge_list_head){
	for (edge_element_t * first_ptr=rearranged_edge_list_head; first_ptr!=NULL; first_ptr=first_ptr->next){
		printf("剩下的边是(%d,%d)\n",first_ptr->from,first_ptr->to);
	}
	printf("遍历结束\n");
}

int count_number(edge_element_t* list){
	int count = 0;
	while(list != NULL){
		count++;
		list = list->next;
	}
	return count;
}

void traverse_node_edges(Node jiedian){
	printf("节点%d:", jiedian.data);
    for (edge * pGuard=jiedian.next->next; pGuard!=NULL; pGuard=pGuard->next){
        printf("  %d", pGuard->data);
    }
	printf("\n");
}


void traverse_all_nodes(Node all_nodes[], int network_size){
	for(int i=0; i<network_size; i++){
		traverse_node_edges(all_nodes[i]);
	}
}

void record_nonoverlapping_edges(edge_element_t *first_ptr, edge_element_t *second_ptr, int new_edge1_nodes[], int new_edge2_nodes[], char ori_non_overlay_file_name[], char dup_non_overlay_file_name[]){
	int ori_edges1[2];
	int ori_edges2[2];
	int dup_edges1[2];
	int dup_edges2[2];
    if (first_ptr->from >= first_ptr->to){
    	ori_edges1[0] = first_ptr->to;
    	ori_edges1[1] = first_ptr->from;
    }else{
    	ori_edges1[0] = first_ptr->from;
    	ori_edges1[1] = first_ptr->to;
    }

    if (second_ptr->from >= second_ptr->to){
		ori_edges2[0] = second_ptr->to;
		ori_edges2[1] = second_ptr->from;
    }else{
		ori_edges2[0] = second_ptr->from;
		ori_edges2[1] = second_ptr->to;
    }

    if (new_edge1_nodes[0] >= new_edge1_nodes[1]){
    	dup_edges1[0] = new_edge1_nodes[1];
    	dup_edges1[1] = new_edge1_nodes[0];
    }else{
    	dup_edges1[0] = new_edge1_nodes[0];
    	dup_edges1[1] = new_edge1_nodes[1];
    }

    if (new_edge2_nodes[0] >= new_edge2_nodes[1]){
       	dup_edges2[0] = new_edge2_nodes[1];
       	dup_edges2[1] = new_edge2_nodes[0];
    }else{
       	dup_edges2[0] = new_edge2_nodes[0];
       	dup_edges2[1] = new_edge2_nodes[1];
    }
	FILE *fp_A, *fp_B;
	fp_A=fopen(ori_non_overlay_file_name,"a");
	fprintf(fp_A, "%d  %d\n%d  %d\n", ori_edges1[0], ori_edges1[1], ori_edges2[0], ori_edges2[1]);
	fclose(fp_A);
	fp_B=fopen(dup_non_overlay_file_name,"a");
	fprintf(fp_B,"%d  %d\n%d %d\n", dup_edges1[0], dup_edges1[1], dup_edges2[0], dup_edges2[1]);
	fclose(fp_B);
}
/*********************
 * create_duplicate_network创建一个网络的有Q比例重复边的网络，重新构造的网络平均度保持不变，但是度分布不能保持
 * 输入:
 * edge_element_t* rearranged_edge_list_head:经过重新排序的边链表
 * int edge_count:网络边的总数目
 * Node duplicate_network[]:生成的有重复比例的网络
 * int network_size:网络节点数
 * float Q:边重复比例
 * edge_element_t* non_edge_list_head:不重复边链表
 *********************/
void create_duplicate_network(edge_element_t* rearranged_edge_list_head, int edge_count, Node duplicate_network[], int network_size, float Q, edge_element_t* non_edge_list_head, char ori_non_overlay_file_name[], char dup_non_overlay_file_name[]){
	int used_edge_count = 0;

	int edge_threshold = round(edge_count*(1-Q)); //Q是边的重复比例,1-Q比例的边不重复,为了解决浮点1.0=0.99999999.。9的问题，必须要round
	edge_threshold -= edge_threshold%2; //变成偶数,往小了减，虽然有误差，但是不大
	printf("edge_count is:%d, edge_threshold is:%d, non list length is %d\n", edge_count, edge_threshold, count_number(non_edge_list_head));

	edge* edge_prior_ptr = NULL; //节点的前节点指针
	edge* edge_PGuard = NULL;
	int new_edge1_nodes[2] = {0}; //第一条新边的节点对
	int new_edge2_nodes[2] = {0}; //第二条新边的节点对
	bool successfully_rematched = true; //最开始必须认为是成功的，这里必须是1
    bool existUpdate = false;
    bool enough = false;
    //开始选取两条边是紧挨着的第一和第二两个边节点
	edge_element_t * first_ptr = NULL; //第一条边的指针
	edge_element_t * second_ptr = NULL; //第二条边的指针

	//首先给链表随机重排序
	randomize_self_all_edges(&rearranged_edge_list_head, edge_count);
	//		tranverse_double_link_list(rearranged_edge_list_head);
	first_ptr = rearranged_edge_list_head;
	second_ptr = rearranged_edge_list_head->next;
	successfully_rematched = true;
	//首先使用已存在的边构造新边
	while(first_ptr!=NULL && first_ptr->next!=NULL && used_edge_count<edge_threshold){
			if (!successfully_rematched){
//				printf("第一个指针要后移，第二个紧接着后移\n");
				first_ptr = first_ptr->next;
				second_ptr = first_ptr->next;
			}
			//第一个不是空，并且也不是最后一个，因为要配对，最后一个无法配对,如果重构边数够了，就不再匹配重构了
			//选择第一个边
			while(second_ptr != NULL){
			//一次遍历没有结束，就继续
			//选择第二个边
				//开始选取两条边是紧挨着的第一和第二两个边节点
				//保证节点度不变的情况下，重新生成两条边
				//1:一种方式:水平连接
				new_edge1_nodes[0] = first_ptr->from;
				new_edge1_nodes[1] = second_ptr->from;
				new_edge2_nodes[0] = first_ptr->to;
				new_edge2_nodes[1] = second_ptr->to;
//				printf("水平(%d,%d),(%d,%d)变成(%d,%d),(%d,%d)!\n",first_ptr->from, first_ptr->to, second_ptr->from, second_ptr->to,new_edge1_nodes[0],new_edge1_nodes[1],new_edge2_nodes[0],new_edge2_nodes[1]);
				//检查重构的有效性，如果有效就插入新边
				successfully_rematched = check_valid_and_insert(duplicate_network, first_ptr, second_ptr, new_edge1_nodes, new_edge2_nodes);
				if (successfully_rematched){
					printf("水平(%d,%d),(%d,%d)变成(%d,%d),(%d,%d)重构成功!\n",first_ptr->from, first_ptr->to, second_ptr->from, second_ptr->to,new_edge1_nodes[0],new_edge1_nodes[1],new_edge2_nodes[0],new_edge2_nodes[1]);
					record_nonoverlapping_edges(first_ptr, second_ptr, new_edge1_nodes, new_edge2_nodes, ori_non_overlay_file_name, dup_non_overlay_file_name);
					existUpdate = true;
					//假如横向重连有效,则重匹配完成
					//从链表中删除已经完成匹配的两个边节点
					delete_edge_nodes_and_move_ptr(&first_ptr, &second_ptr, &rearranged_edge_list_head);
					//如果新生成的边在原来的不存在边列表中，需要在不存在列表中删除
//					printf("检查是否是不存在的边:(%d,%d),(%d,%d)\n",new_edge1_nodes[0],new_edge1_nodes[1],new_edge2_nodes[0],new_edge2_nodes[1]);
					delete_non_edge(&non_edge_list_head, new_edge1_nodes);
					delete_non_edge(&non_edge_list_head, new_edge2_nodes);
					used_edge_count += 2;
					edge_count -= 2;
//					printf("used_edge_count is %d\n", used_edge_count);
					if (used_edge_count == edge_threshold){
						enough = true;
						printf("算够了，我要跳出\n");
						break;
					}
				}else{
					//2:横向重连无效，选择交叉连接
					//交换端点
					new_edge1_nodes[0] = first_ptr->from;
					new_edge1_nodes[1] = second_ptr->to;
					new_edge2_nodes[0] = second_ptr->from;
					new_edge2_nodes[1] = first_ptr->to;
//					printf("交叉(%d,%d),(%d,%d)变成(%d,%d),(%d,%d)!\n",first_ptr->from, first_ptr->to, second_ptr->from, second_ptr->to,new_edge1_nodes[0],new_edge1_nodes[1],new_edge2_nodes[0],new_edge2_nodes[1]);
					successfully_rematched = check_valid_and_insert(duplicate_network, first_ptr, second_ptr, new_edge1_nodes, new_edge2_nodes);
					if (successfully_rematched){
						printf("交叉(%d,%d),(%d,%d)变成(%d,%d),(%d,%d)重构成功!\n",first_ptr->from, first_ptr->to, second_ptr->from, second_ptr->to,new_edge1_nodes[0],new_edge1_nodes[1],new_edge2_nodes[0],new_edge2_nodes[1]);
						record_nonoverlapping_edges(first_ptr, second_ptr, new_edge1_nodes, new_edge2_nodes, ori_non_overlay_file_name, dup_non_overlay_file_name);
						existUpdate = true;
						//假如匹配成功,删除两个节点
						delete_edge_nodes_and_move_ptr(&first_ptr, &second_ptr, &rearranged_edge_list_head);
						//如果新生成的边在原来的不存在边列表中，需要在不存在列表中删除
//						printf("检查是否是不存在的边:(%d,%d),(%d,%d)\n",new_edge1_nodes[0],new_edge1_nodes[1],new_edge2_nodes[0],new_edge2_nodes[1]);
						delete_non_edge(&non_edge_list_head, new_edge1_nodes);
						delete_non_edge(&non_edge_list_head, new_edge2_nodes);
						used_edge_count += 2;
						edge_count -= 2;
//						printf("used_edge_count is %d\n", used_edge_count);
						if (used_edge_count == edge_threshold){
							enough = true;
							printf("算够了，我要跳出\n");
							break;
						}
					}else{
					   //如果都匹配不上，第二个指针后移一个
	//					printf("后移一位!\n");
						second_ptr = second_ptr->next;
					}
				}
			}

			if (enough){
				break;
			}
		}

		printf("used_edge_count is %d, edge_threshold is %d, non_list length is %d\n",used_edge_count,edge_threshold,count_number(non_edge_list_head));

        //如果重构不足，则用不存在的边对等替换同样数目的已存在的边
		while (used_edge_count<edge_threshold && rearranged_edge_list_head!=NULL && non_edge_list_head!=NULL){
			printf("添加不存在边,used_edge_count is %d\n",used_edge_count);
			//删除一条边
			first_ptr = rearranged_edge_list_head;
			rearranged_edge_list_head = rearranged_edge_list_head->next;
			del_Data(duplicate_network[first_ptr->from].next, first_ptr->to);
			del_Data(duplicate_network[first_ptr->to].next, first_ptr->from);
			//添加一条边
			second_ptr = non_edge_list_head;
			non_edge_list_head = non_edge_list_head->next;
			create(duplicate_network[second_ptr->from].next, second_ptr->to);
			create(duplicate_network[second_ptr->to].next, second_ptr->from);
			used_edge_count++;
			free(first_ptr);
			free(second_ptr);
		}

	   //把剩余的节点资源释放掉
		while(rearranged_edge_list_head!=NULL){
			first_ptr = rearranged_edge_list_head;
			rearranged_edge_list_head = rearranged_edge_list_head->next;
	//    	printf("剩下的边是(%d,%d)\n",first_ptr->from,first_ptr->to);
			free(first_ptr);

		}
        //把剩余的不存在边节点释放
		while (non_edge_list_head!=NULL){
			second_ptr = non_edge_list_head;
			non_edge_list_head = non_edge_list_head->next;
//			printf("不存在剩下的边是(%d,%d)\n",second_ptr->from,second_ptr->to);
			free(second_ptr);
		}

    printf("used_edge_count 最后为:%d\n",used_edge_count);

    //更新拷贝的网络
	if (existUpdate){
		printf("updated!\n");
		//如果确实有边更新再去删除无效边
		//重新配对完毕，清除新网络中所有标识为过时的边
		for (int i=0; i<network_size; i++){
			edge_prior_ptr = duplicate_network[i].next; //先把前指针设置为节点边链表的头指针
			edge_PGuard = edge_prior_ptr->next;

 		    while(edge_PGuard!=NULL){
				if (!edge_PGuard->isNew){
					//如果这个节点是要更新的
					edge_prior_ptr->next = edge_PGuard->next;
					free(edge_PGuard);
					edge_PGuard = edge_prior_ptr->next;
				}else{
					edge_prior_ptr = edge_prior_ptr->next;
					edge_PGuard = edge_PGuard->next;
				}
			}
		}
	}
}




