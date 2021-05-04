#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */
 
class Empl
{
public:
    Empl( const string & n, const string & sn, const string & e, unsigned int s ){
      this->name = make_pair(n, sn);
      this->email = e;
      this->salary = s;
    }

    ~Empl( void ){
    }

    pair<string, string> getName( void ) const{
      return this->name;
    }

    string getEmail ( void ) const{
      return this->email;
    }

    unsigned int getSalary ( void ) const{
    return this->salary;
    };

    pair<string, string> name;
    string email;
    unsigned int salary;
};
 
class CPersonalAgenda
{
public:
    CPersonalAgenda  ( void );
    ~CPersonalAgenda ( void );
    bool          Add              ( const string    & name,
                                     const string    & surname,
                                     const string    & email,
                                     unsigned int      salary );
    bool          Del              ( const string    & name,
                                     const string    & surname );
    bool          Del              ( const string    & email );
    bool          ChangeName       ( const string    & email,
                                     const string    & newName,
                                     const string    & newSurname );
    bool          ChangeEmail      ( const string    & name,
                                     const string    & surname,
                                     const string    & newEmail );
    bool          SetSalary        ( const string    & name,
                                     const string    & surname,
                                     unsigned int      salary );
    bool          SetSalary        ( const string    & email,
                                     unsigned int      salary );
    unsigned int  GetSalary        ( const string    & name,
                                     const string    & surname ) const;
    unsigned int  GetSalary        ( const string    & email ) const;
    bool          GetRank          ( const string    & name,
                                     const string    & surname,
                                     int             & rankMin,
                                     int             & rankMax ) const;
    bool          GetRank          ( const string    & email,
                                     int             & rankMin,
                                     int             & rankMax ) const;
    bool          GetFirst         ( string          & outName,
                                     string          & outSurname ) const;
    bool          GetNext          ( const string    & name,
                                     const string    & surname,
                                     string          & outName,
                                     string          & outSurname ) const;
private:
    vector<Empl*> arrn;
    vector<Empl*> arre;
    vector<Empl*> arrs;
    vector<Empl*>::iterator it_name;
    vector<Empl*>::iterator it_email;
    vector<Empl*>::iterator it_salary;
    static bool emailCmp ( const Empl* a, const string & e );
    static bool nameCmp ( const Empl* a, const pair<string, string> & name );
    static bool salaryCmp ( const Empl* a, unsigned int s );
    static bool salaryCmp2 ( unsigned int salary, const Empl* a );
    bool findEmail ( const string & m );
    bool findName ( const string & n, const string & sn );
    void findSalary ( unsigned int s );
};
 
bool CPersonalAgenda::emailCmp(const Empl *a, const string & e) {
    if(a->email < e){
      return true;
    }
    return false;
}
 
bool CPersonalAgenda::nameCmp(const Empl *a, const pair<string, string> & name) {
    if(name.second == a->name.second){
      if(a->name.first < name.first){
        return true;
      }
      return false;
    }
    if(a->name.second < name.second){
      return true;
    }
    else return false;
}
 
bool CPersonalAgenda::salaryCmp(const Empl *a, unsigned int s) {
    if (a->salary < s){
      return true;
    }
    return false;
}
 
bool CPersonalAgenda::salaryCmp2(unsigned int s, const Empl *a) {
    if (a->salary > s){
      return true;
    }
    return false;
}
 
CPersonalAgenda::CPersonalAgenda( void ) {
}
 
CPersonalAgenda::~CPersonalAgenda( void ) {
}
 
bool CPersonalAgenda::Del ( const string & email ) {
 
    if(!findEmail(email)) return false;
    findName((*it_email)->name.first, (*it_email)->name.second);
    findSalary((*it_email)->salary);
    for(auto it = it_salary; it != arrs.end(); it++) {
        if ((*it)->email == email) {
            arrs.erase(it);
            break;
        }
    }
    this->it_email = arre.erase(this->it_email);
    this->it_name = arrn.erase(this->it_name);
    return true;
}
 
