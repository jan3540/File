#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <string.h>
#include <time.h>

void initialize();
void createps();
void displayinfo();
void fifo();
int findpage();

const int PAGEFRAMENUM = 6;

int   vpoint;           //页面访问指针
int   pageframe[PAGEFRAMENUM];    // 分配的页框，假定固定为6物理块, 编写时可以设置一个变量
                        // 来随时改变分配的页框数
int   rpoint;          //页面替换指针
int   inpflag;         //缺页标志，0为不缺页，1为缺页

//页面信息结构
struct PageInfo  
{
int       serial[100];  // 模拟的最大访问页面数，实际控制在20以上
int       diseffect;    // 缺页次数
int       total_pf;     // 分配的页框数
int       total_pn;     // 访问页面序列长度
} pf_info;

////////////////////////////////////////////////////////////////////////
///  随机生成访问序列，这里作了简化，页面在16页以内

void createps( )
{
	int s,i;

    srand((unsigned int)time(NULL));    //初始化随机数的"种子"
	initialize();
	s=(int)((float) rand() / 32767 * 50) + 40; // 随机产生页面序列长度
	pf_info.total_pn = s;

	for(i=0;i<s;i++) //产生随机访问序列
	{  
		pf_info.serial[i]=(int)((float) rand() / 32767 * 16) ;        
     } 	
}

///////////////////////////////////////////////////////////////////
//初始化相关数据结构
void initialize()                        
{
	int i;

	inpflag=0;
	pf_info.diseffect =0;
	pf_info.total_pf = PAGEFRAMENUM; //可以使用随机数产生，这里简化为固定
	
	for(i=0;i<100;i++) // 清空页面序列
	{
       pf_info.serial[i]=-1;
     }
}


////////////////////////////////////////////////////////////////////////
//  显示当前状态及缺页情况

void displayinfo(void)
{  int i,n;

   if(vpoint==0)
   {   printf("\n=============页面访问序列=============\n");
	   
      for(i=0; i<pf_info.total_pn; i++) 
	   {   printf("%4d",pf_info.serial[i]);
		   if ((i+1) % 10 ==0) printf("\n");		   
	   }
       printf("\n======================================\n");
   }

   printf("访问%3d : 内存<",pf_info.serial[vpoint]); 
   for(n=0;n<PAGEFRAMENUM;n++){ // 页框信息
     if (pageframe[n] >=0) 
		 printf("%3d",pageframe[n]);
	 else
         printf("   ");
   }
   printf(" >");

   if(inpflag==1)
	 {  
		 printf(" ==>缺页 "); 
		 printf("缺页率%3.1f",(float)(pf_info.diseffect)*100.00/(vpoint+1)); 
	 }
	printf("\n");
   
}

////////////////////////////////////////////////////////////////////////
//  查找页面是否在内存，1为在内存，0为不在即缺页

int findpage(int page)
{ 
	int n;

	for(n=0;n<PAGEFRAMENUM;n++) {
      if (pageframe[n]==page )
	  {  
		 inpflag=0 ;	    
		 return 1;
	  }
	}
	  
	   //页面不存在，缺页
	  inpflag=1;
	  return 0;	   
}

////////////////////////////////////////////////////////////////////////
//  FIFO页面置换算法

void fifo(void)
{
  
  int  n,count,pstate;  

  rpoint=0;          // 页面替换指针
  createps();        // 随机生成访问序列

  //pstate

  for(n=0; n<PAGEFRAMENUM; n++) // 清除页框信息
    pageframe[n]=-1;
 
  inpflag=0;  

  for(vpoint=0;vpoint<pf_info.total_pn;vpoint++)  // 执行算法
  {    
	    pstate=findpage(pf_info.serial[vpoint]);

		if(pstate==0)// 页不存在则置换页面
		{ 
			pageframe[rpoint]=pf_info.serial[vpoint];				
			rpoint=(rpoint+1) % PAGEFRAMENUM;					
			pf_info.diseffect=pf_info.diseffect+1; // 缺页次数加1				
		}
       Sleep(1000);
	   displayinfo(); // 显示当前状态
     } 	// 置换算法循环结束

   _getch();
   return;
}


///////////////////////////////////////////////////////////////////
//主函数

int main(int argc, char* argv[])
{
  char ch;
  
  system("cls") ;
  while ( true )                           
  {
    printf("***********************************\n");
    printf("     1: FIFO页面置算法 \n") ;
    printf("     2: 退出\n") ;
    printf("***********************************\n");
    printf( "Enter your choice (1 or 2): ");  
    do{   //如果输入信息不正确，继续输入
        ch = (char)_getch() ;
	} while(ch != '1' && ch != '2');
 
    if(ch == '2') //选择2，退出
          return 0;
     else  //选择1，FIFO
          fifo(); 
     system("cls") ;
  }
  //结束
  printf("\nPress Any Key To Continue:");
  _getch() ; 
  return 0;
}
