#include <graphics.h>
#include <conio.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

void Control(  char & c , int & i,int & j);	//蛇函数声明
int Rule(int X,int Y,int L[31][23]);				//规则函数声明
void Start();												//初始界面函数声明
void Border();											//边框函数声明
void Food( int L[31][23] );							//食物函数声明 
void Snake();											//消除蛇身最后一块函数声明
void Remove(int L[31][23]);						//控制方向函数声明

int Score=0;			//初始化得分为0
int CA=4;				//初始化数字4位置上的颜色需要擦掉
int SL=400;			//蛇初始停留时间  控制初始速度
int NUM=0;			//用来计食物的数量
int Difficulty=1;		//用来计难度

/**主函数**/
int main()
{	srand( (unsigned)time(NULL) );	//用当前时间来做随机种子	
	initgraph(800, 480); 						//初始化大小为800*480 单位为像素的图形区域
	Start();											//调用初始界面函数 游戏画面展开
	closegraph();								//游戏结束
	return 27;										//返回27用来重新开始游戏
}

/**蛇函数**/
void Snake()
{	int x=320,y=240;		//图形区中心坐标（x，y）
	int X=15,Y=11;			//数组中心位置（X,Y）
	char k=72;				//用来确定按下的键
	char c[10];				//用来把int类的分数改为字符串类型便于在屏幕上输出
	int n,m,I,J,L[31][23];	//用来确定蛇的位置
	for(I=0;I<31;I++)		//将数组中全部存为0
		for(J=0;J<23;J++)
		L[I][J]=0;
	m=0; n=-20;				//让蛇的开始运动方向为向上
	Border();					//调用边框函数画出边框
	Food(L);					//调用食物函数  随机生成食物

	//蛇的移动
	for(x,y; k!=27 ; x+=m,y+=n)		//k！=27代表按下esc键跳出循环	
	{	
		settextstyle(20,0, "楷体");		//设置字体样式: 字体高度为100像素, 宽度不指定, 字体名称为"楷体"
		sprintf_s(c,"%d",Score);			//把int格式的Score转化为字符串形式的c，并在下一条语句中输出在画布上
		outtextxy(730,30, ("%s",c));	//在指定位置输出文本
		sprintf_s(c,"%d",Score+3);	//把int格式的Score转化为字符串形式的c，并在下一条语句中输出在画布上
		outtextxy(730,70, ("%s",c));	//在指定位置输出文本
		sprintf_s(c,"%d",Difficulty);	//把int格式的Score转化为字符串形式的c，并在下一条语句中输出在画布上
		outtextxy(730,110, ("%s",c)); //在指定位置输出文本
		X=(x/20)-1;Y=(y/20)-1;			//更新数组中的坐标
		if(Rule(X,Y,L)==1) break;		//调用规则函数判断是否违反游戏规则
		for(I=0;I<31;I++)
			for(J=0;J<23;J++)
				if(L[I][J]>0)																				//找出蛇身
				{	setfillcolor(LIGHTBLUE);
					setlinecolor(WHITE);																//蛇身颜色 白+亮蓝
					fillrectangle((I+1)*20-8,(J+1)*20-8,(I+1)*20+8,(J+1)*20+8);	//更新蛇身位置
					L[I][J]+=1;																				//蛇身数字加1
				}		
		if(L[X][Y]!=-1) Remove(L);					//如果没吃食物就把最后一个擦掉
		else { Food(L) ; Score++;CA++ ;}		//吃到食物时，长度加1 ，分数+1，再生成一个食物	
		L[X][Y]=1;											//蛇头定为1
		setlinestyle(PS_SOLID, 2);					//定义蛇身边框宽度2
		setfillcolor(LIGHTBLUE);
		setlinecolor(WHITE);							//蛇头颜色 白+亮蓝 
		fillcircle(x,y,8);									//更新蛇头位置
		Sleep(SL*2/3);									//蛇移动一次共停留SL毫秒
		Control( k ,m , n );								//调用 控制方向函数 改变蛇的运动方向 
		Sleep(SL/3);										//停留SL/3毫秒来显示按方向键效果
  		IMAGE img2;														// 定义 IMAGE 对象
		loadimage(&img2, _T("image\\按方向前.jpg"));	// 读取图片到 img 对象中
		putimage(642, 320, &img2);									// 在坐标 (0, 0) 位置显示 IMAGE 对象
	}
	//游戏结束后初始化数据
	Score=0;
	CA=4;
	SL=400;
	NUM=0;
	for(I=0;I<100;I++)						//给100次按键的机会
	{		k=_getch();							//提示按键
		if(k==13)									//当按下回车
		{	closegraph();	k=main();	}	//调用主函数 重新开始游戏
		if(k==27)									//当按下	esc   退出游戏
		{	break;	}
		else ;
	}
}

