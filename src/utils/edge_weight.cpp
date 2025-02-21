/*
 * edge_weight.cpp
 *
 *  Created on: 2018-12-20
 *      Author: Administrator
 */

#include "utils/edge_weight.h"

void assign_weight_to_edge(Node ER[], vector<int> *edge_weight_vector, int M){
	int i;
	int cur_weight = 0; //��ǰҪ��ֵ��Ȩ��
	edge *eg, *eg1;
	for(i=0;i<M;i++)
	{
		//��ÿ���߸�Ȩ��
		eg=ER[i].next->next;
		while(eg)
		{
			//���ÿ�����Ƿ���Ȩ��
			//�����(id1, id2)��Ȩ�أ����(id2, id1)Ҳ��Ȩ��
			if (eg->weight < 0){
				cur_weight = edge_weight_vector->at(0);
				edge_weight_vector->erase(edge_weight_vector->begin());
				eg->weight = cur_weight;
//				printf("��(%d , %d)Ȩ����%f\n", i, eg->data, eg->weight);
				eg1 = ER[eg->data].next->next;
				while(eg1){
                   if (eg1->data == i){
                	   eg1->weight = cur_weight;
                   }
                   eg1=eg1->next;
				}
			}
			eg=eg->next;
		}
	}
}

