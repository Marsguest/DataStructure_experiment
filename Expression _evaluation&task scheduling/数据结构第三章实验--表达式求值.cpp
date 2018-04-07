#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<malloc.h>
#include<string.h>
#include<string>
#include<stack>

using namespace std;
#define stack_init_size 100//栈的初始大小 
#define stackincrement 10//栈的增量 

typedef struct
{
	int *top;
	int *base;
	int stacksize;
}SqStack;

typedef struct	BiTNode
{
	bool tag;//标志域用来确定他是运算符还是操作数 
	//1为操作数，0为运算符 
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTTree;

//函数声明
void InitStack(SqStack &s);			    	//初始化链栈	
int GetTop(SqStack s);                     //读取栈的第一个元素 
void Push(SqStack &s,int e);               //压栈 
void Pop(SqStack &s,int &e);               //出栈 
bool operator_judge(int c);                //判断字符是否为运算符 
char Compare_opetator(int a,int b);        //比较两个运算符的优先级 
int Operate(int a,int theta,int b);        //进行最简单的一维运算 
int Draw_menu();                           //绘制目录
bool Check_Rationality(char s[]);          //容错分析函数
bool sovle_middle(int &result,char s[]);   //解决中缀表达式求值问题 
bool Mid_to_Suffix(char suffixs[]);        //中缀转后缀的函数 
BiTNode *Creat_BiTTree(char suffixs[]);    //后缀转二叉树函数
void visit(BiTNode *T,char s[],int &count);//遍历中的visit函数 
void *PreOrder(BiTNode *T,char Pres[],int &count);//先序遍历
void InOrder(BiTNode *T,char Ins[],int &count);    //中序遍历 
void PostOrder(BiTNode *T,char Posts[],int &count);//后序遍历
void solve_Pres(char Pres[]);                      //解决前缀表达式求值 


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

char Compare_opetator(int a,int b)//运算符优先级比较 
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

int Draw_menu()//绘制目录 
{
	int i;
	do{
		system("cls");
		cout<<"---------------表达式求值及转化程序---------------"<<endl;
		cout<<"         温馨提示：请在英文输入法下运行该程序"<<endl<<endl;
		cout<<"              1.中缀表达式求值"<<endl<<endl;
		cout<<"              2.中缀表达式转换为后缀表达式"<<endl<<endl;
		cout<<"              3.中缀表达式转换为前缀表达式"<<endl<<endl;
		cout<<"              4.后缀表达式求值" <<endl<<endl;
		cout<<"              5.前缀表达式求值"<<endl<<endl;
		cout<<"              6.输入中缀表达式，输出各种形式的表达式"<<endl<<endl;
		cout<<"              请输入您的选择：";
		cin>>i;
		}while(i<1||i>6);
	return i; 	
}

bool Check_Rationality(char s[])//容错分析函数 
{
	bool judge=true;
 	bool judge1=true;
	int count_num=0;
	string s1=s;
	int length=s1.length();
	int count_op=0;
	for(int i=0;i<length;i++)
	{
		if((s[i]<'0'||s[i]>'9')&&(!operator_judge(s[i]))||s[i]=='#') judge=false; //出现未知操作
		
		if(s[i]=='/'&&s[i+1]=='0') judge=false;  //出现分母为0的情况 
		
		if((s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')&&(s[i+1]=='+'||s[i+1]=='-'||s[i+1]=='*'||s[i+1]=='/')) judge=false; //连续运算符 
		
		if(operator_judge(s[i])) count_op++;
		
		if(s[i]<'0'||s[i]>'9') judge1=false;
	}
	if(count_op==0) judge=false;  //仅有操作数，没有运算符 
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
	}//两个for进行括号匹配的判断
	if(judge1) judge=true;
	return judge; 
}


bool sovle_middle(int &result,char s[])//解决中缀表达式求值问题 
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
		if(!operator_judge(s[index]))//如果不是运算符的话 
		{
			while(!operator_judge(s[index]))//当他不是运算符的话 
			{
				count[indexx]=s[index];
				index++;
				indexx++;
			}
			int	c=atoi(count);
			Push(OPND,c);//将一个连续的数压入栈中
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
		cout<<"表达式出错"<<endl;
		return false;
	}	
}


bool Mid_to_Suffix(char suffixs[])//中缀转后缀的函数 
{
	
	cout<<"请输入中缀表达式"<<endl; 
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
		if(!operator_judge(s[index]))//如果不是运算符的话 
		{
			while(!operator_judge(s[index]))//当他不是运算符的话 
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
		cout<<"表达式出错"<<endl;
		return false;
	}
	
}	

BiTNode *Creat_BiTTree(char suffixs[])//后缀转二叉树函数 
{
	stack<BiTTree> Treestack;
	int index=0;
	int indexx=0;
	char count[100];
	memset(count,'\0',sizeof(count));
	while(suffixs[index]!='\0')
	{
		BiTNode *p;
		if(!operator_judge(suffixs[index]))//如果不是运算符的话 
		{
			while(!operator_judge(suffixs[index])&&suffixs[index]!=' ')//当他不是运算符的话 
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

//以下为树的三种遍历函数，利用递归算法 
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


void *PreOrder(BiTNode *T,char Pres[],int &count)//先序遍历 
{
	if(T!=NULL)
	{
		visit(T,Pres,count);
		PreOrder(T->lchild,Pres,count);
		PreOrder(T->rchild,Pres,count);
	}

}

void InOrder(BiTNode *T,char Ins[],int &count)//中序遍历 
{	
	if(T!=NULL)
	{
		InOrder(T->lchild,Ins,count);
		visit(T,Ins,count);
		InOrder(T->rchild,Ins,count);
	}
}

void PostOrder(BiTNode *T,char Posts[],int &count)//后序遍历 
{
	
	if(T!=NULL)
	{
		PostOrder(T->lchild,Posts,count);
		PostOrder(T->rchild,Posts,count);
		visit(T,Posts,count);
	}
}

void solve_Pres(char Pres[])//解决前缀表达式求值 
{
	strrev(Pres);
	char count[100];
	memset(count,'\0',sizeof(count));
	SqStack OPND;
	InitStack(OPND);
	int index=0,indexx=0;
	while(Pres[index]!='\0')
	{
		if(!operator_judge(Pres[index]))//如果不是运算符的话 
		{
			while(!operator_judge(Pres[index])&&Pres[index]!=' ')//当他不是运算符的话 
			{
				count[indexx]=Pres[index];
				index++;
				indexx++;
			}
			strrev(count);
			int	c=atoi(count);
			Push(OPND,c);//将一个连续的数压入栈中	
    	}
    	else//如果是运算符 
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
	cout<<"结果是:"<<GetTop(OPND)<<endl;	
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
			cout<<"请输入中缀表达式"<<endl;
			fflush(stdin);
			cin.get(s,100);
			
			if(sovle_middle(result,s))
			{
				cout<<"结果是："<<result<<endl;
			}
			system("pause"); 
			goto first;
		}
		case 2:{
			
			system("cls");
			char suffixs[100];
			memset(suffixs,'\0',sizeof(suffixs));
			if(Mid_to_Suffix(suffixs))
			cout<<"相应的后缀表达式为："<<endl;
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
			cout<<"相应的前缀表达式为："<<endl;
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
			cout<<"请输入后缀表达式：（注意：相邻操作数和运算符用空格分隔）"<<endl;
			fflush(stdin);
			cin.get(suffixs,100);
			
			BiTNode *root;
			root=Creat_BiTTree(suffixs);
			
			char Ins[100];
			memset(Ins,'\0',sizeof(Ins));
			int count=0;
			
			InOrder(root,Ins,count);
			cout<<"相应的中缀表达式为:"<<Ins<<endl; 
			int result=0;
			if(sovle_middle(result,Ins))
			{
				cout<<"结果是："<<result<<endl;
			}
			
			system("pause");
			goto first;
		}
		
		case 5:{
			system("cls");
			char Pres[100];
			memset(Pres,'\0',sizeof(Pres));
			cout<<"请输入前缀表达式:（注意：相邻操作数和运算符用空格分隔）"<<endl;
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
			cout<<"相应的后缀表达式为："<<endl;
			cout<<suffixs<<endl;	
			BiTNode *root;
			root=Creat_BiTTree(suffixs);
			cout<<"相应的前缀表达式为："<<endl;
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
