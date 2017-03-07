#ifndef BOOKINFO_H
#define BOOKINFO_H

#include <string>
#include <list>

using namespace std;

enum Field {ID, Name, Aouther};

struct borrowStruct{
    int ID;
    string name;
    string dateOfIssue;
};

class BookInfo{
public:
    string
    BookName,
    AuthourName,
    Publishar;

    int id;
    int AvalableCopy;
    list<borrowStruct> borrowInfo;

    Field *bObjField;

    BookInfo(int inID, Field *inField);

    bool operator==(BookInfo right);
    bool operator>(BookInfo right);
    bool operator>=(BookInfo right);
    bool operator<(BookInfo right);
    bool operator<=(BookInfo right);
    void setSortField(Field *inField);

    bool BorrowBooks(int memberID, string name, string date);
    bool ReturnBooks(int memberID);

};

#endif // BOOKINFO_H
