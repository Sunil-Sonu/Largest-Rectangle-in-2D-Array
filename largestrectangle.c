
#include <stdio.h>
#include <malloc.h>

#define max(a,b) a>b?a:b;

int getLargestRect(int *arr, int m, int n)
{
	int *dp, i = 0, j = 0, k = 0,count=0;
	int maxsum = 0, currsum;
	int maxleft = 0, maxright = 0;
	int maxup = 0, maxdown = 0; 
	int up = 0, down = 0;
	while (count < m){
		dp = (int *)calloc(sizeof(int), n);
		for (i = count; i < m; i++){
			{
				k = 0; currsum = 0; maxup = 0; maxdown = 0;
				
// ======= CONSTRUCTION OF DP TABLE ==========//
				for (j = 0; j < n; j++)
					dp[k++] += *(arr + j*m + i);
		
// ======= Kadane's algorithm  ==============//
			int max_here = *(dp), max_ending = *(dp);
			for (int l = 1; l < n; l++){
				max_ending = max(*(dp + l), max_ending + *(dp + l));
				if (max_ending == *(dp + l))
					maxup = l;
				max_here = max(max_ending, max_here);
				if (max_here == max_ending)
					maxdown = l;
			}
		
//========= Find current sum of these elements========///
			for (int l = maxup; l <= maxdown; l++)
				currsum += *(dp + l);
		
//========= If current sum is greater than maximum sum, then we update the values =========//
			if (currsum > maxsum){
				maxleft = count; maxright = i;
				up = maxup; down = maxdown;
			    maxsum = currsum;
				}
			}
		}
		count++;
	}
	maxsum = 0;
	for (i = up; i <= down; i++)
		for (j = maxleft; j <= maxright; j++)
			maxsum += *(arr + i*m + j);
	free(dp);
	return maxsum;
}
