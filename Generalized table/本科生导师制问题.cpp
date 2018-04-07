#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<windows.h>
using namespace std;

typedef struct GLNode
{
	char name[100];    /*教师或学生的姓名*/
	char prof[100];     /*教师结点表示职称，学生结点表示班级*/
	int type;           /*结点类型：0-教师，1-研究生，2-本科生*/
struct {struct GLNode *hp, *tp;} ptr;
                    /*hp指向同级的下一结点，tp指向下级的首结点*/
}GList;


int Draw_Catalog()
{
	int choice;
	do
	{
		system("cls");
		cout<<"-------------------------本科生导师管理系统-------------------------"<<endl<<endl;
		cout<<"                温馨提示：请在英文输入法下运行该程序"<<endl<<endl; 
		cout<<"                   1.建立：建立导师广义表。"<<endl<<endl;
 		cout<<"                   2.插入：将某位本科生或研究生插入到广义表的相应位置。"<<endl<<endl;
 		cout<<"                   3.删除：将某本科生或研究生从广义表中删除。"<<endl<<endl;
 		cout<<"                   4.查询：查询导师、本科生（研究生）的情况。"<<endl<<endl;
 		cout<<"                   5.统计：某导师带了多少个研究生和本科生。"<<endl<<endl;
 		cout<<"                   6.输出：将某导师所带学生情况输出。"<<endl<<endl;
 		cout<<"                   7.退出：程序结束。"<<endl<<endl;
 		cout<<"你的选择是：";
 		cin>>choice;
	}
	while(choice<1||choice>7);
	return choice;
} 
void Creat_Glist(GList a[],int Teacher_number)//建立导师广义表 
{
	cout<<"请依次输入导师姓名，职称，类型"<<endl;
	for(int i=0;i<Teacher_number;i++) 
	cin>>a[i].name>>a[i].prof>>a[i].type;
	system("cls");
	for(int i=0;i<Teacher_number;i++)//导师大循环 
	{
		system("cls");
		a[i].ptr.hp=a+i;
		cout<<"请输入导师"<<a[i].name<<"带学生的类型"<<endl;
		int choice;
		cout<<"1.导师带研究生"<<endl<<"2.导师不带研究生"<<endl;
		cin>>choice;//导师下设两种情况 
		
		
		if(choice==2)
		{
			system("cls");
			cout<<"请输入该导师"<<a[i].name<<"带的本科生的数量:";
			int undergraduate_number;
			cin>>undergraduate_number;//本科生数量 
			cout<<"请依次输入本科生的姓名，班级，类型"<<endl; 
			GList *undergraduate;//当前指向的本科生 
			undergraduate=(GList*)malloc(sizeof(GList));
			cin>>undergraduate->name>>undergraduate->prof>>undergraduate->type;
			a[i].ptr.tp=undergraduate;
			undergraduate->ptr.tp=NULL;
			for(int i=1;i<undergraduate_number;i++)
			{
				GList *p;
				p=(GList*)malloc(sizeof(GList));
				p->ptr.tp=NULL;
				cin>>p->name>>p->prof>>p->type;
				undergraduate->ptr.hp=p;
				undergraduate=undergraduate->ptr.hp;
			}
			undergraduate->ptr.hp=NULL;		
		}
		else
		{
			system("cls");
			cout<<"请输入该导师"<<a[i].name<<"带的研究生的数量:";
			int graduate_number;
			cin>>graduate_number;
			if(graduate_number==1)
			{
				GList *graduate;//当前指向的研究生 
				graduate=(GList*)malloc(sizeof(GList));
				cout<<"请输入该研究生的姓名，班级，类型"<<endl; 
				cin>>graduate->name>>graduate->prof>>graduate->type;
				a[i].ptr.tp=graduate;
				graduate->ptr.hp=NULL;
				
				cout<<"请依次输入该研究生带的本科生的姓名，班级，类型(本科生类型输入-1时截止)"<<endl;
				GList *undergraduate;//当前指向的本科生 
				undergraduate=(GList*)malloc(sizeof(GList));
				cin>>undergraduate->name>>undergraduate->prof>>undergraduate->type;
				graduate->ptr.tp=undergraduate;
				undergraduate->ptr.tp=NULL;
				
				GList *q_pre;
				do//研究生下的本科生的大循环 
				{
					GList *q;
					q=(GList*)malloc(sizeof(GList));
					q->ptr.tp=NULL;
					cin>>q->name>>q->prof>>q->type;
					undergraduate->ptr.hp=q;
					q_pre=undergraduate;
					undergraduate=undergraduate->ptr.hp;
				}
				while(undergraduate->type!=-1);
				q_pre->ptr.hp=NULL;	
			}
			else//当导师带多个研究生的情况 
			{
			
				cout<<"请输入研究生1的姓名，班级，类型"<<endl; 
				GList *graduate;//当前指向的研究生 
				graduate=(GList*)malloc(sizeof(GList));
				cin>>graduate->name>>graduate->prof>>graduate->type;
				a[i].ptr.tp=graduate;
				
				for(int i=0;i<graduate_number;i++)//研究生的大循环 
				{
					if(i==0)
					{
						
					} 
					else
					{
					
						cout<<"请输入研究生"<<i+1<<"的姓名，班级，类型"<<endl; 
						GList *p;
						p=(GList*)malloc(sizeof(GList));
						p->ptr.tp=NULL;
						cin>>p->name>>p->prof>>p->type;
						graduate->ptr.hp=p;
						graduate=graduate->ptr.hp;
					}
						cout<<"请依次输入该研究生带的本科生的姓名，班级，类型(本科生类型输入-1时截止)"<<endl;
						GList *undergraduate;//当前指向的本科生 
						undergraduate=(GList*)malloc(sizeof(GList));
						cin>>undergraduate->name>>undergraduate->prof>>undergraduate->type;
						graduate->ptr.tp=undergraduate;
						undergraduate->ptr.tp=NULL;
								
						GList *q_pre;
						do//研究生下的本科生的大循环 
						{
							GList *q;
							q=(GList*)malloc(sizeof(GList));
							q->ptr.tp=NULL;
							cin>>q->name>>q->prof>>q->type;
							undergraduate->ptr.hp=q;
							q_pre=undergraduate;
							undergraduate=undergraduate->ptr.hp;
						}
						while(undergraduate->type!=-1);
						q_pre->ptr.hp=NULL;
					
					
				}
				graduate->ptr.hp=NULL;
			}
		}
	}
	a[Teacher_number-1].ptr.hp=NULL;
}

