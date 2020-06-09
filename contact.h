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

        Person str2person(char*);
        Date str2date(char*);

    public: 
        Contact(int size){
            total_num=0;
            persons = new Person[size];
        }
    ~Contact() {delete persons;}

    int load(string);
    int Add(int);
    void print(int);
    int selectMenu();
    int selectDataNo(int count);
    void searchName(int count);
    void dateSort(int count);
    void Delete(int no);
};

#endif
