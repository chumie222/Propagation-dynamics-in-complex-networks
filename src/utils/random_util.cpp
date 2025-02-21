/*
 * random_number.cpp
 *
 *  Created on: 2017-7-16
 *      Author: Administrator
 */
#include "utils/random_util.h"

void random_permutation(int number, int a[]){
	int i,j;
	srand(time(0));
	for(i=0;i<number;i++)
	{
		a[i]=rand()%number;
		int flag=1;
		while(flag==1)// 你的这里可能还会产生重复的数，这里确保产生的数不再重复，只要有重复的就在随机新的数。
		{
			for(j=0;j<i;j++)
				if(a[i]==a[j])
					break;
			if(j<i)
				a[i]=rand()%number;
			if(j==i)
				flag=0;
		}
	}
}


