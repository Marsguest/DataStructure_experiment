#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

int Draw_catalog()//����Ŀ¼
{
	int choice;
	do 
	{
		system("cls");
		cout<<"-----------------��������ȳ���----------------"<<endl<<endl;
		cout<<"           1. ���������ύ��ʱ���"<<endl<<endl;
		cout<<"           2. ������ͬʱ�ύ��"<<endl<<endl;
		cout<<"              ���������ѡ��";
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
	cout<<"���������������";
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
	cout<<"����ִ������Ϊ��"<<endl; 
	for(int i=0;i<N;i++)
	{
		cout<<a[i][0]<<" "<<a[i][1]<<" "<<a[i][2]<<" "<<a[i][3]<<" "<<a[i][4]<<endl;
	}
	cout<<"ƽ���ȴ�ʱ��Ϊ��";
	int count_time=0;
	for(int i=0;i<N;i++)  count_time+=a[i][2];
	double average=(double)count_time/N;
	cout<<average<<endl;
}

void Solve_Question2()
{
	int N;
	cout<<"���������������";
	cin>>N;
	int a[N][6];
	int End_time=0;
	int time=0;
	for(int i=0;i<N;i++)
	{
		cin>>a[i][0]>>a[i][1]>>a[i][2];
		End_time+=a[i][2];//����Ϊ�����ţ������ύʱ�̣���������cpuʱ��
		a[i][3]=0;//�ȴ�ʱ�� 
		a[i][4]=0;//�Ƿ�ôβ��� 
		a[i][5]=0;//������ʱ�� 
	}
	
	int index_waiting=10000;			
	int task_number=0;
	cout<<"��ʱ�̴����������б�"<<endl;
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
	
	cout<<"������ȴ�ʱ������Ϊ��";
	for(int i=0;i<N;i++) cout<<a[i][3]<<" ";
	
	
	cout<<endl<<"ƽ���ȴ�ʱ��Ϊ��";
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