/**规则函数**/
int Rule(int X,int Y,int L[31][23])
{	char c[10];															//用来把int类的分数改为字符串类型便于在屏幕上输出
	if( (X<0)||(X>30)||(Y<0)||(Y>22)||(L[X][Y]>0))			//如果撞到边界或者蛇身就失败
	{	setlinestyle(PS_SOLID,2);
		setfillcolor(BLACK);											//设置提示框背景颜色 黑色 
		fillrectangle(160,180,480,350);
		setcolor(WHITE);												//设置字体颜色   
		settextstyle(30,0, "楷体");									//设置字体样式: 字体高度为100像素, 宽度不指定, 字体名称为"楷体"
		sprintf_s(c,"%d",Score);										//把int格式的Score转化为字符串形式的c，并在下一条语句中输出在画布上
		outtextxy(170, 190, ("您输了！当前得分:"));		//在指定位置输出文本
		outtextxy(420, 190, ("%s",c));								//在指定位置输出文本
		outtextxy(170, 250, ("是否重新开始游戏？ "));	//在指定位置输出文本
		outtextxy(170, 310, ("是(回车)  否（esc）"));		//在指定位置输出文本
		rectangle(162,182,478,348);								//设置提示框边框和字颜色 白色
		return 1;
	}
	return 0;
}

/**初始界面函数**/
void Start()
{	loadimage(0,  "image\\游戏封面.png"	);	//显示封面图片
	_getch();													//按任意键开始游戏
	double x,y,a=0;	
	setlinecolor(BLACK);									//定义线条颜色为黑色
	for(a=0;a<6.29;a+=0.0001)						//用黑色线条旋转覆盖图片
	{	x=650*cos(a)+400.5;
		y=650*sin(a)+240.5;
		line(400,240,(int)x,(int)y);
	}
		cleardevice();										//清屏
		Snake();												//调用蛇函数  游戏开始
}


//边框函数
void Border()
{	setfillcolor(BROWN );
	setlinecolor(BROWN );											//定义边框颜色为棕色
	fillrectangle(0,0,800,10);
	fillrectangle(0,0,10,480);
	fillrectangle(0,470,800,480);
	fillrectangle(630,0,640,480);
	fillrectangle(790,0,800,480);									//用矩形条画出边框
	setlinecolor(WHITE );											//定义边框颜色为棕色
	rectangle(645,15,785,155);									//画出显示分数的窗口
	outtextxy(650,30, "当前得分：");
	outtextxy(650,70, "当前长度：");
	outtextxy(650,110, "当前难度：");							//窗口内文字
	IMAGE img2;														// 定义 IMAGE 对象
	loadimage(&img2, _T("image\\按esc前.jpg"));		// 读取"image\\按esc前.jpg"图片到 img 对象中
	putimage(642, 160, &img2);									// 在坐标 (0, 0) 位置显示 IMAGE 对象
	outtextxy(700,260, "暂停");									//表明功能
	loadimage(&img2, _T("image\\按方向前.jpg"));	// 读取"image\\按方向前.jpg"图片到 img 对象中
	putimage(642, 320, &img2);									// 在坐标 (0, 0) 位置显示 IMAGE 对象
	outtextxy(685,430, "控制方向");								//表明功能
}

