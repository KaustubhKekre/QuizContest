#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
int op1[14]={60,365,80,385,265,385,285,365,265,345,80,345,60,365};
int op2[14]={335,365,355,385,540,385,560,365,540,345,355,345,335,365};
int op3[14]={60,415,80,435,265,435,285,415,265,395,80,395,60,415};
int op4[14]={335,415,355,435,540,435,560,415,540,395,355,395,335,415};
int priceW[10]={400,20,400,220,600,220,600,20,400,20};
int TextW[10]= {20,100,20,220,400,220,400,100,20,100};
char price[11][15]={"Rs. 0","Rs. 10,000","Rs. 20,000","Rs. 40,000","Rs. 80,000","Rs. 3,20,000","Rs. 6,40,000","Rs. 12,50,000","Rs. 25,00,000","Rs. 50,00,000","Rs. 1 crore"};
int ques[14]={60,275,80,315,540,315,560,275,540,235,80,235,60,275};
int *options[5]={ques,op1,op2,op3,op4};
int lfline[3]={100,210,320},llStatus[3]={0,0,0},flag1,count;

void kbc_init()
{
 int i;
 rectangle(20,20,600,450);
 line(20,220,600,220);
 line(400,20,400,220);
 line(20,100,400,100);
 for(i=0;i<5;i++)
	drawpoly(7,options[i]);
 drawpoly(5,priceW);
 drawpoly(5,TextW);
 for(i=0;i<3;i++)
       ellipse(lfline[i],60,0,360,35,20);
 line(20,275,60,275);
 line(20,365,60,365);
 line(20,415,60,415);
 line(285,365,335,365);
 line(285,415,335,415);
 line(560,275,600,275);
 line(560,365,600,365);
 line(560,415,600,415);
}

int move_Vert(int current,int dir)
{
 if(dir==0 && current<5)
 {
  if(current==1 || current==2)
  {
   setfillstyle(WIDE_DOT_FILL,BLACK);
   fillpoly(7,options[current]);
   setfillstyle(WIDE_DOT_FILL,14);
   fillpoly(7,options[current+2]);
   return current+2;
  }
 }
 else if(dir == 1 && current<5)
 {
  if(current==3 || current==4)
  {
   setfillstyle(WIDE_DOT_FILL,BLACK);
   fillpoly(7,options[current]);
   setfillstyle(WIDE_DOT_FILL,14);
   fillpoly(7,options[current-2]);
   return current-2;
  }
 }
 return current;
}

int move_Horizontal(int current,int dir)
{
int j;
 if(current >= 5 )
 {
  if(dir==1 && current!=7)
  {
   setfillstyle(WIDE_DOT_FILL,BLACK);
   fillellipse(lfline[current-5],60,35,20);
   setfillstyle(WIDE_DOT_FILL,14);
   fillellipse(lfline[current-4],60,35,20);
   return current+1;
  }
  else if(dir==0 && current!=5)
  {
   setfillstyle(WIDE_DOT_FILL,BLACK);
   fillellipse(lfline[current-5],60,35,20);
   setfillstyle(WIDE_DOT_FILL,14);
   fillellipse(lfline[current-6],60,35,20);
   return current-1;
  }
  return current;
 }
 if(dir==1)
 {
  if(current==1 || current==3)
  {
   setfillstyle(WIDE_DOT_FILL,BLACK);
   fillpoly(7,options[current]);
   setfillstyle(WIDE_DOT_FILL,14);
   fillpoly(7,options[current+1]);
   return current+1;
  }
 }
 else if(dir==0)
 {
  if(current==2 || current==4)
  {
   setfillstyle(WIDE_DOT_FILL,BLACK);
   fillpoly(7,options[current]);
   setfillstyle(WIDE_DOT_FILL,14);
   fillpoly(7,options[current-1]);
   return current-1;
  }
 }
 else
 {
   setfillstyle(WIDE_DOT_FILL,BLACK);
   fillpoly(7,options[current]);
   for( j=0;j<3;j++)
   {
      if(llStatus[j]==0)
      {
       setfillstyle(WIDE_DOT_FILL,14);
       fillellipse(lfline[j],60,35,20);
       return j+5;
      }
   }
   return current;
 }
 return current;
}

