#include<conio.h>
#include<stdio.h>
#include<iostream.h>
#include<process.h>

#define SZ 42

#define AVALUE 10000
#define EVALUE 1000
#define IVALUE 100
#define OVALUE 10
#define UVALUE 0
#define XVALUE -10000

/***********************************************************/
void cbab()
{
clrscr();
cout<<"Created by   AMIT BHOLA";
for(long int w=0;w<99999999;w++) ;
}
/***********************************************************/
void hline()
{
for(int i=0;i<80;i++)
printf("Ä");
return;
}
/***********************************************************/
void bhline()
{
for(int i=0;i<80;i++)
printf("Û");
return;
}
/***********************************************************/
void writescreen( char name[])
{
   int i;
   char buffer[4000];

   FILE *fp;

   fp=fopen(name,"a");

   gettext(1, 1, 80, 25, buffer);


 char buffer2[4000];
 int j=0;

    for(i=0;i<4000;i++)
     {
      if(int(buffer[i])==15);
      else
       {
	buffer2[j++]=buffer[i];
       }
     }

  for(i=0;i<2000;i++)
   {
    fprintf(fp,"%c",buffer2[i]);
    if( (i+1)%80==0 ) fprintf(fp,"\n");
   }


  fclose(fp);
 return;

}
/**************************************************************************/

int  indexmax		  ( int []  , int );
void establish_neb	  ( int [][SZ], int [][SZ] );
void establish_neborder   ( int [][SZ], int [][2],int );
void establish_reltab	  ( int, int [], char [][SZ],int [][SZ][SZ]);
int  establish_nextstation( int,int [][SZ][SZ],int [],int [],int,int[]);
int  fill_last		  ( char [][SZ],int,int [],int,int [],int [],int);
void establish_wpvgrid	  ( int [][SZ], int,char [][SZ], int [][SZ],int [][SZ]);
int  value 		  ( char );
void establish_xy	  ( int [][SZ],int [][2], int [][SZ],int [][SZ],int []);
void establish_inputmatrix( int);

