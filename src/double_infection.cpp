/*
 * infection.cpp
 *
 *  Created on: 2017-8-11
 *      Author: Administrator
 */
#include "total.h"
#include "network/network_basic_ops.h"
#include "network/ER_network.h"
#include "network/SF_network.h"
#include "network/network_overlay_ops.h"
#include "utils/edge_weight.h"
#define PI 3.1415926
int find_number_of_M_nodes(Node network[], Node * node){
	int count = 0;
	for (edge * pGuard=node->next->next; pGuard!=NULL; pGuard=pGuard->next){
//		printf("node number is %d\n",pGuard->data);
       if (network[pGuard->data].type=='M'){
    	   count++;
       }
	}
	return count;
}


int initialize_zero(int *array, int size){
	for(int i=0; i<size; i++){
		array[i] = 0;
	}
	return 0;
}

bool cusp_condition_A(float inst_rate, float a){
	float rd_accept_rate = 0.0;
	float response_rate = 0.0;

	if (0<inst_rate && inst_rate<=a){
		response_rate = 1;
	}else if(a<inst_rate && inst_rate<=1){
		response_rate = 0;
	}else{
		response_rate = 0;
	}
	rd_accept_rate=rand()/(float)(RAND_MAX);
	if (rd_accept_rate <= response_rate){
        return true;
	}else{
        return false;
	}
}

bool cusp_condition_B(float inst_rate, float a, float b){
	float rd_accept_rate = 0.0;
	float response_rate = 0.0;

	if (0<inst_rate && inst_rate<a - b){
		response_rate = 0;
	}else if(a - b<=inst_rate && inst_rate<=1){
		response_rate = 1;
	}else{
		response_rate = 0;
	}
	rd_accept_rate=rand()/(float)(RAND_MAX);
	if (rd_accept_rate <= response_rate){
        return true;
	}else{
        return false;
	}
}

