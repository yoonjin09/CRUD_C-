#include <iostream>
#include <string>
#include "contact.h"

using namespace std;

#define MAX_NUM 1000 // can be given by standard input

int main() {
    string file_name;
    Contact* contacts;
    int cont_i=0;
    int current,menu,retrieve;
    contacts = new Contact(MAX_NUM);

    cout << "file name of contact data:" << endl;
    cin >> file_name;

    cont_i=contacts->load(file_name);
    current=cont_i;

    while(1){
      menu = contacts->selectMenu();
      if(menu==0) break;
      if(menu==1) contacts->print(current);
      if(menu==2) current = contacts->Add(current);
      if(menu==3) contacts->searchName(current);
      if(menu==4) {
        int no=contacts->selectDataNo(current);
        if(no==0) continue;
        contacts->Delete(no);
      
      } 
      if(menu==5) contacts->dateSort(current);
      if(menu==6) contacts->saveData(file_name, current);
    }
    
    
  
    return 0;
}
