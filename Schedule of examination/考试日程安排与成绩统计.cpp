#include<bits/stdc++.h> 
using namespace std;

struct Student
{
	int student_id;
	char name[50];
	int class_number;
	int course1_score;
	int course2_score;
	int course3_score;
	int sum_score;
} ;
struct Class
{
	int front_st;//指向本班第一个学生 
	int course1_num;
	int course2_num;
	int course3_num;
};

int Draw_menu()//绘制目录 
{
	int i;
	do{
		system("cls");
		cout<<"---------------考试日程安排与成绩统计---------------"<<endl;
		cout<<"         温馨提示：请在英文输入法下运行该程序"<<endl<<endl;
		cout<<"              1.整个年级总排名"<<endl<<endl;
		cout<<"              2.分班级按照考试总分从高到低"<<endl<<endl;
		cout<<"              3.输出指定班的学生考试成绩信息。"<<endl<<endl;
		cout<<"              4.总分从高到低分段输出"<<endl<<endl;
		cout<<"              5.指定的某课程的成绩"<<endl<<endl;	
		cout<<"              6.统计并输出指定班级中总成绩或某一门课成绩的各分数段人数"<<endl<<endl;
		cout<<"              7.查找指定学生（给定学号）的具体信息"<<endl<<endl;
		cin>>i;
		}while(i<1||i>7);
	return i; 	
}

bool cmp(Student a,Student b)
{
	return a.sum_score>b.sum_score;
}




void first_sort(Student student[])
{
	sort(student,student+20,cmp);
	for(int i=0;i<20;i++)
	{
		cout<<student[i].student_id<<" "<<student[i].name<<" "<<student[i].class_number<<" "<<student[i].course1_score<<" "<<student[i].course2_score<<" "<<student[i].course3_score<<" "<<student[i].sum_score<<endl;
	}
}

void second_sort(Student student[])
{
	for(int i=0;i<20;i+=2) 
	{
		Student *p;
		p=&student[i];
		sort(p,p+2,cmp);
	}
	for(int i=0;i<20;i++)
	{
		cout<<student[i].student_id<<" "<<student[i].name<<" "<<student[i].class_number<<" "<<student[i].course1_score<<" "<<student[i].course2_score<<" "<<student[i].course3_score<<" "<<student[i].sum_score<<endl;
	}
}

struct Average
{
	double average;
	int tag;//标志域，1表示第一档90以上 
};

void function_four(Student student[]) 
{
	Average average[20];
	for(int i=0;i<20;i++)
	{
		average[i].average=student[i].sum_score/3.0;
		if(average[i].average>=90) average[i].tag=1;
		else if(average[i].average>=80) average[i].tag=2;
		else if(average[i].average>=70) average[i].tag=3;
		else if(average[i].average>=60) average[i].tag=4;
		else average[i].tag=5;
	}
	
	for(int k=1;k<6;k++)
	{
		switch(k)
		{
			case 1:cout<<"90分以上:"<<endl;break;
			case 2:cout<<"80~89分:"<<endl;break;
			case 3:cout<<"70~79分:"<<endl;break;
			case 4:cout<<"60~69分:"<<endl;break;
			case 5:cout<<"60分以下:"<<endl;break;
		}
		for(int i=0;i<20;i++)
		{
			if(average[i].tag==k) cout<<student[i].student_id<<" "<<student[i].name<<" "<<student[i].class_number<<" "<<student[i].course1_score<<" "<<student[i].course2_score<<" "<<student[i].course3_score<<" "<<student[i].sum_score<<endl;
		}
		
	}
	
}

struct onecourse
{
	Student student[2];
	int course_number;
}; 

struct easy_student
{
	int student_id;
	char name[50];
	int class_number;
	int score;
};

bool cmp1(easy_student a,easy_student b)
{
	return a.score>b.score;
}

void function_five(Student student[],int course[10][3])
{
	cout<<"请输入课程编号：";
	int a;
	cin>>a;
	onecourse	onecourse[10];
	for(int i=0;i<5;i++) onecourse[i].course_number=0;
	int index=0;
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(course[i][j]==a) 
			{
				onecourse[index].student[0]=student[i*2];
				onecourse[index].student[1]=student[i*2+1];
				onecourse[index].course_number=j+1;
				index++;
			}
		}
	}
	
	
	int i=0;
	while(onecourse[i].course_number!=0) i++;

