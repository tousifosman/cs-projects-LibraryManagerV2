#ifndef MEMBERINFO_H
#define MEMBERINFO_H

#include <string>
#include <list>

using namespace std;

//enum Field {ID, Name, Aouther};

class MemberInfo{
public:
    string
    Name,
    Email,
    PhoneNumber;

    int id;
    list<int> borrowInfo;

    //Field *bObjField;

    MemberInfo(int inID);

//    bool operator==(BookInfo right);
//    bool operator>(BookInfo right);
//    bool operator>=(BookInfo right);
//    bool operator<(BookInfo right);
//    bool operator<=(BookInfo right);
//    void setSortField(Field *inField);
//
    bool BorrowBooks(int bookID);
    bool ReturnBooks(int bookID);
};

#endif // MEMBERINFO_H