//传播感染过程
void double_layer_infection(Node A[], Node B[], float alpha_A, float r_A, float alpha_B, int r_B, float a, float b, int k_count, int seed[], int network_size, char *file_A)
{
	Infect Old[2*network_size];			//当前已经感染的节点数组，包括A网络和B网络的
	Infect New_A[network_size];			//A网络新感染的节点数组
	Infect New_B[network_size];			//B网络新感染的节点数组
	Infect New_AB[2*network_size];		//A网络和B网络新感染节点的混合数组
	//char file_dir_name[100]; //文件路径名字符数组
	float rd_Infection_A;
	float rd_Recover_A;
	float rd_Infection_B;
	float rd_Recover_B;

	int rd_Add;
	int i;
	int count_Old=0;
	int count_New_A=0;
	int count_New_B=0;
	int count_New_AB=0;
	int count_Recover_A=0;
	int count_Recover_B=0;
	int ct_S_A=0;
	int ct_I_A=0;
	int ct_R_A=0;
	int ct_M_A=0;

	int ct_S_B=0;
	int ct_I_B=0;
	int ct_R_B=0;
    float inst_rate_A=0;
    float inst_rate_B=0;
    //int k_A = 0;
    //int k_B = 0;
    float inst_tre_A=0;
    float inst_tre_B=0;

	edge *p;
	FILE *fp=NULL;

	if (k_count == network_size){
		//保存最终A网络感染节点个数
		fp=fopen(file_A,"a");
		fprintf(fp,"%f %f %7d\n", alpha_A, alpha_B, network_size);
		fclose(fp);
		return;
	}

	for(i=0;i<network_size;i++)
	{
		New_A[i].data=-1;
		New_A[i].type='A';

		New_B[i].data=-1;
		New_B[i].type='B';
	}

	for(i=0;i<2*network_size;i++)
	{
		Old[i].data=-1;
		Old[i].type='U';
	}

	//统计种子感染节点
	for (i=0; i<k_count; i++){
		A[seed[i]].type='I';
		Old[count_Old].data=seed[i];
		Old[count_Old].type='A';
		count_Old++;

		B[seed[i]].type='I';
		Old[count_Old].data=seed[i];
		Old[count_Old].type='B';
		count_Old++;
	}

	while(count_Old>0)
	{
		//检查感染节点，开始感染周边
		for(i=0;i<count_Old;i++)//S态变成A态
		{
			//如果感染节点来自A网络时
			if(Old[i].type=='A')
			{
				p=A[Old[i].data].next->next;
				while(p!=NULL)
				{
					rd_Infection_A=rand()/(float)(RAND_MAX);
					inst_rate_A = alpha_A;
					if(rd_Infection_A<inst_rate_A && A[p->data].type=='S' && p->transmit=='U')
					{
						p->transmit='T';
						A[p->data].info_count++;
						inst_tre_A = float(A[p->data].info_count)/float(A[p->data].degree);  //  接收信息/节点度
						inst_tre_B = float(B[p->data].info_count)/float(B[p->data].degree);  //  接收信息/节点度
						if (cusp_condition_A(inst_tre_A, a)){ // || cusp_condition_B(inst_tre_B, B_a, B_b)
							A[p->data].type='I';
							New_A[count_New_A].data=p->data;
							New_A[count_New_A].type='A';

							count_New_A++;
							if(B[p->data].type=='S')
							{
								B[p->data].type='I';
								New_B[count_New_B].data=p->data;
								New_B[count_New_B].type='B';
								count_New_B++;
							}
						}
					}
					p=p->next;
				}
			}
			//如果感染节点来自B网络时
			if(Old[i].type=='B')
			{
				p=B[Old[i].data].next->next;
				while(p != NULL)
				{
					rd_Infection_B=rand()/(float)(RAND_MAX);
				    inst_rate_B= alpha_B;
					if(rd_Infection_B<inst_rate_B && B[p->data].type=='S' && p->transmit=='U')
					{
						p->transmit='T';
						B[p->data].info_count++;
						inst_tre_A = float(A[p->data].info_count)/float(A[p->data].degree);  //  接收信息/节点度
						inst_tre_B = float(B[p->data].info_count)/float(B[p->data].degree);  //  接收信息/节点度
						if (cusp_condition_B(inst_tre_B , a, b)){ //cusp_condition_A(inst_tre_A, A_a) ||
							B[p->data].type='I';
							New_B[count_New_B].data=p->data;
							New_B[count_New_B].type='B';
							count_New_B++;
							if(A[p->data].type=='S')
							{
								A[p->data].type='I';
								New_A[count_New_A].data=p->data;
								New_A[count_New_A].type='A';
								count_New_A++;
							}
						}
					}
					p=p->next;
				}
			}
		}

		for(i=0;i<count_Old;i++) //A态变成R态
		{
			if(Old[i].type=='A')
			{
				rd_Recover_A=rand()/(float)(RAND_MAX);
				if(rd_Recover_A<r_A)
				{
					A[Old[i].data].type='R';
					Old[i].data=Old[count_Old-1].data;
					Old[i].type=Old[count_Old-1].type;
					Old[count_Old-1].data=-1;
					Old[count_Old-1].type='U';
					count_Recover_A++;
					i--;
					count_Old--;
				}
			}

			if(Old[i].type=='B')
			{
				rd_Recover_B=rand()/(float)(RAND_MAX);
				if(rd_Recover_B<r_B)
				{
					B[Old[i].data].type='R';
					Old[i].data=Old[count_Old-1].data;
					Old[i].type=Old[count_Old-1].type;

					Old[count_Old-1].data=-1;
					Old[count_Old-1].type='U';

					count_Recover_B++;
					i--;
					count_Old--;
				}
			}
		}


		for(i=0;i<count_New_A;i++)
		{
			New_AB[i].data=New_A[i].data;
			New_AB[i].type=New_A[i].type;
		}

		for(i=0;i<count_New_B;i++)
		{
			New_AB[count_New_A+i].data=New_B[i].data;
			New_AB[count_New_A+i].type=New_B[i].type;
		}

		count_New_AB=count_New_A+count_New_B;
		while(count_New_AB>0)
		{
			rd_Add=rand()%(count_New_AB);
			Old[count_Old].data=New_AB[rd_Add].data;
			Old[count_Old].type=New_AB[rd_Add].type;

			New_AB[rd_Add].data=New_AB[count_New_AB-1].data;
			New_AB[rd_Add].type=New_AB[count_New_AB-1].type;

			New_AB[count_New_AB-1].data=-1;
			New_AB[count_New_AB-1].type='U';

			count_New_AB--;
			count_Old++;
		}
		count_New_A=0;
		count_New_B=0;
	}

	for(i=0;i<network_size;i++)
	{
		if(A[i].type=='S')
		{
			ct_S_A++;
		}
		if(A[i].type=='I')
		{
			ct_I_A++;
		}
		if(A[i].type=='R')
		{
			ct_R_A++;
		}
		if(A[i].type=='M')
		{
			ct_M_A++;
		}

		if(B[i].type=='S')
		{
			ct_S_B++;
		}
		if(B[i].type=='I')
		{
			ct_I_B++;
		}
		if(B[i].type=='R')
		{
			ct_R_B++;
		}
	}
	//保存最终A网络感染节点个数
	fp=fopen(file_A,"a");
	fprintf(fp,"%f %f %7d\n", alpha_A, alpha_B, ct_R_A );
	fclose(fp);
}