void Insert_student(GList a[],int Teacher_number)//插入函数 
{
	cout<<"导师列表如下:"<<endl;
	for(int i=0;i<Teacher_number;i++)
	{
		cout<<i+1<<"."<<a[i].name<<endl;
	}
	cout<<"请输入你插入的学生对应的导师：";
	int choice_teacher;
	cin>>choice_teacher;
	if(a[choice_teacher-1].ptr.tp->type==2)//如果老师只带本科生的话 
	{
		cout<<"注意该导师只带本科生"<<endl;
		cout<<"请输入你要插入的本科生的姓名，班级，类型"<<endl;
		GList *pwork,*newstudent;
		pwork=a[choice_teacher-1].ptr.tp;
		while(pwork->ptr.hp) pwork=pwork->ptr.hp;
		newstudent=(GList*)malloc(sizeof(GList));
		cin>>newstudent->name>>newstudent->prof>>newstudent->type;
		pwork->ptr.hp=newstudent;
	}
	else//如果导师带研究生的话 
	{
		system("cls");
		cout<<"你要插入的是"<<endl;
		cout<<"1.本科生"<<endl;
		cout<<"2.研究生"<<endl;
		int studentchoice ;
		cin>>studentchoice;
		if(studentchoice==1)//插入的是本科生 
		{
		
			cout<<"该导师所带的研究生列表如下:"<<endl;
			GList *pwork;
			pwork=a[choice_teacher-1].ptr.tp;
			int i=1;
			while(pwork->ptr.hp)
			{
	
				cout<<i++<<"."<<pwork->name<<endl;
				pwork=pwork->ptr.hp;
			}
			cout<<i<<"."<<pwork->name<<endl;
			int choice_graduate;
			cout<<"请输入你插入的本科生对应的研究生：";
			cin>>choice_graduate;
			pwork=a[choice_teacher-1].ptr.tp;
			for(int i=1;i<choice_graduate;i++) pwork=pwork->ptr.hp;
			GList *student2work;
			student2work=pwork->ptr.tp;
			while(student2work->ptr.hp) student2work=student2work->ptr.hp;
			GList *student2new;
			student2new=(GList*)malloc(sizeof(GList));
			student2new->ptr.tp=NULL;
			student2new->ptr.hp=NULL;
			student2work->ptr.hp=student2new;
			cout<<"请输入插入的本科生的姓名，班级，类型"<<endl;
			cin>>student2new->name>>student2new->prof>>student2new->type;
		}
		else//插入的是研究生 
		{
			GList *student2work;
			student2work=a[choice_teacher-1].ptr.tp;
			while(student2work->ptr.hp) student2work=student2work->ptr.hp;
			GList *student2new;
			student2new=(GList*)malloc(sizeof(GList));
			student2new->ptr.tp=NULL;
			student2new->ptr.hp=NULL;
			student2work->ptr.hp=student2new;
			cout<<"请输入插入的研究生的姓名，班级，类型"<<endl;
			cin>>student2new->name>>student2new->prof>>student2new->type;
		}
	}
	cout<<endl<<"插入成功";	
	
}