//	for(int k=0;k<i;k++)
//	{
//		cout<<onecourse[k].student[0].name<<" "<<onecourse[k].student[1].name<<endl;
//	}
	
	easy_student student1[2*i];
	index=0;
	for(int k=0;k<(2*i);k+=2)
	{
		if(onecourse[index].course_number==1) 
		{
			student1[k].score=onecourse[index].student[0].course1_score;
			student1[k+1].score=onecourse[index].student[1].course1_score;
		}
		else if(onecourse[index].course_number==2) 
		{
			student1[k].score=onecourse[index].student[0].course2_score;
			student1[k+1].score=onecourse[index].student[1].course2_score;
		}
		else 
		{
			student1[k].score=onecourse[index].student[0].course3_score;
			student1[k+1].score=onecourse[index].student[1].course3_score;
		}
		
		student1[k].student_id=onecourse[index].student[0].student_id;
		student1[k+1].student_id=onecourse[index].student[1].student_id;
		strcpy(student1[k].name,onecourse[index].student[0].name);
		strcpy(student1[k+1].name,onecourse[index].student[1].name);
		student1[k].class_number=onecourse[index].student[0].class_number;
		student1[k+1].class_number=onecourse[index].student[1].class_number;
		index++;
	}
	cout<<"学号 姓名 班级 该科成绩"<<endl;
	sort(student1,student1+(2*i),cmp1);
	for(int j=0;j<(2*i);j++)
	{
		cout<<student1[j].student_id<<" "<<student1[j].name<<" "<<student1[j].class_number<<" "<<student1[j].score<<endl;
	}										
}

void function_six(Student student[],int course[10][3])
{
	
	cout<<"1.总成绩分段人数统计"<<endl<<"2.某课程分段人数统计"<<endl;
	int a;
	cin>>a;
	cout<<"选择班级"<<endl;
	int classnumber;
	cin>>classnumber;
	if(a==1)
	{
		
	
		
		Average average[2];
		for(int i=2*(classnumber-1);i<2*classnumber;i+=2)
		{
			average[0].average=student[i].sum_score/3.0;
			if(average[0].average>=90) average[i].tag=1;
			else if(average[0].average>=80) average[i].tag=2;
			else if(average[0].average>=70) average[i].tag=3;
			else if(average[0].average>=60) average[i].tag=4;
			else average[0].tag=5;
			
			average[1].average=student[i+1].sum_score/3.0;
			if(average[1].average>=90) average[1].tag=1;
			else if(average[1].average>=80) average[1].tag=2;
			else if(average[1].average>=70) average[1].tag=3;
			else if(average[1].average>=60) average[1].tag=4;
			else average[1].tag=5;
			
		}
		
		for(int k=1;k<6;k++)
		{
			switch(k)
			{
				case 1:cout<<"90分以上:"<<endl;break;
				case 2:cout<<"80~89分:"<<endl;break;
				case 3:cout<<"70~79分:"<<endl;break;
				case 4:cout<<"60~69分:"<<endl;break;
				case 5:cout<<"60分以下:"<<endl;break;
			}

				if(average[0].tag==k) 
				cout<<student[2*(classnumber-1)].student_id<<" "<<student[2*(classnumber-1)].name<<" "<<student[2*(classnumber-1)].class_number<<" "<<student[2*(classnumber-1)].course1_score<<" "<<student[2*(classnumber-1)].course2_score<<" "<<student[2*(classnumber-1)].course3_score<<" "<<student[2*(classnumber-1)].sum_score<<endl;
				if(average[1].tag==k) 
				cout<<student[2*classnumber-1].student_id<<" "<<student[2*classnumber-1].name<<" "<<student[2*classnumber-1].class_number<<" "<<student[2*classnumber-1].course1_score<<" "<<student[2*classnumber-1].course2_score<<" "<<student[2*classnumber-1].course3_score<<" "<<student[2*classnumber-1].sum_score<<endl;
		}
	}
	else
	{
		cout<<"本班级开设的课程有"<<course[classnumber-1][0]<<" "<<course[classnumber-1][1]<<" "<<course[classnumber-1][2]<<endl;
		int choice;
		cin>>choice;
		int a[5]={0};
		if(choice==1)
		{
			for(int i=2*(classnumber-1);i<2*classnumber;i++)
			{
				if(student[i].course1_score>90) a[0]++;
				else if(student[i].course1_score>80) a[1]++;
				else if(student[i].course1_score>70) a[2]++;
				else if(student[i].course1_score>60) a[3]++;
				else a[4]++;
			}
		}
		else if(choice==2)
		{
			for(int i=2*(classnumber-1);i<2*classnumber;i++)
			{
				if(student[i].course2_score>90) a[0]++;
				else if(student[i].course2_score>80) a[1]++;
				else if(student[i].course2_score>70) a[2]++;
				else if(student[i].course2_score>60) a[3]++;
				else a[4]++;
			}
		}
		else
		{
			for(int i=2*(classnumber-1);i<2*classnumber;i++)
			{
				if(student[i].course3_score>90) a[0]++;
				else if(student[i].course3_score>80) a[1]++;
				else if(student[i].course3_score>70) a[2]++;
				else if(student[i].course3_score>60) a[3]++;
				else a[4]++;
			}
		}
		cout<<"90分以上:"<<a[0]<<"人"<<endl;
		cout<<"80~89分:"<<a[1]<<"人"<<endl;
		cout<<"70~79分:"<<a[2]<<"人"<<endl;
		cout<<"60~69分:"<<a[3]<<"人"<<endl;
		cout<<"60分以下:"<<a[4]<<"人"<<endl;
		
	}
}

