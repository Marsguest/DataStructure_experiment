#include<iostream>
#include<cstdio>
#include<malloc.h>
using namespace std;


typedef struct Node
{
    int data;
    Node *next;
}linklist;//������ṹ�� 

linklist *Creat_linklist(int n)//����ѭ������ 
{
	linklist *L,*pwork,*final;//����Ϊͷָ�룬����ָ��͵�ǰ״̬�µ�βָ�롣 
	L=(linklist*)malloc(sizeof(linklist));
	final=L;
	int i;
	for(i=1;i<=n-1;i++)
	{
		
		final->data=i;
		pwork=(linklist*)malloc(sizeof(linklist));
		final->next=pwork;
		
		final=final->next;
	}
	final->data=i;
	final->next=L;//βָ��ָ��ͷָ�룬�γ�ѭ������ 

	return L;
} 

int main()
{
	int n,m;
	cout<<"����������:"<<endl;
	cin>>n;
	cout<<"����������:"<<endl;
	cin>>m;
	cout<<"��Ȧ�Ĵ���Ϊ��"<<endl; 
	
	
	linklist *first,*p;
	first=Creat_linklist(n);
	p=first;
	

	if(m!=1)
	{
	
		while(p->next!=p)//���г�Ȧ���������Ƿ��ʣһ��������ѭ�� 
		{
			int count=1;//count���ڼ��� 
			while(count<m-1)
			{
				p=p->next;
				count++;
			}
			cout<<p->next->data<<endl;
			linklist *q=p->next;
			p->next=p->next->next;
			p=p->next;
			free(q);//ɾ�������� 
		
		}
		cout<<p->data;
	}
	else for(int i=1;i<=n;i++) 
		{
			cout<<p->data<<endl;
			p=p->next;
		}
	return 0;
}