bool CPersonalAgenda::Del ( const string & name, const string & surname ) {
 
    if(!findName(name, surname)) return false;
    findEmail((*it_name)->email);
    findSalary((*it_name)->salary);
    for(auto it = it_salary; it != arrs.end(); it++) {
        if ((*it)->email == (*it_email)->email) {
            arrs.erase(it);
            break;
        }
    }
    this->it_email = arre.erase(this->it_email);
    this->it_name = arrn.erase(this->it_name);
    return true;
}
 
bool CPersonalAgenda::ChangeEmail ( const string & name, const string & surname, const string & newEmail ) {
    if(!findName(name, surname)) return false;
    if(findEmail(newEmail)) return false;
    auto tmp_salary = (*(this->it_name))->salary;
    Del(name, surname);
    Add(name, surname, newEmail, tmp_salary);
    return true;
}

bool CPersonalAgenda::ChangeName ( const string & email, const string & newName, const string & newSurname ) {
    if(!findEmail(email)) return false;
    if(findName(newName, newSurname)) return false;
    auto tmp_salary = (*(this->it_email))->salary;
    Del(email);
    Add(newName, newSurname, email, tmp_salary);
    return true;
}
 
bool CPersonalAgenda::GetRank ( const string & name, const string & surname, int & rankMin, int & rankMax ) const {
    auto pair_name = make_pair(name, surname);
    auto it_name = lower_bound(arrn.begin(), arrn.end(), pair_name, nameCmp);
    if (!(arrn.end() != it_name && (*it_name)->name.first == name && (*it_name)->name.second == surname)) return false;
 
    auto it_salary_down = lower_bound(arrs.begin(), arrs.end(), (*it_name)->salary, salaryCmp);
    auto it_salary_up = upper_bound(arrs.begin(), arrs.end(), (*it_name)->salary, salaryCmp2);

    rankMin = (int) (it_salary_down - arrs.begin());
    rankMax = rankMin + (int) (it_salary_up - it_salary_down)-1;
 
    return true;
}
 
bool CPersonalAgenda::GetRank ( const string & email, int & rankMin, int & rankMax ) const {
    auto it_email = lower_bound(arre.begin(), arre.end(), email, emailCmp);
    if (!(it_email != arre.end() && (*it_email)->email == email)) return false;
 
    auto it_salary_down = lower_bound(arrs.begin(), arrs.end(), (*it_email)->salary, salaryCmp);
    auto it_salary_up = upper_bound(arrs.begin(), arrs.end(), (*it_email)->salary, salaryCmp2);
 
    rankMin = (int) (it_salary_down - arrs.begin());
    rankMax = rankMin + (int) (it_salary_up - it_salary_down)-1;
 
    return true;
}

unsigned int  CPersonalAgenda::GetSalary ( const string & name, const string & surname ) const {
    auto pair_name = make_pair(name, surname);
    auto it_name = lower_bound(arrn.begin(), arrn.end(), pair_name, nameCmp);
    if (!(arrn.end() != it_name && (*it_name)->name.first == name && (*it_name)->name.second == surname)) return 0;
    return (*it_name)->salary;
}
 
unsigned int  CPersonalAgenda::GetSalary ( const string    & email ) const {
    auto it_email = lower_bound(arre.begin(), arre.end(), email, emailCmp);
    if (!(it_email != arre.end() && (*it_email)->email == email)) return 0;
    return (*it_email)->salary;
}

bool CPersonalAgenda::SetSalary ( const string & name, const string & surname, unsigned int salary ) {
    if(!findName(name, surname)) return false;
    if(salary == (*(this->it_name))->salary) return true;
    auto tmp_email = (*(this->it_name))->email;
    Del(name, surname);
    Add(name, surname, tmp_email, salary);
    return true;
}
 
bool CPersonalAgenda::SetSalary ( const string & email, unsigned int salary ) {
    if(!findEmail(email)) return false;
    if(salary == (*(this->it_email))->salary) return true;
    auto tmp_name = make_pair((*(this->it_email))->name.first, (*(this->it_email))->name.second);
    Del(email);
    Add(tmp_name.first, tmp_name.second, email, salary);
    return true;
 
}

bool CPersonalAgenda::GetNext ( const string & name, const string & surname, string & outName, string & outSurname ) const {
    auto pair_name = make_pair(name, surname);
    auto it_name = lower_bound(arrn.begin(), arrn.end(), pair_name, nameCmp);
    unsigned long index = it_name - arrn.begin();
    if(index+1 >= arrn.size()) return false;
    outName = arrn[index+1]->name.first;
    outSurname = arrn[index+1]->name.second;
    return true;
}

