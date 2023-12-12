#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<string.h>
#include<ctype.h>//检测字符


#define RecordNums 15//结构体数组数量

int NowStudentNums = 0;//当前记录人数


//不使用数据结构
//用结构体数组和文件操作来实现

//学生结构体定义
typedef struct Student
{
	char s_Num[64];//学号
	char s_Name[64];//姓名
	char s_Chinese[64];//语
	char s_Math[64];//数
	char s_English[64];//英
	double s_SumScore;//总分
}Student;


//创建学生结构体数组
Student StuArry[RecordNums];

//创建成绩结构体
typedef struct Score
{
	double SuScore;//subject score
}Score;

//创建成绩结构体——大小同学生结构体数组
Score SoArry[RecordNums];

//创建管理员结构体
typedef struct Admin
{
	char UserName[64];
	char PassWord[64];
}Admin;

//创建一个管理员用户
Admin AdminUser;

//显示全部数据的页面跳转标识
int FlagAI = -1;
//查询找到页面跳转标识
int FlagFPT = -1;
/*
			MainSteps
	1.先搭处图形窗口的大致形态
	2.逐步实现里面的内容
*/

/*
	图形界面实现
*/

//前置声明——查看请跳转到下面查看具体说明
void AdminPage();
void AdminSignIn();
void CommonUserPage();
void SaveInfor();
void ReadInfor();
void ShowAllInfor();
void InputInfor();
void S1mplePrint();
void AdDeSeMoPage();
void DeleteStuInfor();
int ReturnPosi();
void ModifyStudInfor();
void PrintFoudInfor();
void DeSomeStu();
void SortAcChinese();
void SortAcMath();
void SortAcEnglish();
void SortAcSumScore();
bool ScoreFormat(char PerSuSc[]);
//首页
void FirstPage()
{
	//只要进入程序就读取数据——获取当前NowStudentNums
	ReadInfor();

	//窗口大小
	initgraph(760, 760);
	//鼠标操作1
	MOUSEMSG m1;


	cleardevice();
	IMAGE picture1;
	loadimage(&picture1, "./firstbc.jpg", 760, 760);
	putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);




	setfillcolor(GREEN);


	//大标题
	char FirstTitle[20] = { "学生成绩管理系统" };
	settextstyle(60, 0, "黑体");
	outtextxy(150, 100, FirstTitle);

	//三个选项的背景
	fillrectangle(230, 445, 560, 490);
	fillrectangle(230, 505, 560, 550);
	fillrectangle(230, 565, 560, 610);

	setbkmode(TRANSPARENT);

	//三个选项的文字
	settextstyle(40, 0, "黑体");

	//三个选项
	char FirstSelect1[20] = { "管理员操作界面" };
	char FirstSelect2[20] = { "普通用户操作界面" };
	char FirstSelect3[20] = { "退出程序" };
	outtextxy(240, 450, FirstSelect1);
	outtextxy(240, 510, FirstSelect2);
	outtextxy(240, 570, FirstSelect3);

	//进入主界面选项操作界面
	while (1)
	{
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 230 && m1.x <= 560 && m1.y >= 445 && m1.y <= 490)//管理员界面
		{
			setlinecolor(RED);
			rectangle(230, 445, 560, 490);
			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				//加入管理员登录
				AdminSignIn();
			}
		}
		else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 505 && m1.y <= 550)//普通用户界面
		{
			setlinecolor(RED);
			rectangle(230, 505, 560, 550);
			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				CommonUserPage();
			}
		}
		else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 565 && m1.y <= 610)//退出
		{
			setlinecolor(RED);
			rectangle(230, 565, 560, 610);
			if (m1.uMsg == WM_LBUTTONDOWN)
			{
				exit(0);
			}
		}
		//鼠标不在上面悬停
		else
		{
			setlinecolor(WHITE);
			rectangle(230, 445, 560, 490);
			rectangle(230, 505, 560, 550);
			rectangle(230, 565, 560, 610);
		}
	}

}

//管理员界面
void AdminPage()
{
	initgraph(760, 760);
	//先清除一下
	cleardevice();
	//定义第二个鼠标操作
	MOUSEMSG m2;



	cleardevice();
	IMAGE picture1;
	loadimage(&picture1, "./firstbc.jpg", 760, 760);
	putimage(0, 0, &picture1);
	setfillcolor(GREEN);
	setbkmode(TRANSPARENT);

	char SecondTitle1[5] = { "管" };
	char SecondTitle2[5] = { "理" };
	char SecondTitle3[5] = { "员" };
	char SecondTitle4[5] = { "操" };
	char SecondTitle5[5] = { "作" };
	char SecondTitle6[5] = { "界" };
	char SecondTitle7[5] = { "面" };


	settextstyle(50, 0, "黑体");
	outtextxy(50, 150, SecondTitle1);
	outtextxy(50, 210, SecondTitle2);
	outtextxy(50, 270, SecondTitle3);
	outtextxy(50, 330, SecondTitle4);
	outtextxy(50, 390, SecondTitle5);
	outtextxy(50, 450, SecondTitle6);
	outtextxy(50, 510, SecondTitle7);


	setbkmode(TRANSPARENT);


	//三个选项的背景
	fillrectangle(230, 240, 560, 285);
	fillrectangle(230, 370, 560, 415);
	fillrectangle(230, 500, 560, 545);

	setbkmode(TRANSPARENT);

	//三个选项的文字
	settextstyle(40, 0, "黑体");

	//三个选项
	char SecondSelect1[20] = { "显示所有数据" };
	char SecondSelect2[20] = { "增删查改数据" };
	char SecondSelect3[20] = { "返回" };


	outtextxy(270, 240, SecondSelect1);
	outtextxy(270, 370, SecondSelect2);
	outtextxy(350, 500, SecondSelect3);


	//进入主界面选项操作界面
	while (1)
	{
		m2 = GetMouseMsg();//获取鼠标操作
		if (m2.x >= 230 && m2.x <= 560 && m2.y >= 240 && m2.y <= 285)
		{
			setlinecolor(RED);
			rectangle(230, 240, 560, 285);
			if (m2.uMsg == WM_LBUTTONDOWN)
			{
				//显示所有数据
				FlagAI = 1;
				cleardevice();
				ShowAllInfor();

			}
		}
		else if (m2.x >= 230 && m2.x <= 560 && m2.y >= 370 && m2.y <= 415)
		{
			setlinecolor(RED);
			rectangle(230, 370, 560, 415);
			if (m2.uMsg == WM_LBUTTONDOWN)
			{
				//增删查改界面
				cleardevice();
				AdDeSeMoPage();
			}
		}
		else if (m2.x >= 230 && m2.x <= 560 && m2.y >= 500 && m2.y <= 545)
		{
			setlinecolor(RED);
			rectangle(230, 500, 560, 545);
			if (m2.uMsg == WM_LBUTTONDOWN)
			{
				//返回
				cleardevice();
				FirstPage();
			}
		}
		//鼠标不在上面悬停
		else
		{
			setlinecolor(WHITE);
			rectangle(230, 240, 560, 285);
			rectangle(230, 370, 560, 415);
			rectangle(230, 500, 560, 545);
		}
	}

}

