/**
 * algorithm EfficientClosestPair from Levitin 3rd p194
 * closest pair by divide and conquer
 * @author Jon Beck
 * @modified by Nischal Shrestha
 * @version 4 March 2017
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <cfloat>
#include <cmath>

using namespace std;

typedef unsigned int uint;

/**
 * Make a class that sorts ascending by the first element of a pair
 */
struct SortFirst
{
  bool operator()(const pair<double,double> & left,
                  const pair<double,double> & right)
  {
    if( left.first == right.first )
      return left.second < right.second;
    return left.first < right.first;
  }
};

/**
 * Make a class that sorts ascending by the second element of a pair
 */
struct SortSecond
{
  bool operator()(const pair<double,double> & left,
                  const pair<double,double> & right)
  {
    if( left.second == right.second )
      return left.first < right.first;
    return left.second < right.second;
  }
};

/**
 * simple cartesian distance between two points imlemented
 * as pairs of doubles
 */
double distance( const pair<double,double> & p1,
                 const pair<double,double> & p2 )
{
  double diff_xs = p1.first - p2.first;
  double diff_ys = p1.second - p2.second;
  return sqrt( diff_xs * diff_xs + diff_ys * diff_ys );
}
/**
 * brute force closest pair distance
 * find the distance between the closest pair of points by brute force.
 * @param p a vector of points modeled as pairs of doubles, in
 * ascending order by the x coordinate
 * @param count a unsigned integer to count the basic operations.
 * @return the Cartesian distance between the closest pair of points
 */
double bf_close_pair_dist (const vector<pair<double,double>> & p, 
                            uint & count)
{
  double dist = DBL_MAX;
  for ( uint i = 1 ; i < p.size() - 1 ; ++i)
  {
    for ( uint j = i + 1 ; j < p.size() ; ++j )
    {
      double distancehere = distance( p.at( i ), p.at( j ));

      // Increase basic operation count, multiplication(squaring)
      // Squaring calculated in 'distance' function.
      count++;

      dist = min( dist, distancehere);     
    }
  }
  return dist;
}

/**
 * divide and conquer closest pair
 * if the number of elements is less than 4, solve by brute force
 * @param p a vector of points modeled as pairs of doubles, in
 * ascending order by the x coordinate
 * @param q a vector of points modeled as pairs of doubles, in
 * ascending order by the y coordinate
 * @param count a unsigned integer to count the basic operations.
 * @return the Cartesian distance between the closest pair of points
 */
double dc_close_pair_dist( const vector<pair<double,double>> & p,
                           const vector<pair<double,double>> & q, 
                           uint & count)
{
  if( p.size() < 2 )
    return 0.0;
  if( p.size() == 2 )
    return distance( p.at( 0 ), p.at( 1 ));
  if( p.size() == 3 )
  {
    double dist01 = distance( p.at( 0 ), p.at( 1 ));
    double dist02 = distance( p.at( 0 ), p.at( 2 ));
    double dist12 = distance( p.at( 1 ), p.at( 2 ));
    double min01 = dist01 < dist02 ? dist01 : dist02;
    return min01 < dist12 ? min01 : dist12;
  }

  vector<pair<double,double>> pl;
  vector<pair<double,double>> pr;
  vector<pair<double,double>> ql;
  vector<pair<double,double>> qr;

  for( uint i = 0; i < p.size() / 2; i++ )
  {
    pl.push_back( p.at( i ));
    ql.push_back( p.at( i ));

    // Increase basic operation count, copying half of 
    // the data in new vector.
    count++;
  }

  for( uint i = p.size() / 2; i < p.size(); i++ )
  {
    pr.push_back( p.at( i ));
    qr.push_back( p.at( i ));

    // Increase basic operation count, copying other half of 
    // the data in new vector.
    count++;
  }

  // pl and pr and in order, but need to sort ql and qr
  sort( ql.begin(), ql.end(), SortSecond() );
  sort( qr.begin(), qr.end(), SortSecond() );

  double dl = dc_close_pair_dist( pl, ql , count);
  double dr = dc_close_pair_dist( pr, qr , count);
  double d = min( dl, dr );
  double m = p.at( p.size() / 2 - 1 ).first;

  vector<pair<double,double>> s;
  for( auto point : q )
  {
    if( abs( point.first - m ) < d )
    {
      s.push_back( point );
    }
  }

  double dminsq = d * d;

  if( s.size() == 0 )
  {
    return sqrt( dminsq );
  }

  for( uint i = 0; i < s.size() - 1; i++ )
  {
    uint k = i + 1;
    while( k < s.size() &&
           pow( s.at( k ).second - s.at( i ).second, 2.0 ) < dminsq )
    {
      
      dminsq = min( pow( s.at( k ).first - s.at( i ).first, 2.0 ) +
                    pow( s.at( k ).second - s.at( i ).second, 2.0 ),
                    dminsq );
      // Increase basic operation count, calculating the minimum dist. 
      count++;

      k++;
    }
  }
  return sqrt( dminsq );
}

/*
 * standard input of points must be of the form
 * x-value y-value
 * x-value y-value
 * ...
 */
int main()
{
  vector<pair<double, double>> p; // Levitin's P array
  vector<pair<double, double>> q; // Levitin's Q array

  // Initializing the varibales to count basic operation for
  // each of the function.
  uint count_bf = 0;
  uint count_dc = 0;

  while( !cin.eof() )
  {
    double xvalue;
    double yvalue;

    cin >> xvalue >> yvalue;
    if( !cin.eof() )
    {
      p.push_back( make_pair( xvalue, yvalue ));
      q.push_back( make_pair( xvalue, yvalue ));
    }
  }

  // Calculating the input size for the program.
  uint inputSize = p.size();

  sort( p.begin(), p.end(), SortFirst() );
  sort( q.begin(), q.end(), SortSecond() );

  double mindistbf = bf_close_pair_dist(p , count_bf);
  double mindist = dc_close_pair_dist( p , q , count_dc);

  cout << "Miniumum bf distance: " << mindistbf << endl;
  cout << "Miniumum dc distance: " << mindist << endl;

  cerr << inputSize << "\t" << count_bf << "\t" << count_dc << endl;
  return 0;
}