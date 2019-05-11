#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

pthread_t tid[3]; 

int length=5; //inisialisasi jumlah untuk looping
void* playandcount(void *arg)
{
    while(1)
    {
    char command[10][50];
    char waktu[10][50];

//Reading File
    char ch, file_name[25];
    FILE *fp;
 
    strcpy(file_name,"crontab.data");

    fp = fopen(file_name, "r"); // read mode
    
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    
    int i,j,t;
    i=0;
    j=0;
    t=0;
    while((ch = fgetc(fp)) != EOF)
    {
        if(t<5)
        {
            if(ch == ' ')
            {
                t++;
            }
            waktu[j][i]=ch;
            i++;
            if(t==5)
            {
                waktu[j][i]='\0';
                i=0;
            }
        }
        else
        {
             if(ch =='\n')
            {
                command[j][i]='\0';
                i=0;
                j++;
                t=0;
            }
            else
            {
                command[j][i]=ch;
                i++;
            }
        }
    }
        
       
    command[j][i]='\0';
    fclose(fp);
//End of Reading File

//Executing Commands in File
    int k;
    int numspace,cmptotal;
    numspace=0;
    cmptotal=0;
    int u = 0;
    char tempwaktu[5];
    //k=0;

    time_t rawtime;
   struct tm *info;
   char buffer[80];
   char menitnow[5];
   char jamnow[5];
   char daynow[5];
   char monthnow[5];
   char weeknow[5];

    for(k=0;k<j;k++)
    {
        time( &rawtime );

    info = localtime( &rawtime );
    strftime(buffer,80,"%M%H%d%m%w", info);
    //printf("%s\n",buffer);

    menitnow[0]=buffer[0];
    menitnow[1]=buffer[1];
    menitnow[2]='\0';
    jamnow[0]=buffer[2];
    jamnow[1]=buffer[3];
    jamnow[2]='\0';
    daynow[0]=buffer[4];
    daynow[1]=buffer[5];
    daynow[2]='\0';
    monthnow[0]=buffer[6];
    monthnow[1]=buffer[7];
    monthnow[2]='\0';
    weeknow[0]='0';
    weeknow[1]=buffer[8];
    weeknow[2]='\0';
    //printf("%s\n",weeknow);

    strcpy(tempwaktu,"");
    numspace=0;

    for(u=0;u<strlen(waktu[k]);u++)
{
    if(waktu[k][u] == ' ')
    {
        numspace++;
    }
    else if(numspace==0)
    {
        strcpy(tempwaktu,"");
        if(waktu[k][u]=='*')
        {
            cmptotal+=3;
        }
        else
        {
            if(waktu[k][u+1]==' ')
            {
                tempwaktu[0]='0';
                tempwaktu[2]='\0';
                tempwaktu[1]=waktu[k][u];
            }
            else
            {
                tempwaktu[1]=waktu[k][u+1];
                tempwaktu[2]='\0';
                tempwaktu[0]=waktu[k][u];
                u+=1;
            }

            if(strcmp(menitnow,tempwaktu)==0)cmptotal+=3;  
        }
    }
    else if(numspace==1)
    {
        strcpy(tempwaktu,"");
        if(waktu[k][u]=='*')
        {
            
            cmptotal+=3;
        }
        else
        {
            if(waktu[k][u+1]==' ')
            {
                tempwaktu[0]='0';
                tempwaktu[2]='\0';
                tempwaktu[1]=waktu[k][u];
                
            }
            else
            {
                tempwaktu[1]=waktu[k][u+1];
                tempwaktu[2]='\0';
                tempwaktu[0]=waktu[k][u];
                u+=1;
            }
            

            if(strcmp(jamnow,tempwaktu)==0)cmptotal+=3;    
        }
        
    }
    else if(numspace==2)
    {
        strcpy(tempwaktu,"");
        if(waktu[k][u]=='*')
        {
            
            cmptotal++;
        }
        else
        {
            if(waktu[k][u+1]==' ')
            {
                tempwaktu[0]='0';
                tempwaktu[2]='\0';
                tempwaktu[1]=waktu[k][u];
                
            }
            else
            {
                tempwaktu[1]=waktu[k][u+1];
                tempwaktu[2]='\0';
                tempwaktu[0]=waktu[k][u];
                u+=1;
            }
             

            if(strcmp(daynow,tempwaktu)==0)cmptotal++;    
        }
        
    }
    else if(numspace==3)
    {
        strcpy(tempwaktu,"");
        if(waktu[k][u]=='*')
        {
        
            cmptotal+=3;
        }
        else
        {
            if(waktu[k][u+1]==' ')
            {
                tempwaktu[0]='0';
                tempwaktu[2]='\0';
                tempwaktu[1]=waktu[k][u];
            
            }
            else
            {
                tempwaktu[1]=waktu[k][u+1];
                tempwaktu[2]='\0';
                tempwaktu[0]=waktu[k][u];
                u+=1;
            } 
 
            if(strcmp(monthnow,tempwaktu)==0)cmptotal+=3;   
        }
        
    }
    else if(numspace==4)
    {
        strcpy(tempwaktu,"");
        if(waktu[k][u]=='*')
        {
            cmptotal++;
        }
        else
        {
            if(waktu[k][u+1]==' ')
            {
                tempwaktu[0]='0';
                tempwaktu[2]='\0';
                tempwaktu[1]=waktu[k][u];
            }
            else
            {
                tempwaktu[1]=waktu[k][u+1];
                tempwaktu[2]='\0';
                tempwaktu[0]=waktu[k][u];
                u+=1;
            }
            //printf("%s\n",tempwaktu);
            if(strcmp(weeknow,tempwaktu)==0)cmptotal++;  
        }
    }
    else
    {
        break;
    }   
}

    printf("command: %s, cmp =%d\n",command[k],cmptotal);
    if(cmptotal >=10)
    {
        printf("Executing command: %s\n",command[k]);
        system(command[k]);
    }   
      sleep(1);
      cmptotal=0;
    }
    //sleep(60);
    }
}



int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/abin/PlayGround/")) < 0) {
    exit(EXIT_FAILURE);
  }

//   close(STDIN_FILENO);
//   close(STDOUT_FILENO);
//   close(STDERR_FILENO);

  while(1) {
    
    int i=0;
	int err;
	while(i<1) // loop sejumlah thread
	{
		err=pthread_create(&(tid[i]),NULL,&playandcount,NULL); //membuat thread
		if(err!=0) //cek error
		{
			//printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}
		i++;
	}
	pthread_join(tid[0],NULL);
	exit(0);


    sleep(30);
  }
  
  exit(EXIT_SUCCESS);
}