//普通用户界面
void CommonUserPage()
{
	initgraph(760, 760); 记得删

		//先清除一下
		cleardevice();
	//定义第二个鼠标操作
	MOUSEMSG m3;

	cleardevice();
	IMAGE picture1;
	loadimage(&picture1, "./firstbc.jpg", 760, 760);
	putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);



	setfillcolor(GREEN);


	char SecondTitle1[5] = { "普" };
	char SecondTitle2[5] = { "通" };
	char SecondTitle3[5] = { "用" };
	char SecondTitle4[5] = { "户" };
	char SecondTitle5[5] = { "操" };
	char SecondTitle6[5] = { "作" };
	char SecondTitle7[5] = { "界" };
	char SecondTitle8[5] = { "面" };


	settextstyle(50, 0, "黑体");
	outtextxy(50, 150, SecondTitle1);
	outtextxy(50, 210, SecondTitle2);
	outtextxy(50, 270, SecondTitle3);
	outtextxy(50, 330, SecondTitle4);
	outtextxy(50, 390, SecondTitle5);
	outtextxy(50, 450, SecondTitle6);
	outtextxy(50, 510, SecondTitle7);
	outtextxy(50, 570, SecondTitle8);


	setbkmode(TRANSPARENT);


	//三个选项的背景

	fillrectangle(230, 240, 560, 285);
	fillrectangle(230, 370, 560, 415);
	fillrectangle(230, 500, 560, 545);

	setbkmode(TRANSPARENT);

	//三个选项的文字
	settextstyle(40, 0, "黑体");

	//三个选项
	char ThirdSelect1[20] = { "显示所有数据" };
	char ThirdSelect2[20] = { "查询数据" };
	char ThirdSelect3[20] = { "返回" };



	outtextxy(270, 240, ThirdSelect1);
	outtextxy(310, 370, ThirdSelect2);
	outtextxy(350, 500, ThirdSelect3);




	//进入主界面选项操作界面
	while (1)
	{
		m3 = GetMouseMsg();//获取鼠标操作
		if (m3.x >= 230 && m3.x <= 560 && m3.y >= 240 && m3.y <= 285)//选项1
		{
			setlinecolor(RED);
			rectangle(230, 240, 560, 285);
			if (m3.uMsg == WM_LBUTTONDOWN)
			{
				//显示所有数据
				FlagAI = -1;
				cleardevice();
				ShowAllInfor();
			}
		}
		else if (m3.x >= 230 && m3.x <= 560 && m3.y >= 370 && m3.y <= 415)//选项2
		{
			setlinecolor(RED);
			rectangle(230, 370, 560, 415);
			if (m3.uMsg == WM_LBUTTONDOWN)
			{
				//查询数据
				FlagFPT = -1;
				PrintFoudInfor();
				CommonUserPage();
			}
		}
		else if (m3.x >= 230 && m3.x <= 560 && m3.y >= 500 && m3.y <= 545)//选项3——返回
		{
			setlinecolor(RED);
			rectangle(230, 500, 560, 545);
			if (m3.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				FirstPage();
			}
		}
		//鼠标不在上面悬停
		else
		{
			setlinecolor(WHITE);
			rectangle(230, 240, 560, 285);
			rectangle(230, 370, 560, 415);
			rectangle(230, 500, 560, 545);
		}
	}
}

/*
	//功能实现//
*/