int main()
{
	cout<<"请输入各班级要考的课程编号："<<endl;
	int course[10][3];
	for(int i=0;i<10;i++)
	{
		cin>>course[i][0]>>course[i][1]>>course[i][2];
	}
	int conflict_course[10][10]={0};
	for(int i=0;i<10;i++)
	{
		conflict_course[course[i][0]][course[i][1]]=1;
		conflict_course[course[i][1]][course[i][0]]=1;
		
		conflict_course[course[i][0]][course[i][2]]=1;	
		conflict_course[course[i][2]][course[i][0]]=1;
		
		conflict_course[course[i][1]][course[i][2]]=1;
		conflict_course[course[i][2]][course[i][1]]=1;
	}

	int clash[10]={0};//中介数组为了使查询冲突变快 
	int result[10]={0};//结果数组，用来存各个课程所在的子集编号
	int count=0;//子集序号
	int pre=10; 
	
	queue <int> q1;

	for(int i=0;i<10;i++) q1.push(i);

	
	while(!q1.empty())
	{
		
		int key=q1.front();
		q1.pop();
		if(key<=pre)	//刚出队元素小于前一个出队元素，生成一个新子集
		{
			count++;
			memset(clash,0,sizeof(clash));
		}
	
		
		if(clash[key]==0) 
		{
			result[key]=count;
			for(int i=0;i<10;i++)
			{
				clash[i]+=conflict_course[key][i];
			}
		}
		else q1.push(key);
		pre=key;
	} 

	cout<<"共分为以下几个时间段考试：(给出的是课程编号)"<<endl;
	int max=0;
	for(int i=0;i<10;i++)
	{
		if(max<result[i]) max=result[i];
	}
	int p=1;

	while(p<=max)
	{
		cout<<"第"<<p<<"个时间段:"; 
		for(int i=0;i<10;i++)
		{
			if(result[i]==p) cout<<i<<" ";
		}
		p++;
		cout<<endl;
	}
	system("pause");
	Student student[20];
	Class classes[10];
	system("cls");
	cout<<"请输入各个学生信息，依次为学号，姓名，班级，三科成绩:"<<endl; 
	for(int i=0;i<20;i++)
	{
		cin>>student[i].student_id>>student[i].name>>student[i].class_number>>student[i].course1_score>>student[i].course2_score>>student[i].course3_score;
		student[i].sum_score=student[i].course1_score+student[i].course2_score+student[i].course3_score;
	}
	for(int i=0;i<10;i++)
	{
		classes[i].course1_num=course[i][0];
		classes[i].course2_num=course[i][1];
		classes[i].course3_num=course[i][2];
		classes[i].front_st=i*2;
	}//初始化操作
	first:
	switch(Draw_menu())
	{
		case 1:{
			system("cls");
			cout<<"学号 姓名 班级 三科成绩 总成绩"<<endl;
			Student student_fuben_1[20];
			for(int i=0;i<20;i++){
				student_fuben_1[i]=student[i];
			}
			first_sort(student_fuben_1);
			system("pause");
			goto first;
		}
		case 2:{
			system("cls");
			cout<<"学号 姓名 班级 三科成绩 总成绩"<<endl;
			Student student_fuben_2[20];
			for(int i=0;i<20;i++){
				student_fuben_2[i]=student[i];
			}
			second_sort(student_fuben_2);
			system("pause");
			goto first;
		}
		case 3:{
			system("cls");
			int class_number;
			cout<<"请选择班级:";
			cin>>class_number;
			cout<<"学号 姓名 班级 三科成绩 总成绩"<<endl;
			for(int i=(class_number-1)*2;i<class_number*2;i++)
			{
				cout<<student[i].student_id<<" "<<student[i].name<<" "<<student[i].class_number<<" "<<student[i].course1_score<<" "<<student[i].course2_score<<" "<<student[i].course3_score<<" "<<student[i].sum_score<<endl;
	
			}
			system("pause");
			goto first;
		}
		case 4:{
			system("cls");
			Student student_fuben_3[20];
			for(int i=0;i<20;i++){
				student_fuben_3[i]=student[i];
			}
			function_four(student_fuben_3); 
			system("pause");
			goto first;
		}
		case 5:{
			system("cls");
			function_five(student,course); 
			system("pause");
			goto first;
		}
		case 6:{
			system("cls");
			function_six(student,course);
			system("pause");
			goto first;
		}
		case 7:{
			system("cls");
			cout<<"请输入学号:"<<endl; 
			int num;
			cin>>num;
			cout<<"学号 姓名 班级 三科成绩 总成绩"<<endl;
			for(int i=0;i<20;i++)
			{
				if(student[i].student_id==num) 
				{
					cout<<student[i].student_id<<" "<<student[i].name<<" "<<student[i].class_number<<" "<<student[i].course1_score<<" "<<student[i].course2_score<<" "<<student[i].course3_score<<" "<<student[i].sum_score<<endl;
					break;
				}
			}
			system("pause");
			goto first;
		}
	}
	
	return 0;
}
