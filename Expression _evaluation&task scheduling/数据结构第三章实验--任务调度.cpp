#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

int Draw_catalog()//绘制目录
{
	int choice;
	do 
	{
		system("cls");
		cout<<"-----------------多任务调度程序----------------"<<endl<<endl;
		cout<<"           1. 忽略任务提交的时间差"<<endl<<endl;
		cout<<"           2. 各任务不同时提交。"<<endl<<endl;
		cout<<"              请输入你的选择：";
		cin>>choice;
	}while(choice<1||choice>2);
	return choice;
} 

void Temp(int &a,int &b)
{
	int index;
	index=a;
	a=b;
	b=index;
}

void Solve_Question1()
{
	int N;
	cout<<"请输入任务个数：";
	cin>>N;
	int a[N][5];
	for(int i=0;i<N;i++)
	{
		cin>>a[i][0]>>a[i][1];
	}
	
	for(int i=0;i<N;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			if(a[i][1]>a[j][1])
			{
				Temp(a[i][0],a[j][0]);
				Temp(a[i][1],a[j][1]);
			}
		}
	}
	

	a[0][2]=0;
	a[0][4]=0;
	a[0][3]=a[0][1];
	int Waiting_time=0;
	for(int i=1;i<N;i++)
	{
		Waiting_time+=a[i-1][1];
		a[i][2]=Waiting_time;
		a[i][3]=a[i][2]+a[i][1];
		a[i][4]=a[i][2];
	}
	cout<<"任务执行序列为："<<endl; 
	for(int i=0;i<N;i++)
	{
		cout<<a[i][0]<<" "<<a[i][1]<<" "<<a[i][2]<<" "<<a[i][3]<<" "<<a[i][4]<<endl;
	}
	cout<<"平均等待时间为：";
	int count_time=0;
	for(int i=0;i<N;i++)  count_time+=a[i][2];
	double average=(double)count_time/N;
	cout<<average<<endl;
}

void Solve_Question2()
{
	int N;
	cout<<"请输入任务个数：";
	cin>>N;
	int a[N][6];
	int End_time=0;
	int time=0;
	for(int i=0;i<N;i++)
	{
		cin>>a[i][0]>>a[i][1]>>a[i][2];
		End_time+=a[i][2];//依次为任务编号，任务提交时刻，任务所需cpu时间
		a[i][3]=0;//等待时间 
		a[i][4]=0;//是否该次操作 
		a[i][5]=0;//操作的时间 
	}
	
	int index_waiting=10000;			
	int task_number=0;
	cout<<"各时刻处理任务编号列表："<<endl;
	for(time=0;time<End_time;time++)
	{
		index_waiting=10000;			
		task_number=0;
		for(int i=0;i<N;i++)
		{
			
			if(a[i][1]<=time&&a[i][5]<a[i][2])
			{
				if((a[i][2]-a[i][5])<index_waiting)
				{
					index_waiting=a[i][2]-a[i][5];
					task_number=a[i][0]-1;
				}		
			} 
		}
		a[task_number][5]++;
		a[task_number][4]=1;
		
		
		for(int j=0;j<N;j++)
		{
			if(a[j][1]<=time&&a[j][4]==0&&a[j][5]<a[j][2]) a[j][3]++;
		}
		a[task_number][4]=0;
		
		
		
		cout<<time<<" "<<task_number+1<<endl;
	}
	
	cout<<"各任务等待时间依次为：";
	for(int i=0;i<N;i++) cout<<a[i][3]<<" ";
	
	
	cout<<endl<<"平均等待时间为：";
	int count_time=0;
	for(int i=0;i<N;i++)  count_time+=a[i][3];
	double average=(double)count_time/N;
	cout<<average<<endl;
	
	
	
		 
}

int main()
{
	
	switch(Draw_catalog())
	{
		case 1:{
			system("cls");
			Solve_Question1();
			break;
		}
		case 2:{
			system("cls");
			Solve_Question2();
			break;
		}
	}
	return 0;
} 
