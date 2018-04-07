#include<bits/stdc++.h>
using namespace std;

#define CLASS_MAX_NUMBER 20

struct Project
{
	char Number[10];
	char name[100];
	int credit; 
	bool project_exist;//�жϵ�ǰ�γ��Ƿ�ɾȥ�� 
};

struct DGraph
{
	Project project[CLASS_MAX_NUMBER];
	int vexnum;
	int ArcCell[CLASS_MAX_NUMBER][CLASS_MAX_NUMBER];
};

void Creat_DGraph(DGraph *p);//��������ͼ
void Add_project(DGraph *p);
void Delete_project(DGraph *p);
void Information_modify(DGraph *p);
void ToplogicalSort(DGraph *p,int ToplogicalSort_reslut[]); //�����ز����� 
void Output_according_to_teachingplan(DGraph *p,int ToplogicalSort_reslut[]);//����ѧ�ƻ������ͨ���ز����� 
int Draw_menu();//����Ŀ¼ 



void Creat_DGraph(DGraph *p)
{
	cout<<"������γ�����"<<endl;
	cin>>p->vexnum;
	cout<<"����������γ̱�ţ��γ����ƺ�ѧ��"<<endl;
	for(int i=1;i<=p->vexnum;i++) 
	{
		cin>>p->project[i].Number>>p->project[i].name>>p->project[i].credit;
		p->project[i].project_exist=true;
	}
	memset(p->ArcCell,0,sizeof(p->ArcCell));
	cout<<"������ż�Ե���ʽ����γ�֮���ǰ���ϵ(���տγ̱��)"<<endl;
	int i,j;
	for(int k=1;k<=19;k++)
	{
		cin>>i>>j;
		p->ArcCell[i][j]=1;
	}
	
}

void Add_project(DGraph *p)
{
	p->vexnum++;
	int i=p->vexnum;
	cout<<"����������Ҫ��ӵĿγ̱�ţ��γ����ƺ�ѧ��"<<endl;
	cin>>p->project[i].Number>>p->project[i].name>>p->project[i].credit;
	p->project[i].project_exist=true;
	cout<<"������ÿγ�ǰ���γ̵���Ŀ"<<endl;
	int preclass_number;
	cin>>preclass_number;
	cout<<"��������������ӿγ̵�ǰ���γ̵ı��"<<endl;
	int preclass;
	for(int k=0;k<preclass_number;k++) 
	{
		cin>>preclass;
		p->ArcCell[preclass][i]=1;
	}
	
	cout<<"������ÿγ̺�̿γ̵���Ŀ"<<endl;
	int postclass_number;
	cin>>postclass_number;
	cout<<"��������������ӿγ̵ĺ�̿γ̵ı��"<<endl;
	int postclass;
	for(int k=0;k<postclass_number;k++) 
	{
		cin>>postclass;
		p->ArcCell[i][postclass]=1;
	}
	
}

void Delete_project(DGraph *p)
{
	cout<<"��������Ҫ����Ŀγ̱��"<<endl;
	int delete_project_number;
	cin>>delete_project_number;
	for(int i=1;i<=p->vexnum;i++)
	{
		p->ArcCell[i][delete_project_number]=0;
		p->ArcCell[delete_project_number][i]=0;
	}
	memset(p->project[delete_project_number].Number,'\0',sizeof(p->project[delete_project_number].Number));
	memset(p->project[delete_project_number].name,'\0',sizeof(p->project[delete_project_number].name));
	p->project[delete_project_number].credit=0;
	p->project[delete_project_number].project_exist=false;//��ǰ�γ̵�bool��Ϊ�㣬��ʾɾ�� 
	cout<<"ɾ���ɹ�"<<endl;
}

void Information_modify(DGraph *p)
{
	cout<<"�����������޸ĵĿγ̱��"<<endl;
	int mod_project_number;
	cin>>mod_project_number;
	int choice;
	cout<<"�����޸ĵ���ĿΪ��"<<endl;
	cout<<"1.�γ�����"<<endl;
	cout<<"2.�γ�ѧ��"<<endl;
	cin>>choice;
	if(choice==1)
	{
		memset(p->project[mod_project_number].name,'\0',sizeof(p->project[mod_project_number].name));//���Ƴ�ʼ������ 
		cout<<"�������µĿγ�����"<<endl;
		cin>>p->project[mod_project_number].name;
	} 
	if(choice==2)
	{
		cout<<"�������µĿγ�ѧ��"<<endl;
		cin>>p->project[mod_project_number].credit;
	}
	cout<<"�޸ĳɹ�"<<endl; 
}