int select_seeds(int seed_count, int seed[], int network_size){
	int RandNum;
	int i, flag = 0, t=0;
	int MIN = 0;
	int MAX = network_size-1;
	if (seed_count == network_size){
        for(i=0; i<network_size; i++){
        	seed[i] = i;
        }
        return 0;
	}
	while(1)
	{
		flag = 0;
		if(t == seed_count)
			break;

		RandNum = (rand()%(MAX - MIN)) + MIN;
		for(i = 0; i < t; i++)
		{
			if(seed[i] == RandNum)
				flag = 1;
		}
		if(flag != 1)
		{
			seed[t] = RandNum;
			t++;
		}
	}
	return 0;
}

void init_threshold(Node info_network[],  int network_size)
{
	int i;
	edge *eg;

	for(i=0;i<network_size;i++)
	{
		info_network[i].type='S';
		info_network[i].info_count = 0;
		eg=info_network[i].next->next;
		while(eg)
		{
			eg->transmit='U';
			eg=eg->next;
		}
	}
}

void calculate_combined_degree_distribution(Node network1[], Node network2[], int network_size, int max_degree, char *combined_degree_file){
    int combined_degree[max_degree+1][max_degree+1] = {0};

   	for (int i=0; i<=max_degree; i++){
   		for (int j=0; j<=max_degree; j++){
   			combined_degree[i][j] = 0;
   		}
   	}

	FILE *fp;
    char file_dir_name[100];
    for (int i=0; i<network_size; i++){
	    combined_degree[network1[i].degree][network2[i].degree] += 1;
    }

    memset(file_dir_name, 0, 100);
   	sprintf(file_dir_name, combined_degree_file);
   	fp=fopen(file_dir_name,"w");

   	for (int i=0; i<=max_degree; i++){
   		for (int j=0; j<=max_degree; j++){
            if (combined_degree[i][j]!=0){
            	fprintf(fp,"%d %d %f\n", i, j, (float)combined_degree[i][j]/(float)network_size);
//            	printf("%d %d %f\n", i, j, (float)combined_degree[i][j]/(float)network_size);
            }
   		}
   	}
   	fclose(fp);
}

void save_degree_into_file(char *file, char *file_distribution, Node network[], int network_size)
{
	FILE *fp, *fp1;

		int distri[network_size] = {0};
		if((fp=fopen(file,"w"))==NULL || (fp1=fopen(file_distribution,"w"))==NULL) {
			printf("weight distribution File cannot be opened\n");
		}else{
			//写出每一条边的端点对
			//写入网络大小
			for (int i=0; i<network_size; i++){
				distri[network[i].degree]++;
				fprintf(fp, "%d\n", network[i].degree);
			}

			for (int i=0; i<network_size; i++){
				if (distri[i]){
					fprintf(fp1, "%d %f\n", i, (float)distri[i]/(float)network_size);
				}
			}
		}
		fclose(fp);
		fclose(fp1);

}


