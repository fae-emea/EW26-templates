#include "test_config.h"
#ifdef  TEST_012_STRINGCOPY


#include <string.h>
#include <stdlib.h>


#define MAX_TEST	20000
#define	MAX_BUFFER	256	

char bcdtoasc(const unsigned char);
char bcdmtoasc(const unsigned char,const unsigned char);
char bintoasc(const char);
char asciitobin(char);
unsigned char  asctobin(const char *);
unsigned short asctowbin(const char *);
unsigned int   asctolbin(const char *);
unsigned char ascnccbin(const char *,int);
unsigned int ascncclbin(const char *,int);
int  asctoint(const char *,int);
void asctosbin(unsigned char *,const char *);
void strcopy_ncc(char *,const char *,int,int);
int  ascnccint(const char *,int);
double ascnccf(const char *,int);
void deltabsp( char *);
unsigned short hantozen(char);
int	ncccount(const char *);


const char data1[]="1,12,123,1234,12345,123456,1234567,12345678,1234567890,12345467890A,1234567890AB,1234567890ABC,1234567890ABCD,1234567890ABCDE";
char buffer[MAX_BUFFER];

int test_012(void)
{
	volatile unsigned long i,j;


	
	for(j=0;j<MAX_TEST;j++){

		memset(buffer,0,MAX_BUFFER);
		strcopy_ncc(buffer,data1,0,MAX_BUFFER);
		if( strcmp(buffer,"1")!=0 ){
		  	for(;;);
		}
		memset(buffer,1,MAX_BUFFER);
		strcopy_ncc(buffer,data1,1,MAX_BUFFER);
		if( strcmp(buffer,"12")!=0 ){
		  	for(;;);
		}
		memset(buffer,2,MAX_BUFFER);
		strcopy_ncc(buffer,data1,2,MAX_BUFFER);
		if( strcmp(buffer,"123")!=0 ){
		  	for(;;);
		}
		memset(buffer,3,MAX_BUFFER);
		strcopy_ncc(buffer,data1,11,MAX_BUFFER);
		if( strcmp(buffer,"1234567890ABC")!=0 ){
		  	for(;;);
		}
	}
	return 0;
}

#define	SP				0x20
#define	TAB				0x09


//char bcdtoasc(const unsigned char s)
//{
//	char	t;
//
//	t=0x0f & s;
//	if(0x00 <= t && t<=0x09)
//		t|=0x30;
//	else
//		t = '0';
//	return(t);
//}
//
//char bcdmtoasc(const unsigned char s,const unsigned char t)
//{
//	char u;
//
//	u=t & s;
//	if(0x00 <= u && u<=0x09)
//		u|=0x30;
//	else
//		u = '0';
//	return(u);
//}
//
//char asciitobin(char s)
//{
//	char t;
//
//	t=s;
//	if( ('0'<=t) && (t<='9') )
//		return(t-'0');
//	if( ('A'<=t) && (t<='F') )
//		return(t-55);
//	if( ('a'<=t) && (t<='f') )
//		return(t-87);
//	return(0);
//}
//
//char bintoasc(const char s)
//{
//	int i;
//
//	i=0x0f & s;
//	if( (0<=i) && (i<=9) )
//		return( (char)(i+0x30) );
//	if( (0x0a<=i) && (i<=0x0f) )
//		return( (char)(i+0x37) );
//	else
//		return('0');
//}
//unsigned char asctobin(const char *s)
//{
//	unsigned char t;
//	const char *u;
//
//	u=s;
//	t=asciitobin(*u)*0x10;
//	u++;
//	t+=asciitobin(*u);
//	return(t);
//}
//
//unsigned short asctowbin(const char *s)
//{
//	const char	*t;
//	unsigned short i;
//
//	t=s;
//	i=asciitobin(*t)*0x1000;
//	t++;
//	i+=asciitobin(*t)*0x100;
//	t++;
//	i+=asciitobin(*t)*0x10;
//	t++;
//	i+=asciitobin(*t);
//	return(i);
//}
//
//unsigned int asctolbin(const char *s)
//{
//	int	i,j;
//	unsigned long m;
//	const char *t;
//
//	t=s;
//	i=strlen(t);
//	m=0;
//	for(j=i;j>0;j--)
//	{
//		m=m+asciitobin(*t)*((long)1 << (4*(j-1)) );
//		t++;
//	}
//	return(m);
//}
//
//unsigned char ascnccbin(const char *s,int i)
//{
//	char t[4];
//
//	strcopy_ncc(t,s,i,sizeof(t));
//	return( asctobin(t) );
//}
//
//unsigned int ascncclbin(const char *s,int i)
//{
//	char t[10];
//
//	strcopy_ncc(t,s,i,sizeof(t));
//	return( asctolbin(t) );
//}
//
//int	asctoint(const char *s,int i)
//{
//	char	t[13];
//	if( (1<=i) && (i<=11) )
//	{
//		strncpy(t,s,i);
//		t[i]='\0';
//		return(atoi(t));
//	}
//	else
//		return(0);
//}
//
//void	asctosbin(unsigned char *s,const char *t)
//{
//	unsigned char *u;
//	const char *v;
//
//	u=s;
//	v=t;
//	while(*v!='\0')
//	{
//		*u ++ = asctobin(v);
//		v+=2;
//	}
//}

