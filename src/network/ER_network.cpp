/*
 * ER_network.cpp
 *
 *  Created on: 2017-7-16
 *      Author: Administrator
 */

#include "total.h"
#include "network/ER_network.h"
#include "network/network_basic_ops.h"

/*******************************************
 * 鐢熸垚ER缃戠粶
 * Node ER[]:瑕佺敓鎴愮殑ER缃戠粶鑺傜偣闆嗗悎
 * float p:ER缃戠粶杈圭殑鐢熸垚姒傜巼
 * int network_size:缃戠粶鑺傜偣鏁�
 * char ch[]:瀛楄妭鏁扮粍
 * edge_element_t **edge_list:瀛樺偍鐨勫崟鍚戣竟鍒楄〃鐨勫湴鍧�锛屾寚閽堢殑鎸囬拡
 *******************************************/
int ER_Model(Node ER[], float p, int network_size, edge_element_t **edge_list)
{
	int total_edge_count = 0;
	float rd ;
	int degree[network_size] = {0};
	*edge_list = NULL;
	edge_element_t* edge_list_tail = NULL;
	edge_element_t* pGuard = NULL;
	for(int i = 0; i < network_size ; i++)
	{
		for(int j =i+1 ; j < network_size ; j++)
		{
			rd = (float)rand()/(RAND_MAX);
			if(rd < p)
			{
				create(ER[i].next, j);
				create(ER[j].next, i);
				total_edge_count++;
			}else{

			}
		}
	}
	for(int i = 0 ; i < network_size ; i++)
	{
		degree[i] = length(ER[i].next);
		ER[i].degree=degree[i];
	}
    return total_edge_count;
}

/*******************************************
 * 鐢熸垚ER缃戠粶,杩斿洖鎵�鏈夎竟鐨勫垪琛紙鍗曞悜鐨勶級锛屽悓鏃惰繑鍥�1-Q姣斾緥鐨勪笉閲嶅鐨勮竟
 * 鐢熸垚鐨勮竟鏁版渶澶氭槸(N*(N-1)/2)*p
 * Node ER[]:瑕佺敓鎴愮殑ER缃戠粶鑺傜偣闆嗗悎
 * float p:ER缃戠粶杈圭殑鐢熸垚姒傜巼
 * int network_size:缃戠粶鑺傜偣鏁�
 * char ch[]:瀛楄妭鏁扮粍
 * edge_element_t **edge_list:瀛樺偍鐨勫崟鍚戣竟鍒楄〃鐨勫湴鍧�锛屾寚閽堢殑鎸囬拡
 * float Q:缃戠粶杈归噸澶嶆瘮渚�
 * edge_element_t **non_existent_edge_list:鏈繛鎺ョ殑杈归摼琛紝闀垮害涓�(N*(N-1)/2)*p
 *******************************************/
int ER_Model_with_Q(Node ER[], float p, int network_size, char ch[], edge_element_t **edge_list, float Q, edge_element_t **non_existent_edge_list)
{
	int total_edge_count = 0;
	//ER_NETWORK_SIZE鏄綉缁滅偣鏁�
	//FILE *fp1;
	float rd;
	*edge_list = NULL;
	*non_existent_edge_list = NULL;
	edge_element_t* edge_list_tail = NULL;
	edge_element_t* pGuard = NULL;
	edge_element_t* non_pGuard = NULL;
	edge_element_t* non_edge_list_tail = NULL;
	int non_existent_edge_amount = (1-Q)*p*(network_size*(network_size-1))/2;
	printf("non_existent_edge_amount is %d, network_size is %d\n", non_existent_edge_amount, network_size);
	int non_existent_edge_counter = 0;
//	int k = 0;
	//鎸夋鐜噋杩涜杈圭殑杩炴帴
	for(int i = 0; i < network_size ; i++)
	{
		for(int j =i+1 ; j < network_size ; j++)
		{
			rd = (float)rand()/(RAND_MAX);
			//fprintf(fp1,"%f\n",rd);
			if(rd < p)
			{
				create(ER[i].next, j);
				create(ER[j].next, i);
				total_edge_count++;
//				printf("绗�%d鏉¤竟瀵�:(%d,%d),(%d,%d)\n",total_edge_count,i,j,j,i);
				pGuard = (edge_element_t*)malloc(sizeof(edge_element_t));
				pGuard->from = i;
				pGuard->to = j;
                if (*edge_list == NULL){
                    //鍋囧寮�濮嬭竟閾捐〃鏄┖锛屽垯涓嶆柇鎻掑叆閾捐〃灏鹃儴
                	*edge_list = pGuard;
                	edge_list_tail = pGuard;
                	edge_list_tail->next = NULL;
                }else{
                	edge_list_tail->next = pGuard;
                	edge_list_tail = pGuard;
                	edge_list_tail->next = NULL;
                }
			}else{
                //涓嶄細瀛樺湪鐨勮竟锛岃褰�,瀛樺偍non_existent_edge_amount涓�
                if (non_existent_edge_counter < non_existent_edge_amount){
                	non_pGuard = (edge_element_t*)malloc(sizeof(edge_element_t));
					non_pGuard->from = i;
					non_pGuard->to = j;
					//閲囩敤鍚�
                    if (*non_existent_edge_list == NULL){
                    	*non_existent_edge_list = non_pGuard;
                    	non_pGuard->pre = NULL;
						non_edge_list_tail = non_pGuard;
						non_edge_list_tail->next = NULL;
                    }else{
                    	non_edge_list_tail->next = non_pGuard;
                    	non_pGuard->pre = non_edge_list_tail;
                    	non_edge_list_tail = non_pGuard;
                    	non_edge_list_tail->next = NULL;
                    }
                    non_existent_edge_counter++;
                }
			}
		}
	}
    return total_edge_count;
}