//录入信息——通过弹窗输入&系统自动计算总分
void InputInfor()
{
	//InputBox中的数字参数——限制输入内容的位数


	//名字可以重复但是学号不能重复
	//通过循环来检查是否有重复的

	//输入学号
	while (1)
	{
		TCHAR InputWindow0[] = _T("请输入该学生的学号");
		InputBox(StuArry[NowStudentNums].s_Num, 9, InputWindow0);

		int FlagInput2 = 0;
		//计算输入的字符串长度
		int nums = strlen(StuArry[NowStudentNums].s_Num);
		//判断输入的是否是纯数字
		for (int i = 0; i < nums; i++)
		{
			if (StuArry[NowStudentNums].s_Num[i] >= '0' && StuArry[NowStudentNums].s_Num[i] <= '9')//如果不是数字
			{

			}
			else
			{
				FlagInput2 = 1;
				HWND hwndInput2 = GetHWnd();
				int isok = MessageBox(hwndInput2, "输入格式有误，请重新输入", "提示", MB_OK);
				break;
			}
		}
		//判断输入的是否是纯数字
		for (int e = 0; e < nums; e++)
		{
			if (StuArry[NowStudentNums].s_Num[e] >= '0' && StuArry[NowStudentNums].s_Num[e] <= '9')//如果不是数字
			{

			}
			else
			{
				FlagInput2 = 1;
				HWND hwndInput2 = GetHWnd();
				break;
				int isok = MessageBox(hwndInput2, "输入格式有误，请重新输入", "提示", MB_OK);

			}
		}

		if (FlagInput2 == 0)
		{
			//判断是否输入重复
			int FlagInput1 = 0;
			for (int i = 0; i < NowStudentNums; i++)
			{
				if (strcmp(StuArry[NowStudentNums].s_Num, StuArry[i].s_Num) == 0)
				{
					FlagInput1 = 1;
				}
			}
			if (FlagInput1 == 1)
			{
				HWND hwndInput1 = GetHWnd();
				int isok = MessageBox(hwndInput1, "该学生已经存在，请重新输入", "提示", MB_OK);
			}
			if (FlagInput1 == 0)
			{
				break;
			}
		}
	}




	//输入姓名
	TCHAR InputWindow1[] = _T("请输入该学生的姓名");
	InputBox(StuArry[NowStudentNums].s_Name, 10, InputWindow1);




	//输入语文成绩
	while (1)
	{
		TCHAR InputWindow2[] = _T("请输入该学生的语文成绩");
		InputBox(StuArry[NowStudentNums].s_Chinese, 4, InputWindow2);

		if (ScoreFormat(StuArry[NowStudentNums].s_Chinese))//为真跳出循环
		{
			break;
		}

	}





	//输入数学成绩
	while (1)
	{
		TCHAR InputWindow3[] = _T("请输入该学生的数学成绩");
		InputBox(StuArry[NowStudentNums].s_Math, 4, InputWindow3);

		if (ScoreFormat(StuArry[NowStudentNums].s_Math))//为真跳出循环
		{
			break;
		}

	}


	//输入英语成绩
	while (1)
	{
		TCHAR InputWindow4[] = _T("请输入该学生的英语成绩");
		InputBox(StuArry[NowStudentNums].s_English, 4, InputWindow4);

		if (ScoreFormat(StuArry[NowStudentNums].s_English))//为真跳出循环
		{
			break;
		}

	}




	//计算总分
	StuArry[NowStudentNums].s_SumScore =
		atof(StuArry[NowStudentNums].s_Chinese) +
		atof(StuArry[NowStudentNums].s_Math) +
		atof(StuArry[NowStudentNums].s_English);

	//保存数据
	SaveInfor();
}

//判断输入的分数格式是否正确
bool ScoreFormat(char PerSuSc[])
{
	//判断输入的是否是纯数字
	int nums = strlen(PerSuSc);
	//判断输入的是否是纯数字
	for (int i = 0; i < nums; i++)
	{
		if (PerSuSc[i] >= '0' && PerSuSc[i] <= '9')//如果不是数字
		{
		}
		else
		{
			HWND hwndInput5 = GetHWnd();
			int isok = MessageBox(hwndInput5, "输入格式有误，请重新输入", "提示", MB_OK);
			return false;
		}
	}
	return true;
}

