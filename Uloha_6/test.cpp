#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

// enable only if your implementation supports Add ( ) with more than three parameters
 #define MULTIPLE_STOPS

template<typename _E>
bool retrue(const _E & var){
    return true;
}

template <typename _T, typename _E>
class CAccess
{
  public:
   // default constructor
    CAccess() {

   }
   // destructor
   // Add
   template <typename... _A>
   CAccess & Add(const _E & vertex, const _A & ... city){
       list<_T> lst={city...};
       for (auto i = lst.begin(); i != lst.end(); ++i){
           for (auto j = i; j != lst.end(); ++j){
               graph [ *i ].push_back( make_pair( *j, vertex));
               graph [ *j ].push_back( make_pair( *i, vertex));
           }
       }
//       graph [ arr[i] ].push_back( make_pair( to, vertex));
//       graph [  ].push_back( make_pair( from, vertex));
        return * this;
   }
   // Find (with optional max and filter)
   map< _T, int > Find (const _T & city,const int max=0)const{
       return Find(city,max,retrue<_E>);
   };

   template <typename _F>
    map< _T, int > Find (const _T & city,const int max, const _F func)const{
       queue < pair < _T , int > > q;
       set < _T > visited;
       map < _T, int > pred;
       if(!graph.count(city)){
            stringstream strs;
            strs<<"unknown "<<city;
            string str=strs.str();
           throw invalid_argument(str);
       }
       pred.insert(pair<_T,int>(city,0));
       q.push ( make_pair ( city, 0 ) );
       visited.insert ( city );
       while(!q.empty()){
           const _T node = q.front ( ).first;
           const int dist = q.front ( ).second;
           q.pop();

           for ( auto const & n : graph.at ( node ) )
           {
               if ( visited.count ( n.first ) == 0 && (max>=dist+1||max==0) && func(n.second))
               {
                   q.push (make_pair ( n.first, dist + 1 ) );
                   visited.insert ( n.first );
                       pred.insert ( pair<_T,int>(n.first, dist+1) );
               }
           }
       }
       return pred;
   }

    private:
    map < _T, vector< pair< _T, _E > > > graph;
};

template < class T, class U >
std::ostream & operator << ( std::ostream& os, const std::map < T, U > & x )
{
    for ( const std::pair < const T, U > & kv : x )
        os << kv.first << " -> " << kv.second << std::endl;
    return os;
}

