#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class InvalidDateException
{
};
#endif /* __PROGTEST__ */

// uncomment if your code implements the overloaded suffix operators
// #define TEST_LITERALS

class Year
{
	public:
		Year(int year);
		int getY()const;
		Year operator - (){
			return Year(this->year*(-1));
    	}
	private:
		int year;
};

Year :: Year (int year)
{
	this->year=year;
}

int Year :: getY()const{
	return this->year;
}

class Month
{
	public:
		Month(int year);
		int getM()const;
	private:
		int month;
};

Month :: Month (int month)
{
	this->month=month;
}

int Month :: getM()const{
	return this->month;
}

class Day
{
	public:
		Day(int year);
		int getD()const;
	private:
		int day;
};

Day :: Day (int day)
{
	this->day=day;
}

int Day :: getD()const{
	return this->day;
}

class CDate
{
  public:
    // constructor
    CDate(int year,int month, int day);
    // operator(s) +
    CDate operator + (const Year & y)const{
    	return CDate(this->year+y.getY(),this->month,this->day);
    }
    CDate operator + (const Month & m)const{
    	int tmp=this->month+m.getM();
    	int month = tmp%12;
    	int year = this->year+(tmp/12);
    	if(month==0){
    		month=12;
    		year--;
    	}
    	return CDate(year,month,this->day);
    }
    CDate operator + (const Day & d){
    	int year=this->year;
    	int month=this->month;
    	int day=this->day+d.getD();
    	if(day<0)return CDate(this->year,this->month,this->day) - Day(abs(day-1));
    	while(day>(365+prestupny(year))){
    		day-=(365+prestupny(year));
    		year++;
    	}
    	while(day>mesiace[month]+prestupnym(year,month)){
    		day-=mesiace[month];
    		month++;
    		if(month==13)month=1;
    	}
    	return CDate(year,month,day);
    }
    // operator(s) -
    CDate operator - (const Year & y){
    	return CDate(this->year-y.getY(),this->month,this->day);
    }
    CDate operator - (const Month & m)const{
    	int minus = m.getM();
    	int month = this->month-(minus % 12);
    	int year = this->year;
    	if(month<1){
    		month=12-abs(month);
    		year--;
    	}
    	year -= (minus/12);
    	return CDate(year,month,this->day);
    }
    CDate operator - (const Day & d){
		int year=this->year;
    	int month=this->month;
    	int day=this->day-d.getD();

    	while(day<1){
    		month--;
    		if(month<1){
    			year--;
    			month+=12;
    		}
    		day+=mesiace[month]+prestupnym(year,month);
    	}
    	return CDate(year,month,day);
    }
    // operator +=
    CDate & operator += (const Year & y){
    	this->year+=y.getY();
    	return *this;
    }
    CDate & operator += (const Month & m){
    	this->month+=m.getM();
    	return *this;
    }
    CDate & operator += (const Day & d){
    	this->day+=d.getD();
    	return *this;
    }
    // operator ==
    // operator !=
    // operator <
    // operator(s) +=
    // operator <<
    friend ostream & operator << ( ostream & output, const CDate & c );

