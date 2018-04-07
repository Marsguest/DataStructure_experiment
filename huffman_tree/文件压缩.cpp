#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

void Statistics(FILE *fp,int a[])//ͳ��Ƶ�ʺ��� 
{
	string str="����ͳ�Ƹ��ַ�Ƶ��";
	for(int i=0; i<str.size(); i++)
	{
		Sleep(30);
		cout<<str[i];
	}
	cout<<endl;
	char ch;
	if((fp=fopen("D:\\���ݽṹ\\���ݽṹ������ʵ�鱨��\\source file.txt","r"))==NULL)
	{
		cout<<"cannot open the file"<<endl;
		exit(0);
	}
	ch=fgetc(fp);
	while(ch!=EOF)
	{
		a[ch]++;
		ch=fgetc(fp);
	}
	fclose(fp);
}

typedef struct
{
	char a;
	int b;
}character_weight;//�ַ���������Ӧ��Ȩ�� 

typedef struct
{ 
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;

void CreatHuffmanTree(int character_number,character_weight characters[],HTNode tree[])
{
	for(int i=1;i<=character_number;i++) 
	{
		tree[i].weight=characters[i-1].b;	//������ַ�Ȩֵ�������±��0��ʼ 
		tree[i].parent=0;
		tree[i].lchild=0;
		tree[i].rchild=0;
	}//��ʼ�� 
	
	for(int i=character_number+1;i<=2*character_number-1;i++) 
	{
		tree[i].weight=0;
		tree[i].parent=0;
		tree[i].lchild=0;
		tree[i].rchild=0;
	}
	

	int extra_number=character_number+1;
	while(!tree[2*character_number-1].weight)
	{
		int min1=10000;
		int min_number1;
		int min2=10000;
		int min_number2;
	
		for(int i=1;i<=2*character_number-1;i++)
		{
			if(tree[i].parent==0&&tree[i].weight!=0)
			{
				if(tree[i].weight<min1)
				{
					min1=tree[i].weight;
					min_number1=i;
				}
			}
		}
		tree[min_number1].parent=-1;
		for(int i=1;i<=2*character_number-1;i++)
		{
			if(tree[i].parent==0&&tree[i].weight!=0)
			{
				if(tree[i].weight<min2)
				{
					min2=tree[i].weight;
					min_number2=i;
				}
			}
		}
		tree[min_number1].parent=extra_number;//extra_numberΪ��ǰ���ŵ���ǰ��һ��λ�� 
		tree[min_number2].parent=extra_number;
		
		tree[extra_number].weight=min1+min2;
		tree[extra_number].lchild=min_number1;
		tree[extra_number].rchild=min_number2;
		
		extra_number++;
		
		
	}
	
//	for(int i=1;i<=2*character_number-1;i++)
//	{
//		cout<<tree[i].weight<<" "<<tree[i].parent<<" "<<tree[i].lchild<<" "<<tree[i].rchild<<endl;
//	}//��֤���õĹ������� 
	
	
	
	
	FILE *p2;
	if((p2=fopen("D:\\���ݽṹ\\���ݽṹ������ʵ�鱨��\\HufTree.dat","w"))==NULL)
	{
		cout<<"cannot open the file"<<endl;
		exit(0);
	}
	for(int i=1;i<=2*character_number-1;i++)
	{
		fprintf(p2,"%d",tree[i].weight);
		fprintf(p2," ");
		fprintf(p2,"%d",tree[i].parent);
		fprintf(p2," ");
		fprintf(p2,"%d",tree[i].lchild);
		fprintf(p2," ");
		fprintf(p2,"%d",tree[i].rchild);
		fprintf(p2," ");
	}
	fclose(p2);
//	system("start D:\\���ݽṹ\\���ݽṹ������ʵ�鱨��\\HufTree.dat");
}


void Coding(int character_number,character_weight characters[],HTNode tree[],char cd[257][256])//���������ѹ������ 
{
	cout<<endl;
	Sleep(1000);
	string str="��ʼ���룬����ѹ������";
	for(int i=0; i<str.size(); i++)
	{
		Sleep(30);
		cout<<str[i];
	}
	str="ѹ���ɹ�";
	cout<<endl;
	Sleep(100);
	for(int i=0; i<str.size(); i++)
	{
		Sleep(10);
		cout<<str[i];
	}
	cout<<endl;
	for(int i=1;i<character_number+1;i++) memset(cd[i],'\0',sizeof(cd[i]));//cd��ά�������ڴ��õı��� 
	
	int count_number=0;
	for(int i=1;i<=character_number;i++)
	{
		int count_number=0;
		int code;
		int pre=i;
		int past;
		do
		{
			past=tree[pre].parent;
			code=pre==tree[past].lchild?0:1;
			cd[i][count_number++]=code+48;
			
			pre=past;
		}while(tree[past].parent!=0);
		
	}
	
	for(int i=1;i<character_number+1;i++) strrev(cd[i]);
//	for(int i=1;i<character_number+1;i++) cout<<cd[i]<<endl;   //��֤���� 
	FILE *fp1;
	
	if((fp1=fopen("D:\\���ݽṹ\\���ݽṹ������ʵ�鱨��\\HufCode.txt","w"))==NULL)
	{
		cout<<"cannot open the file"<<endl;
		exit(0);
	}
	for(int i=1;i<character_number+1;i++)
	{
		fprintf(fp1,"%c",characters[i-1]);
		fprintf(fp1," ");
		fprintf(fp1,"%s",cd[i]);
		fprintf(fp1,"\n");
	}
	
	fclose(fp1);

	
	
	
	//����ѹ������ 
	char sourcefile[256];//������ַ��� 
	memset(sourcefile,'\0',sizeof(sourcefile));
	FILE *fp2;
	
	if((fp2=fopen("D:\\���ݽṹ\\���ݽṹ������ʵ�鱨��\\source file.txt","r"))==NULL)
	{
		cout<<"cannot open the file"<<endl;
		exit(0);
	}
	fscanf(fp2,"%s",&sourcefile);
	fclose(fp2);
	
	FILE *fp6;
	if((fp6=fopen("D:\\���ݽṹ\\���ݽṹ������ʵ�鱨��\\CodeFile.dat","w"))==NULL)
	{
		cout<<"cannot open the file"<<endl;
		exit(0);
	}
	for(int i=0;i<strlen(sourcefile);i++)
	{
		for(int j=0;j<character_number;j++)
		{
			if(sourcefile[i]==characters[j].a)
			fprintf(fp6,"%s",cd[j+1]);
		}
	}
	
	
	fclose(fp6);
	

}

void Decompression(int character_number,character_weight characters[],HTNode tree[],char cd[257][256]) //���� 
{
	cout<<endl;
	Sleep(1000);
	string str="���ڽ���";
	for(int i=0; i<str.size(); i++)
	{
		Sleep(30);
		cout<<str[i];
	}
	cout<<endl; 
	Sleep(100);
	str="��ѹ�ɹ�";
	for(int i=0; i<str.size(); i++)
	{
		Sleep(30);
		cout<<str[i];
	}
	cout<<endl;
	
	FILE *fp3;
	char s[1000];//��ѹ���� 
	if((fp3=fopen("D:\\���ݽṹ\\���ݽṹ������ʵ�鱨��\\CodeFile.dat","r"))==NULL)
	{
		cout<<"cannot open the file"<<endl;
		exit(0);
	}	
	fscanf(fp3,"%s",&s);
	char news[256];
	memset(news,'\0',sizeof(news));
	int index=0;
	int pwork=2*character_number-1;//pworkָ��� 
	for(int i=0;i<strlen(s);i++)
	{
		if(s[i]=='0') pwork=tree[pwork].lchild;
		else pwork=tree[pwork].rchild;
		if(tree[pwork].lchild==0&&tree[pwork].rchild==0) 
		{
			news[index++]=characters[pwork-1].a;
			pwork=2*character_number-1;//��ָ�ظ� 
		}
	}
	
	fclose(fp3);
	
	FILE *fp4;
	
	if((fp4=fopen("D:\\���ݽṹ\\���ݽṹ������ʵ�鱨��\\newsourcefile.txt","w"))==NULL)
	{
		cout<<"cannot open the file"<<endl;
		exit(0);
	}	
	fprintf(fp4,"%s",news);
	fclose(fp4);	
	system("start D:\\���ݽṹ\\���ݽṹ������ʵ�鱨��\\newsourcefile.txt");	
	
}

int main()
{
	FILE *fp;
	int frequency[256];//Ƶ������ 
	memset(frequency,0,sizeof(frequency));
	Statistics(fp,frequency);
	int character_number=0;

	for(int i=0;i<255;i++)
	{
		if(frequency[i]!=0) character_number++;
	}
	character_weight characters[character_number];
	int j=0;
	for(int i=0;i<255;i++)
	{
		if(frequency[i]!=0)
		{
			characters[j].a=i;
			characters[j].b=frequency[i];
			j++;
		}
	}
	
	HTNode tree[2*character_number];
	
	
	CreatHuffmanTree(character_number,characters,tree);//�����շ�����
	
	char cd[257][256];//���ڴ�ű��룬�±���һ��ʼͳ�Ƶ�һ�� 
	Coding(character_number,characters,tree,cd);//�����Լ�ѹ���Ĺ��� 
	
	Decompression(character_number,characters,tree,cd);//��ѹ���� 
	
	


	 

	return 0;
} 
