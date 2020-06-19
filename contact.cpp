#include <stdio.h>
#include <string.h>
#include <iostream>
#include "contact.h"


using namespace std;


Date str2date(char*str){
  Date date;
  char temp[10];
  
  strncpy(temp, str, 5);
  temp[5]=0;
  date.year = atoi(temp);

  strncpy(temp, str+5, 2);
  temp[2]=0;
  date.month = atoi(temp);

  strncpy(temp, str+7, 2);
  temp[2]=0;
  date.day = atoi(temp);
  
  return date;
}

Person str2contact(char* line){
  Person cont;
  char *token;
  char temp[64];
  
  int i=0;
  
        token = strtok(line, ";");
        while(token){
            strcpy(temp, token);
            // copy the items to struct
            switch(i){
               case 0: strcpy(cont.name, temp); break;
               case 1: cont.dob = str2date(temp); cont.date=atoi(temp); break;
               case 2: strcpy(cont.email, temp); break;
               case 3: strncpy(cont.phone,temp,14);
                       cont.phone[14]='\0'; 
                       break;
            } 
            //printf("token: [%s]\n", token);
            i++;
            token = strtok(NULL, ";"); 
        }
  return cont;
  
}
 


int Contact::load(string file_name){
    char c_str[1024];
    strcpy(c_str, file_name.c_str());

    FILE *fp;
    char *line=NULL;
    size_t len;
    char *token;
    
    fp = fopen(c_str, "r");
    if (fp == NULL) {
        printf("Cannot open %s\n", c_str);
        exit(-1);
    }

    
    int cont_i = 0;

     while (getline(&line, &len, fp) != EOF){
       persons[cont_i++]=str2contact(line);
    }
    
    free(line);
    fclose(fp);
  return cont_i;
}

int Contact::Add(int cont_i){
  char aname[64];
  char adate[10];
  char aemail[64];
  char aphone[14];
  char lines[200]="";
  getchar();
  
  cout<<"\n**추가**\n"<<endl;
  cout<<"이름을 입력하세요: ";
  cin.getline(aname,64);

  cout<<"생일을 입력하세요(YYYYMMDD): ";
  cin>>adate;
  if(strlen(adate)!=8){
    cout<<"\n!!!!형식에 맞게 입력하세요!!!!"<<endl;
    cout<<"!!!!취소되었습니다!!!!";
    return cont_i;
  } 

  cout<<"이메일을 입력하세요: ";
  cin>>aemail;

  cout<<"전화번호을 입력하세요(-을 입력하세요): ";
  cin>>aphone;
  if(strlen(aphone) != 13){
    cout<<"\n!!!!형식에 맞게 입력하세요!!!!";
    cout<<"!!!!취소되었습니다!!!!";
    return cont_i;
  }

  strcat(lines,aname);
  strcat(lines,"; ");
  strcat(lines,adate);
  strcat(lines,"; ");
  strcat(lines,aemail);
  strcat(lines,"; ");
  strcat(lines,aphone);

  persons[cont_i++]=str2contact(lines);
  cout<<"\n저장이 완료되었습니다";
  return cont_i;
}

void Contact::print(int current){
    int i;
    Person c;
    printf("\n");
   for(i=0; i<current; i++){
     c=persons[i];
     if(c.date!=-1){
      printf("%s; %d %d %d;%s;%11s\n",c.name, c.dob.year, c.dob.month,c.dob.day,c.email,c.phone);
     }
   }

}

int Contact::selectMenu(){
  int menu;
  printf("\n\n<Menu>\n");
  printf("1. Print\n");
  printf("2. Add\n");
  printf("3. Retrieve\n");
  printf("4. Delete\n");
  printf("5. Sort\n");
  printf("6. Save\n");
  printf("0. Exit\n\n");
  cout<<"Select menu: ";
  cin>>menu;
  return menu;
}

