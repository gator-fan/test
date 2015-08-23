#include <stdio.h>

int a[51][51];
int book[51][51], n, m, sum;

void dfs(int x, int y)
{
	int next[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0}};
	int k, tx, ty;

	for(k = 0; k <= 3; ++k)
	{
		tx = x + next[k][0];
		ty = y + next[k][1];
		if(tx < 1 || tx > n || ty < 1 || ty > m) continue;
		if(a[tx][ty] > 0 && book[tx][ty] == 0){
			sum++;
			book[tx][ty] = 1;
			dfs(tx, ty);
			book[tx][ty] = 0;
		}
	}
	return;
}

int main()
{
	int i, j, startx, starty;
	scanf("%d %d %d %d", &n, &m, &startx, &starty);
	for(i = 1; i <= n; i++)
		scanf("%d %d %d %d %d %d %d %d %d %d", 
				&a[i][1], 
				&a[i][2],
				&a[i][3], 
				&a[i][4],
				&a[i][5],
				&a[i][6], 
				&a[i][7],
				&a[i][8], 
				&a[i][9],
				&a[i][10]
				);

	book[startx][starty] = 1;
	sum = 1;
	dfs(startx, starty);
	printf("%d\n", sum);
	return 0;
}