int main(int argc, char *argv[])
{
	FILE *fp;
	int network_size = 10000;//
	int total_edge_count1=0,  total_edge_count2= 0; //

    int max_degree = 0;
    int ave_degree = 10;
    //int start_x = 0;
    //int end_x = 0;
    int B_threshold=0;
    int flag = atoi(argv[1]);  //初始创建网络和度分布的标志，若是0表示新建，是1表示读取已存在的数据
    int seed_count = atoi(argv[2]);
	int A = atoi(argv[3]);
	int B = atoi(argv[4]);
	float a = A*0.01;
    float b = B*0.01;
//	int degree_weight = atoi(argv[7]); //SF网络参数
//    double v = degree_weight*0.1;

    //printf("c is %d", c); //ER
	//printf("degree_weight is %d", degree_weight); // SF
	float p = (float)ave_degree/(float)network_size;

	char file_dir_name[100];
	Node A_info_network[network_size]; //网络节点数组
	Node B_info_network[network_size]; //网络节点数组

	edge_element_t *A_info_edge_list = NULL;  //网络边链表
	edge_element_t* B_info_edge_list = NULL;  //网络边链表
	srand((unsigned)time(NULL));//重设随机数

	init_Node(A_info_network, network_size);
	init_Node(B_info_network, network_size);
	int max_degree_1 = 0;
	int max_degree_2 = 0;
    //生成ER网络
	char filename[100];
	char filename1[100];

	sprintf(file_dir_name, "data/%d", B_threshold); //ER
//	sprintf(file_dir_name, "data/%d", degree_weight); //SF

	if (mkdir(file_dir_name,0775))//如果不存在就用mkdir函数来创建
	{
		printf("creat dir failed!!!\n");
	}

	if (flag==0){
	    total_edge_count1 = ER_Model(A_info_network, p, network_size, &A_info_edge_list); //ER
//		degree_Seq(A_info_network, v, network_size);
//		total_edge_count1 = SF_Model(A_info_network, network_size); //SF
		printf("total_edge_count1 is %d\n", total_edge_count1);
		sprintf(file_dir_name, "data/%d/ER_A_info_network_a_%.2f_b_%.2f.txt", B_threshold, a, b);//ER
//		sprintf(file_dir_name, "data/%d/SF_A_info_network_TB_%d_B_%d_v_%d.txt", degree_weight, B_threshold, B, degree_weight);//SF
		save_network_into_file(A_info_network,  network_size, file_dir_name);
		sprintf(file_dir_name, "data/%d/ER_A_info_network_degree_a_%.2f_b_%.2f.txt", B_threshold, a, b);//ER
//		sprintf(file_dir_name, "data/%d/SF_A_info_network_degree_TB_%d_B_%d_v_%d.txt", degree_weight, B_threshold, B, degree_weight);
        max_degree_1 = save_network_degree_distribution(A_info_network, network_size, file_dir_name);

        total_edge_count2 = ER_Model(B_info_network, p, network_size, &B_info_edge_list);//ER
//		degree_Seq(B_info_network, v, network_size);
//		total_edge_count2 = SF_Model(B_info_network, network_size);//SF

		printf("total_edge_count2 is %d\n", total_edge_count2);
		sprintf(file_dir_name, "data/%d/ER_B_info_network_a_%.2f_b_%.2f.txt",B_threshold, a, b);//ER
//		sprintf(file_dir_name, "data/%d/SF_B_info_network_TB_%d_B_%d_v_%d.txt", degree_weight, B_threshold, B, degree_weight);//SF
		save_network_into_file(B_info_network, network_size, file_dir_name);
		sprintf(file_dir_name, "data/%d/ER_B_info_network_degree_a_%.2f_b_%.2f.txt",B_threshold, a, b);//ER
//		sprintf(file_dir_name, "data/%d/SF_B_info_network_degree_TB_%d_B_%d_v_%d.txt",degree_weight, B_threshold, B, degree_weight);//SF
		max_degree_2 = save_network_degree_distribution(B_info_network,  network_size, file_dir_name);

		sprintf(filename, "data/%d/ER_A_degree_list_a_%.2f_b_%.2f.txt",B_threshold, a, b);//ER
	    sprintf(filename1, "data/%d/ER_A_degree_distribution_a_%.2f_b_%.2f.txt",B_threshold, a, b);//ER
//		sprintf(filename, "data/%d/SF_A_degree_list_TB_%d_B_%d_v_%d.txt", degree_weight, B_threshold, B, degree_weight);
//		sprintf(filename1, "data/%d/SF_A_degree_distribution_TB_%d_B_%d_v_%d.txt", degree_weight, B_threshold, B, degree_weight);
		save_degree_into_file(filename, filename1, A_info_network, network_size);

		sprintf(filename, "data/%d/ER_B_degree_list_a_%.2f_b_%.2f.txt",B_threshold, a, b);//ER
		sprintf(filename1, "data/%d/ER_B_degree_distribution_a_%.2f_b_%.2f.txt",B_threshold, a, b);//ER
//		sprintf(filename, "data/%d/SF_B_degree_list_TB_%d_B_%d_v_%d.txt", degree_weight, B_threshold, B, degree_weight);//SF
//		sprintf(filename1, "data/%d/SF_B_degree_distribution_TB_%d_B_%d_v_%d.txt", degree_weight, B_threshold, B, degree_weight);//SF
		save_degree_into_file(filename,filename1,B_info_network, network_size);

		if (max_degree_1 >= max_degree_2){
			max_degree = max_degree_1;
		}else{
			max_degree = max_degree_2;
		}
		sprintf(file_dir_name, "data/%d/ER_combined_degree.txt", B_threshold);//ER度分布
//		sprintf(file_dir_name, "data/%d/SF_combined_degree_TB_%d_B_%d_v_%d.txt", degree_weight, B_threshold, B, degree_weight);//SF度分布
		calculate_combined_degree_distribution(A_info_network, B_info_network, network_size, max_degree, file_dir_name);
	}else{
		sprintf(file_dir_name, "data/%d/ER_A_info_network_a_%.2f_b_%.2f.txt", B_threshold, a, b);//ER
//		sprintf(file_dir_name, "data/%d/SF_A_info_network_TB_%d_B_%d_v_%d.txt", degree_weight, B_threshold, B, degree_weight);//SF

		total_edge_count1 = read_network_from_file(file_dir_name, A_info_network);
		printf("total_edge_count1 is %d\n", total_edge_count1);
		sprintf(file_dir_name, "data/%d/ER_B_info_network_a_%.2f_b_%.2f.txt", B_threshold, a, b);//ER
//		sprintf(file_dir_name, "data/%d/SF_B_info_network_TB_%d_B_%d_v_%d.txt", degree_weight, B_threshold, B, degree_weight);//SF
		total_edge_count2 = read_network_from_file(file_dir_name, B_info_network);
		printf("total_edge_count2 is %d\n", total_edge_count2);

	}

//	//种子数设置为10，即rho0=0.001
	printf("seed_count is %d\n", seed_count);
	int seed_array[seed_count] = {0};
	int i,index_a,index_b;

	memset(filename, 0, 100);
	sprintf(filename, "data/%d/ER_Final_R_A_a_%.2f_b_%.2f_seed_%d.txt", B_threshold, a, b, seed_count);//ER
	//sprintf(filename, "data/%d/SF_Final_R_A_TA_%d_TB_%d_A_%d_B_%d_seed_%d_v_%d.txt", degree_weight, A_threshold, B_threshold, A, B, seed_count, degree_weight);//SF
	fp=fopen(filename,"w");
	fclose(fp);

	for(i=0; i<=1000; i++)
	{
		printf("i is %d\n", i);
		for (index_b=0; index_b<=100; index_b++)//传播速率，上下两层网络传播速率保持一致
		{
			index_a = index_b;
			init_threshold(A_info_network,  network_size);
			init_threshold(B_info_network,  network_size);
			select_seeds(seed_count, seed_array, network_size);
			double_layer_infection(A_info_network, B_info_network, (float)index_a/(float)100,  1, (float)index_b/(float)100, 1, a, b, seed_count, seed_array, network_size, filename);
		}
	}

    return 0;
}
