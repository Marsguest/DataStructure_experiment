#include<bits/stdc++.h>
using namespace std;

#define CLASS_MAX_NUMBER 20

struct Project
{
	char Number[10];
	char name[100];
	int credit; 
	bool project_exist;//判断当前课程是否被删去了 
};

struct DGraph
{
	Project project[CLASS_MAX_NUMBER];
	int vexnum;
	int ArcCell[CLASS_MAX_NUMBER][CLASS_MAX_NUMBER];
};

void Creat_DGraph(DGraph *p);//创建有向图
void Add_project(DGraph *p);
void Delete_project(DGraph *p);
void Information_modify(DGraph *p);
void ToplogicalSort(DGraph *p,int ToplogicalSort_reslut[]); //构造拓补序列 
void Output_according_to_teachingplan(DGraph *p,int ToplogicalSort_reslut[]);//按教学计划输出，通过拓补序列 
int Draw_menu();//绘制目录 



void Creat_DGraph(DGraph *p)
{
	cout<<"请输入课程总数"<<endl;
	cin>>p->vexnum;
	cout<<"请依次输入课程编号，课程名称和学分"<<endl;
	for(int i=1;i<=p->vexnum;i++) 
	{
		cin>>p->project[i].Number>>p->project[i].name>>p->project[i].credit;
		p->project[i].project_exist=true;
	}
	memset(p->ArcCell,0,sizeof(p->ArcCell));
	cout<<"请以序偶对的形式输入课程之间的前后关系(按照课程编号)"<<endl;
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
	cout<<"请依次输入要添加的课程编号，课程名称和学分"<<endl;
	cin>>p->project[i].Number>>p->project[i].name>>p->project[i].credit;
	p->project[i].project_exist=true;
	cout<<"请输入该课程前驱课程的数目"<<endl;
	int preclass_number;
	cin>>preclass_number;
	cout<<"请依次输入新添加课程的前驱课程的编号"<<endl;
	int preclass;
	for(int k=0;k<preclass_number;k++) 
	{
		cin>>preclass;
		p->ArcCell[preclass][i]=1;
	}
	
	cout<<"请输入该课程后继课程的数目"<<endl;
	int postclass_number;
	cin>>postclass_number;
	cout<<"请依次输入新添加课程的后继课程的编号"<<endl;
	int postclass;
	for(int k=0;k<postclass_number;k++) 
	{
		cin>>postclass;
		p->ArcCell[i][postclass]=1;
	}
	
}

void Delete_project(DGraph *p)
{
	cout<<"请输入你要输出的课程编号"<<endl;
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
	p->project[delete_project_number].project_exist=false;//当前课程的bool域为零，表示删除 
	cout<<"删除成功"<<endl;
}

void Information_modify(DGraph *p)
{
	cout<<"请输入你想修改的课程编号"<<endl;
	int mod_project_number;
	cin>>mod_project_number;
	int choice;
	cout<<"你想修改的项目为："<<endl;
	cout<<"1.课程名称"<<endl;
	cout<<"2.课程学分"<<endl;
	cin>>choice;
	if(choice==1)
	{
		memset(p->project[mod_project_number].name,'\0',sizeof(p->project[mod_project_number].name));//名称初始化操作 
		cout<<"请输入新的课程名称"<<endl;
		cin>>p->project[mod_project_number].name;
	} 
	if(choice==2)
	{
		cout<<"请输入新的课程学分"<<endl;
		cin>>p->project[mod_project_number].credit;
	}
	cout<<"修改成功"<<endl; 
}

void ToplogicalSort(DGraph *p,int ToplogicalSort_reslut[]) //构造拓补序列 
{
	int indegree[p->vexnum+1];//统计各结点的入度 
	memset(indegree,0,sizeof(indegree));
	for(int i=1;i<=p->vexnum;i++)
		for(int j=1;j<=p->vexnum;j++)
			if(p->ArcCell[i][j]) indegree[j]++;
			
	stack <int> s;
	for(int i=1;i<=p->vexnum;i++)
		if(!indegree[i]) s.push(i);
		
	//开始进行拓补排序
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
	cout<<"拓补序列为："; 
	while(ToplogicalSort_reslut[num]!=0)
		cout<<ToplogicalSort_reslut[num++]<<" ";
	cout<<endl<<endl;
	
}

