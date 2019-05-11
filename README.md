# FP_SISOP19_B09

# Daemon Thread
Buatlah program C yang menyerupai crontab menggunakan daemon dan thread. Ada sebuah file crontab.data untuk menyimpan config dari crontab. Setiap ada perubahan file tersebut maka secara otomatis program menjalankan config yang sesuai dengan perubahan tersebut tanpa perlu diberhentikan. Config hanya sebatas * dan 0-9 (tidak perlu /,- dan yang lainnya)

#
* Untuk membaca File

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
      