/**食物函数**/
void Food( int L[31][23] )
{	int A=rand()%31;
	int B=rand()%23;												//生成食物在数组中的坐标（A,B）
	if(L[A][B]!=0) Food(L);										//食物位置不合适时重新生成A和B
	else
	{	//这一部分是对食物的描写
		L[A][B]=-1;													//将食物所在位置设为非0
		setlinestyle(PS_SOLID, 1);								//定义食物边框宽度1
		setfillcolor(RGB(rand()%255,rand()%255,rand()%255+1));
		setlinecolor(LIGHTGREEN );             
		fillcircle(20*(A+1),20*(B+1),8);						//画随机颜色的实心圆 半径为8
		setfillcolor(RGB(rand()%255,rand()%255,rand()%255+1));		
		fillcircle(20*(A+1),20*(B+1),3);						//画随机颜色的实心圆  半径为3
		NUM++;
		if(NUM==5) 
		{	SL=SL*4/5	; Difficulty++ ;	NUM=0;}		//如果吃了五个果实 速度变为原来的5/4，果实数量归零
	}
}

/**消除蛇身最后一块函数**/
void Remove(int L[31][23])
{	for(int i=0;i<31;i++)
		for(int j=0;j<23;j++)
			if(L[i][j]==CA)								//找到CA（即最后一块蛇身）所在的数组中对应的行列
			{	L[i][j]=0;	
				int x=20*(i+1),y=20*(j+1);			//把数组中的行和列转为坐标
				setfillcolor(BLACK);
				setlinecolor(BLACK);  
				fillrectangle(x-8,y-8,x+8,y+8);	//用黑色矩形 把最后一块擦去
			}
}

