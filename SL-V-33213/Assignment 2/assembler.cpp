#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
using namespace std;

string r[4] ={"AREG","BREG","CREG","DREG"}; 

struct mot
{
	char name[10];
	char type[3];
	int opcode;
	int size;
} mne[20];

struct l
{
    char name[10]; 
    int address; 
} lit[20];

struct s
{
    char name[10]; 
    int address; 
    int value;
    int type;
} sy[20];

int lc,ns,ni;


FILE *fir;

void symbol(char wc[])
{
	int flag_sym=0;
	for(int k=0;k<ns;k++)
	{
		if(!strcmp(sy[k].name,wc))
		{
			
			flag_sym=1;
			fprintf(fir,"(%s,%d)\t %d\n","S",k,lc);
			break;
		}
	}
	if(flag_sym==0)
	{
		strcpy(sy[ns].name,wc);
		sy[ns].address=-1;
		//printf("\nhello");
		fprintf(fir,"(%s,%d)\t %d\n","S",ns,lc);
		ns++;
	}
	flag_sym=0;
}

void literal(char wc[])
{
	int flag_lit=0;
	for(int k=0;k<ni;k++)
	{
		if(!strcmp(lit[k].name,wc))
		{
			flag_lit=1;
			fprintf(fir,"(%s,%d)\t %d\n","L",k,lc);
			break;
		}
	}
	if(flag_lit==0)
	{
		strcpy(lit[ni].name,wc);
		lit[ni].address=-1;
		fprintf(fir,"(%s,%d)\t %d\n","L",ni,lc);
		ni++;
	}
	flag_lit=0;	
}

int main()
{

	FILE *fim;
	FILE *fip;
	fip=fopen("test4.asm","r"); 
	fir=fopen("output.txt","w"); 
	int i=0,j=0,flag_sym=0,values=0,sl=0,lit_count=0,sy_no=0;
        char wc[10],lit_check;
        int m=0,reg=0,flag_lit=0,nm=0;
        fim=fopen("MOT.txt","r");
	
	while(!feof(fim))
	{
		fscanf(fim,"%s",wc); 
		strcpy(mne[nm].name,wc);
		fscanf(fim,"%s",wc);
		strcpy(mne[nm].type,wc);
		fscanf(fim,"%d",&values);
		mne[nm].opcode=values;
		fscanf(fim,"%d",&values);
		mne[nm].size=values;
		nm++;
	}
	nm--;
	
        
        
        fscanf(fip,"%s",wc); 
       	if(!strcmp(wc,"START")) 
       	{
       		fscanf(fip,"%d",&lc);
       		fprintf(fir,"(%s,%d)(%d)\t \n","AD",1,lc);
       	}
       	else
       	{
       		printf("\nERROR CODE SHOULD BEGIN WITH START");
       		return 0;
       	}
        
       	while(!feof(fip))
        {
        	flag_sym=0;
        	flag_lit=0;
        	
        	fscanf(fip,"%s",wc); 
        	
        	if(!strcmp(wc,"STOP"))
				break;
        	else
        	{
        		
        	for(i=0;i<nm;i++)
        	{
        	
        		if(!strcmp(wc,mne[i].name))
        		{
        			if(!strcmp(mne[i].type,"IS"))
        			{
        				if(!strcmp(mne[i].name,"READ") || !strcmp(mne[i].name,"PRINT"))
        				{
        					fscanf(fip,"%s",wc);
        					symbol(wc);
        					break;	
        				}
        				else
        				{
						fprintf(fir,"(%s,%d)","IS",i);
		       				
		 				fscanf(fip,"%s",wc);
						for(j=0;j<4;j++)
						{
							if(!strcmp(wc,r[j].c_str()))
							{
								fprintf(fir,"(%d)",j+1);	
								fscanf(fip,"%s",wc);
								lit_check=wc[0];
								sl=0;
								if(lit_check=='\'')
								{
									literal(wc);
							
							
								
								}
								else
								{
									symbol(wc);
							
								}
						
				
							}
						}	
						lc+=mne[i].size;
						break;
					}
				}
				else if(!strcmp(mne[i].type,"AD"))
				{
					printf("\n IN AD CASE");
					if(!strcmp(mne[i].name,"LTORG"))
					{
					fprintf(fir,"(%s,%d)\t %d\n","AD",i,lc);
					for(int k=lit_count;k<ni;k++)
		       			{
		       				lit[k].address=lc;
						lc++;
		     			}
		     			lit_count=ni;
		     			
		     			break;
		     			}
		     			else if(!strcmp(mne[i].name,"ORIGIN"))
		     			{
		     				fscanf(fip,"%d",&lc);
		     				break;
		     			}
				}
				
			}
		}
		}
		
		if(i==nm)
		{
			symbol(wc);
		}			
      }
      while(!feof(fip))
      {
      		fscanf(fip,"%s",wc);
                if(!strcmp(wc,"END"))
         	     	break;
                for(int k=0;k<ns;k++)
		{
			if(!strcmp(sy[k].name,wc))
			{		
				flag_sym=1;
				fprintf(fir,"(%s,%d)\t %d\n","S",k,lc);
				sy[k].address=lc;
				break;
			}
		}
		if(flag_sym==0)
		{
			strcpy(sy[ns].name,wc);
			sy[ns].address=lc;
			fprintf(fir,"(%s,%d)\t %d\n","S",ns,lc);
			ns++;
		}
		flag_sym=0;
	        fscanf(fip,"%s",wc); 
      	        if(!strcmp(wc,"DC"))
        	{	
        		fscanf(fip,"%s",wc);
			lit_check=wc[0];
			sl=0;
			if(lit_check=='\'')
			{
				for(int p=lit_count;p<ni;p++)
				{
					if(!strcmp(lit[p].name,wc))
					{
						flag_lit=1;
						fprintf(fir,"%s	 (%s,%d)\t %d\n","DC","L",p,lc);
						break;
					}
				}
				if(flag_lit==0)
				{
					strcpy(lit[ni].name,wc);
					lit[ni].address=-1;
					fprintf(fir,"%s  (%s,%d)\t %d\n","DC","L",ni,lc);
					ni++;
				}
					flag_lit=0;		
			}	
        		lc++;
        	}
        	else if(!strcmp(wc,"DS"))
        	{
    			
        		fscanf(fip,"%d",&values);
        		sy[ns].value=values;
        		fprintf(fir,"%s , Size=%d   %d\n","DS",values,lc);
        		sy[ns].type=1;
        		sy[ns].address=lc;
        		lc=lc+values;
        	}
        }
		       printf("\nSYMBOL TABLE AS FOLLOWS\n");
		       for(i=0;i<ns;i++)
		       {
		       	if(sy[i].address==-1)
		       	{
		       		printf("\nERROR SYMBOL (%s) NOT DECLARED",sy[i].name);
		       	}
				printf("\nSYMBOL: %s , ADDRESS : %d",sy[i].name,sy[i].address);
		       }
			      printf("\nLITERAL TABLE AS FOLLOWS\n");
			       for(i=lit_count;i<ni;i++)
			       {
		       			lit[i].address=lc;
		       			lc++;
		       		}
				printf("ns:%d",ns);
		       
		       for(i=0;i<ni;i++)
		       {
		       
				printf("\nLiteral: %s , ADDRESS : %d",lit[i].name,lit[i].address);	
		       }
			return 0;
		}
