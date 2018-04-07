#include<iostream>
#include<cstdio>
#include<malloc.h>
using namespace std;


typedef struct Node
{
    int data;
    Node *next;
}linklist;//定义结点结构体 

linklist *Creat_linklist(int n)//创建循环链表 
{
	linklist *L,*pwork,*final;//依次为头指针，工作指针和当前状态下的尾指针。 
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
	final->next=L;//尾指针指向头指针，形成循环链表。 

	return L;
} 

int main()
{
	int n,m;
	cout<<"请输入人数:"<<endl;
	cin>>n;
	cout<<"请输入密码:"<<endl;
	cin>>m;
	cout<<"出圈的次序为："<<endl; 
	
	
	linklist *first,*p;
	first=Creat_linklist(n);
	p=first;
	

	if(m!=1)
	{
	
		while(p->next!=p)//进行出圈操作，由是否仅剩一个结点控制循环 
		{
			int count=1;//count用于计数 
			while(count<m-1)
			{
				p=p->next;
				count++;
			}
			cout<<p->next->data<<endl;
			linklist *q=p->next;
			p->next=p->next->next;
			p=p->next;
			free(q);//删除结点操作 
		
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