void main()
{
 char input[SZ][SZ];
 int tcr[SZ],status[SZ][SZ],neb[SZ][SZ],neborder[1000][2],wpv[SZ][SZ],
     reltab[6][SZ][SZ],station[SZ],stnsta[SZ],last[SZ],layout[SZ][SZ],xy[2];
 int n,i,j,k,nextstni,midx,midy,x,y,noflast,leftovers;
 FILE *fp;
 clrscr();
 midx=SZ/2; midy=SZ/2;
 ///////////////////////////// input //////////////////////////////////

 cout<<"\n\n\n\n		          C  A  L  Y  P  L  A  N\n\n";
 bhline();
 cout<<"\n\n		  Computer   Aided   Layout   Planning	\n\n		      (based on CORELAP technique)";
 gotoxy(23,20);
 cout<<"Press any key to continue...";
 getch();

 clrscr();
 cout<<"CALYPLAN\n";
 hline();
 cout<<"\n\nReading input data from file INPUT.TXT\n\nEnter no. of stations : ";
 cin>>n;

 establish_inputmatrix(n);
 //exit(0);
 fp=fopen("C:\\CALYPLAN\\calyplan.txt","r");


 for(i=0;i<n;i++)
  {
   for(j=0;j<n;j++)
    {
     fscanf(fp," %c",&input[i][j]);
    }
   fscanf(fp,"%d\n",&tcr[i]);
  }
 fclose(fp);
///////////////////////////// initialisation //////////////////////////////////
 for(i=0;i<SZ;i++)
  {
   for(j=0;j<SZ;j++)
    {
     status[i][j]=0;
     neb   [i][j]=0;
     wpv   [i][j]=0;
     layout[i][j]=0;
    }
  }

 for(i=0;i<6;i++)
  {
   for(j=0;j<SZ;j++)
    {
     for(k=0;k<SZ;k++)
      {
       reltab[i][j][k]=0;
      }
    }
  }
 for(i=0;i<n;i++)
  {
   station[i]=i+1;
   last   [i]=0;
   stnsta [i]=0;
  }

 xy[0]=xy[1]=0;
 leftovers=0;
 /////////////////////////// 1st station placement //////////////////////////
 nextstni=indexmax(tcr,n);
 noflast=0;
 noflast=fill_last(input,nextstni,last,n,tcr,stnsta,noflast);

 x=midx; y=midy;
 layout[x][y]=station[nextstni];
 status[x][y]=1;
 stnsta[station[nextstni]-1]=1;

 cout<<"\n1\tstation : "<<station[nextstni]<<"\tat 	"<<x<<" , "<<y;//<<"\tlast : "<<last[0]<<","<<last[1];
 writescreen("C:\\CALYPLAN\\calytemp.txt");
 /////////////////////////// rest placements //////////////////////////
 for(i=1;i<n;i++)
 {
  if( (i+noflast)==n ) { leftovers=1; /*cout<<" M "<<i<<" "<<noflast;*/ }
  if(!leftovers)
   {
	  establish_neb		(status,neb);
	  establish_neborder	(neb,neborder,midx);
	  establish_reltab	(n,stnsta,input,reltab);
 nextstni=establish_nextstation	(n,reltab,tcr,last,noflast,stnsta);
 noflast =fill_last		(input,nextstni,last,n,tcr,stnsta,noflast);
	  establish_wpvgrid	(wpv,nextstni,input,status,layout);
	  establish_xy		(neb,neborder,wpv,status,xy);

	  x=xy[0]; y=xy[1];
	  layout[x][y]=station[nextstni];
	  status[x][y]=1;
	  neb[x][y]=0;
	  stnsta[station[nextstni]-1]=1;

	  for(j=0;j<SZ;j++)
	   for(k=0;k<SZ;k++)
	    wpv[j][k]=0;
   }

  if(leftovers)
   {
	  establish_neb		(status,neb);
	  establish_neborder	(neb,neborder,midx);

 nextstni=last[noflast-1];

	  establish_wpvgrid	(wpv,nextstni,input,status,layout);
	  establish_xy		(neb,neborder,wpv,status,xy);

	  x=xy[0]; y=xy[1];
	  layout[x][y]=station[nextstni];
	  status[x][y]=1;
	  neb[x][y]=0;
	  stnsta[station[nextstni]-1]=1;

	  for(j=0;j<SZ;j++)
	   for(k=0;k<SZ;k++)
	    wpv[j][k]=0;

    noflast--;
   }
  cout<<"\n"<<i+1<<"\tstation : "<<station[nextstni]<<"\tat 	"<<x<<" , "<<y;//<<"\tlast : "<<last[0]<<","<<last[1]<<" , "<<noflast;
  writescreen("C:\\CALYPLAN\\calytemp.txt");
 }
///////////////// all placements over ////////////////////////////////////
 fp=fopen("C:\\CALYPLAN\\calyplan.txt","a");
 for(i=0;i<SZ;i++)
  {
   for(j=0;j<SZ;j++)
    {
     if(!layout[i][j]) fprintf(fp,"    ");
     else fprintf(fp,"%-4d",layout[i][j]);
    }
   fprintf(fp,"\n");
  }
 fclose(fp);
 cout<<"\n\nOutput saved in file 			calyplan.txt\nIntermediate status saved in file	calytemp.txt\n\nPress any key to exit...";
 writescreen("C:\\CALYPLAN\\calytemp.txt");
 getch();
 cbab();
}
/*************************************************************************/
int indexmax(int a[],int n)
{
 int m=0;
 for (int i=1;i<n;i++)
  if (a[i]>a[m]) m=i;
 return m;
}
/*************************************************************************/
void establish_neb	( int st[][SZ], int nb[][SZ] )
{
 int i,j;

 for(i=1;i<SZ-1;i++)
  {
   for(j=1;j<SZ-1;j++)
    {
     if(st[i][j]) ;
     else
      if( st[i-1][j-1] || st[i-1][j] || st[i-1][j+1] ||
	  st[i  ][j-1] ||		st[i  ][j+1] ||
	  st[i+1][j-1] || st[i+1][j] || st[i+1][j+1]    )
      nb[i][j]=1;
    }
  }

 return;
}
/*************************************************************************/
void establish_neborder ( int nb[][SZ], int nbo[][2], int mx )
{
 int i,j,x,y,stx,sty,nofneb=0, nbdone[SZ][SZ];

 for(i=0;i<SZ;i++)
  for(j=0;j<SZ;j++)
   nbdone[i][j]=0;


 for(i=0;i<SZ;i++)
  for(j=0;j<SZ;j++)
   if(nb[i][j]) nofneb++;

 for(j=1;j<SZ;j++)
  {
   if(nb[mx][j-1] && (!nb[mx][j]) )
    { stx=mx; sty=j-1; break; }
  }

 nbo[0][0]=stx;	nbo[0][1]=sty; nb[stx][sty]=1;
 x=stx; y=sty;

 for(i=1;i<=nofneb-1;i++)
  {
   if(nb[x][y-1] && !nbdone[x][y-1] )
	{ x=x; y=y-1; nbo[i][0]=x; nbo[i][1]=y; nbdone[x][y]=1; continue; }

   if(nb[x+1][y] && !nbdone[x+1][y] )
	{ x=x+1; y=y; nbo[i][0]=x; nbo[i][1]=y; nbdone[x][y]=1; continue; }

   if(nb[x][y+1] && !nbdone[x][y+1] )
	{ x=x; y=y+1; nbo[i][0]=x; nbo[i][1]=y; nbdone[x][y]=1; continue; }

   if(nb[x-1][y] && !nbdone[x-1][y] )
	{ x=x-1; y=y; nbo[i][0]=x; nbo[i][1]=y; nbdone[x][y]=1; continue; }
  }

 return;
}
/**************************************************************************/
void establish_reltab
 ( int n, int stnsta[], char input[][SZ],int reltab[][SZ][SZ])
{
 int i,j,nop,placedstns[SZ];
 char relation;

  for(i=0,j=0;i<n;i++)
   { if(stnsta[i]) placedstns[j++]=i; }
  nop=j;

  for(i=0; i<nop; i++)
   {
    for(j=0;j<n;j++)
     {
      relation=input[placedstns[i]][j];
      switch(relation)
       {
	case 'a':
	case 'A':
	 reltab[0][placedstns[i]][j]=1;
	 break;
	case 'e':
	case 'E':
	 reltab[1][placedstns[i]][j]=1;
	 break;
	case 'i':
	case 'I':
	 reltab[2][placedstns[i]][j]=1;
	 break;
	case 'o':
	case 'O':
	 reltab[3][placedstns[i]][j]=1;
	 break;
	case 'u':
	case 'U':
	 reltab[4][placedstns[i]][j]=1;
	 break;
	case 'x':
	case 'X':
	 reltab[5][placedstns[i]][j]=1;
	 break;
	case '-':
	 break;
	default:
	 cout<<"\nUnidentified character '"<<relation<<"'found in input table.\n\nPress any key to terminate program...";
	 getch();
	 exit(0);
	 break;
       }
     }
   }
 return;
}
/*************************************************************************/
int establish_nextstation( int n,int reltab[][SZ][SZ],int tcr[],int last[],
			   int noflast, int stnsta[])
{
 int i,j,k,p,t[SZ],tc[SZ],m=0,flag=0,notinlast=1;

 for(i=0;i<6;i++)
  {
   for(j=0;j<n;j++)
    {
     for(k=0;k<n;k++)
      {
       for(p=0;p<noflast;p++)
	{
	 if (k==last[p]) { notinlast=0; break; }
	}
      // cout<<"\n "<<i<<" "<<j<<" "<<k<<" "<<reltab[i][j][k];       //////
       if(reltab[i][j][k] && (!stnsta[k]) && notinlast)
	{ t[m++]=k; flag=1; }
       else notinlast=1;
      }
    }
   //getch();				/////////
   if(flag) break;
  }

  for(j=0;j<m;j++)
   { //cout<<" "<<tcr[j]<<",";           //////////
     tc[j]=tcr[t[j]];
   }

  //getch();                           ///////
  //exit(0);                           ////////
 return (t[indexmax(tc,m)]);
}