void ToplogicalSort(DGraph *p,int ToplogicalSort_reslut[]) //�����ز����� 
{
	int indegree[p->vexnum+1];//ͳ�Ƹ�������� 
	memset(indegree,0,sizeof(indegree));
	for(int i=1;i<=p->vexnum;i++)
		for(int j=1;j<=p->vexnum;j++)
			if(p->ArcCell[i][j]) indegree[j]++;
			
	stack <int> s;
	for(int i=1;i<=p->vexnum;i++)
		if(!indegree[i]) s.push(i);
		
	//��ʼ�����ز�����
	int num=0;
	while(!s.empty())
	{
		int top;
		top=s.top();
		s.pop();
		ToplogicalSort_reslut[num++]=top;
		for(int j=1;j<=p->vexnum;j++)
		{
			if(p->ArcCell[top][j])
			{
				if(!--indegree[j]) s.push(j);
			}
		}
		
	}
	num=0;
	cout<<"�ز�����Ϊ��"; 
	while(ToplogicalSort_reslut[num]!=0)
		cout<<ToplogicalSort_reslut[num++]<<" ";
	cout<<endl<<endl;
	
}

void Output_according_to_teachingplan(DGraph *p,int ToplogicalSort_reslut[])//����ѧ�ƻ������ͨ���ز����� 
{
	cout<<"1. ����ѧ���е�ѧϰ�����������ȵ��ƶ���ѧ�ƻ���"<<endl;
	cout<<"2. �������̵ܶ�ʱ�����ѧϰ���ƶ���ѧ�ƻ���"<<endl;
	cout<<"���ѡ���ǣ�";
	int choice;
	cin>>choice;
	if(choice==1)
	{
		int average_credit=0;
		for(int i=1;i<=p->vexnum;i++)
		{
			average_credit+=p->project[i].credit;
		}
		
		int remaining_number=average_credit;
		average_credit/=8;
		system("cls");
		cout<<"ƽ��ѧ��Ϊ:"<<average_credit<<endl;
		
		int term_number=1;
		int i=1,j=0;//iΪѧ�ڱ�ţ�jΪ�ز����е��±� 
		
		while(remaining_number>=0) 
		{
			int term_credit=0;
			int thisterm_remaining_number=average_credit;//��ǰѧ�ڻ����޵�ѧ���� 
			cout<<"��"<<i<<"ѧ��:" <<endl;
			if(remaining_number>thisterm_remaining_number)
			{
			
				while(thisterm_remaining_number>0)
				{
					cout<<p->project[ToplogicalSort_reslut[j]].Number<<" ";
					cout<<p->project[ToplogicalSort_reslut[j]].name<<" ";
					cout<<p->project[ToplogicalSort_reslut[j]].credit<<" ";
					cout<<"ֱ�����޿γ̣�";
					for(int i=1;i<=p->vexnum;i++)
					{
						if(p->ArcCell[i][ToplogicalSort_reslut[j]]==1) cout<<p->project[i].Number<<" ";
					}
					thisterm_remaining_number-=p->project[ToplogicalSort_reslut[j]].credit;
					
					remaining_number-=p->project[ToplogicalSort_reslut[j]].credit;
					
					term_credit+=p->project[ToplogicalSort_reslut[j]].credit;
					j++;
					cout<<endl;
				}
				i++;
			}
			else 
			{
				cout<<p->project[ToplogicalSort_reslut[j]].Number<<" ";
				cout<<p->project[ToplogicalSort_reslut[j]].name<<" ";
				cout<<p->project[ToplogicalSort_reslut[j]].credit<<" ";
				cout<<"ֱ�����޿γ̣�";
				for(int i=1;i<=p->vexnum;i++)
				{
					if(p->ArcCell[i][ToplogicalSort_reslut[j]]==1) cout<<p->project[i].Number<<" ";
				}
				thisterm_remaining_number-=p->project[ToplogicalSort_reslut[j]].credit;
					
				remaining_number-=p->project[ToplogicalSort_reslut[j]].credit;
					
				term_credit+=p->project[ToplogicalSort_reslut[j]].credit;
				cout<<endl;
			}
			cout<<endl;
			cout<<"��ѧ��ѧ������Ϊ��"<<term_credit<<endl<<endl;
			
		}
		cout<<"ѧ������Ϊ:"<<i<<endl;

		 
	} 
	else
	{
		int term_credit;
		int term_number=1;
		int project_number=0;
		int project_count=p->vexnum;//��¼ʣ��γ��� 
		while(project_count>=5)
		{
			term_credit=0;
			cout<<"��"<<term_number<<"ѧ��:" <<endl;
			for(int k=1;k<=5;k++)
			{
				cout<<p->project[ToplogicalSort_reslut[project_number]].Number<<" ";
				cout<<p->project[ToplogicalSort_reslut[project_number]].name<<" ";
				cout<<p->project[ToplogicalSort_reslut[project_number]].credit<<" ";
				cout<<"ֱ�����޿γ̣�";
				
				for(int i=1;i<=p->vexnum;i++)
				{
					if(p->ArcCell[i][ToplogicalSort_reslut[project_number]]==1) cout<<p->project[i].Number<<" ";
				}
				cout<<endl;
				term_credit+=p->project[ToplogicalSort_reslut[project_number]].credit;
				project_number++;
			}
			project_count-=5;
		
			term_number++;
			cout<<"��ѧ��ѧ������Ϊ��"<<term_credit<<endl<<endl;
		}
		term_credit=0;
		cout<<"��"<<term_number<<"ѧ��:" <<endl;
		for(int k=1;k<=project_count;k++)
		{
			cout<<p->project[ToplogicalSort_reslut[project_number]].Number<<" ";
			cout<<p->project[ToplogicalSort_reslut[project_number]].name<<" ";
			cout<<p->project[ToplogicalSort_reslut[project_number]].credit<<" ";
			cout<<"ֱ�����޿γ̣�";
			
				
			for(int i=1;i<=p->vexnum;i++)
			{
				if(p->ArcCell[i][ToplogicalSort_reslut[project_number]]==1) cout<<p->project[i].Number<<" ";
				
			}
			cout<<endl;
			term_credit+=p->project[ToplogicalSort_reslut[project_number]].credit;
			project_number++;
		}
		cout<<"��ѧ��ѧ������Ϊ��"<<term_credit<<endl<<endl;
		cout<<endl;
		
	}
	
	
}


