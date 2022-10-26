#include<stdio.h>
#include<iostream>
using namespace std;

typedef struct
{
    char* name;
    int age;
}Person;

struct newPerson
{
    char *name;
    int age;
};


int main(){
    char name1[]="liming";
    char name2[]="liuqi";
    Person liming = {
        name1,18
    };

    newPerson liuqi = {
            name2, 19};
    printf("Liming's age is %d.\n",liming.age);
    cout << "Liming's age is "<< liming.age<<".\n";

    printf("Liuqi's age is %d.\n", liuqi.age);
    cout << "Liuqi's age is " << liuqi.age << ".\n";
}