void Delete_student(GList a[],int Teacher_number)
{
	system("cls");
	cout<<"导师列表如下:"<<endl;
	for(int i=0;i<Teacher_number;i++)
	{
		cout<<i+1<<"."<<a[i].name<<endl;
	}
	cout<<"请输入你要删除的学生对应的导师：";
	int choice_teacher;
	cin>>choice_teacher;
	
	if(a[choice_teacher-1].ptr.tp->type==2)//如果老师只带本科生的话 
	{
		cout<<"注意该导师只带本科生"<<endl;
		cout<<"该导师带的本科生如下:"<<endl;
		GList *pwork;
		pwork=a[choice_teacher-1].ptr.tp;
		int i=1;
		while(pwork)
		{
			cout<<i++<<"."<<pwork->name<<endl;
			pwork=pwork->ptr.hp;
		}
		int choice;
		cout<<"请输入你要删除的学生编号：";
		cin>>choice;
		pwork=a[choice_teacher-1].ptr.tp;
		for(i=1;i<choice-1;i++)
		{
			pwork=pwork->ptr.hp;
		}
		pwork->ptr.hp=pwork->ptr.hp->ptr.hp;
	
	}
	else
	{
		system("cls");
		cout<<"你要删除的是"<<endl;
		cout<<"1.本科生"<<endl;
		cout<<"2.研究生"<<endl;
		int studentchoice ;
		cin>>studentchoice;
		if(studentchoice==1)//删除的是本科生 
		{
			cout<<"该导师所带的研究生列表如下:"<<endl;
			GList *pwork;
			pwork=a[choice_teacher-1].ptr.tp;
			int i=1;
			while(pwork->ptr.hp)
			{
	
				cout<<i++<<"."<<pwork->name<<endl;
				pwork=pwork->ptr.hp;
			}
			cout<<i<<"."<<pwork->name<<endl;
			int choice_graduate;
			cout<<"请输入你删除的本科生对应的研究生：";
			cin>>choice_graduate;
			pwork=a[choice_teacher-1].ptr.tp;
			for(i=1;i<choice_graduate-1;i++) pwork=pwork->ptr.hp;
			
			GList *student2work;
			student2work=pwork->ptr.tp;
			cout<<"该研究生所带的本科生列表如下:"<<endl;
			i=1;
			while(student2work->ptr.hp)
			{
	
				cout<<i++<<"."<<student2work->name<<endl;
				student2work=student2work->ptr.hp;
			}
			int choice_ungraduate;
			cout<<"请输入你删除的本科生对应的编号";
			cin>>choice_ungraduate;
			student2work=pwork->ptr.tp;
			for(i=1;i<choice_ungraduate-1;i++)
			{
				student2work=student2work->ptr.hp;
			}
			student2work->ptr.hp=student2work->ptr.hp->ptr.hp;
		}
		else
		{
			cout<<"该导师所带的研究生列表如下:"<<endl;
			GList *pwork;
			pwork=a[choice_teacher-1].ptr.tp;
			int i=1;
			while(pwork->ptr.hp)
			{
	
				cout<<i++<<"."<<pwork->name<<endl;
				pwork=pwork->ptr.hp;
			}
			cout<<i<<"."<<pwork->name<<endl;
			int choice_graduate;
			cout<<"请输入你删除的研究生对应的编号：";
			cin>>choice_graduate;
			pwork=a[choice_teacher-1].ptr.tp;
			for(i=1;i<choice_graduate-1;i++)
			{
				pwork=pwork->ptr.hp;
			}
			pwork->ptr.hp=pwork->ptr.hp->ptr.hp;		
		} 
		
	} 
	
}

