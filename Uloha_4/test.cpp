#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;
#endif /* __PROGTEST__ */

class String
{
public:
    String(){               //implicit constructor
        buffer = nullptr;
        size = 0;
    };

    String(const String & s){   //string constructor
        size = s.size;
        buffer = new char[size];
        for(int i = 0; i < size; i++){  //copy string char by char from old string to new
            buffer[i] = s.buffer[i];
        }
    };

    String(const char *p){  //array constructor
        int i = 0;
        const char * t = p;
        while(*p++) {       //find length of p
            i++;
        }
        buffer = new char[i];
        int j = 0;

        for(;*t;t++,j++) {   //copy data from p to new
            buffer[j] = *t;
        }
        size = j;
    };

    ~String(){              //destructor
        delete [] buffer;    //free buffer
    };

    int length() const{
        if(buffer == nullptr) { //check if string is empty
            return 0;
        }
        else {
            return size;        //return size of string
        }
    };

    char & operator[] (unsigned int x){ //overloaded operator
        return buffer[x];
    };

    void operator =(const String & s){  //overloaded operator
        delete [] buffer;           //delete old data from left operand
        buffer=new char[s.size];    //create new space for left operand
        size=s.size;                //copy size of string
        for (int i = 0; i <size; ++i) {
            buffer[i] = s.buffer[i];    //copy string char by char into left operand
        }
    };

    friend bool operator ==(const String & s,const String & t){ //overloaded operator
        if(s.length() != t.length()) {  // check if length of strings is different
            return false;
        }
        else {
            for(int i = 0; i < s.length(); i++) { // check character by characte if they are the same
                if(s.buffer[i] != t.buffer[i]) {
                    return false;
                }
            }
        }
        return true;
    };

    friend ostream & operator<<(ostream & os, const String & s){ // overloaded operator
        for(int i = 0; i < s.size; i++) {
            os << s.buffer[i];  //add string into ostream character by character
        }
        return os;
    }
private:
    int size;
    char * buffer;
};
/*
************************************************************************************************************
 */
template <class T>
class MyVector
{
public:
    MyVector(){ //implicit constructor
        size = 0;
        alloc = 1;
        arr = new T[alloc];
    }

    int getSize()const{//getter for size
        return size;
    }

    void insert(const T & item){//insert irem into MyVector
        if(size == alloc){  // check if there is enough space allocated, if not realloc more
            realloc();
        }
        arr[size] = item;   // add item to MyVector
        size++;             // increase number of items
    }

    MyVector (const MyVector<T> & item){    //copy constructor
        alloc = item.alloc;         // copy number of allocated elements
        arr = new T[alloc];
        size = item.size;           // comy maximum elements allocated
        for(int i = 0; i<size;i++){  //copy ellement after ellement
            arr[i] = item.arr[i];
        }
    }

    MyVector<T> & operator =(const MyVector<T> item){//overloaded operator
        delete [] arr;  //delete left argument
        alloc = item.alloc;
        arr = new T[alloc]; // create new space for left argument
        size = item.size;
        for( int i = 0; i<size;i++){  //copy elements of vector to left argument
            arr[i] = item.arr[i];
        }
        return *this;
    }

    T & operator [] (int index){
        return arr[index];
    };

    const T & operator [] (int index)const{
        return arr[index];
    }

    ~MyVector(){
        delete [] arr;  // free allocated memory
    }

    void DecSize(){
        size--;
    }
    void setSize(int v){
        size = v;
    }

private:
    T * arr;
    int size;
    int alloc;
    void realloc(){     // expand alocated memory
        alloc *= 2;     // double the size of allocated memory
        T * tmp = new T[alloc]; //allocate new memory
        for( int i = 0; i < alloc/2; i++){    // copy the data
            tmp[i] = arr[i];
        }
        delete [] arr;     // free the memory from smaller vector
        arr = tmp;
    }
};
/*
************************************************************************************************************
 */