void Contact::searchName(int count){
  int scount=0;
  char search[64];
  Person c;
  getchar();
  cout<<"검색하고 싶은 이름은?: ";
  cin.getline(search,64);
  for(int t=0; t<count; t++){
    c = persons[t];
    if(strstr(c.name, search)) printf("\n%s; %d %d %d;%s;%11s",c.name, c.dob.year, c.dob.month,c.dob.day,c.email,c.phone);
  }
}

void Contact::searchEmail(int count){
  int scount=0;
  char search[64];
  Person c;
  getchar();
  cout<<"검색하고 싶은 이메일은?: ";
  cin.getline(search,64);
  for(int t=0; t<count; t++){
    c = persons[t];
    if(strstr(c.email, search)) printf("\n%s; %d %d %d;%s;%11s",c.name, c.dob.year, c.dob.month,c.dob.day,c.email,c.phone);
  }
}

int compareVAL_D(const void *arg1, const void *arg2){
  int v1;
  int v2;
  v1 = ((Person*)arg1)->date;
  v2 = ((Person*)arg2)->date;

  if(v1>v2) return 1;
  else if(v1 == v2) return 0;  
  else return -1;
}

void Contact::dateSort(int count){
 qsort(persons,count, sizeof(Person),compareVAL_D); 
}

int compareVAL_N(const void *arg1, const void *arg2){
  char v1[64];
  char v2[64];
  strcpy(v1,((Person*)arg1)->name);
  strcpy(v2,((Person*)arg2)->name);

  if(strcmp(v1,v2)>0) return 1;
  else if(strcmp(v1,v2)==0) return 0;  
  else return -1;
}

void Contact::nameSort(int count){
 qsort(persons,count, sizeof(Person),compareVAL_N); 
}

int Contact::selectDataNo(){
  int no;
  cin>>no;
  return no;
}

int Contact::selectDelete(int count){
  int no;
  int nocount = count;
  char dname[64];
  Person c;
  Contact::print(count);
  getchar();
  cout<<"\n삭제하고 싶은 이름은?: ";
  cin.getline(dname,64);
  for(int t=0; t<count; t++){
    c = persons[t];
    if(strcmp(c.name, dname)==0) {
      printf("\n%s 관련한 정보를 삭제 하겠습니다 \n",c.name);
      no=t+1;
      nocount--;
    }
  }
  if(nocount == count) {
    cout<<"일치하는 정보가 없습니다 \n 정확하게 입력하세요."<<endl;
    no=0;
  }
  return no;
}

int Contact::Delete(int no, int count){
  for(int t=no-1; t<count; t++){
    persons[t]=persons[t+1];
  } 
  count--;
  return count; 
}

void Contact::saveData(string filename, int count){
  FILE*fp;
  char ch[30];
  strcpy(ch,filename.c_str());
  Person c;
  fp=fopen(ch,"wt");
  for(int i=0; i< count;i++){
    c=persons[i];
    if(c.date!=-1){
      if(c.dob.month>9 && c.dob.day>9){
        fprintf(fp,"%s; %d%d%d;%s;%s", c.name, c.dob.year, c.dob.month,c.dob.day,c.email,c.phone);
      }
      else if(c.dob.month>9 && c.dob.day<10){
        fprintf(fp,"%s; %d%d0%d;%s;%s", c.name, c.dob.year, c.dob.month,c.dob.day,c.email,c.phone);
      }
      else if(c.dob.month<10 && c.dob.day>9){
        fprintf(fp,"%s; %d0%d%d;%s;%s", c.name, c.dob.year, c.dob.month,c.dob.day,c.email,c.phone);
      }
      else if(c.dob.month<10 && c.dob.day<10){
        fprintf(fp,"%s; %d0%d0%d;%s;%s", c.name, c.dob.year, c.dob.month,c.dob.day,c.email,c.phone);
      }
      if(i!=count-1){
        fprintf(fp,"\n");
      }
    }
    
  }
}