#ifndef __PROGTEST__
//=================================================================================================
class CTrain
{
  public:
                             CTrain                        ( const string    & company,
                                                             int               speed )
                             : m_Company ( company ),
                               m_Speed ( speed )
    {
    }
    //---------------------------------------------------------------------------------------------
    string                   m_Company;
    int                      m_Speed;
};
//=================================================================================================
class TrainFilterCompany
{
  public:
                             TrainFilterCompany            ( const set<string> & companies ) 
                             : m_Companies ( companies ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain & train ) const
    { 
      return m_Companies . find ( train . m_Company ) != m_Companies . end (); 
    }
    //---------------------------------------------------------------------------------------------
  private:  
    set <string>             m_Companies;    
};
//=================================================================================================
class TrainFilterSpeed
{
  public:
                             TrainFilterSpeed              ( int               min, 
                                                             int               max )
                             : m_Min ( min ), 
                               m_Max ( max ) 
    { 
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain    & train ) const
    { 
      return train . m_Speed >= m_Min && train . m_Speed <= m_Max; 
    }
    //---------------------------------------------------------------------------------------------
  private:  
    int                      m_Min;
    int                      m_Max; 
};
//=================================================================================================
bool                         NurSchnellzug                 ( const CTrain    & zug )
{
  return ( zug . m_Company == "OBB" || zug . m_Company == "DB" ) && zug . m_Speed > 100;
}
//=================================================================================================
int                          main                          ( void )
{
  CAccess<string,CTrain> lines;
  lines . Add ( CTrain (   "DB", 120 ), "Berlin", "Prague"   )
        . Add ( CTrain (   "CD",  80 ), "Berlin", "Prague"   )
        . Add ( CTrain (   "DB", 160 ), "Berlin", "Dresden"  )
        . Add ( CTrain (   "DB", 160 ), "Dresden", "Munchen" )
        . Add ( CTrain (   "CD",  90 ), "Munchen", "Prague"  )
        . Add ( CTrain (   "DB", 200 ), "Munchen", "Linz"    )
        . Add ( CTrain (  "OBB",  90 ), "Munchen", "Linz"    )
        . Add ( CTrain (   "CD",  50 ), "Linz", "Prague"     )
        . Add ( CTrain (   "CD", 100 ), "Prague", "Wien"     )
        . Add ( CTrain (  "OBB", 160 ), "Linz", "Wien"       )
        . Add ( CTrain ( "SNCF", 300 ), "Paris", "Marseille" )
        . Add ( CTrain ( "SNCF", 250 ), "Paris", "Dresden"   )
        . Add ( CTrain ( "SNCF", 200 ), "London", "Calais"   );
  assert ( lines . Find ( "Berlin" ) == (map<string,int>
  {
    make_pair ( "Berlin", 0 ),
    make_pair ( "Dresden", 1 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Marseille", 3 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "London" ) == (map<string,int>
  {
    make_pair ( "Calais", 1 ),
    make_pair ( "London", 0 )
  }) );
  assert ( lines . Find ( "Wien" ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Marseille", 5 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Paris", 4 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 0 )
  }) );
  assert ( lines . Find ( "Wien", 3 ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 0 )
  }) );
  assert ( lines . Find ( "Wien", 5, NurSchnellzug ) == (map<string,int>
  {
    make_pair ( "Berlin", 4 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Prague", 5 ),
    make_pair ( "Wien", 0 )
  }) );
  assert ( lines . Find ( "Prague", 3,  TrainFilterCompany ( { "CD", "DB" } ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 1 ),
    make_pair ( "Dresden", 2 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 1 ),
    make_pair ( "Prague", 0 ),
    make_pair ( "Wien", 1 )
  }) );
  assert ( lines . Find ( "Munchen", 4, TrainFilterSpeed ( 160, 250 ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 1 ),
    make_pair ( "Linz", 1 ),
    make_pair ( "Munchen", 0 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "Munchen", 4, [] ( const CTrain & x ) { return x . m_Company == "CD"; } ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Munchen", 0 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "London", 20, [] ( const CTrain & x ) { return x . m_Company == "CD"; } ) == (map<string,int>
  {
    make_pair ( "London", 0 )
  }) );
  try
  {
     auto res = lines . Find ( "Salzburg" );
     assert ( "No exception thrown" == NULL );
  }
  catch ( const invalid_argument & e )
  {
    assert ( string ( e . what () ) == "unknown Salzburg" );
  }
#ifdef MULTIPLE_STOPS
  lines . Add ( CTrain ( "RZD",  80 ), "Prague", "Kiev", "Moscow", "Omsk", "Irkutsk", "Vladivostok" );
  lines . Add ( CTrain ( "LAV", 160 ), "Malaga", "Cordoba", "Toledo", "Madrid", "Zaragoza", "Tarragona", "Barcelona", "Montpellier", "Marseille" );
  assert ( lines . Find ( "Madrid" ) == (map<string,int>
  {
    make_pair ( "Barcelona", 1 ),
    make_pair ( "Berlin", 4 ),
    make_pair ( "Cordoba", 1 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 6 ),
    make_pair ( "Kiev", 6 ),
    make_pair ( "Linz", 5 ),
    make_pair ( "Madrid", 0 ),
    make_pair ( "Malaga", 1 ),
    make_pair ( "Marseille", 1 ),
    make_pair ( "Montpellier", 1 ),
    make_pair ( "Moscow", 6 ),
    make_pair ( "Munchen", 4 ),
    make_pair ( "Omsk", 6 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Prague", 5 ),
    make_pair ( "Tarragona", 1 ),
    make_pair ( "Toledo", 1 ),
    make_pair ( "Vladivostok", 6 ),
    make_pair ( "Wien", 6 ),
    make_pair ( "Zaragoza", 1 )
  }) );
  assert ( lines . Find ( "Omsk", 4 ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 1 ),
    make_pair ( "Kiev", 1 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Moscow", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Omsk", 0 ),
    make_pair ( "Paris", 4 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Vladivostok", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "Moscow", 10, TrainFilterCompany ( { "RZD", "DB" } ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 1 ),
    make_pair ( "Kiev", 1 ),
    make_pair ( "Linz", 5 ),
    make_pair ( "Moscow", 0 ),
    make_pair ( "Munchen", 4 ),
    make_pair ( "Omsk", 1 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Vladivostok", 1 )
  }) );
#endif /* MULTIPLE_STOPS */
  return 0;
}
#endif  /* __PROGTEST__ */