/*************************************************************************/
int fill_last ( char input [][SZ],int nextstni,int last[], int n, int tcr[],
		int stnsta [], int nofl)
{
 int i,j,k,t[SZ],tc[SZ],m=0,atleast1found=0,alreadypresentinlast=0,
     alreadyplaced=0;

     for(k=0;k<n;k++)
      {
       if(input[nextstni][k] == 'x' || input[nextstni][k]=='X' )
	{
	 for(i=0;i<nofl;i++)
	  {
	   if (last[i]==k)
	    { alreadypresentinlast=1; break; }
	  }

	 if(stnsta[k]) alreadyplaced=1;

	 if(!alreadypresentinlast && !alreadyplaced)
	  {
	    t[m++]=k;
	    atleast1found=1;
	    alreadypresentinlast=0;
	    alreadyplaced=0;
//	    cout<<"k";
	  }
	}
      }

 if(atleast1found)
 {
  for(j=0;j<m;j++) { tc[j]=-1*tcr[j]; }
  i= t[indexmax(tc,m)];
  last[nofl]=i;
  return (nofl+1);
 }
 else return (nofl);
}

/*************************************************************************/
void establish_wpvgrid	  ( int wpv[][SZ], int nextstni,char input[][SZ],
			    int status [][SZ], int layout [][SZ] )
{
 int i,j,k;

 for(i=0;i<SZ;i++)
  {
   for(j=0;j<SZ;j++)
    {
     if(status[i][j])
      { wpv[i][j]=value(input[nextstni][layout[i][j]-1]); }
    }
  }

 return;
}