class CMail
{
  public:
    CMail(const char * from, const char * to, const char * body ){
        this -> from = String(from);
        this -> to = String(to);
        this -> body = String(body);
    };

    bool operator ==( const CMail & x ) const{
        return (from == x.from && to == x.to && body == x.body); // if any part of "left" CMail is different than "right" return false
    };

    String getto()const{    // return recieving email from Cmail
        return to;
    }

    String getfrom()const{ // return sending email from Cmail
        return from;
    }
private:
    String from;
    String to;
    String body;
};
/*
************************************************************************************************************
 */
class CMailIterator
{
  public:
    CMailIterator (){
        count = 0;
        pos = 0;
    };

    operator bool( void ) const{    //checks if counter havent't passed number of mails in iterator. If so, it means we have reached end of iterator.
        return(count > pos);
    };

    bool operator !( void ) const{//same as overloaded bool but reversed
        return(count <= pos);
    };

    const CMail & operator *( void ) const{
        return *mails[pos]; // return CMail to whitch iterator is pointing
    };

    CMailIterator & operator ++( void ){
        pos++;
        return *this;
    };

    void add (CMail *i){
        count++;
        mails.insert(i);
    };

  private:
    MyVector <CMail *> mails;
    int count;
    int pos;
};
/*
************************************************************************************************************
 */
class CMailServer
{
  public:
    CMailServer( ){

    };

    CMailServer( const CMailServer & src ){ //copy constructor
        for (int i = 0; i < src.history.getSize(); i++) {  // copy vector element by element
            CMail* tmp = new CMail(src.getmail(i));
            history.insert(tmp);
        }
    };

    CMailServer & operator =( const CMailServer & src ){
        if ( &src == this )return *this;    // check if left operand equals right, if so return it
        int s = history.getSize();
        for (int i = 0; i < s; i++) {  // delete left side of operator
            delete history[i];
            history.DecSize();
        }
        for (int i = 0; i < src.history.getSize(); i++) {  // copy vector element by element
            CMail* tmp = new CMail(src.getmail(i));
            history.insert(tmp);
        }
        return *this;
    };

    ~CMailServer( void ){
        for (int i = 0; i < history.getSize(); i++) { //delete all elements
            delete history[i];
        }
    };

    void SendMail (const CMail & m ){
        CMail* tmp = new CMail(m);
        history.insert(tmp);
    };

    CMailIterator Outbox (const char * email ) const{
        CMailIterator it = CMailIterator();
        for (int i = 0; i < history.getSize(); i++) {  //iterate through all mails in history
            if (history[i] -> getfrom() == String(email)){      //CMails, whitch have correct sending emails are inserted into iterator
                it.add(history[i]);
            };
        };
        return it;          // return iterator with correct emails in it
    };

    CMailIterator Inbox (const char * email ) const{
        CMailIterator it = CMailIterator();
        for (int i = 0; i < history.getSize(); i++) {  //iterate through all mails in history
            if (history[i] -> getto() == String(email)){        //CMails, whitch have correct sending emails are inserted into iterator
                it.add(history[i]);
            };
        };
        return it;          // return iterator with correct emails in it
    };
    CMail getmail (int i)const{
        return *history[i];
    }

private:
    MyVector<CMail *>history;
};
/*
************************************************************************************************************
 */