int Draw_menu()//����Ŀ¼ 
{
	int i;
	do{
		system("cls");
		cout<<"---------------��ѧ�ƻ�����ϵͳ---------------"<<endl;
		cout<<"         ��ܰ��ʾ������Ӣ�����뷨�����иó���"<<endl<<endl;
		cout<<"              1.�γ̽���Ŀ¼�Ķ���"<<endl<<endl;
		cout<<"              2.�γ�����"<<endl<<endl;
		cout<<"              3.�γ�ɾ��"<<endl<<endl;
		cout<<"              4.�γ���Ϣ�޸�"<<endl<<endl;
		cout<<"              5. ����һ�������Ľ�ѧ�ƻ������"<<endl<<endl;
		cout<<"              6.�˳�����"<<endl<<endl;	
		cout<<"              ����������ѡ��";
		cin>>i;
		}while(i<1||i>6);
	return i; 	
}



int main()
{
	DGraph *p;
	p=(DGraph*)malloc(sizeof(DGraph));
	int ToplogicalSort_reslut[20];
	memset(ToplogicalSort_reslut,0,sizeof(ToplogicalSort_reslut));
	
	first:
	switch(Draw_menu())
	{
		case 1:{
			system("cls");
			Creat_DGraph(p);
			
			for(int i=1;i<=p->vexnum;i++)
			{
				for(int j=1;j<=p->vexnum;j++) cout<<p->ArcCell[i][j]<<" ";
				cout<<endl;
			}
			
			system("pause"); 
				
			goto first;
		}
		case 2:{
			system("cls");
			Add_project(p);
			for(int i=1;i<=p->vexnum;i++)
			{
				for(int j=1;j<=p->vexnum;j++) cout<<p->ArcCell[i][j]<<" ";
				cout<<endl;
			}
			system("pause");
			goto first;
		}
		case 3:{
			system("cls");
			Delete_project(p);
			for(int i=1;i<=p->vexnum;i++)
			{
				for(int j=1;j<=p->vexnum;j++) cout<<p->ArcCell[i][j]<<" ";
				cout<<endl;
			}
			system("pause");
			goto first;
		}
		case 4:{
			system("cls");
			Information_modify(p);
			system("pause");
			goto first;
		}
		case 5:{
			system("cls");
			ToplogicalSort(p,ToplogicalSort_reslut);
			Output_according_to_teachingplan(p,ToplogicalSort_reslut); 
			system("pause");
			goto first;
		}
	}
	
	return 0;
}
