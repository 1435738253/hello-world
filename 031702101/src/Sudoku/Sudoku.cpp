#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;
int m, n;
int a[2000][2000];
FILE* fp1;
FILE* fp2;
bool check_gong(int n, int x, int row, int col)//验证宫
{
	int i, j;
	int r = n / m;
	int c = n % m;
	r = r / row * row;
	c = c / col * col;
	for (i = r; i < (r + row); i++)
	{
		for (j = c; j < (c + col); j++)
		{
			if (a[i][j] == x) return false;
		}
	}
	return true;
}

bool check(int n,int x)//行和列的验证
{
	int row = n / m;
	int col = n % m;
	int i, j, k=1;
	for (i = 0; i < m; i++)//验证行
	{
		if (a[row][i] == x) return false;
	}
	for(j = 0; j<m; j++)//验证列
	{
		if (a[j][col] == x) return false;
	}
	//判断是否需要验证宫
	if (m == 4) k = check_gong(n, x, 2, 2);
	else if (m == 6) k = check_gong(n, x, 2, 3);
	else if (m == 8) k = check_gong(n, x, 4, 2);
	else if (m == 9) k = check_gong(n, x, 3, 3);
	if(k==1) return true;
	else return false;
}

void output()//输出函数 
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			fprintf(fp2, "%d", a[i][j]);
			if (j < (m - 1)) fprintf(fp2, " ");
		}
		fprintf(fp2, "\n");
	}
}

void backtrace(int n)//回溯法进行填数
{
	int i;
	if (n == m * m)//满了就完成填数
	{
		output();//输出结果
		return;
	}
	int row = n / m;
	int col = n % m;
	if (a[row][col] == 0)
	{
		for (i = 1; i <= m; i++)
		{
			if (check(n,i))//可以填数
			{
				a[row][col] = i;
				backtrace(n + 1);//进入下一层函数
				a[row][col] = 0;//回溯
			}
		}
	}
	else
	{
		backtrace(n + 1);//进入下一层函数
	}
}

int main(int argc, char* argv[])
{
#pragma warning(disable:4996)
	int i, j, k;
	m = atoi(argv[2]);
	n = atoi(argv[4]);
	char* in = argv[6];
	char* out = argv[8];
	fp1 = fopen(in, "r");//输入
	fp2 = fopen(out, "w");//输出
	if (fp1 == NULL) return -1;
	if (fp2 == NULL) return -1;
	fclose(fp2);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)//输入 
		{
			for (k = 0; k < m; k++)
			{
				fscanf(fp1, "%d", &a[j][k]);//存到a数组
			}
		}
		fp2 = fopen(out, "a");
		backtrace(0);
		if (n > 0) fprintf(fp2, "\n");
		fclose(fp2);
	}
	fclose(fp1);
	return 0;
}