//增删查改界面
void AdDeSeMoPage()
{


	//鼠标操作
	MOUSEMSG SL;

	//默认将会按照总分排序


	initgraph(860, 760);


	cleardevice();
	IMAGE picture2;
	loadimage(&picture2, "./secondbc.jpg", 860, 760);
	putimage(0, 0, &picture2);
	setbkmode(TRANSPARENT);




	setfillcolor(GREEN);
	fillrectangle(690, 90, 850, 140);//增
	fillrectangle(690, 190, 850, 240);//删
	fillrectangle(690, 290, 850, 340);//查
	fillrectangle(690, 390, 850, 440);//改
	fillrectangle(690, 490, 850, 540);//清空
	fillrectangle(690, 590, 850, 640);//返回

	//表头文字部分
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "黑体");
	outtextxy(0, 0, "排名");
	outtextxy(80, 0, "学号");
	outtextxy(200, 0, "姓名");
	outtextxy(300, 0, "语文");
	outtextxy(400, 0, "数学");
	outtextxy(500, 0, "英语");
	outtextxy(600, 0, "总分");
	outtextxy(740, 0, "选项");
	outtextxy(740, 100, "添加");
	outtextxy(740, 200, "删除");
	outtextxy(740, 300, "查找");
	outtextxy(740, 400, "修改");
	outtextxy(740, 500, "清空");
	outtextxy(740, 600, "返回");


	//打印当前已经有的信息——记录为空的提示也在这里面
	S1mplePrint();

	//进入鼠标操作环节
	while (1)
	{
		SL = GetMouseMsg();
		if (SL.x >= 690 && SL.x <= 850 && SL.y >= 90 && SL.y <= 140)
		{

			setlinecolor(RED);
			rectangle(690, 90, 850, 140);
			if (SL.uMsg == WM_LBUTTONDOWN)
			{
				//添加
				InputInfor();
				cleardevice();
				//完成操作重新载入——刷新
				AdDeSeMoPage();
			}
		}
		else if (SL.x >= 690 && SL.x <= 850 && SL.y >= 190 && SL.y <= 240)
		{

			setlinecolor(RED);
			rectangle(690, 190, 850, 240);
			if (SL.uMsg == WM_LBUTTONDOWN)
			{
				//删除
				DeSomeStu();
				//完成操作重新载入——刷新
				AdDeSeMoPage();
			}
		}
		else if (SL.x >= 690 && SL.x <= 850 && SL.y >= 290 && SL.y <= 340)
		{

			setlinecolor(RED);
			rectangle(690, 290, 850, 340);
			if (SL.uMsg == WM_LBUTTONDOWN)
			{
				FlagFPT = 1;
				//查询
				PrintFoudInfor();
				//完成操作重新载入——刷新
				AdDeSeMoPage();
			}
		}
		else if (SL.x >= 690 && SL.x <= 850 && SL.y >= 390 && SL.y <= 440)
		{
			setlinecolor(RED);
			rectangle(690, 390, 850, 440);
			if (SL.uMsg == WM_LBUTTONDOWN)
			{
				//修改
				ModifyStudInfor();
				//完成操作重新载入——刷新
				AdDeSeMoPage();
			}
		}
		else if (SL.x >= 690 && SL.x <= 850 && SL.y >= 490 && SL.y <= 540)
		{
			setlinecolor(RED);
			rectangle(690, 490, 850, 540);
			if (SL.uMsg == WM_LBUTTONDOWN)
			{
				//确保误删——弹窗加以提示
				HWND hwndDel = GetHWnd();
				int isok = MessageBox(hwndDel, "确认清空?", "提示", MB_OKCANCEL);
				if (isok == IDOK)
				{
					//调用清空函数
					DeleteStuInfor();
					//完成操作重新载入——刷新
					AdDeSeMoPage();
					//弹窗提示
					int tips1 = MessageBox(hwndDel, "清空成功！", "提示", MB_OK);
				}
				else if (isok == IDCANCEL)
				{
					//点击取消不做反应
				}
			}
		}
		else if (SL.x >= 690 && SL.x <= 850 && SL.y >= 590 && SL.y <= 640)
		{
			//返回
			setlinecolor(RED);
			rectangle(690, 590, 850, 640);
			if (SL.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				//完成操作重新载入——刷新
				AdminPage();


				//辅助测试——显示当前人数
				/*char temptps[5];
				sprintf(temptps, "%d", NowStudentNums);


				HWND hwndTemp = GetHWnd();
				int tips2 = MessageBox(hwndTemp, temptps, "提示", MB_OK);*/
			}
		}
		//鼠标不悬停
		else
		{
			setlinecolor(WHITE);
			rectangle(690, 90, 850, 140);//增
			rectangle(690, 190, 850, 240);//删
			rectangle(690, 290, 850, 340);//查
			rectangle(690, 390, 850, 440);//改
			rectangle(690, 490, 850, 540);//清空
			rectangle(690, 590, 850, 640);//返回

		}
	}
}

//保存数据到文件中
void SaveInfor()
{


	//如果学号和姓名都不是空的才写入文件
	if (strlen(StuArry[NowStudentNums].s_Num) != 0 && strlen(StuArry[NowStudentNums].s_Name) != 0)
	{
		FILE* fp = fopen("StudentInforFile.txt", "a");
		if (fp == NULL)
		{
			return;
		}
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%lf\n",
			StuArry[NowStudentNums].s_Num,
			StuArry[NowStudentNums].s_Name,
			StuArry[NowStudentNums].s_Chinese,
			StuArry[NowStudentNums].s_Math,
			StuArry[NowStudentNums].s_English,
			StuArry[NowStudentNums].s_SumScore);
		fclose(fp);
		//保存完毕人数++
		NowStudentNums++;
	}



}

//抹除全部数据再保存——主要用于修改功能
void SaveInforModi()
{
	//先删掉，但是不将人数置空所以不能调用之前的删除函数
	remove("StudentInforFile.txt");
	//如果学号和姓名都不是空的才写入文件
	FILE* fp = fopen("StudentInforFile.txt", "a");
	if (fp == NULL)
	{
		return;
	}
	for (int i = 0; i < NowStudentNums; i++)
	{
		if (strlen(StuArry[i].s_Num) != 0 && strlen(StuArry[i].s_Name) != 0)
		{

			fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%lf\n",
				StuArry[i].s_Num,
				StuArry[i].s_Name,
				StuArry[i].s_Chinese,
				StuArry[i].s_Math,
				StuArry[i].s_English,
				StuArry[i].s_SumScore);
		}
	}

	fclose(fp);
}

//读取文件中的信息-同步到当前结构体数组中,并同步得到NowStudentNums
void ReadInfor()
{
	FILE* fp = fopen("StudentInforFile.txt", "r");
	if (fp == NULL)
	{
		return;
	}
	//将文件中的数据读取到当前的结构体数组中
	for (int i = 0; i < RecordNums; i++)
	{

		fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%lf\t\n",
			StuArry[i].s_Num,
			StuArry[i].s_Name,
			StuArry[i].s_Chinese,
			StuArry[i].s_Math,
			StuArry[i].s_English,
			&StuArry[i].s_SumScore);
	}

	int FileStudentNums = 0;//辅助先得到文件中的人数

	//读取出文件中数据的人数个数
	for (int k = 0; k < RecordNums; k++)
	{
		if (strlen(StuArry[k].s_Name) != 0)
		{
			//当前人数——FileStudentNums不能设全局变量，否则多次读取的时候会出现问题
			NowStudentNums = ++FileStudentNums;
		}
	}
	fclose(fp);
}

//彻底清空——删除文件
void DeleteStuInfor()
{
	//删除文件
	remove("StudentInforFile.txt");
	//置空当前人数
	NowStudentNums = 0;
}

