/*
 * SF_network.cpp
 *
 *  Created on: 2017-7-16
 *      Author: Administrator
 */

#include "total.h"
#include "network/SF_network.h"
#include "network/network_basic_ops.h"

void degree_Seq(Node SF[], double lambda, int SF_NETWORK_SZIE)
{
	int K;
	int i,j;
	int u;
	float h;
	double seqence[SF_NETWORK_SZIE/2];  //
	double CDD[SF_NETWORK_SZIE/2];      //
	double zeta=0;   //
	double rd;
	double rd_1;
    double mean_k=0;
    int max_index = 0;
    char filename[100];
    K=100;
    int degree_distribution[SF_NETWORK_SZIE] = {0}; //瀹氫箟搴﹀垎甯�
    double degree_dis = 0;
   	FILE *fp;
    int min_degree = 4;
	for(i=0; i<SF_NETWORK_SZIE/2; i++)
	{
		seqence[i]=0;
	}

	printf("K=%d\n",K);

	for(i=min_degree; i<=K; i++)
	{//i=3
		seqence[i]=pow(i*1.0,-lambda);
	    zeta=zeta+seqence[i];
	}

/*	for(i=3;i<=K;i++)
	{
		printf("\nseqence[%d]=%f",i,seqence[i]);
	}*/

	printf("zeta=%f\n",zeta);
	mean_k=0;
	for(i=min_degree;i<=K;i++)
	{
		seqence[i]=(seqence[i])/zeta;
		mean_k += i*seqence[i];
	}

/*	for(i=3;i<=K;i++)
	{
		printf("\nseqence[%d]=%f",i,seqence[i]);
	}*/

	for(i=0;i<=SF_NETWORK_SZIE/2;i++)
	{
		CDD[i]=0;
	}

	for(i=min_degree;i<=K;i++)
	{
		CDD[i]=CDD[i-1]+seqence[i];
	}

/*	for(i=3;i<=K;i++)
	{
		printf("\nCDD[%d]=%f",i,CDD[i]);
	}
*/
    printf("mean_k is %f\n", mean_k);
	//
	srand((unsigned)time(NULL));//
	for(i=0;i<SF_NETWORK_SZIE;i++)
	{
		rd=(float)rand()/(RAND_MAX);
		for(j=min_degree;j<=K;j++)
		{
			if(rd<CDD[j])
			{
				h=(((double)j)/((double)mean_k))*((double)10);
				u=(int)h;
				rd_1=(float)rand()/(RAND_MAX);
				if(rd_1<h-u)
				{
					SF[i].degree=u+1;
				}
				else
				{
					SF[i].degree=u;
				}
				if (max_index<SF[i].degree){
					max_index = SF[i].degree;
				}
				degree_distribution[SF[i].degree]++;
				break;
			}
		}
	}

//	sprintf(filename, "degree_sf_v_%.2f.txt",lambda);
//	fp=fopen(filename,"w");
//	for (i=1; i<=max_index; i++){
//	    degree_dis = (double)degree_distribution[i]/(double)10000;
//		fprintf(fp,"%f\n",degree_dis);
//	}
//	fclose(fp);
}

//
int SF_Model(Node SF[], int SF_NETWORK_SZIE)
{
	int count=0;	//
	int total_edge_count = 0; //
	int i,j;

//	int ct1,ct2;

	int m,n;

	int seq[SF_NETWORK_SZIE*10];

	int temp;

//	ct1=0;
//	ct2=0;

	for(i=0;i<SF_NETWORK_SZIE;i++)
	{
		for(j=0;j<SF[i].degree;j++)
		{
			seq[count++]=i;
		}
	}
	for(i=0;i<count;i++)
	{
	//	printf("%4d",seq[i]);
	}
	//printf("count=%d,seq[count]=%d",count,seq[count-1]);

	j=count;


	while(j>1)
	{
		m=rand()%j;
		n=rand()%j;
	//	printf("---------------------------------\n");
		while(m==n || find_Data(SF[seq[m]].next,seq[n]) || find_Data(SF[seq[n]].next,seq[m]) || seq[m]==seq[n])
		{
			m=rand()%j;
			n=rand()%j;
//			printf("---------\n");
		}
//				printf("\nj=%d",j);

		create(SF[seq[m]].next,seq[n]);
		create(SF[seq[n]].next,seq[m]);
		total_edge_count++;
		temp=seq[m];
		seq[m]=seq[j-1];
		seq[j-1]=temp;

		j--;

		temp=seq[n];
		seq[n]=seq[j-1];
		seq[j-1]=temp;

		j--;
	}
	//printf("\nj=%d\n",j);
//	for(i=0;i<SF_NETWORK_SZIE;i++)
//	{
//		print(SF[i].next,type);
//	}
	return total_edge_count;
}