/**控制方向函数**/
void Control(  char & k , int & m,int & n )
{	IMAGE img,img2;							// 定义 IMAGE 对象
	getimage(&img, 0, 0, 640, 480);	// 将当前界面保存区域至 img 对象
	if (_kbhit())k = _getch();				//记录按键
	switch( 2*m-n )
	{	case 20:																			//如果当前移动方向为 “↑”
				if (_kbhit())
				{	k = _getch();
					if(k==75)	
					{	loadimage(&img2, _T("image\\按左后.jpg"));	// 读取图片到 img 对象中
						putimage(642, 320, &img2);								// 在坐标 (0, 0) 位置显示 IMAGE 对象
						m =-20; n=0;	break;}										// 当按下 “←” 时向左拐
					else if(k==77)	
					{	loadimage(&img2, _T("image\\按右后.jpg"));	// 读取图片到 img 对象中
						putimage(642, 320, &img2);								// 在坐标 (0, 0) 位置显示 IMAGE 对象
						m = 20; n=0;	break;}											//当按下  “→” 时向右拐
					else
						Control( k ,m , n );												//调用 控制方向函数 改变蛇的运动方向 
						break;
				}
		case -20:																			//如果当前移动方向为“↓”
				if (_kbhit())
				{	k = _getch();			
					if(k==75)	
					{	loadimage(&img2, _T("image\\按左后.jpg"));	// 读取图片到 img 对象中
						putimage(642, 320, &img2);								// 在坐标 (0, 0) 位置显示 IMAGE 对象
						m =-20; n=0;	break; }										// 当按下 “←” 时向左拐
					else if(k==77)	
					{	loadimage(&img2, _T("image\\按右后.jpg"));	// 读取图片到 img 对象中
						putimage(642, 320, &img2);								// 在坐标 (0, 0) 位置显示 IMAGE 对象
						m = 20; n=0;	break; } 										//当按下  “→” 时向右拐
					else 
						Control( k ,m , n );												//调用 控制方向函数 改变蛇的运动方向 
						break;
				}
		case -40:																			//如果当前移动方向为 “←”		 
				if (_kbhit())
				{	k = _getch();
					if(k==72)	
					{	loadimage(&img2, _T("image\\按上后.jpg"));	// 读取图片到 img 对象中
						putimage(642, 320, &img2);								// 在坐标 (0, 0) 位置显示 IMAGE 对象
						m =0; n=-20;	break; } 									// 当按下 “↑” 时向上拐
					else if(k==80)	
					{	loadimage(&img2, _T("image\\按下后.jpg"));	// 读取图片到 img 对象中
						putimage(642, 320, &img2);								// 在坐标 (0, 0) 位置显示 IMAGE 对象
						m =0; n= 20;	break; } 										// 当按下 “↓” 时向下拐
					else 
						Control( k ,m , n );												//调用 控制方向函数 改变蛇的运动方向 
						break;
				}
		case 40:																			//如果当前移动方向为 “→”
				if (_kbhit())
				{	k = _getch();
					if(k==72)	
					{	loadimage(&img2, _T("image\\按上后.jpg"));	// 读取图片到 img 对象中
						putimage(642, 320, &img2);								// 在坐标 (0, 0) 位置显示 IMAGE 对象
						m =0; n=-20;	break; } 									// 当按下 “↑” 时向上拐
					else if(k==80)
					{	loadimage(&img2, _T("image\\按下后.jpg"));	// 读取图片到 img 对象中
						putimage(642, 320, &img2);								// 在坐标 (0, 0) 位置显示 IMAGE 对象 
						m =0; n= 20;	break; } 										// 当按下 “↓” 时向下拐
					else 
						Control( k ,m , n );												//调用 控制方向函数 改变蛇的运动方向 
						break;
				}
		}
	if(k==27)																				//如果按esc   询问是否退出游戏
	{	loadimage(&img2, _T("image\\按esc后.jpg"));					// 读取图片到 img 对象中
		putimage(642, 160, &img2);												// 在坐标 (0, 0) 位置显示 IMAGE 对象
		setlinestyle(PS_SOLID,2);
		setfillcolor(BLACK);															//设置提示框背景颜色 黑色 
		fillrectangle(160,180,460,290);
		setcolor(WHITE);																//设置字体颜色   
		rectangle(162,182,458,288);												//设置提示框边框和字颜色 白色 
		settextstyle(30,0, "楷体");													//设置字体样式: 字体高度为100像素, 宽度不指定, 字体名称为"楷体"
		outtextxy(170, 190, ("  是否退出游戏？ "));						//在指定位置输出文本
		outtextxy(170, 250, ("是(回车)  否（esc）"));						//在指定位置输出文本
		k=_getch();																		//按键选择
		putimage(0, 0, &img);														//返回之前的界面
		if(k==27)	
		{	loadimage(&img2, _T("image\\按esc前.jpg"));				// 读取图片到 img 对象中
			putimage(642, 160, &img2);											// 在坐标 (0, 0) 位置显示 IMAGE 对象
			k=0;	}																			//如果按 esc 则继续游戏
		if(k==13)																			//如果按回车会显示分数 并退出游戏
		{	char c[10];																	//用来把int类的分数改为字符串类型便于在屏幕上输出
			setlinestyle(PS_SOLID,2);
			setfillcolor(BLACK);														//设置提示框背景颜色 黑色 
			fillrectangle(160,180,480,350);
			setcolor(WHITE);															 //设置字体颜色   
			settextstyle(30,0, "楷体");												 //设置字体样式: 字体高度为100像素, 宽度不指定, 字体名称为"楷体"
			sprintf_s(c,"%d",Score);													//把int格式的Score转化为字符串形式的c，并在下一条语句中输出在画布上
			outtextxy(170, 190, ("游戏结束！当前得分:"));				//在指定位置输出文本
			outtextxy(440, 190, ("%s",c));											//在指定位置输出得分
			outtextxy(170, 250, ("是否重新开始游戏？ "));				//在指定位置输出文本
			outtextxy(170, 310, ("是(回车)  否（esc）"));					//在指定位置输出文本
			rectangle(162,182,478,348);											//设置提示框边框和字颜色 白色
			k=27;
		}
	}
}

