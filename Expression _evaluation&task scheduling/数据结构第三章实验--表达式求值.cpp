#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<malloc.h>
#include<string.h>
#include<string>
#include<stack>

using namespace std;
#define stack_init_size 100//ջ�ĳ�ʼ��С 
#define stackincrement 10//ջ������ 

typedef struct
{
	int *top;
	int *base;
	int stacksize;
}SqStack;

typedef struct	BiTNode
{
	bool tag;//��־������ȷ��������������ǲ����� 
	//1Ϊ��������0Ϊ����� 
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTTree;

//��������
void InitStack(SqStack &s);			    	//��ʼ����ջ	
int GetTop(SqStack s);                     //��ȡջ�ĵ�һ��Ԫ�� 
void Push(SqStack &s,int e);               //ѹջ 
void Pop(SqStack &s,int &e);               //��ջ 
bool operator_judge(int c);                //�ж��ַ��Ƿ�Ϊ����� 
char Compare_opetator(int a,int b);        //�Ƚ���������������ȼ� 
int Operate(int a,int theta,int b);        //������򵥵�һά���� 
int Draw_menu();                           //����Ŀ¼
bool Check_Rationality(char s[]);          //�ݴ��������
bool sovle_middle(int &result,char s[]);   //�����׺���ʽ��ֵ���� 
bool Mid_to_Suffix(char suffixs[]);        //��׺ת��׺�ĺ��� 
BiTNode *Creat_BiTTree(char suffixs[]);    //��׺ת����������
void visit(BiTNode *T,char s[],int &count);//�����е�visit���� 
void *PreOrder(BiTNode *T,char Pres[],int &count);//�������
void InOrder(BiTNode *T,char Ins[],int &count);    //������� 
void PostOrder(BiTNode *T,char Posts[],int &count);//�������
void solve_Pres(char Pres[]);                      //���ǰ׺���ʽ��ֵ 


void InitStack(SqStack &s)
{
	s.base=(int *)malloc(stack_init_size*sizeof(int));
	if(!s.base) exit(0);
	s.top=s.base;
	s.stacksize=stack_init_size;
}

int GetTop(SqStack s)
{
	int e;
	if(s.top==s.base)
	{
		cout<<"ERROR";
		exit(0);
	}
	e=*(s.top-1);
	return e;
}

void Push(SqStack &s,int e)
{
	if(s.top-s.base>=s.stacksize)
	{
		s.base=(int *)realloc(s.base,(s.stacksize+stackincrement)*sizeof(int));
		if(!s.base) exit(0);
		
		s.top=s.base+s.stacksize;
		s.stacksize+=stackincrement;
	}
	*s.top++=e;
}


void Pop(SqStack &s,int &e)
{
	if(s.top==s.base) exit(0);
	e=*--s.top;
}

bool operator_judge(int c)
{
	bool ok=false;
	char arr[7]={'+','-','*','/','(',')','#'} ;
	for(int i=0;i<7;i++)
	{
		if(c==arr[i]) {
			ok=true;
			break;
		}
	}
	return ok;
}

char Compare_opetator(int a,int b)//��������ȼ��Ƚ� 
{
	int i,j;
	char map[7][7]={{'>','>','<','<','<','>','>'},
                    {'>','>','<','<','<','>','>'},
                    {'>','>','>','>','<','>','>'},
                    {'>','>','>','>','<','>','>'},
                    {'<','<','<','<','<','=','0'},
                    {'>','>','>','>','0','>','>'},
                    {'<','<','<','<','<','0','='}};
	switch(a){
		case'+':i=0;break;
		case'-':i=1;break;
		case'*':i=2;break;
		case'/':i=3;break;
		case'(':i=4;break;
		case')':i=5;break;
		case'#':i=6;break;
	}
	
	switch(b){
		case'+':j=0;break;
		case'-':j=1;break;
		case'*':j=2;break;
		case'/':j=3;break;
		case'(':j=4;break;
		case')':j=5;break;
		case'#':j=6;break;
	}
    return map[i][j];           	
}

int Operate(int a,int theta,int b)
{
	int c;
	switch(theta)
	{
		case '+':
			c=a+b;
			break;
		case '-':
			c=a-b;
			break;
		case '*':
			c=a*b;
			break;
		case '/':
			c=a/b;
			break;
	}
	return c;
}

int Draw_menu()//����Ŀ¼ 
{
	int i;
	do{
		system("cls");
		cout<<"---------------���ʽ��ֵ��ת������---------------"<<endl;
		cout<<"         ��ܰ��ʾ������Ӣ�����뷨�����иó���"<<endl<<endl;
		cout<<"              1.��׺���ʽ��ֵ"<<endl<<endl;
		cout<<"              2.��׺���ʽת��Ϊ��׺���ʽ"<<endl<<endl;
		cout<<"              3.��׺���ʽת��Ϊǰ׺���ʽ"<<endl<<endl;
		cout<<"              4.��׺���ʽ��ֵ" <<endl<<endl;
		cout<<"              5.ǰ׺���ʽ��ֵ"<<endl<<endl;
		cout<<"              6.������׺���ʽ�����������ʽ�ı��ʽ"<<endl<<endl;
		cout<<"              ����������ѡ��";
		cin>>i;
		}while(i<1||i>6);
	return i; 	
}

bool Check_Rationality(char s[])//�ݴ�������� 
{
	bool judge=true;
 	bool judge1=true;
	int count_num=0;
	string s1=s;
	int length=s1.length();
	int count_op=0;
	for(int i=0;i<length;i++)
	{
		if((s[i]<'0'||s[i]>'9')&&(!operator_judge(s[i]))||s[i]=='#') judge=false; //����δ֪����
		
		if(s[i]=='/'&&s[i+1]=='0') judge=false;  //���ַ�ĸΪ0����� 
		
		if((s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')&&(s[i+1]=='+'||s[i+1]=='-'||s[i+1]=='*'||s[i+1]=='/')) judge=false; //��������� 
		
		if(operator_judge(s[i])) count_op++;
		
		if(s[i]<'0'||s[i]>'9') judge1=false;
	}
	if(count_op==0) judge=false;  //���в�������û������� 
	for(int i=0;i<length;i++)
	{
		if(s1[i]=='(')
		{
			for(int j=i+1;j<length;j++)
			{
				if(s1[j]==')')
				{
					s1[i]=0;
					s1[j]=0;
					break;				
				}
			}
		}
	}
	for(int i=0;i<length;i++)
	{
		if(s1[i]=='('||s1[i]==')') judge=false;
	}//����for��������ƥ����ж�
	if(judge1) judge=true;
	return judge; 
}


bool sovle_middle(int &result,char s[])//�����׺���ʽ��ֵ���� 
{
	char count[100];
	memset(count,'\0',sizeof(count));
	if(Check_Rationality(s))
	{
	int slength=strlen(s);
	s[slength]='#';
	
	
	SqStack OPTR,OPND;
	InitStack(OPTR);
	Push(OPTR,'#');
	InitStack(OPND);
	int index=0,indexx=0;
	while(s[index]!='#'||GetTop(OPTR)!='#')
	{
		if(!operator_judge(s[index]))//�������������Ļ� 
		{
			while(!operator_judge(s[index]))//��������������Ļ� 
			{
				count[indexx]=s[index];
				index++;
				indexx++;
			}
			int	c=atoi(count);
			Push(OPND,c);//��һ����������ѹ��ջ��
	  	}
		else switch(Compare_opetator(GetTop(OPTR),s[index]))
		{
			case '<':
				Push(OPTR,s[index]);
				index++;
				break;
			case '=':
				int x;
				Pop(OPTR,x);
				index++;
				break;
			case '>':
				int theta;
				int a,b;
				Pop(OPTR,theta);
				Pop(OPND,a);
				Pop(OPND,b);
				Push(OPND,Operate(b,theta,a));
				
				
				break;
		}
		indexx=0;
		memset(count,'\0',sizeof(count));
	}
	result=GetTop(OPND);
	return true;
	}
	else
	{
		cout<<"���ʽ����"<<endl;
		return false;
	}	
}


bool Mid_to_Suffix(char suffixs[])//��׺ת��׺�ĺ��� 
{
	
	cout<<"��������׺���ʽ"<<endl; 
	char s[100],count[100];
	memset(count,'\0',sizeof(count));
	memset(s,'\0',sizeof(s));
	fflush(stdin);
	cin.get(s,100);
	if(Check_Rationality(s))
	{
		int slength=strlen(s);
		s[slength]='#';
		SqStack OPTR;
		InitStack(OPTR);
		Push(OPTR,'#');
		int index=0,indexx=0;
		int suffixs_count=0;
	
	while(s[index]!='#'||GetTop(OPTR)!='#')
	{
		if(!operator_judge(s[index]))//�������������Ļ� 
		{
			while(!operator_judge(s[index]))//��������������Ļ� 
			{
				count[indexx]=s[index];
				suffixs[suffixs_count]=s[index];
				index++;
				indexx++;
				suffixs_count++;
			}
			suffixs[suffixs_count]=' ';
			suffixs_count++;
    	}
		else switch(Compare_opetator(GetTop(OPTR),s[index]))
		{
			case '<':
				Push(OPTR,s[index]);
				index++;
				break;
			case '=':
				int x;
				Pop(OPTR,x);
				index++;
				break;
			case '>':
				int theta;
				char optr;
				Pop(OPTR,theta);
				optr=theta;
				suffixs[suffixs_count]=optr;
				suffixs_count++;
				suffixs[suffixs_count]=' ';
				suffixs_count++;
				break;
		}
		indexx=0;
		memset(count,'\0',sizeof(count));	
	}
	cout<<endl;
	return true;
	}
	else
	{
		cout<<"���ʽ����"<<endl;
		return false;
	}
	
}	

BiTNode *Creat_BiTTree(char suffixs[])//��׺ת���������� 
{
	stack<BiTTree> Treestack;
	int index=0;
	int indexx=0;
	char count[100];
	memset(count,'\0',sizeof(count));
	while(suffixs[index]!='\0')
	{
		BiTNode *p;
		if(!operator_judge(suffixs[index]))//�������������Ļ� 
		{
			while(!operator_judge(suffixs[index])&&suffixs[index]!=' ')//��������������Ļ� 
			{
				count[indexx]=suffixs[index]; 
				index++;
				indexx++;
			}
			int	c=atoi(count);
			
			p=(BiTNode*)malloc(sizeof(BiTNode));
			p->tag=1;
			p->data=c;
			p->lchild=NULL;
			p->rchild=NULL;
			index++;
			Treestack.push(p);
		}
		else 
		{
			p=(BiTNode*)malloc(sizeof(BiTNode));
			p->tag=0;
			p->data=suffixs[index];
			p->rchild=Treestack.top();
			Treestack.pop();
			p->lchild=Treestack.top();
			Treestack.pop();	
			index+=2;
			Treestack.push(p);
		}
		indexx=0;
		memset(count,'\0',sizeof(count));
		
		
	}
	BiTNode *root;
	root=Treestack.top();
	return root;
	
}

//����Ϊ�������ֱ������������õݹ��㷨 
void visit(BiTNode *T,char s[],int &count)
{
	count=strlen(s);
	if(T->tag==1) 
	{
		sprintf(s+count,"%d",T->data);
	}
	else
	{
		char c=T->data;
		s[count]=c;
	}
} 


void *PreOrder(BiTNode *T,char Pres[],int &count)//������� 
{
	if(T!=NULL)
	{
		visit(T,Pres,count);
		PreOrder(T->lchild,Pres,count);
		PreOrder(T->rchild,Pres,count);
	}

}

void InOrder(BiTNode *T,char Ins[],int &count)//������� 
{	
	if(T!=NULL)
	{
		InOrder(T->lchild,Ins,count);
		visit(T,Ins,count);
		InOrder(T->rchild,Ins,count);
	}
}

void PostOrder(BiTNode *T,char Posts[],int &count)//������� 
{
	
	if(T!=NULL)
	{
		PostOrder(T->lchild,Posts,count);
		PostOrder(T->rchild,Posts,count);
		visit(T,Posts,count);
	}
}

void solve_Pres(char Pres[])//���ǰ׺���ʽ��ֵ 
{
	strrev(Pres);
	char count[100];
	memset(count,'\0',sizeof(count));
	SqStack OPND;
	InitStack(OPND);
	int index=0,indexx=0;
	while(Pres[index]!='\0')
	{
		if(!operator_judge(Pres[index]))//�������������Ļ� 
		{
			while(!operator_judge(Pres[index])&&Pres[index]!=' ')//��������������Ļ� 
			{
				count[indexx]=Pres[index];
				index++;
				indexx++;
			}
			strrev(count);
			int	c=atoi(count);
			Push(OPND,c);//��һ����������ѹ��ջ��	
    	}
    	else//���������� 
    	{
    		int a,b;
    		Pop(OPND,a);
			Pop(OPND,b);
			Push(OPND,Operate(b,Pres[index],a));
			index++;
    	}
    	indexx=0;
    	index++; 
		memset(count,'\0',sizeof(count));
	}
	cout<<"�����:"<<GetTop(OPND)<<endl;	
}

int main()
{
	first:
	switch(Draw_menu())
	{
		case 1:{
			
		
			system("cls");
			int result;
			char s[100];
			memset(s,'\0',sizeof(s));
			cout<<"��������׺���ʽ"<<endl;
			fflush(stdin);
			cin.get(s,100);
			
			if(sovle_middle(result,s))
			{
				cout<<"����ǣ�"<<result<<endl;
			}
			system("pause"); 
			goto first;
		}
		case 2:{
			
			system("cls");
			char suffixs[100];
			memset(suffixs,'\0',sizeof(suffixs));
			if(Mid_to_Suffix(suffixs))
			cout<<"��Ӧ�ĺ�׺���ʽΪ��"<<endl;
			cout<<suffixs<<endl;
			system("pause"); 
			goto first;
		}
		case 3:{
			
			system("cls");
			char suffixs[100];
			memset(suffixs,'\0',sizeof(suffixs));
			Mid_to_Suffix(suffixs);
			BiTNode *root;
			root=Creat_BiTTree(suffixs);
			cout<<"��Ӧ��ǰ׺���ʽΪ��"<<endl;
			char Pres[100];
			memset(Pres,'\0',sizeof(Pres));
			int count=0;
			PreOrder(root,Pres,count);
			cout<<Pres<<endl; 
			system("pause");
			goto first;
		}
			
		
		case 4:{
			system("cls");
			char suffixs[100];
			memset(suffixs,'\0',sizeof(suffixs));
			cout<<"�������׺���ʽ����ע�⣺���ڲ�������������ÿո�ָ���"<<endl;
			fflush(stdin);
			cin.get(suffixs,100);
			
			BiTNode *root;
			root=Creat_BiTTree(suffixs);
			
			char Ins[100];
			memset(Ins,'\0',sizeof(Ins));
			int count=0;
			
			InOrder(root,Ins,count);
			cout<<"��Ӧ����׺���ʽΪ:"<<Ins<<endl; 
			int result=0;
			if(sovle_middle(result,Ins))
			{
				cout<<"����ǣ�"<<result<<endl;
			}
			
			system("pause");
			goto first;
		}
		
		case 5:{
			system("cls");
			char Pres[100];
			memset(Pres,'\0',sizeof(Pres));
			cout<<"������ǰ׺���ʽ:��ע�⣺���ڲ�������������ÿո�ָ���"<<endl;
			fflush(stdin);
			cin.get(Pres,100);
			solve_Pres(Pres);
			
			system("pause");
			goto first; 
			
		}
		
		case 6:{
			system("cls");
			char suffixs[100];
			memset(suffixs,'\0',sizeof(suffixs));
			if(Mid_to_Suffix(suffixs))
			cout<<"��Ӧ�ĺ�׺���ʽΪ��"<<endl;
			cout<<suffixs<<endl;	
			BiTNode *root;
			root=Creat_BiTTree(suffixs);
			cout<<"��Ӧ��ǰ׺���ʽΪ��"<<endl;
			char Pres[100];
			memset(Pres,'\0',sizeof(Pres));
			int count=0;
			PreOrder(root,Pres,count);
			cout<<Pres<<endl; 
			system("pause"); 
			goto first;
		}		
	}
} 