#ifndef __PROGTEST__
int main ( void )
{
  char from[100], to[100], body[1024];
  assert ( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "peter", "progtest deadline" ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "progtest deadline", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "john", "progtest deadline" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "progtest deadline", "john" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "john", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "peter", "john" ) ) );
  CMailServer s0;
  s0 . SendMail ( CMail ( "john", "peter", "some important mail" ) );
  strncpy ( from, "john", sizeof ( from ) );
  strncpy ( to, "thomas", sizeof ( to ) );
  strncpy ( body, "another important mail", sizeof ( body ) );
  s0 . SendMail ( CMail ( from, to, body ) );
  strncpy ( from, "john", sizeof ( from ) );
  strncpy ( to, "alice", sizeof ( to ) );
  strncpy ( body, "deadline notice", sizeof ( body ) );
  s0 . SendMail ( CMail ( from, to, body ) );
  s0 . SendMail ( CMail ( "alice", "john", "deadline confirmation" ) );
  s0 . SendMail ( CMail ( "peter", "alice", "PR bullshit" ) );
  CMailIterator i0 = s0 . Inbox ( "alice" );
  assert ( i0 && *i0 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i0 && *i0 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ! ++i0 );

  CMailIterator i1 = s0 . Inbox ( "john" );
  assert ( i1 && *i1 == CMail ( "alice", "john", "deadline confirmation" ) );
  assert ( ! ++i1 );

  CMailIterator i2 = s0 . Outbox ( "john" );
  assert ( i2 && *i2 == CMail ( "john", "peter", "some important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "thomas", "another important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ! ++i2 );

  CMailIterator i3 = s0 . Outbox ( "thomas" );
  assert ( ! i3 );

  CMailIterator i4 = s0 . Outbox ( "steve" );
  assert ( ! i4 );

  CMailIterator i5 = s0 . Outbox ( "thomas" );
  s0 . SendMail ( CMail ( "thomas", "boss", "daily report" ) );
  assert ( ! i5 );

  CMailIterator i6 = s0 . Outbox ( "thomas" );
  assert ( i6 && *i6 == CMail ( "thomas", "boss", "daily report" ) );
  assert ( ! ++i6 );

  CMailIterator i7 = s0 . Inbox ( "alice" );
  s0 . SendMail ( CMail ( "thomas", "alice", "meeting details" ) );
  assert ( i7 && *i7 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i7 && *i7 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ! ++i7 );

  CMailIterator i8 = s0 . Inbox ( "alice" );
  assert ( i8 && *i8 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i8 && *i8 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i8 && *i8 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ! ++i8 );

    CMailServer s1 ( s0 );
  s0 . SendMail ( CMail ( "joe", "alice", "delivery details" ) );
  s1 . SendMail ( CMail ( "sam", "alice", "order confirmation" ) );
  CMailIterator i9 = s0 . Inbox ( "alice" );
  assert ( i9 && *i9 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i9 && *i9 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i9 && *i9 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i9 && *i9 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( ! ++i9 );

  CMailIterator i10 = s1 . Inbox ( "alice" );
  assert ( i10 && *i10 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i10 && *i10 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i10 && *i10 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i10 && *i10 == CMail ( "sam", "alice", "order confirmation" ) );
  assert ( ! ++i10 );

  CMailServer s2;
  s2 . SendMail ( CMail ( "alice", "alice", "mailbox test" ) );
  CMailIterator i11 = s2 . Inbox ( "alice" );
  assert ( i11 && *i11 == CMail ( "alice", "alice", "mailbox test" ) );
  assert ( ! ++i11 );

  s2 = s0;
  s0 . SendMail ( CMail ( "steve", "alice", "newsletter" ) );
  s2 . SendMail ( CMail ( "paul", "alice", "invalid invoice" ) );
  CMailIterator i12 = s0 . Inbox ( "alice" );
  assert ( i12 && *i12 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i12 && *i12 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i12 && *i12 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i12 && *i12 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( ++i12 && *i12 == CMail ( "steve", "alice", "newsletter" ) );
  assert ( ! ++i12 );

  CMailIterator i13 = s2 . Inbox ( "alice" );
  assert ( i13 && *i13 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i13 && *i13 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i13 && *i13 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i13 && *i13 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( ++i13 && *i13 == CMail ( "paul", "alice", "invalid invoice" ) );
  assert ( ! ++i13 );

  return 0;
}
#endif /* __PROGTEST__ */
