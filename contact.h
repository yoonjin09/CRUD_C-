#ifndef __CONTACT_H__
#define __CONTACT_H__
#include <string>

using namespace std;

typedef struct{
    int year;
    int month;
    int day;
}Date;

typedef struct{
    char name[64];
    Date dob;
    int date;
    char email[64];
    char phone[15];
}Person;


class Contact {
    private:
        Person* persons;
        int total_num;

        //Person str2person(char*);
        Date str2date(char*);

    public: 
        Contact(int size){
            total_num=0;
            persons = new Person[size];
        }
    ~Contact() {delete persons;}

    int load(string); //로드
    int Add(int); //추가 입력
    int selectMenu(); //main에서 메뉴 입력
    int selectDataNo(); //숫자 입력 받기
    int selectDelete(int); //삭제 할 내용 입력 받기
    int Delete(int, int); //삭제
    void print(int); //출력
    void searchName(int); //이름 검색(이름으로 retrievce)
    void searchEmail(int); //이메일 검색(이메일로 retrievce)
    void dateSort(int); //생일 기준으로 sort
    void nameSort(int); //이름 기준으로 sort
    void saveData(string,int); //저장
};

#endif
