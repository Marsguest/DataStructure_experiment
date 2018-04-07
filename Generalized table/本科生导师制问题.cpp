#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<windows.h>
using namespace std;

typedef struct GLNode
{
	char name[100];    /*��ʦ��ѧ��������*/
	char prof[100];     /*��ʦ����ʾְ�ƣ�ѧ������ʾ�༶*/
	int type;           /*������ͣ�0-��ʦ��1-�о�����2-������*/
struct {struct GLNode *hp, *tp;} ptr;
                    /*hpָ��ͬ������һ��㣬tpָ���¼����׽��*/
}GList;


int Draw_Catalog()
{
	int choice;
	do
	{
		system("cls");
		cout<<"-------------------------��������ʦ����ϵͳ-------------------------"<<endl<<endl;
		cout<<"                ��ܰ��ʾ������Ӣ�����뷨�����иó���"<<endl<<endl; 
		cout<<"                   1.������������ʦ�����"<<endl<<endl;
 		cout<<"                   2.���룺��ĳλ���������о������뵽��������Ӧλ�á�"<<endl<<endl;
 		cout<<"                   3.ɾ������ĳ���������о����ӹ������ɾ����"<<endl<<endl;
 		cout<<"                   4.��ѯ����ѯ��ʦ�����������о������������"<<endl<<endl;
 		cout<<"                   5.ͳ�ƣ�ĳ��ʦ���˶��ٸ��о����ͱ�������"<<endl<<endl;
 		cout<<"                   6.�������ĳ��ʦ����ѧ����������"<<endl<<endl;
 		cout<<"                   7.�˳������������"<<endl<<endl;
 		cout<<"���ѡ���ǣ�";
 		cin>>choice;
	}
	while(choice<1||choice>7);
	return choice;
} 
void Creat_Glist(GList a[],int Teacher_number)//������ʦ����� 
{
	cout<<"���������뵼ʦ������ְ�ƣ�����"<<endl;
	for(int i=0;i<Teacher_number;i++) 
	cin>>a[i].name>>a[i].prof>>a[i].type;
	system("cls");
	for(int i=0;i<Teacher_number;i++)//��ʦ��ѭ�� 
	{
		system("cls");
		a[i].ptr.hp=a+i;
		cout<<"�����뵼ʦ"<<a[i].name<<"��ѧ��������"<<endl;
		int choice;
		cout<<"1.��ʦ���о���"<<endl<<"2.��ʦ�����о���"<<endl;
		cin>>choice;//��ʦ����������� 
		
		
		if(choice==2)
		{
			system("cls");
			cout<<"������õ�ʦ"<<a[i].name<<"���ı�����������:";
			int undergraduate_number;
			cin>>undergraduate_number;//���������� 
			cout<<"���������뱾�������������༶������"<<endl; 
			GList *undergraduate;//��ǰָ��ı����� 
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
			cout<<"������õ�ʦ"<<a[i].name<<"�����о���������:";
			int graduate_number;
			cin>>graduate_number;
			if(graduate_number==1)
			{
				GList *graduate;//��ǰָ����о��� 
				graduate=(GList*)malloc(sizeof(GList));
				cout<<"��������о������������༶������"<<endl; 
				cin>>graduate->name>>graduate->prof>>graduate->type;
				a[i].ptr.tp=graduate;
				graduate->ptr.hp=NULL;
				
				cout<<"������������о������ı��������������༶������(��������������-1ʱ��ֹ)"<<endl;
				GList *undergraduate;//��ǰָ��ı����� 
				undergraduate=(GList*)malloc(sizeof(GList));
				cin>>undergraduate->name>>undergraduate->prof>>undergraduate->type;
				graduate->ptr.tp=undergraduate;
				undergraduate->ptr.tp=NULL;
				
				GList *q_pre;
				do//�о����µı������Ĵ�ѭ�� 
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
			else//����ʦ������о�������� 
			{
			
				cout<<"�������о���1���������༶������"<<endl; 
				GList *graduate;//��ǰָ����о��� 
				graduate=(GList*)malloc(sizeof(GList));
				cin>>graduate->name>>graduate->prof>>graduate->type;
				a[i].ptr.tp=graduate;
				
				for(int i=0;i<graduate_number;i++)//�о����Ĵ�ѭ�� 
				{
					if(i==0)
					{
						
					} 
					else
					{
					
						cout<<"�������о���"<<i+1<<"���������༶������"<<endl; 
						GList *p;
						p=(GList*)malloc(sizeof(GList));
						p->ptr.tp=NULL;
						cin>>p->name>>p->prof>>p->type;
						graduate->ptr.hp=p;
						graduate=graduate->ptr.hp;
					}
						cout<<"������������о������ı��������������༶������(��������������-1ʱ��ֹ)"<<endl;
						GList *undergraduate;//��ǰָ��ı����� 
						undergraduate=(GList*)malloc(sizeof(GList));
						cin>>undergraduate->name>>undergraduate->prof>>undergraduate->type;
						graduate->ptr.tp=undergraduate;
						undergraduate->ptr.tp=NULL;
								
						GList *q_pre;
						do//�о����µı������Ĵ�ѭ�� 
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

void Insert_student(GList a[],int Teacher_number)//���뺯�� 
{
	cout<<"��ʦ�б�����:"<<endl;
	for(int i=0;i<Teacher_number;i++)
	{
		cout<<i+1<<"."<<a[i].name<<endl;
	}
	cout<<"������������ѧ����Ӧ�ĵ�ʦ��";
	int choice_teacher;
	cin>>choice_teacher;
	if(a[choice_teacher-1].ptr.tp->type==2)//�����ʦֻ���������Ļ� 
	{
		cout<<"ע��õ�ʦֻ��������"<<endl;
		cout<<"��������Ҫ����ı��������������༶������"<<endl;
		GList *pwork,*newstudent;
		pwork=a[choice_teacher-1].ptr.tp;
		while(pwork->ptr.hp) pwork=pwork->ptr.hp;
		newstudent=(GList*)malloc(sizeof(GList));
		cin>>newstudent->name>>newstudent->prof>>newstudent->type;
		pwork->ptr.hp=newstudent;
	}
	else//�����ʦ���о����Ļ� 
	{
		system("cls");
		cout<<"��Ҫ�������"<<endl;
		cout<<"1.������"<<endl;
		cout<<"2.�о���"<<endl;
		int studentchoice ;
		cin>>studentchoice;
		if(studentchoice==1)//������Ǳ����� 
		{
		
			cout<<"�õ�ʦ�������о����б�����:"<<endl;
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
			cout<<"�����������ı�������Ӧ���о�����";
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
			cout<<"���������ı��������������༶������"<<endl;
			cin>>student2new->name>>student2new->prof>>student2new->type;
		}
		else//��������о��� 
		{
			GList *student2work;
			student2work=a[choice_teacher-1].ptr.tp;
			while(student2work->ptr.hp) student2work=student2work->ptr.hp;
			GList *student2new;
			student2new=(GList*)malloc(sizeof(GList));
			student2new->ptr.tp=NULL;
			student2new->ptr.hp=NULL;
			student2work->ptr.hp=student2new;
			cout<<"�����������о������������༶������"<<endl;
			cin>>student2new->name>>student2new->prof>>student2new->type;
		}
	}
	cout<<endl<<"����ɹ�";	
	
}

void Delete_student(GList a[],int Teacher_number)
{
	system("cls");
	cout<<"��ʦ�б�����:"<<endl;
	for(int i=0;i<Teacher_number;i++)
	{
		cout<<i+1<<"."<<a[i].name<<endl;
	}
	cout<<"��������Ҫɾ����ѧ����Ӧ�ĵ�ʦ��";
	int choice_teacher;
	cin>>choice_teacher;
	
	if(a[choice_teacher-1].ptr.tp->type==2)//�����ʦֻ���������Ļ� 
	{
		cout<<"ע��õ�ʦֻ��������"<<endl;
		cout<<"�õ�ʦ���ı���������:"<<endl;
		GList *pwork;
		pwork=a[choice_teacher-1].ptr.tp;
		int i=1;
		while(pwork)
		{
			cout<<i++<<"."<<pwork->name<<endl;
			pwork=pwork->ptr.hp;
		}
		int choice;
		cout<<"��������Ҫɾ����ѧ����ţ�";
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
		cout<<"��Ҫɾ������"<<endl;
		cout<<"1.������"<<endl;
		cout<<"2.�о���"<<endl;
		int studentchoice ;
		cin>>studentchoice;
		if(studentchoice==1)//ɾ�����Ǳ����� 
		{
			cout<<"�õ�ʦ�������о����б�����:"<<endl;
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
			cout<<"��������ɾ���ı�������Ӧ���о�����";
			cin>>choice_graduate;
			pwork=a[choice_teacher-1].ptr.tp;
			for(i=1;i<choice_graduate-1;i++) pwork=pwork->ptr.hp;
			
			GList *student2work;
			student2work=pwork->ptr.tp;
			cout<<"���о��������ı������б�����:"<<endl;
			i=1;
			while(student2work->ptr.hp)
			{
	
				cout<<i++<<"."<<student2work->name<<endl;
				student2work=student2work->ptr.hp;
			}
			int choice_ungraduate;
			cout<<"��������ɾ���ı�������Ӧ�ı��";
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
			cout<<"�õ�ʦ�������о����б�����:"<<endl;
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
			cout<<"��������ɾ�����о�����Ӧ�ı�ţ�";
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

void count_student(GList a[],int Teacher_number)//ͳ�ƹ��� 
{
	system("cls");
	cout<<"��ʦ�б�����:"<<endl;
	for(int i=0;i<Teacher_number;i++)
	{
		cout<<i+1<<"."<<a[i].name<<endl;
	}
	cout<<"��������Ҫ����ĵ�ʦ��";
	int choice_teacher;
	cin>>choice_teacher;
	if(a[choice_teacher-1].ptr.tp->type==2)//�����ʦֻ���������Ļ� 
	{
		cout<<"ע��õ�ʦֻ��������"<<endl;
		cout<<"�õ�ʦ���ı�������ĿΪ:";
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
	else//������������ 
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
		cout<<"�õ�ʦ�����о�����ĿΪ:"<<count_gra<<endl;
		cout<<"�õ�ʦ���ı�������ĿΪ:"<<count_ungra<<endl;	
	}
	cout<<endl;
} 

void output(GList a[],int Teacher_number)
{
	system("cls");
	cout<<"��ʦ�б�����:"<<endl;
	for(int i=0;i<Teacher_number;i++)
	{
		cout<<i+1<<"."<<a[i].name<<endl;
	}
	cout<<"��������Ҫ����ĵ�ʦ��";
	int choice_teacher;
	cin>>choice_teacher;
	cout<<a[choice_teacher-1].name<<"-"<<a[choice_teacher-1].prof<<"-"<<a[choice_teacher-1].type<<endl;
	if(a[choice_teacher-1].ptr.tp->type==2)//�����ʦֻ���������Ļ� 
	{
		cout<<"ע��õ�ʦֻ��������"<<endl;
		cout<<"�õ�ʦ���ı���������:"<<endl;
		GList *pwork;
		pwork=a[choice_teacher-1].ptr.tp;
		int i=1;
		while(pwork)
		{
			cout<<pwork->name<<"-"<<pwork->prof<<"-"<<pwork->type<<endl;
			pwork=pwork->ptr.hp;
		}
	}
	else//������������ 
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
	string str="-------------------------��������ʦ����ϵͳ-------------------------";
	for(int i=0; i<str.size(); i++)
	{
		Sleep(30);
		cout<<str[i];
	}
	cout<<endl<<"�����뵼ʦ������";
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