int checkSelected(int current,int ansStatus[],int ansDisp[])
{
  int i;
  flag1=0;
  if(ansStatus[current]==1)
  {
    setfillstyle(SOLID_FILL,GREEN);
    fillpoly(7,options[current]);
    return 1;
  }
  if(ansStatus[current]==2)
  {
   ansDisp[current-1]=0;
   setfillstyle(SOLID_FILL,YELLOW);
   fillpoly(7,options[current]);
   for(i=1;i<=4;i++)
     if(ansStatus[i]==2)
       ansStatus[i]=0;
  }
  else
  {
    setfillstyle(SOLID_FILL,RED);
    fillpoly(7,options[current]);
    for(i=1; i<=4 ;i++)
    {
      if(ansStatus[i]==1)
      {
       setfillstyle(SOLID_FILL,GREEN);
       fillpoly(7,options[i]);
      }
    }
    return 0;
  }
  return 5;
}

void fillblack()
{
 int i;
 setfillstyle(SOLID_FILL,BLACK);
 for(i=0;i<5;i++)
	fillpoly(7,options[i]);
 fillpoly(5,TextW);
}

void printPrice(int count)
{
 int i;
 for(i=1;i<=10;i++)
 {
    setcolor(7);
    if(i==3 || i==6 || i==10)
      setcolor(14);
    if(count==i)
      setcolor(10);
    outtextxy(420,210-18*i,price[i]);
 }
    setcolor(15);
}

void lifeLine(int current,int ansDisp[],int ansStatus[])
{
char c[3][4]={{"05%"},{"10%"},{"15%"}},*ch="A";
  int a=5,j;
 int i,count=0;
 if(current == 5 && llStatus[current-5]==0)
 {
   llStatus[current-5]=1;
   for(i=0;i<5;i++)
     if(ansStatus[i+1]==0)
     {
      ansDisp[i]=0;
      count++;
      if(count==2)
       return;
     }
 }
 if(current == 6 && llStatus[current-5]==0)
 {
   llStatus[current-5]=1;
   for(i=1;i<5;i++)
     if(ansStatus[i]==0)
       ansStatus[i]=2;
 }
 if(current == 7 && llStatus[current-5]==0)
 {
  llStatus[current-5]=1;
  setfillstyle(SOLID_FILL,BLACK);
  fillpoly(5,priceW);
  line(420,60,420,180);
  line(420,180,590,180);

  setfillstyle(SOLID_FILL,WHITE);
  for(i=1,j=0;i<=4;i++,*ch=i+64)
  {
    outtextxy(410+40*i,190,ch);
    if(ansStatus[i]!=1)
    {
      bar(400+40*i,180-a,420+40*i,180);
      outtextxy(402+40*i,165-a,c[j++]);
    }
    else{
      bar(400+40*i,110,420+40*i,180);
      outtextxy(402+40*i,95,"70%");
      }
    a=a+5;
  }
  getch();
  setfillstyle(SOLID_FILL,BLACK);
  fillpoly(5,priceW);
  printPrice(i);
 }
 llStatus[current-5]=1;
}

void printOptions(char ans[4][150],int ansDisp[])
{
 int i;
 for(i=1;i<=4;i++)
  if(ansDisp[i-1]!=0)
    outtextxy(options[i][2],options[i][1]-5,ans[i-1]);
}

