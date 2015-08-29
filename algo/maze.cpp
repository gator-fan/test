#include <stdio.h>

int n, m, p, q, min = 9999999;
int a[51][51], book[51][51];

void dfs(int x, int y, int step)
{
	int next[4][2] = {{0, 1}, {0, -1}, {1,0}, {-1,0}};
	int tx, ty, k;
	if(x == p && y == q){
		if(step < min) min = step;
		return;
	}

	for(int k = 0; k < 4; ++k){
		tx = x + next[k][0];
		ty = y + next[k][1];

		if(tx < 1 || tx > n || ty < 1 || ty > m) continue;

		if(a[tx][ty] == 0 && book[tx][ty] == 0)
		{
			book[tx][ty] = 1;
			dfs(tx, ty, step+1);
			//book[tx][ty] = 0;
		}
	}

	return ;
}

int main()
{
	int i, j, startx, starty;
	scanf("%d %d\n", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d %d %d %d", 
				&a[i][1], 
				&a[i][2],
				&a[i][3], 
				&a[i][4]
			 );

	scanf("%d %d %d %d", &startx, &starty, &p, &q);
	book[startx][starty] = 1;
	dfs(startx, starty, 0);
	printf("\n%d\n", min);
	return 0;
}