bool CPersonalAgenda::GetFirst ( string & outName, string & outSurname ) const {
    if(arre.size() > 0) {
        outName = arrn.front()->name.first;
        outSurname = arrn.front()->name.second;
    } else {
        return false;
    }
    return true;
}
 
 void CPersonalAgenda::findSalary ( unsigned int s )  {
    this->it_salary = lower_bound(arrs.begin(), arrs.end(), s, salaryCmp);
}

bool CPersonalAgenda::findName ( const string & n, const string & sn ) {
    this->it_name = lower_bound(arrn.begin(), arrn.end(), make_pair(n, sn), nameCmp);
    if(it_name != arrn.end() && (*it_name)->name.second == sn && (*it_name)->name.first == n) return true;
    return false;
}

bool CPersonalAgenda::findEmail ( const string & e ) {
    this->it_email = lower_bound(arre.begin(), arre.end(), e, emailCmp);
    if(it_email != arre.end() && (*it_email)->email == e) return true;
    return false;
}

 bool CPersonalAgenda::Add ( const string & name, const string & surname, const string & email, unsigned int salary ) {
 
    if(findEmail(email)) return false;
    if(findName(name, surname)) return false;
    findSalary(salary);
    auto a = new Empl(name, surname, email, salary);
    arrn.insert(this->it_name, a);
    arre.insert(this->it_email, a);
    arrs.insert(this->it_salary, a);
    delete a;
    return true;
}