void	strcopy_ncc(char *t,const char *s,int i,int k)
{
	const char *u;
	char	*v;
	int	j;

	j=0;
	u=s;
	v=t;
	if(i>=0)	
	{
		if(i!=0)
		{
			while(*u != '\0')
			{
				if(*u == ',')
				{
					j++;
					if(j==i)
						break;
				}
				u++;
			}
			u++;
		}
		if(*u != '\0')
		{
			while(!(*u == ',') & !(*u =='\0'))
			{
				*v ++ = *u ++;
				k--;
				if(k<=1)
					break;
			}
			*v='\0';
		}
	}
}
//
//int ascnccint(const char *s,int i)
//{
//	char t[12];
//
//	strcopy_ncc(t,s,i,sizeof(t));
//	return(atoi(t));
//}
//
//
//double ascnccf(const char *s,int i)
//{
//	char t[25];
//
//	strcopy_ncc(t,s,i,sizeof(t));
//	return(atof(t));
//}
//
//void deltabsp( char *s)
//{
//	char *t;
//
//	t=s;
//	for(;;)
//	{
//		if( *t==0x00 )
//		{
//			*s='\0';
//			break;
//		}
//		else if( (*t==SP) || (*t==TAB) )
//		{
//			t++;
//		}
//		else
//		{
//			*s ++ = *t ++;
//		}
//	}
//}
//
//unsigned short hantozen(char s)
//{
//	char t;
//
//	const unsigned short i[]={
//	0x8140,0x8149,0x814a,0x8194,
//	0x8190,0x8193,0x8195,0x818c,
//	0x8169,0x816a,0x8169,0x817b,
//	0x8166,0x817c,0x8144,0x815e};
//
//	t=s;
//	if( (0x20<=t) && (t<=0x2f) )
//		return(i[t-0x20]);	
//	else if( ('0'<=t) && (t<='9') )
//		return(0x824f+t-'0');
//	else if( ('A'<=t) && (t<='Z') )
//		return(0x8260+t-'A');
//	else if( ('a'<=t) && (t<='z') )
//		return(0x8281+t-'a');
//	else
//		return((unsigned short)t);
//}
//
//int	ncccount(const char *s)
//{
//	int i,j;
//	const char *t;
//
//	t=s,j=0;
//	for(i=0;i<256;i++)
//	{
//		if( *t=='\0' )
//			break;
//		else if( *t==',' )
//			j++;
//		t++;
//	}
//	return( j );
//}
#endif
