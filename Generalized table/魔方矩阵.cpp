#include<iostream>
#include<cstdio>
using namespace std;



int main()
{
	int m;
	cout<<"请输入矩阵行数m:";
	cin>>m;
	cout<<"魔方矩阵为："<<endl;
	if(m%2==0)
	{
		cout<<"您输入的是偶数"<<endl;
		return 0;
	}
	else
	{
		int a[m][m];
		for(int i=0;i<m;i++)
			for(int j=0;j<m;j++) a[i][j]=0;
		int i=0;
		int j=m/2;
		int past_i;
		int past_j;
		a[i][j]=1;
		int number=2;
		while(number<=(m*m))
		{
			past_i=i;
			past_j=j;
			i=(i-1+m)%m;
			j=(j-1+m)%m;

			if(a[i][j]==0) 
			{
				a[i][j]=number++;
			}
			else
			{
				i=past_i+1;
				j=past_j;
				a[i][j]=number++;	
			}
		}
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<m;j++)
			{
				cout<<a[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}
