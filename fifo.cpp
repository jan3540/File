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

int   vpoint;           //ҳ�����ָ��
int   pageframe[PAGEFRAMENUM];    // �����ҳ�򣬼ٶ��̶�Ϊ6�����, ��дʱ��������һ������
                        // ����ʱ�ı�����ҳ����
int   rpoint;          //ҳ���滻ָ��
int   inpflag;         //ȱҳ��־��0Ϊ��ȱҳ��1Ϊȱҳ

//ҳ����Ϣ�ṹ
struct PageInfo  
{
int       serial[100];  // ģ���������ҳ������ʵ�ʿ�����20����
int       diseffect;    // ȱҳ����
int       total_pf;     // �����ҳ����
int       total_pn;     // ����ҳ�����г���
} pf_info;

////////////////////////////////////////////////////////////////////////
///  ������ɷ������У��������˼򻯣�ҳ����16ҳ����

void createps( )
{
	int s,i;

    srand((unsigned int)time(NULL));    //��ʼ���������"����"
	initialize();
	s=(int)((float) rand() / 32767 * 50) + 40; // �������ҳ�����г���
	pf_info.total_pn = s;

	for(i=0;i<s;i++) //���������������
	{  
		pf_info.serial[i]=(int)((float) rand() / 32767 * 16) ;        
     } 	
}

///////////////////////////////////////////////////////////////////
//��ʼ��������ݽṹ
void initialize()                        
{
	int i;

	inpflag=0;
	pf_info.diseffect =0;
	pf_info.total_pf = PAGEFRAMENUM; //����ʹ������������������Ϊ�̶�
	
	for(i=0;i<100;i++) // ���ҳ������
	{
       pf_info.serial[i]=-1;
     }
}


////////////////////////////////////////////////////////////////////////
//  ��ʾ��ǰ״̬��ȱҳ���

void displayinfo(void)
{  int i,n;

   if(vpoint==0)
   {   printf("\n=============ҳ���������=============\n");
	   
      for(i=0; i<pf_info.total_pn; i++) 
	   {   printf("%4d",pf_info.serial[i]);
		   if ((i+1) % 10 ==0) printf("\n");		   
	   }
       printf("\n======================================\n");
   }

   printf("����%3d : �ڴ�<",pf_info.serial[vpoint]); 
   for(n=0;n<PAGEFRAMENUM;n++){ // ҳ����Ϣ
     if (pageframe[n] >=0) 
		 printf("%3d",pageframe[n]);
	 else
         printf("   ");
   }
   printf(" >");

   if(inpflag==1)
	 {  
		 printf(" ==>ȱҳ "); 
		 printf("ȱҳ��%3.1f",(float)(pf_info.diseffect)*100.00/(vpoint+1)); 
	 }
	printf("\n");
   
}

////////////////////////////////////////////////////////////////////////
//  ����ҳ���Ƿ����ڴ棬1Ϊ���ڴ棬0Ϊ���ڼ�ȱҳ

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
	  
	   //ҳ�治���ڣ�ȱҳ
	  inpflag=1;
	  return 0;	   
}

////////////////////////////////////////////////////////////////////////
//  FIFOҳ���û��㷨

void fifo(void)
{
  
  int  n,count,pstate;  

  rpoint=0;          // ҳ���滻ָ��
  createps();        // ������ɷ�������

  //pstate

  for(n=0; n<PAGEFRAMENUM; n++) // ���ҳ����Ϣ
    pageframe[n]=-1;
 
  inpflag=0;  

  for(vpoint=0;vpoint<pf_info.total_pn;vpoint++)  // ִ���㷨
  {    
	    pstate=findpage(pf_info.serial[vpoint]);

		if(pstate==0)// ҳ���������û�ҳ��
		{ 
			pageframe[rpoint]=pf_info.serial[vpoint];				
			rpoint=(rpoint+1) % PAGEFRAMENUM;					
			pf_info.diseffect=pf_info.diseffect+1; // ȱҳ������1				
		}
       Sleep(1000);
	   displayinfo(); // ��ʾ��ǰ״̬
     } 	// �û��㷨ѭ������

   _getch();
   return;
}


///////////////////////////////////////////////////////////////////
//������

int main(int argc, char* argv[])
{
  char ch;
  
  system("cls") ;
  while ( true )                           
  {
    printf("***********************************\n");
    printf("     1: FIFOҳ�����㷨 \n") ;
    printf("     2: �˳�\n") ;
    printf("***********************************\n");
    printf( "Enter your choice (1 or 2): ");  
    do{   //���������Ϣ����ȷ����������
        ch = (char)_getch() ;
	} while(ch != '1' && ch != '2');
 
    if(ch == '2') //ѡ��2���˳�
          return 0;
     else  //ѡ��1��FIFO
          fifo(); 
     system("cls") ;
  }
  //����
  printf("\nPress Any Key To Continue:");
  _getch() ; 
  return 0;
}
