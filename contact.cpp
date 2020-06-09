#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
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
  
  cout<<"이름을 입력하세요: ";
  cin.getline(aname,64);

  cout<<"생일을 입력하세요";
  cin>>adate;

  cout<<"이메일을 입력하세요";
  cin>>aemail;

  cout<<"전화번호을 입력하세요";
  cin>>aphone;


  strcat(lines,aname);
  strcat(lines,"; ");
  strcat(lines,adate);
  strcat(lines,"; ");
  strcat(lines,aemail);
  strcat(lines,"; ");
  strcat(lines,aphone);

  persons[cont_i++]=str2contact(lines);
  return cont_i;
}

void Contact::print(int current){
    int i;
    Person c;
    printf("\n");
   for(i=0; i<current; i++){
     c=persons[i];
     if(c.date!=-1){
      printf("%d번 %s; %d %d %d;%s;%11s\n",i+1, c.name, c.dob.year, c.dob.month,c.dob.day,c.email,c.phone);
     }
   }

}

int Contact::selectMenu(){
  int menu;
  printf("\n\n<Menu>\n");
  printf("1. Print\n");
  printf("2. Insert\n");
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
    if(strstr(c.name, search)) printf("\n%d번 %s; %d %d %d;%s;%11s",t+1, c.name, c.dob.year, c.dob.month,c.dob.day,c.email,c.phone);
  }
}



int compareVAL(const void *arg1, const void *arg2){
  int v1;
  int v2;
  v1 = ((Person*)arg1)->date;
  v2 = ((Person*)arg2)->date;

  if(v1>v2) return -1;
  else if(v1 == v2) return 0;  
  else return 1;
}

void Contact::dateSort(int count){
 qsort(persons,count, sizeof(Person),compareVAL); 
}

int Contact::selectDataNo(int count){
  int no;
  Contact::print(count);
  printf("삭제할 번호는(취소: 0)?: ");
  cin>>no;
  return no;
}

void Contact::Delete(int no){
  persons[no-1].date=-1;
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
      fprintf(fp,"%s; %d%d%d;%s;%s\n", c.name, c.dob.year, c.dob.month,c.dob.day,c.email,c.phone);
    }
  }
}