//通用的单纯在屏幕上的对应位置打印出结构体中的每一个元素
void S1mplePrint()
{
	//如果为空就不往下执行
	if (NowStudentNums == 0)
	{

		settextstyle(50, 0, "黑体");
		outtextxy(200, 200, "当前记录为空!");
		return;
	}

	for (int q = 1; q <= NowStudentNums; q++)
	{


		//顺序
		settextstyle(30, 0, "黑体");
		char Nums[5];
		sprintf(Nums, "%d", q);

		//缩放字体
		settextstyle(25, 0, "黑体");
		//学号

		outtextxy(80, 40 + 40 * q, StuArry[q - 1].s_Num);
		//姓名
		outtextxy(200, 40 + 40 * q, StuArry[q - 1].s_Name);
		//语文成绩
		outtextxy(300, 40 + 40 * q, StuArry[q - 1].s_Chinese);
		//数学成绩
		outtextxy(400, 40 + 40 * q, StuArry[q - 1].s_Math);
		//英语成绩
		outtextxy(500, 40 + 40 * q, StuArry[q - 1].s_English);
		//输出总分
		if (strlen(StuArry[q - 1].s_Name) != 0)
		{
			outtextxy(0, 40 + 40 * q, Nums);
			char SuSo[20];
			sprintf(SuSo, "%.2f", StuArry[q - 1].s_SumScore);//小数点后保留两位
			outtextxy(600, 40 + 40 * q, SuSo);
		}
	}
}

//显示所有数据-通用
void ShowAllInfor()
{

	//鼠标操作
	MOUSEMSG SA;
	initgraph(860, 760);
	//默认只是打印数据到屏幕上
	cleardevice();
	IMAGE picture2;
	loadimage(&picture2, "./secondbc.jpg", 860, 760);
	putimage(0, 0, &picture2);

	setfillcolor(GREEN);
	setbkmode(TRANSPARENT);




	fillrectangle(690, 90, 850, 140);
	fillrectangle(690, 190, 850, 240);
	fillrectangle(690, 290, 850, 340);
	fillrectangle(690, 390, 850, 440);
	fillrectangle(690, 590, 850, 640);



	//表头文字部分
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "黑体");
	outtextxy(0, 0, "排名");
	outtextxy(80, 0, "学号");
	outtextxy(200, 0, "姓名");
	outtextxy(300, 0, "语文");
	outtextxy(400, 0, "数学");
	outtextxy(500, 0, "英语");
	outtextxy(600, 0, "总分");
	outtextxy(700, 0, "排序方式");
	outtextxy(700, 100, "按语文排序");
	outtextxy(700, 200, "按数学排序");
	outtextxy(700, 300, "按英语排序");
	outtextxy(700, 400, "按总分排序");

	outtextxy(740, 600, "返回");

	S1mplePrint();//默认只是单纯的打印

	while (1)
	{
		SA = GetMouseMsg();
		if (SA.x >= 690 && SA.x <= 850 && SA.y >= 90 && SA.y <= 140)
		{
			//按语文排
			setlinecolor(RED);
			rectangle(690, 90, 850, 140);
			if (SA.uMsg == WM_LBUTTONDOWN)
			{
				SortAcChinese();
				//刷新重新载入
				ShowAllInfor();

			}
		}
		else if (SA.x >= 690 && SA.x <= 850 && SA.y >= 190 && SA.y <= 240)
		{
			//按数学排
			setlinecolor(RED);
			rectangle(690, 190, 850, 240);
			if (SA.uMsg == WM_LBUTTONDOWN)
			{
				SortAcMath();
				//刷新重新载入
				ShowAllInfor();
			}
		}
		else if (SA.x >= 690 && SA.x <= 850 && SA.y >= 290 && SA.y <= 340)
		{
			//按英语排
			setlinecolor(RED);
			rectangle(690, 290, 850, 340);
			if (SA.uMsg == WM_LBUTTONDOWN)
			{
				SortAcEnglish();
				//刷新重新载入
				ShowAllInfor();
			}
		}
		else if (SA.x >= 690 && SA.x <= 850 && SA.y >= 390 && SA.y <= 440)
		{
			//按照总分排
			setlinecolor(RED);
			rectangle(690, 390, 850, 440);
			if (SA.uMsg == WM_LBUTTONDOWN)
			{
				SortAcSumScore();
				//刷新重新载入
				ShowAllInfor();
			}

		}
		else if (SA.x >= 690 && SA.x <= 850 && SA.y >= 590 && SA.y <= 640)
		{
			//返回
			setlinecolor(RED);
			rectangle(690, 590, 850, 640);
			if (SA.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				//判断从哪个窗口点进来的
				if (FlagAI == 1)
				{
					AdminPage();
				}
				else if (FlagAI == -1)
				{
					CommonUserPage();
				}

			}
		}
		else
		{
			setlinecolor(WHITE);
			rectangle(690, 90, 850, 140);
			rectangle(690, 190, 850, 240);
			rectangle(690, 290, 850, 340);
			rectangle(690, 390, 850, 440);
			rectangle(690, 590, 850, 640);

		}

	}

}

//返回要查找/修改/删除人所在结构体的下标
int ReturnPosi()
{
	//接收用户输入
	char ReceInput[64];
	TCHAR InputWindowFI[] = _T("请输入学号或者姓名进行(查找)(修改)(删除)");
	InputBox(ReceInput, 10, InputWindowFI);

	//进行循环查找，一旦相同就跳出循环
	for (int w = 0; w < NowStudentNums; w++)
	{
		if (strcmp(StuArry[w].s_Name, ReceInput) == 0 || strcmp(StuArry[w].s_Num, ReceInput) == 0)//返回0表示两个字符串相等
		{
			return w;
		}
	}
	//如果没找到这人就返回-1
	return -1;
}