void Output_according_to_teachingplan(DGraph *p,int ToplogicalSort_reslut[])//按教学计划输出，通过拓补序列 
{
	cout<<"1. 按各学期中的学习负担尽量均匀地制定教学计划。"<<endl;
	cout<<"2. 按尽可能短的时间完成学习，制定教学计划。"<<endl;
	cout<<"你的选择是：";
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
		cout<<"平均学分为:"<<average_credit<<endl;
		
		int term_number=1;
		int i=1,j=0;//i为学期编号，j为拓补序列的下标 
		
		while(remaining_number>=0) 
		{
			int term_credit=0;
			int thisterm_remaining_number=average_credit;//当前学期还能修的学分数 
			cout<<"第"<<i<<"学期:" <<endl;
			if(remaining_number>thisterm_remaining_number)
			{
			
				while(thisterm_remaining_number>0)
				{
					cout<<p->project[ToplogicalSort_reslut[j]].Number<<" ";
					cout<<p->project[ToplogicalSort_reslut[j]].name<<" ";
					cout<<p->project[ToplogicalSort_reslut[j]].credit<<" ";
					cout<<"直接先修课程：";
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
				cout<<"直接先修课程：";
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
			cout<<"本学期学分上限为："<<term_credit<<endl<<endl;
			
		}
		cout<<"学期总数为:"<<i<<endl;

		 
	} 
	else
	{
		int term_credit;
		int term_number=1;
		int project_number=0;
		int project_count=p->vexnum;//记录剩余课程数 
		while(project_count>=5)
		{
			term_credit=0;
			cout<<"第"<<term_number<<"学期:" <<endl;
			for(int k=1;k<=5;k++)
			{
				cout<<p->project[ToplogicalSort_reslut[project_number]].Number<<" ";
				cout<<p->project[ToplogicalSort_reslut[project_number]].name<<" ";
				cout<<p->project[ToplogicalSort_reslut[project_number]].credit<<" ";
				cout<<"直接先修课程：";
				
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
			cout<<"本学期学分上限为："<<term_credit<<endl<<endl;
		}
		term_credit=0;
		cout<<"第"<<term_number<<"学期:" <<endl;
		for(int k=1;k<=project_count;k++)
		{
			cout<<p->project[ToplogicalSort_reslut[project_number]].Number<<" ";
			cout<<p->project[ToplogicalSort_reslut[project_number]].name<<" ";
			cout<<p->project[ToplogicalSort_reslut[project_number]].credit<<" ";
			cout<<"直接先修课程：";
			
				
			for(int i=1;i<=p->vexnum;i++)
			{
				if(p->ArcCell[i][ToplogicalSort_reslut[project_number]]==1) cout<<p->project[i].Number<<" ";
				
			}
			cout<<endl;
			term_credit+=p->project[ToplogicalSort_reslut[project_number]].credit;
			project_number++;
		}
		cout<<"本学期学分上限为："<<term_credit<<endl<<endl;
		cout<<endl;
		
	}
	
	
}


int Draw_menu()//绘制目录 
{
	int i;
	do{
		system("cls");
		cout<<"---------------教学计划编制系统---------------"<<endl;
		cout<<"         温馨提示：请在英文输入法下运行该程序"<<endl<<endl;
		cout<<"              1.课程进修目录的读入"<<endl<<endl;
		cout<<"              2.课程增加"<<endl<<endl;
		cout<<"              3.课程删除"<<endl<<endl;
		cout<<"              4.课程信息修改"<<endl<<endl;
		cout<<"              5. 满足一定条件的教学计划的输出"<<endl<<endl;
		cout<<"              6.退出程序"<<endl<<endl;	
		cout<<"              请输入您的选择：";
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