void count_student(GList a[],int Teacher_number)//统计功能 
{
	system("cls");
	cout<<"导师列表如下:"<<endl;
	for(int i=0;i<Teacher_number;i++)
	{
		cout<<i+1<<"."<<a[i].name<<endl;
	}
	cout<<"请输入你要输出的导师：";
	int choice_teacher;
	cin>>choice_teacher;
	if(a[choice_teacher-1].ptr.tp->type==2)//如果老师只带本科生的话 
	{
		cout<<"注意该导师只带本科生"<<endl;
		cout<<"该导师带的本科生数目为:";
		GList *pwork;
		pwork=a[choice_teacher-1].ptr.tp;
		int i=0;
		while(pwork)
		{
			i++;
			pwork=pwork->ptr.hp;
		}
		cout<<i;
	}
	else//不仅带本科生 
	{
		int count_gra=0;
		int count_ungra=0;
		GList *gra;
		gra=a[choice_teacher-1].ptr.tp;
		while(gra)
		{
			count_gra++;
			GList *ungra;
			ungra=gra->ptr.tp;
			while(ungra)
			{
				count_ungra++;
				ungra=ungra->ptr.hp; 
			}
			gra=gra->ptr.hp; 
		}
		cout<<"该导师带的研究生数目为:"<<count_gra<<endl;
		cout<<"该导师带的本科生数目为:"<<count_ungra<<endl;	
	}
	cout<<endl;
} 

void output(GList a[],int Teacher_number)
{
	system("cls");
	cout<<"导师列表如下:"<<endl;
	for(int i=0;i<Teacher_number;i++)
	{
		cout<<i+1<<"."<<a[i].name<<endl;
	}
	cout<<"请输入你要输出的导师：";
	int choice_teacher;
	cin>>choice_teacher;
	cout<<a[choice_teacher-1].name<<"-"<<a[choice_teacher-1].prof<<"-"<<a[choice_teacher-1].type<<endl;
	if(a[choice_teacher-1].ptr.tp->type==2)//如果老师只带本科生的话 
	{
		cout<<"注意该导师只带本科生"<<endl;
		cout<<"该导师带的本科生如下:"<<endl;
		GList *pwork;
		pwork=a[choice_teacher-1].ptr.tp;
		int i=1;
		while(pwork)
		{
			cout<<pwork->name<<"-"<<pwork->prof<<"-"<<pwork->type<<endl;
			pwork=pwork->ptr.hp;
		}
	}
	else//不仅带本科生 
	{
		GList *gra;
		gra=a[choice_teacher-1].ptr.tp;
		while(gra)
		{
			cout<<gra->name<<"-"<<gra->prof<<"-"<<gra->type<<endl;
			GList *ungra;
			ungra=gra->ptr.tp;
			while(ungra)
			{
				cout<<ungra->name<<"-"<<ungra->prof<<"-"<<ungra->type<<endl;
				ungra=ungra->ptr.hp; 
			}
			gra=gra->ptr.hp; 
		}
	}
	
	
}





int main()
{	
	string str="-------------------------本科生导师管理系统-------------------------";
	for(int i=0; i<str.size(); i++)
	{
		Sleep(30);
		cout<<str[i];
	}
	cout<<endl<<"请输入导师数量：";
	int Teacher_number;
	cin>>Teacher_number;
	GList a[Teacher_number]; 
	first:
	switch(Draw_Catalog())
	{
		case 1:{
			system("cls"); 
			Creat_Glist(a,Teacher_number);
			goto first;
			
		}
		case 2:{
			system("cls");
			Insert_student(a,Teacher_number);
			goto first;
		}
		case 3:{
			Delete_student(a,Teacher_number);
			goto first;
		}
		
		case 5:{
			count_student(a,Teacher_number);
			system("pause");	
			goto first;
		}
		
		case 6:{
			output(a,Teacher_number);
			system("pause");
			goto first;
		}
		case 7:{
			break;
		}
	}
	
	return 0;
} 
