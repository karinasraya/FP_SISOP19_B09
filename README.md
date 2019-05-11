# FP_SISOP19_B09

# Daemon Thread
Buatlah program C yang menyerupai crontab menggunakan daemon dan thread. Ada sebuah file crontab.data untuk menyimpan config dari crontab. Setiap ada perubahan file tersebut maka secara otomatis program menjalankan config yang sesuai dengan perubahan tersebut tanpa perlu diberhentikan. Config hanya sebatas * dan 0-9 (tidak perlu /,- dan yang lainnya)

#
* Untuk membaca File
 
      strcpy(file_name,"crontab.data");

      fp = fopen(file_name, "r"); // read mode
    
      if (fp == NULL)
      {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
      }

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
      
* Untuk membaca waktu dan eksekusi

      for(k=0;k<j;k++)
      {
            time( &rawtime );

      info = localtime( &rawtime );
      strftime(buffer,80,"%M%H%d%m%w", info);

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
      }
      }
      
* Sehingga program ini akan berjalan sesuai dengan waktu dan command perintahnya.