#ifndef __PROGTEST__
int main ( void )
{
    string outName, outSurname;
    int lo, hi;
 
    CPersonalAgenda b1;
    assert ( b1 . Add ( "John", "Smith", "john", 30000 ) );
    assert ( b1 . Add ( "John", "Miller", "johnm", 35000 ) );
    assert ( b1 . Add ( "Peter", "Smith", "peter", 23000 ) );
    assert ( b1 . GetFirst ( outName, outSurname )
             && outName == "John"
             && outSurname == "Miller" );
    assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( b1 . GetNext ( "John", "Smith", outName, outSurname )
             && outName == "Peter"
             && outSurname == "Smith" );
    assert ( ! b1 . GetNext ( "Peter", "Smith", outName, outSurname ) );
    assert ( b1 . SetSalary ( "john", 32000 ) );
    assert ( b1 . GetSalary ( "john" ) ==  32000 );
    assert ( b1 . GetSalary ( "John", "Smith" ) ==  32000 );
    assert ( b1 . GetRank ( "John", "Smith", lo, hi )
             && lo == 1
             && hi == 1 );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 1
             && hi == 1 );
    assert ( b1 . GetRank ( "peter", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . GetRank ( "johnm", lo, hi )
             && lo == 2
             && hi == 2 );
    assert ( b1 . SetSalary ( "John", "Smith", 35000 ) );
    assert ( b1 . GetSalary ( "John", "Smith" ) ==  35000 );
    assert ( b1 . GetSalary ( "john" ) ==  35000 );
    assert ( b1 . GetRank ( "John", "Smith", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . GetRank ( "peter", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . GetRank ( "johnm", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . ChangeName ( "peter", "James", "Bond" ) );
    assert ( b1 . GetSalary ( "peter" ) ==  23000 );
    assert ( b1 . GetSalary ( "James", "Bond" ) ==  23000 );
    assert ( b1 . GetSalary ( "Peter", "Smith" ) ==  0 );
    assert ( b1 . GetFirst ( outName, outSurname )
             && outName == "James"
             && outSurname == "Bond" );
    assert ( b1 . GetNext ( "James", "Bond", outName, outSurname )
             && outName == "John"
             && outSurname == "Miller" );
    assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( ! b1 . GetNext ( "John", "Smith", outName, outSurname ) );
    assert ( b1 . ChangeEmail ( "James", "Bond", "james" ) );
    assert ( b1 . GetSalary ( "James", "Bond" ) ==  23000 );
    assert ( b1 . GetSalary ( "james" ) ==  23000 );
    assert ( b1 . GetSalary ( "peter" ) ==  0 );
    assert ( b1 . Del ( "james" ) );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 0
             && hi == 1 );
    assert ( b1 . Del ( "John", "Miller" ) );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . GetFirst ( outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( ! b1 . GetNext ( "John", "Smith", outName, outSurname ) );
    assert ( b1 . Del ( "john" ) );
    assert ( ! b1 . GetFirst ( outName, outSurname ) );
    assert ( b1 . Add ( "John", "Smith", "john", 31000 ) );
    assert ( b1 . Add ( "john", "Smith", "joHn", 31000 ) );
    assert ( b1 . Add ( "John", "smith", "jOhn", 31000 ) );
 
    CPersonalAgenda b2;
    assert ( ! b2 . GetFirst ( outName, outSurname ) );
    assert ( b2 . Add ( "James", "Bond", "james", 70000 ) );
    assert ( b2 . Add ( "James", "Smith", "james2", 30000 ) );
    assert ( b2 . Add ( "Peter", "Smith", "peter", 40000 ) );
    assert ( ! b2 . Add ( "James", "Bond", "james3", 60000 ) );
    assert ( ! b2 . Add ( "Peter", "Bond", "peter", 50000 ) );
    assert ( ! b2 . ChangeName ( "joe", "Joe", "Black" ) );
    assert ( ! b2 . ChangeEmail ( "Joe", "Black", "joe" ) );
    assert ( ! b2 . SetSalary ( "Joe", "Black", 90000 ) );
    assert ( ! b2 . SetSalary ( "joe", 90000 ) );
    assert ( b2 . GetSalary ( "Joe", "Black" ) ==  0 );
    assert ( b2 . GetSalary ( "joe" ) ==  0 );
    assert ( ! b2 . GetRank ( "Joe", "Black", lo, hi ) );
    assert ( ! b2 . GetRank ( "joe", lo, hi ) );
    assert ( ! b2 . ChangeName ( "joe", "Joe", "Black" ) );
    assert ( ! b2 . ChangeEmail ( "Joe", "Black", "joe" ) );
    assert ( ! b2 . Del ( "Joe", "Black" ) );
    assert ( ! b2 . Del ( "joe" ) );
    assert ( ! b2 . ChangeName ( "james2", "James", "Bond" ) );
    assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "james" ) );
    assert ( ! b2 . ChangeName ( "peter", "Peter", "Smith" ) );
    assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "peter" ) );
    assert ( b2 . Del ( "Peter", "Smith" ) );
    assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "peter2" ) );
    assert ( ! b2 . SetSalary ( "Peter", "Smith", 35000 ) );
    assert ( b2 . GetSalary ( "Peter", "Smith" ) ==  0 );
    assert ( ! b2 . GetRank ( "Peter", "Smith", lo, hi ) );
    assert ( ! b2 . ChangeName ( "peter", "Peter", "Falcon" ) );
    assert ( ! b2 . SetSalary ( "peter", 37000 ) );
    assert ( b2 . GetSalary ( "peter" ) ==  0 );
    assert ( ! b2 . GetRank ( "peter", lo, hi ) );
    assert ( ! b2 . Del ( "Peter", "Smith" ) );
    assert ( ! b2 . Del ( "peter" ) );
    assert ( b2 . Add ( "Peter", "Smith", "peter", 40000 ) );
    assert ( b2 . GetSalary ( "peter" ) ==  40000 );
    
  CPersonalAgenda b3;
  assert ( b3 . Add ( "!!!", "!", "Mpuhsmxmahgcca", 70000 ) );
  assert ( b3 . Add ( "!!", "!!!", "as", 40000 ) );
  assert ( b3 . Del ( "!!", "!!!" ) );
  assert ( b3 . Add ( "!!", "!!!", "as", 40000 ) );
  assert ( b3 . Add ( "!!", "!!", "!as", 500 ) );
  assert ( b3 . Add ( "aasdas!", "!!dsadas!", "a~!@#$%^&*()_+s", 11000 ) );
  assert ( b3 . Add ( "lsk!", "!!sad!", "&*as", 300 ) );
  assert ( b3 . Add ( "al!", "!sss!!", "a0976s", 70 ) );
  assert ( b3 . ChangeEmail ( "!!", "!!", "C" ) );
  assert ( b3 . ChangeEmail ( "!!", "!!!", "james" ) );
  assert ( b3 . ChangeName ("james", "DFGHJ", "XCFGHJ" ) );
  assert ( b3 . ChangeName ("&*as", "plmnjkl", "rghnm" ) );
  assert ( b3 . Add ( "aasd!", "!!!", "a{}s", 3 ) );
  assert ( b3 . Add ( "al!", "al!", "a||s", 4560 ) );
  assert ( b3 . Add ( "!ds", "aasdas!", "aSs", 12000 ) );
  assert ( b3 . GetSalary ( "Mpuhsmxmahgcca" ) ==  70000 );
  assert ( b3 . GetSalary ( "aSs" ) ==  12000 );
  assert ( b3 . GetSalary ( "C" ) ==  500 );
  assert ( b3 . Add ( "a", "1", "a", 1 ) );
  assert ( b3 . Add ( "b", "2", "b", 2 ) );
  assert ( b3 . Add ( "a", "3", "c", 3 ) );
  assert ( b3 . Add ( "b", "4", "d", 4 ) );
  assert ( b3 . Add ( "a", "5", "e", 5 ) );
  assert ( b3 . Add ( "b", "6", "f", 6 ) );
  assert ( b3 . Add ( "a", "7", "g", 7 ) );
  assert ( b3 . Add ( "b", "8", "h", 8 ) );
  assert ( b3 . Add ( "aa", "1", "aa", 1 ) );
  assert ( b3 . Add ( "c", "2", "bb", 2 ) );
  assert ( b3 . Add ( "e", "3", "cc", 3 ) );
  assert ( b3 . Add ( "g", "4", "dd", 4 ) );
  assert ( b3 . Add ( "h", "5", "ee", 5 ) );
  assert ( b3 . Add ( "f", "6", "ff", 6 ) );
  assert ( b3 . Add ( "d", "7", "gg", 7 ) );
  assert ( b3 . Add ( "bb", "8", "hh", 8 ) );
  assert ( b3 . Add ( "", "", "", 8 ) );

  assert ( b3. Add ("peter","jalovec","petj",5));
  assert ( b3. Add ("tomas","stastny","toms",5));
  assert ( b3. Add ("peter","stastny","pets",5));

  assert ( !b3 . Add ( "aa", "1", "aa", 1 ) );
  assert ( !b3 . Add ( "c", "2", "b", 2 ) );
  assert ( !b3 . Add ( "e", "3", "c", 3 ) );
  assert ( !b3 . Add ( "g", "4", "d", 4 ) );
  assert ( !b3 . Add ( "h", "5", "e", 5 ) );
  assert ( !b3 . Add ( "f", "6", "f", 6 ) );
  assert ( !b3 . Add ( "d", "7", "g", 7 ) );
  assert ( !b3 . Add ( "bb", "8", "h", 8 ) );
  assert ( !b3 . Add ( "a", "1", "a", 1 ) );
  assert ( !b3 . Add ( "b", "2", "b", 2 ) );
  assert ( !b3 . Add ( "a", "3", "c", 3 ) );
  assert ( !b3 . Add ( "b", "4", "d", 4 ) );
  assert ( !b3 . Add ( "a", "5", "e", 5 ) );
  assert ( !b3 . Add ( "b", "6", "f", 6 ) );
  assert ( !b3 . Add ( "a", "7", "g", 7 ) );
  assert ( !b3 . Add ( "b", "8", "h", 8 ) );
  assert ( !b3 . Add ( "!!!", "!", "Mpuhsmxmahgcca", 70000 ) );
  assert ( !b3 . Add ( "!!", "!!", "!as", 500 ) );
  assert ( !b3 . Add ( "aasdas!", "!!dsadas!", "a~!@#$%^&*()_+s", 11000 ) );
  assert ( !b3 . Add ( "al!", "!sss!!", "a0976s", 70 ) );
  assert ( !b3 . Add ( "aasd!", "!!!", "a{}s", 3 ) );
  assert ( !b3 . Add ( "al!", "al!", "a||s", 4560 ) );
  assert ( !b3 . Add ( "!ds", "aasdas!", "aSs", 12000 ) );

    return 0;
}
#endif /* __PROGTEST__ */