//打印找到人 的信息
void PrintFoudInfor(int Position)
{
	//鼠标操作
	MOUSEMSG PFI;
	initgraph(860, 760);





	cleardevice();
	IMAGE picture2;
	loadimage(&picture2, "./secondbc.jpg", 860, 760);
	putimage(0, 0, &picture2);




	setfillcolor(GREEN);
	fillrectangle(690, 590, 850, 640);
	setbkmode(TRANSPARENT);

	//表头文字部分
	settextstyle(30, 0, "黑体");
	outtextxy(40, 100, "学号");
	outtextxy(200, 100, "姓名");
	outtextxy(300, 100, "语文");
	outtextxy(400, 100, "数学");
	outtextxy(500, 100, "英语");
	outtextxy(600, 100, "总分");
	outtextxy(740, 600, "返回");

	//打印被查找人的信息


	//学号
	outtextxy(40, 140, StuArry[Position].s_Num);
	//姓名
	outtextxy(200, 140, StuArry[Position].s_Name);
	//语文成绩
	outtextxy(300, 140, StuArry[Position].s_Chinese);
	//数学成绩
	outtextxy(400, 140, StuArry[Position].s_Math);
	//英语成绩
	outtextxy(500, 140, StuArry[Position].s_English);
	//输出总分
	char SuSo[20];
	sprintf(SuSo, "%.2f", StuArry[Position].s_SumScore);//小数点后保留两位
	outtextxy(600, 140, SuSo);

	while (1)
	{
		PFI = GetMouseMsg();
		if (PFI.x >= 690 && PFI.x <= 850 && PFI.y >= 590 && PFI.y <= 640)
		{
			//返回
			setlinecolor(RED);
			rectangle(690, 590, 850, 640);
			if (PFI.uMsg == WM_LBUTTONDOWN)
			{
				cleardevice();
				if (FlagFPT == 1)
				{
					AdDeSeMoPage();
				}
				else if (FlagFPT = -1)
				{
					CommonUserPage();
				}
			}
		}
		//鼠标不在选项上
		else
		{
			setlinecolor(WHITE);
			rectangle(690, 590, 850, 640);
		}

	}
}


//查询——这个负责最终的调用
void PrintFoudInfor()
{
	//定义一个变量用来接收下标
	int TempPosi = ReturnPosi();
	if (TempPosi == -1)//没找到
	{
		//获取窗口句柄
		HWND hndtipsF = GetHWnd();
		//用一个字符数组来总结句子
		int isok = MessageBox(hndtipsF, "查无此人!", "提示", MB_OK);
	}
	else//找到了——打印输出
	{
		cleardevice();
		PrintFoudInfor(TempPosi);
	}
}