/*************************************************************************/
int value (char ch)
{
 int t;
 switch (ch)
  {
	case 'a':
	case 'A':
	 //t=10000;
	 t=AVALUE;
	 break;

	case 'e':
	case 'E':
	 //t=1000;
	 t=EVALUE;
	 break;

	case 'i':
	case 'I':
	 //t=100;
	 t=IVALUE;
	 break;

	case 'o':
	case 'O':
	 //t=10;
	 t=OVALUE;
	 break;

	case 'u':
	case 'U':
	 //t=0;
	 t=UVALUE;
	 break;

	case 'x':
	case 'X':
	 //t=-10000;
	 t=XVALUE;
	 break;

       }
   return t;
}

/*************************************************************************/
void establish_xy  ( int nb[][SZ],int neborder[][2], int wpv[][SZ],
		     int st[][SZ],int xy[])
{
 int i,j,k,nofneb=0,tm,t[SZ],m=0;


 for(i=0;i<SZ;i++)
  for(j=0;j<SZ;j++)
   if(nb[i][j]) nofneb++;

 for(k=0;k<nofneb;k++)
  {
   xy[0]=neborder[k][0]; xy[1]=neborder[k][1];
   tm=0;
   //cout<<" "<<xy[0]<<"XY"<<xy[1]<<"-";
   i=xy[0]; j=xy[1];

   if(st[i-1][j  ])   { tm+=wpv[i-1][j  ]; }
   if(st[i  ][j-1])   { tm+=wpv[i  ][j-1]; }
   if(st[i  ][j+1])   { tm+=wpv[i  ][j+1]; }
   if(st[i+1][j  ])   { tm+=wpv[i+1][j  ]; }

   if(st[i-1][j-1])   { tm+=wpv[i-1][j-1]/2; }
   if(st[i-1][j+1])   { tm+=wpv[i-1][j+1]/2; }
   if(st[i+1][j-1])   { tm+=wpv[i+1][j-1]/2; }
   if(st[i+1][j+1])   { tm+=wpv[i+1][j+1]/2; }

   t[m++]=tm;  //cout<<"_";
  }

  //cout<<endl; for(i=0;i<m;i++) { cout<<" w"<<t[i]; } cout<<endl; getch();

  xy[0]=neborder[indexmax(t,m)][0];
  xy[1]=neborder[indexmax(t,m)][1];

 return;
}
/**************************************************************************/
void establish_inputmatrix( int n)
{
 FILE *fp1,*fp2;
 char tab[SZ][SZ],tabt[SZ][SZ];
 int i,j,k,i1,j1;

 fp1=fopen("C:\\CALYPLAN\\input.txt","r");
 fp2=fopen("C:\\CALYPLAN\\temp.txt","w");

 if(fp1==NULL) { cout<<"\n\n Input file input.txt not found !\n\n\nPress any key to exit..."; getch(); exit(0); }


 for(i=0;i<n-1;i++)
  {
   for(j=0;j<n-1;j++)
    {
     if(j<i) tab[i][j]=' ';
     else
     fscanf(fp1," %c",&tab[i][j]);
    }
  }

  for(i=0;i<n-1;i++)
  {
   for(j=0;j<n-1;j++)
    {
     tabt[i][j]=tab[j][i];
    }
  }

  for(i=0;i<n;i++)
  {
   for(j=0,j1=0;j<n;j++)
    {
     if      (j<i && i>0) fprintf(fp2,"%c\t",tabt[i-1][j1++]);
     else if (j>i) fprintf(fp2,"%c\t",tab[i][j1++]);
     else          fprintf(fp2,"-\t");
    }
    fprintf(fp2,"\n");
  }

 fclose(fp1);
 fclose(fp2);

 fp2=fopen("C:\\CALYPLAN\\temp.txt","r");

 int na,ne,ni,no,nu,nx,tcr[SZ];
 char ch;

 for(i=0;i<n;i++)
  { tcr[i]= 0; }

 for(i=0;i<n;i++)
  {
   na=ne=ni=no=nu=nx=0;

   for(j=0;j<n;j++)
    {
     fscanf(fp2," %c",&ch);
     switch(ch)
      {
	case 'a':
	case 'A':
	 na++;
	 break;

	case 'e':
	case 'E':
	 ne++;
	 break;

	case 'i':
	case 'I':
	 ni++;
	 break;

	case 'o':
	case 'O':
	 no++;
	 break;

	case 'u':
	case 'U':
	 nu++;
	 break;

	case 'x':
	case 'X':
	 nx++;
	 break;
	default:
	 ;
      }
     }
   tcr[i]=na*value('a')+
	  ne*value('e')+
	  ni*value('i')+
	  no*value('o')+
	  nu*value('u')+
	  nx*value('x');
   //cout<<endl<<tcr[i]; getch();
   fscanf(fp2,"\n");
  }

 fclose(fp2);
 fp1=fopen("C:\\CALYPLAN\\temp.txt","r");
 fp2=fopen("C:\\CALYPLAN\\calyplan.txt","w");

 for(i=0;i<n;i++)
  {
   for(j=0;j<n;j++)
    {
     fscanf(fp1," %c",&ch);
     fprintf(fp2,"%c\t",ch);
    }
   fprintf(fp2,"%d\n",tcr[i]);
   fscanf(fp1,"\n");
  }
  fclose(fp1);
  fclose(fp2);
  //remove("C:\\CALYPLAN\\calyplan.txt");
  //rename("C:\\CALYPLAN\\temp.txt","C:\\CAYPLAN\\calyplan.txt");

 return;
}
/******************* end of program **********************************/