    int getYear(){
    	return this->year;
    }
    int getMonth(){
    	return this->month;
    }
    int getDay(){
    	return this->day;
    }
  private:
  	bool prestupny(int rok);
  	int prestupnym(int rok,int m);
  	bool test ( int y, int m, int d );
  	int mesiace[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int year;
    int month;
    int day;
};

ostream & operator << ( ostream & output, const CDate & d )
{
    output<<d.year<<"-";
    if(d.month<=9)output<<"0";
    output<<d.month<<"-";
    if(d.day<=9)output<<"0";
    output<<d.day;
    return output;
}

bool CDate :: prestupny( int rok) {
	if(rok%4 == 0){
		if( rok%100 == 0){
    		if ( rok%400 == 0){
    			if ( rok%4000 == 0){
					return false;	
    			}
    			else return true;
    		}
			else return false;
    	} 
		else return true;
	}
    else return false;
}

int CDate :: prestupnym( int rok, int m) {
	if(rok%4 == 0 && m==2){
		if( rok%100 == 0){
    		if ( rok%400 == 0 && m==2){
    			if ( rok%4000 == 0){
					return 0;	
    			}
    			else return 1;
    		}
    	} 
		else return 1;
	}
    else return 0;
}

bool CDate :: test ( int y, int m, int d )
{
	if(y<1600)return true;
	if(prestupny(y)&&(m==2)&&(d==29))return false;
	if((m<1)||(m>12))return true;
	if((d<1)||(d>mesiace[m]))return true;
	return false;
}

CDate :: CDate(int year,int month, int day){
	if(test(year,month,day)){
		throw InvalidDateException();
	}
	this->year=year;
	this->month=month;
	this->day=day;
}


#ifndef __PROGTEST__
string             toString                                ( const CDate     & x )
{
  ostringstream oss;
  oss << x;
  return oss . str ();
}

int                main                                    ( void )
{
  CDate tmp ( 2000, 1, 1 );
  assert ( toString ( CDate ( 2000, 1, 1 ) )  == "2000-01-01" );
  assert ( toString ( CDate ( 2500, 12, 21 ) )  == "2500-12-21" );
  assert ( toString ( CDate ( 1685, 7, 11 ) )  == "1685-07-11" );
  try
  {
    tmp = CDate ( 1900, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2000, 2, 29 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 2004, 2, 29 ) )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 4000, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 1 ) )  == "2019-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 7 ) )  == "2025-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 73 ) )  == "2091-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 3 ) )  == "2018-06-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 1 ) )  == "2018-04-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 285 ) )  == "2041-12-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 1 ) )  == "2018-03-16" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 12 ) )  == "2018-03-27" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 1234567 ) )  == "5398-05-02" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 3 ) )  == "2018-03-18" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 3 ) + Year ( 2 ) ) == "2020-03-18" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 3 ) + Year ( 2 ) + Month ( 3 ) )  == "2020-06-18" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 3 ) + Year ( 2 ) + Month ( 3 ) + Day ( 5 ) )  == "2020-06-23" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 3 ) + Year ( 2 ) + Month ( 3 ) + Day ( 5 ) + Month ( 11 ) )  == "2021-05-23" );
  try
  {
    tmp = CDate ( 2000, 2, 29 ) + Year ( 300 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 3, 30 ) + Month ( 11 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2001, 2, 20 ) + Day ( 9 ) )  == "2001-03-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) + Day ( 28 ) + Month ( 1 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 1999, 1, 1 ) + Year ( 1 ) + Day ( 28 ) + Month ( 1 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 2001, 1, 1 ) + Day ( 1095 ) + Day ( 28 ) + Month ( 1 ) )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 2001, 1, 1 ) + Day ( 28 ) + Month ( 1 ) + Day ( 1095 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + Day ( 28 ) + Month ( 1 ) + Year ( 1 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2000, 1, 1 );
  assert ( toString ( tmp - Year ( 5 ) + Month ( 2 ) )  == "1995-03-01" );
  assert ( toString ( tmp ) == "2000-01-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 1 ) )  == "1999-01-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 1 ) - Month ( 3 ) )  == "1998-10-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 1 ) - Month ( 3 ) - Day ( 10 ) )  == "1998-09-21" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 2 ) - Month ( -3 ) )  == "1998-04-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 2 ) - Month ( -3 ) + Day ( -10 ) )  == "1998-03-22" );
  assert ( toString ( CDate ( 2000, 1, 1 ) + Day ( 59 ) - Month ( 1 ) - Year ( 2 ) )  == "1998-01-29" );
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + Day ( 59 ) - Year ( 2 ) - Month ( 1 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2000, 1, 1 );
  //tmp +=  - Year ( 2 ) - Month ( -3 );// + Day ( -10 );
  /*assert ( toString ( tmp ) == "1998-03-22" );
  tmp = CDate ( 2000, 1, 1 );
  tmp += Day ( 59 ) - Month ( 1 ) - Year ( 2 );
  assert ( toString ( tmp ) == "1998-01-29" );
  try
  {
    tmp = CDate ( 2000, 1, 1 );
    tmp += Day ( 59 ) - Year ( 2 ) - Month ( 1 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2018, 3, 15 ) + Day ( -3 );
  assert ( toString ( tmp ) == "2018-03-12" );
  assert ( !( CDate ( 2018, 3, 15 ) == CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) != CDate ( 2000, 1, 1 ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) == CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) != CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + Day ( 1 ) == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( 1 ) != CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) + Day ( 1 ) < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + Day ( -1 ) == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( -1 ) != CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) + Day ( -1 ) < CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) - CDate ( 2000, 1, 1 ) == 6648 );
  assert ( CDate ( 2000, 1, 1 ) - CDate ( 2018, 3, 15 ) == -6648 );
  assert ( CDate ( 2018, 3, 15 ) + Year ( 3 ) + Month ( -18 ) - CDate ( 2000, 1, 1 ) == 7197 );
  assert ( CDate ( 5398, 5, 2 ) - CDate ( 2018, 3, 15 ) == 1234567 );
#ifdef TEST_LITERALS
  assert ( toString ( CDate ( 2000, 1, 1 ) )  == "2000-01-01" );
  assert ( toString ( CDate ( 2500, 12, 21 ) )  == "2500-12-21" );
  assert ( toString ( CDate ( 1685, 7, 11 ) )  == "1685-07-11" );
  try
  {
    tmp = CDate ( 1900, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2000, 2, 29 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 2004, 2, 29 ) )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 4000, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1_year )  == "2019-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 7_years )  == "2025-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 73_years )  == "2091-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 3_months )  == "2018-06-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1_month )  == "2018-04-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 285_months )  == "2041-12-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1_day )  == "2018-03-16" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 12_days )  == "2018-03-27" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1234567_days )  == "5398-05-02" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 3_days + 2_years + 3_months + 5_days + 11_months )  == "2021-05-23" );
  try
  {
    tmp = CDate ( 2000, 2, 29 ) + 300_years;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 3, 30 ) + 11_months;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2001, 2, 20 ) + 9_days )  == "2001-03-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) + 28_days + 1_month )  == "2000-02-29" );
  assert ( toString ( CDate ( 1999, 1, 1 ) + 1_year + 28_days + 1_month )  == "2000-02-29" );
  assert ( toString ( CDate ( 2001, 1, 1 ) + 1095_days + 28_days + 1_month )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 2001, 1, 1 ) + 28_days + 1_month + 1095_days;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + 28_days + 1_month + 1_year;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2000, 1, 1 );
  assert ( toString ( tmp - 5_years + 2_months )  == "1995-03-01" );
  assert ( toString ( tmp ) == "2000-01-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - 1_year - 3_months - 10_days )  == "1998-09-21" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - 2_years - ( -3_months ) + ( -10_days ) )  == "1998-03-22" );
  assert ( toString ( CDate ( 2000, 1, 1 ) + 59_days - 1_month - 2_years )  == "1998-01-29" );
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + 59_days - 2_years - 1_month;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2000, 1, 1 );
  tmp +=  - 2_years - ( -3_months ) + ( -10_days );
  assert ( toString ( tmp ) == "1998-03-22" );
  tmp = CDate ( 2000, 1, 1 );
  tmp += 59_days - 1_month - 2_years;
  assert ( toString ( tmp ) == "1998-01-29" );
  try
  {
    tmp = CDate ( 2000, 1, 1 );
    tmp += 59_days - 2_years - 1_month;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2018, 3, 15 ) + ( -3_days );
  assert ( toString ( tmp ) == "2018-03-12" );
  assert ( !( CDate ( 2018, 3, 15 ) == CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) != CDate ( 2000, 1, 1 ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) == CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) != CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + 1_day == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + 1_day != CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) + 1_day < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + ( -1_day ) == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + ( -1_day ) != CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) + ( -1_day ) < CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) - CDate ( 2000, 1, 1 ) == 6648 );
  assert ( CDate ( 2000, 1, 1 ) - CDate ( 2018, 3, 15 ) == -6648 );
  assert ( CDate ( 2018, 3, 15 ) + 3_years + ( -18_months ) - CDate ( 2000, 1, 1 ) == 7197 );
  assert ( CDate ( 5398, 5, 2 ) - CDate ( 2018, 3, 15 ) == 1234567 );
  ostringstream oss;
  oss << setfill ( 'x' ) << left << hex << CDate ( 2000, 1, 1 ) << ' ' << setw ( 10 ) << 65536;
  assert ( oss . str () == "2000-01-01 10000xxxxx" );
#endif /* TEST_LITERALS */
  return 0;
}
#endif /* __PROGTEST__ */