//修改学生信息，找到返回下标，重新给他赋值，保存，否则直接弹窗警告
void ModifyStudInfor()
{
	//直接套用上面查找的操作，在此基础上加一行修改前
	//因为需要得到要修改人在结构体数组中的位置-下标，所以不能将函数直接拿过来用，得粘贴过来
	//定义一个变量用来接收下标
	int TempModi = ReturnPosi();
	if (TempModi == -1)//没找到
	{
		//获取窗口句柄
		HWND hndtipsM = GetHWnd();
		//用一个字符数组来总结句子
		int isok = MessageBox(hndtipsM, "查无此人!", "提示", MB_OK);
	}
	else//找到了这个学生进行下面的操作
	{
		cleardevice();
		//鼠标操作
		MOUSEMSG Modi;
		initgraph(860, 760);



		IMAGE picture2;
		loadimage(&picture2, "./secondbc.jpg", 860, 760);
		putimage(0, 0, &picture2);


		setfillcolor(GREEN);
		fillrectangle(690, 590, 850, 640);

		//表头文字部分
		setbkmode(TRANSPARENT);
		settextstyle(50, 0, "黑体");
		outtextxy(40, 40, "修改前");
		outtextxy(40, 240, "修改后");
		settextstyle(30, 0, "黑体");
		outtextxy(40, 100, "学号");
		outtextxy(200, 100, "姓名");
		outtextxy(300, 100, "语文");
		outtextxy(400, 100, "数学");
		outtextxy(500, 100, "英语");
		outtextxy(600, 100, "总分");
		outtextxy(740, 600, "返回");

		outtextxy(40, 300, "学号");
		outtextxy(200, 300, "姓名");
		outtextxy(300, 300, "语文");
		outtextxy(400, 300, "数学");
		outtextxy(500, 300, "英语");
		outtextxy(600, 300, "总分");

		//打印被查找人的信息
		//学号
		outtextxy(40, 140, StuArry[TempModi].s_Num);
		//姓名
		outtextxy(200, 140, StuArry[TempModi].s_Name);
		//语文成绩
		outtextxy(300, 140, StuArry[TempModi].s_Chinese);
		//数学成绩
		outtextxy(400, 140, StuArry[TempModi].s_Math);
		//英语成绩
		outtextxy(500, 140, StuArry[TempModi].s_English);
		//输出总分
		if (strlen(StuArry[TempModi].s_Name) != 0)
		{
			char SuSo1[20];
			sprintf(SuSo1, "%.2f", StuArry[TempModi].s_SumScore);//小数点后保留两位
			outtextxy(600, 140, SuSo1);
		}







		//加入输入弹窗——重新书写内容

		//修改学号
		while (1)
		{
			//用于接收输入的学号，先覆盖进去
			char TempModiNums[64];

			TCHAR InputWindow0[] = _T("请输入该学生的学号");
			InputBox(TempModiNums, 9, InputWindow0);

			if (strcmp(TempModiNums, StuArry[TempModi].s_Num) == 0)//如果输入的学号和本身位置的学号相同
			{
				//不作出变化,直接break
				break;
			}
			else//如果输入的学号和本身位置的学号不同，则需要判断与整个结构体中是否有重复的
			{
				int FlagInput3 = 0;

				int nums = strlen(TempModiNums);

				//判断输入的是否是纯数字
				for (int i = 0; i < nums; i++)
				{
					if (TempModiNums[i] >= '0' && TempModiNums[i] <= '9')//如果不是数字
					{

					}
					else
					{
						FlagInput3 = 1;
						HWND hwndInput3 = GetHWnd();
						int isok = MessageBox(hwndInput3, "输入格式有误，请重新输入", "提示", MB_OK);
						break;
					}
				}

				if (FlagInput3 == 0)
				{
					//为什么这里新输入的学号，会显示在结构体数组中存在，
					//因为这是修改函数，上面输入的学号已经覆盖到了他应该取得位置，
					/*
					思路1.先别把要该的值覆盖进去，先进行判断
							判断完成符合条件最后再把值赋给它，
					思路2.将原本的学生结构体数组复制一份
							 在新的结构体数组中遍历判断


							 //这里选择第一种
					*/
					//判断是否输入重复
					int FlagInput4 = 0;
					for (int i = 0; i < NowStudentNums; i++)
					{
						if (strcmp(TempModiNums, StuArry[i].s_Num) == 0)
						{
							FlagInput4 = 1;
							break;
						}
					}
					if (FlagInput4 == 1)
					{
						HWND hwndInput4 = GetHWnd();
						int isok = MessageBox(hwndInput4, "该学生已经存在，请重新输入", "提示", MB_OK);
					}
					else if (FlagInput4 == 0)
					{
						//覆盖
						memcpy(TempModiNums, StuArry[TempModi].s_Num, nums);
						break;
					}
				}
			}
		}

		//修改姓名
		TCHAR InputWindow1[] = _T("请输入该学生的姓名");
		InputBox(StuArry[TempModi].s_Name, 10, InputWindow1);

		//输入语文成绩
		while (1)
		{
			TCHAR InputWindow2[] = _T("请输入该学生的语文成绩");
			InputBox(StuArry[TempModi].s_Chinese, 4, InputWindow2);

			if (ScoreFormat(StuArry[TempModi].s_Chinese))//为真跳出循环
			{
				break;
			}

		}





		//输入数学成绩
		while (1)
		{
			TCHAR InputWindow3[] = _T("请输入该学生的数学成绩");
			InputBox(StuArry[TempModi].s_Math, 4, InputWindow3);

			if (ScoreFormat(StuArry[TempModi].s_Math))//为真跳出循环
			{
				break;
			}

		}


		//输入英语成绩
		while (1)
		{
			TCHAR InputWindow4[] = _T("请输入该学生的英语成绩");
			InputBox(StuArry[TempModi].s_English, 4, InputWindow4);

			if (ScoreFormat(StuArry[TempModi].s_English))//为真跳出循环
			{
				break;
			}

		}

		//计算总分
		StuArry[TempModi].s_SumScore =
			atof(StuArry[TempModi].s_Chinese) +
			atof(StuArry[TempModi].s_Math) +
			atof(StuArry[TempModi].s_English);

		//打印被查找人的信息
		//学号
		outtextxy(40, 340, StuArry[TempModi].s_Num);
		//姓名
		outtextxy(200, 340, StuArry[TempModi].s_Name);
		//语文成绩
		outtextxy(300, 340, StuArry[TempModi].s_Chinese);
		//数学成绩
		outtextxy(400, 340, StuArry[TempModi].s_Math);
		//英语成绩
		outtextxy(500, 340, StuArry[TempModi].s_English);
		//输出总分-加一个限制条件
		if (strlen(StuArry[TempModi].s_Name) != 0)
		{
			char SuSo2[20];
			sprintf(SuSo2, "%.2lf", StuArry[TempModi].s_SumScore);//小数点后保留两位
			outtextxy(600, 340, SuSo2);
		}

		//保存文件
		SaveInforModi();





		while (1)
		{
			Modi = GetMouseMsg();
			if (Modi.x >= 690 && Modi.x <= 850 && Modi.y >= 590 && Modi.y <= 640)
			{
				//返回
				setlinecolor(RED);
				setlinecolor(RED);

				rectangle(690, 590, 850, 640);
				if (Modi.uMsg == WM_LBUTTONDOWN)
				{
					cleardevice();
					//回到增删查改界面
					AdDeSeMoPage();

					//辅助测试——显示当前人数
					/*char temptps[5];
					sprintf(temptps, "%d", NowStudentNums);


					HWND hwndTemp = GetHWnd();
					int tips2 = MessageBox(hwndTemp, temptps, "提示", MB_OK);*/
				}
			}
			//鼠标不悬停
			else
			{
				setlinecolor(WHITE);

				rectangle(690, 590, 850, 640);

			}
		}
	}
}

//删除某个学生的信息
void DeSomeStu()
{
	//先进行查找，找到返回下标，然后依次将该下标后面的数据往前推，最后人数--
	//没找到就查无此人
	//查找
	// 
	//因为要实现的功能不同，所以不能直接调用查找函数
	//定义一个变量用来接收下标
	int TempDelt = ReturnPosi();
	if (TempDelt == -1)//没找到
	{
		//获取窗口句柄
		HWND hndtipsD = GetHWnd();
		//用一个字符数组来总结句子
		int isok = MessageBox(hndtipsD, "查无此人!", "提示", MB_OK);
	}
	else//找到了，确认是否删除
	{
		//找到了就提示是否确定删除
		//获取窗口句柄
		//delete sure?
		HWND hndtipsDS = GetHWnd();
		//用一个字符数组来总结句子
		int isok = MessageBox(hndtipsDS, "确定删除？", "提示", MB_OKCANCEL);
		if (isok == IDOK)
		{
			//确定删除操作
			//将这个元素的后一个依次迁移
			for (int d = TempDelt; d < NowStudentNums - 1; d++)
			{
				StuArry[d] = StuArry[d + 1];
			}
			//现在的人数-1
			NowStudentNums--;
			//删除完成只是将当前结构体里面的数据清除了，但是文件中并没有作出更改
			//更新到文件中
			SaveInforModi();//用这个全部清空的函数，再对文件进行重写
		}
		else if (isok == IDCANCEL)
		{
			//取消删除不执行任何操作
		}
	}

}

