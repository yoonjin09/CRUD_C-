#include <iostream>
#include <string>
#include "contact.h"

using namespace std;

#define MAX_NUM 1000 // can be given by standard input

int main() {
    string file_name; //파일 이름 입력 변수
    Contact* contacts;
    int cont_i=0;
    int current,menu,num1;  //current : 현재 저장된 정보 개수, menu : 메뉴 선택, num1 : 숫자 선택(sort와 retrieve에 사용)
    contacts = new Contact(MAX_NUM);

    cout << "file name of contact data:" << endl;
    cin >> file_name;

    cont_i=contacts->load(file_name); //로드
    current=cont_i;

    while(1){
      menu = contacts->selectMenu();
      if(menu==0) break;  //종료
      if(menu==1) contacts->print(current); //출력
      if(menu==2) current = contacts->Add(current); //추가 입력
      if(menu==3) { //검색
        cout << "이름으로 검색하시려면 1, 이메일로 검색하시려면 2를 누르세요: ";
        num1=contacts->selectDataNo();
        switch (num1){
          case 1 :cout<<"이름으로 검색합니다"<<endl<<endl;
                  contacts->searchName(current);
                  break;
          case 2 :cout<<"이메일로 검색합니다"<<endl;
                  contacts->searchEmail(current); break;
          default : cout<<"1이나 2를 입력해주세요"<<endl; break;
        }
      }
      if(menu==4) { //삭제
        int no=contacts->selectDelete(current);
        if(no==0) continue;
        current=contacts->Delete(no, current);
      
      } 
      if(menu==5){  //정렬
        cout << "이름을 기준으로 sort를 진행하려면 1, 생일로 sort를 진행하려면 2를 누르세요: ";
        num1=contacts->selectDataNo();
        switch (num1){
          case 1 :cout<<"이름을 기준으로 정렬합니다"<<endl;
                  contacts->nameSort(current);
                  break;
          case 2 :cout<<"생일을 기준으로 정렬합니다"<<endl;
                  contacts->dateSort(current); 
                  break;
          default : cout<<"1이나 2를 입력해주세요"<<endl; break;
        }
        if(num1 == 1 || num1 ==2){
          cout<<"\n완료했습니다";
          contacts->print(current);
        } 
      }
      if(menu==6) { //저장
        contacts->saveData(file_name, current);
        cout<<"\n저장이 완료 되었습니다"<<endl;
      }    
    }
    
    
  
    return 0;
}