void main()
{       FILE *fques,*fans,*fstatus;
	int gd=DETECT,gm,error,check,i=0,flag,k;
	int ansStatus[10][5],ansDisp[4]={1,1,1,1};
	int current = 1,j;
	char ch,ques[10][250],ans[10][4][150];
	initgraph(&gd,&gm,"c:\\TURBOC3\\BGI");
	kbc_init();

	fques=fopen("question.txt", "r");
	fans =fopen("answers.txt","r");
	fstatus=fopen("status.txt","r");
	if(fques && fans && fstatus)
	for(i=0;i<10;i++)
	 {
	   fgets(ques[i],250,fques);
	   ques[i][strlen(ques[i])-1]='\0';
	   fscanf(fans,"%[^B] %[^C] %[^D] %[^*] %s",ans[i][0],ans[i][1],ans[i][2],ans[i][3]);
	   ansStatus[i][1]=fgetc(fstatus)-48;
	   ansStatus[i][2]=fgetc(fstatus)-48;
	   ansStatus[i][3]=fgetc(fstatus)-48;
	   ansStatus[i][4]=fgetc(fstatus)-48;
	   ansStatus[i][0]=fgetc(fstatus);
	 }
	i=k=0;
	while(1)
	{
	 if(flag==1)
	    fillblack();
	 settextstyle(2,HORIZ_DIR,5);
	 if(llStatus[0]==0)
	   outtextxy(lfline[0]-15,55,"50:50");
	 if(llStatus[1]==0)
	   outtextxy(lfline[1]-15,55," 2x");
	 if(llStatus[2]==0)
	   outtextxy(lfline[2]-15,55,"poll");
	 for(j=0;j<3;j++)
	    if(llStatus[j]==1)
	    {
	      setfillstyle(XHATCH_FILL,RED);
	      fillellipse(lfline[j],60,35,20);
	    }
	 printPrice(i);
	 outtextxy(80,270,ques[i]);
	 printOptions(ans[i],ansDisp);
	 flag=0;
	 ch=getch();
	 check=1;
	 switch(ch)
	 {
	  case 'w': current=move_Vert(current,1);
		    break;
	  case 'a': current=move_Horizontal(current,0);
		    break;
	  case 's': current=move_Vert(current,0);
		    break;
	  case 'd': current=move_Horizontal(current,1);
		    break;
	  case 'l': if((llStatus[0]==0 || llStatus[1]==0 || llStatus[2]==0) && flag1==0)
		      current=move_Horizontal(current,3);
		      break;
	  case 13 : if(current<5)
		    {
		     check=-1;
		     if(ansDisp[current-1]==1)
		       check=checkSelected(current,ansStatus[i],ansDisp);
		     printOptions(ans[i],ansDisp);
		     if(check==1)
		     {
		       if(i==3 || i==6)
			 k=i;
		       i++;
		       flag=1;
		       settextstyle(7,HORIZ_DIR,2);
		       outtextxy(60,120,"Correct Answer !!");
		       outtextxy(60,150,"You won");
		       outtextxy(160,150,price[i]);
		       for(j=0;j<4;j++)
			  ansDisp[j]=1;
		     }
		    }
		    else
		    {
		     if(current>=5 && flag1==0)
			lifeLine(current,ansDisp,ansStatus[i]);
		     if(current==6)
			flag1=1;
		     fillblack();
		     printOptions(ans[i],ansDisp);
		     current=1;
		    }
		    break;
	  case 'e': break;
	 }
	 if(flag==1)
		delay(3000);
	 if(check==0)
	 {
	   settextstyle(7,HORIZ_DIR,2);
	   outtextxy(60,120,"Wrong Answer ");
	   outtextxy(60,150,"You won");
	   outtextxy(165,150,price[k]);
	 }
	 if(ch=='e')
	 {
	   settextstyle(7,HORIZ_DIR,2);
	   outtextxy(60,120,"Congratulations you won");
	   outtextxy(60,150,price[i]);
	 }
	 if((ch=='e'|| check == 0 || i==10) && flag1==0)
		break;
	}
	getch();
	closegraph();
	fclose(fques);
	fclose(fans);

}