//按照语文成绩进行排序
void SortAcChinese()
{
	//使用冒泡排序针对语文成绩对学生进行排序


	//用循环将每个人的成绩都存进成绩的结构体数组
	for (int i = 0; i < NowStudentNums; i++)
	{
		SoArry[i].SuScore = atof(StuArry[i].s_Chinese);
	}
	//对结构体进行排序

	//注意:当用两个结构体进行排序时，即一个结构体辅助另一个结构体进行排序时，
	//注意两个需要同时发生变化，两个结构体都需要发生变化，积累经验

	for (int r = 0; r < NowStudentNums; r++)
	{
		Score TempScore;
		Student TempStudent;
		for (int j = 1; j < NowStudentNums - r; j++)
		{
			if (SoArry[j - 1].SuScore < SoArry[j].SuScore)
			{
				TempScore = SoArry[j];
				TempStudent = StuArry[j];

				SoArry[j] = SoArry[j - 1];
				StuArry[j] = StuArry[j - 1];

				SoArry[j - 1] = TempScore;
				StuArry[j - 1] = TempStudent;
			}
		}
	}
	//不用保存，默认是按照添加的顺序排序
}

//按照数学成绩进行排序
void SortAcMath()
{
	//每次给成绩结构体数组赋值都会被重新覆盖

	//用循环将每个人的成绩都存进成绩的结构体数组
	for (int i = 0; i < NowStudentNums; i++)
	{
		SoArry[i].SuScore = atof(StuArry[i].s_Math);
	}
	//对结构体进行排序

	//注意:当用两个结构体进行排序时，即一个结构体辅助另一个结构体进行排序时，
	//注意两个需要同时发生变化，两个结构体都需要发生变化，积累经验

	for (int t = 0; t < NowStudentNums; t++)
	{
		Score TempScore;
		Student TempStudent;
		for (int j = 1; j < NowStudentNums - t; j++)
		{
			if (SoArry[j - 1].SuScore < SoArry[j].SuScore)
			{
				TempScore = SoArry[j];
				TempStudent = StuArry[j];

				SoArry[j] = SoArry[j - 1];
				StuArry[j] = StuArry[j - 1];

				SoArry[j - 1] = TempScore;
				StuArry[j - 1] = TempStudent;
			}
		}
	}
	//不用保存，默认是按照添加的顺序排序
}

//按照英语成绩进行排序
void SortAcEnglish()
{
	//每次给成绩结构体数组赋值都会被重新覆盖

	//用循环将每个人的成绩都存进成绩的结构体数组
	for (int i = 0; i < NowStudentNums; i++)
	{
		SoArry[i].SuScore = atof(StuArry[i].s_English);
	}
	//对结构体进行排序

	//注意:当用两个结构体进行排序时，即一个结构体辅助另一个结构体进行排序时，
	//注意两个需要同时发生变化，两个结构体都需要发生变化，积累经验
	//因为顺序是一样的，可以把两个想象成一个

	for (int y = 0; y < NowStudentNums; y++)
	{
		Score TempScore;
		Student TempStudent;
		for (int j = 1; j < NowStudentNums - y; j++)
		{
			if (SoArry[j - 1].SuScore < SoArry[j].SuScore)
			{
				TempScore = SoArry[j];
				TempStudent = StuArry[j];

				SoArry[j] = SoArry[j - 1];
				StuArry[j] = StuArry[j - 1];

				SoArry[j - 1] = TempScore;
				StuArry[j - 1] = TempStudent;
			}
		}
	}
	//不用保存，默认是按照添加的顺序排序
}

//按照总分进行排序
void SortAcSumScore()
{
	for (int i = 0; i < NowStudentNums; i++)
	{
		Student TempStudent;
		for (int j = 1; j < NowStudentNums - i; j++)
		{
			if (StuArry[j - 1].s_SumScore < StuArry[j].s_SumScore)
			{

				TempStudent = StuArry[j];


				StuArry[j] = StuArry[j - 1];


				StuArry[j - 1] = TempStudent;
			}
		}
	}
}


//管理员登录
void AdminSignIn()
{
	//打开文件将账号和密码读过来
	FILE* fp = fopen("AdminSignIn.txt", "r");
	if (fp == NULL)
	{
		return;
	}
	//读取到对应的管理员结构体数组
	fscanf(fp, "%s\t%s\t\n", AdminUser.UserName, AdminUser.PassWord);

	//关闭文件
	fclose(fp);




	char ReceAcctNumber[64];
	TCHAR InputAcct[] = _T("请输入用户名");
	InputBox(ReceAcctNumber, 10, InputAcct);

	char ReceAcctPassWord[64];
	TCHAR InputPass[] = _T("请输入密码");
	InputBox(ReceAcctPassWord, 10, InputPass);

	//如果用户名和密码都正确才进度到管理员界面
	//否则弹窗提示错误
	if (strcmp(AdminUser.UserName, ReceAcctNumber) == 0 && strcmp(AdminUser.PassWord, ReceAcctPassWord) == 0)
	{
		cleardevice();
		AdminPage();
	}
	else
	{
		HWND SignError = GetHWnd();
		int isok = MessageBox(SignError, "用户名或密码错误!", "提示", MB_OK);
	}
}



int main(void)
{
	FirstPage();
	return 0;
}