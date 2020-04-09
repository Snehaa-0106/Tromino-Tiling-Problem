#include<stdio.h>
#include<stdlib.h>
int ** board;
int cnt=0;

void cal_tromino(int x1,int y1,int x2,int y2,int x3, int y3) {
	cnt++;
	board[x1][y1] = cnt;
	board[x2][y2] = cnt;
	board[x3][y3] = cnt;
}
int tromino_recursive(int n,int x,int y) {
	int i,j,r,c;
	if(n == 2){
		cnt++;
		for(i=0;i<n;i++) {
			for(j=0;j<n;j++){
				if(board[x+i][y+j]==0)
					board[x+i][y+j]=cnt;
			}
		}
		return 0;
	}
	for(i=x;i<n;i++) {
		for(j=y;j<n;j++){
			if(board[i][j]!=0) {
				r=i; c=j;
			}
		}
	}
	if(r< x + n/2 &&c < y+ n/2) {
		cal_tromino(x+n/2,y+ (n/2) - 1,x+n/2,y+n/2,x+n/2-1,y+n/2);
	}
	else if(r>=x+ n/2 && c < y + n/2) {
		cal_tromino(x+n/2,y+ (n/2) - 1,x+n/2,y+n/2,x+n/2-1,y+n/2-1);
	}
	else if(r < x + n/2 && c >= y + n/2) {
		cal_tromino(x+(n/2) - 1,y+ (n/2),x+(n/2),y+n/2,x+(n/2)-1,y+(n/2) -1);
	}
	else if(r >= x + n/2 && c >= y + n/2) {
		cal_tromino(x+(n/2) -1, y+ (n/2),x+(n/2),y+(n/2) -1,x+(n/2)-1,y+(n/2)-1);
	}
	tromino_recursive(n/2, x, y+n/2);
	tromino_recursive(n/2, x, y);
	tromino_recursive(n/2, x+n/2, y);
	tromino_recursive(n/2, x+n/2, y+n/2);
	return 0;
}
void tile(int size) {
  	tromino_recursive(size,0,0);
}
int main()
{
	int i,j,k,r,c,size,lrx[100],llx[100],urx[100],ulx[100],lr,ur,ul,ll,s[100][100];
	printf("Please enter size of board (0 to quit):");
	scanf("%d",&size);
	while(size!=0)
	{
		lr=0;
		ll=0;
		ur=0;
		ul=0;
		printf("Please enter coordinates of missing square (separate by a space):");
		scanf("%d %d",&r,&c);
		int ** array = (int**)malloc(size*sizeof(int *));
		for(i = -1;i <=size; i++)
		{
		    array[i] = (int*)malloc(size*sizeof(int));
			for(j = -1; j <=size; j++)
			{
				array[i][j] = 0;
		    }
		}
		array[r][c]=-1;
		board=array;
		tile(size);
		for(k=1;k<=cnt;k++)
		{
			for(i=0;i<size;i++)
			{
				for(j=0;j<size;j++)
				{
					if(board[i][j+1]==k&&board[i+1][j]==k&&board[i][j]==k)
					{
						llx[ll]=k;
						ll++;
					}
					else if(board[i][j-1]==k&&board[i+1][j]==k&&board[i][j]==k)
					{
						lrx[lr]=k;
						lr++;
					}
					else if(board[i-1][j]==k&&board[i][j+1]==k&&board[i][j]==k)
					{
						urx[ur]=k;
						ur++;
					}
					else if(board[i][j-1]==k&&board[i-1][j]==k&&board[i][j]==k)
					{
						ulx[ul]=k;
						ul++;
					}
				}
			}
		}
		for(i=0;i<size;i++)
			for(j=0;j<size;j++)
				if(board[i][j]==-1)
					s[i][j]=-1;
		for(k=0;k<ll;k++)
			for(i=0;i<size;i++)
				for(j=0;j<size;j++)
					if(board[i][j]==llx[k])
						s[i][j]=-2;
		for(k=0;k<lr;k++)
			for(i=0;i<size;i++)
				for(j=0;j<size;j++)
					if(board[i][j]==lrx[k])
						s[i][j]=-3;
		for(k=0;k<ul;k++)
			for(i=0;i<size;i++)
				for(j=0;j<size;j++)
					if(board[i][j]==ulx[k])
						s[i][j]=-4;
		for(k=0;k<ur;k++)
			for(i=0;i<size;i++)
				for(j=0;j<size;j++)
					if(board[i][j]==urx[k])
						s[i][j]=-5;
		for(j=size-1;j>=0;j--)
		{
			for(i=0;i<size;i++)
			{
				if(s[i][j]==-1)
					printf("MS ");
				else if(s[i][j]==-2)
					printf("LL ");
				else if(s[i][j]==-3)
					printf("UL ");
				else if(s[i][j]==-4)
					printf("UR ");
				else if(s[i][j]==-5)
					printf("LR ");
			}
			printf("\n");
		}
		printf("Enter the size:");
		scanf("%d",&size);
	}
	return 0;
}
