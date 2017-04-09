 
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
std::ostream& operator <<(std::ostream& o, const vector<T>& v)
{
  for(auto i : v)
    o << i << ' ';
  return o;
}

template <typename T>
std::ostream& operator <<(std::ostream& o, const list<T>& v)
{
  int ii = 0;
  for(auto i : v) {
    ii++;
    o << i << (!(ii%5)? "\n" : " , ");
  }
  return o;
}

////////////////////


#define COUT cout


using Vi = vector< int >;
using ViI = Vi::iterator;

using Vii = vector< Vi >;
using ViiI = Vii::iterator;

template <>
std::ostream& operator <<(std::ostream& o, const Vi& v)
{
  for(auto i : v) {
    o << i << ' ';
  }
  o << endl;
  return o;
}
template <>
std::ostream& operator <<(std::ostream& o, const Vii & vii)
{
  for(auto i : vii) {
    o << i;
  }
  return o;
}
using Li = list< int >;
using LiI = Li::iterator;

struct Ic {
  int i;
  Li l;
  Ic() : i(0), l(0){ }
};

using Vic = vector< Ic >;
using VicI = Vic::iterator;

using Vvic = vector< Vic >;
using VvicI = Vvic::iterator;

template <>
std::ostream& operator <<(std::ostream& o, const Li & v)
{
  int ii = (int)v.size();
  for(auto i : v) {
    ii--;
    // o << i << (!(ii%5)? "\n" : " , ");
    o << i << (ii?", ":"");
  }
  return o;
}

std::ostream& operator <<(std::ostream& o, const Ic& ic)
{
    o << ic.i << ' ';
    if (ic.l.size()) { //o << "list: (size: " << v.size() << ") " ;
      o << '(';
      o << ic.l;
      o << ')';
      
    }
    return o;
}

template <>
std::ostream& operator <<(std::ostream& o, const Vic& v)
{
  for(auto i : v) {
    o << i << ' ';
  }
  o << endl;
  return o;
}
template <>
std::ostream& operator <<(std::ostream& o, const Vvic & vii)
{
  for(auto i : vii) {
    //    o << i << 'X';
    o << i;
  }
  return o;
}


///// ---------------------------------
/*
Problem 3: Theatre Seating

You run a small theater and each month, you have patrons mail in requests for pre-sale tickets. You need to process these ticket requests and either tell them where their party will sit or explain to the patron why you can't complete their order.

You have a few rules that you need to follow when you fill the orders:

Fill as many orders as possible
Put parties as close to the front as possible.
If there are not enough seats available in the theater to handle a party, tell them "Sorry, we can't handle your party."
Each party must sit in a single row in a single section. If they won't fit, tell them "Call to split party".
Your program must parse a theater layout and a list of ticket requests and produce a list of tickets or explanations in the same order as the requests.

The theater layout is made up of 1 or more rows. Each row is made up of 1 or more sections separated by a space.

After the theater layout, there is one empty line, followed by 1 or more theater requests. The theater request is made up of a name followed by a space and the number of requested tickets.

Sample input:

6 6
3 5 5 3
4 6 6 4
2 8 8 2
6 6

Smith 2
Jones 5
Davis 6
Wilson 100
Johnson 3
Williams 4
Brown 8
Miller 12
Your program must produce results to standard output in the same order as the requests, with the name of the person who requested the ticket and either the row and section of the ticket or the explanations "Sorry, we can't handle your party" or "Call to split party."

Sample output:

Smith Row 1 Section 1
Jones Row 2 Section 2
Davis Row 1 Section 2
Wilson Sorry, we can't handle your party.
Johnson Row 2 Section 1
Williams Row 1 Section 1
Brown Row 4  Section 2
Miller Call to split party.

*/

struct Customer {
  string name;
  int count;
  int index;
  string legend;

  Customer() {}
  Customer(string name,  int count, int index, string legend = "") : name(name), count(count), index(index), legend(legend) { 
    // COUT << "Customer(name: '" << name << "' count: " << count << ")" <<  endl;
  }

};

std::ostream& operator <<(std::ostream& o, const Customer& c)
{
  o << c.name << ' ' << c.legend ;
  return o;
}

using Vc = vector <Customer>;
using VcI = Vc::iterator;

template <>
std::ostream& operator <<(std::ostream& o, const Vc& vc)
{
  for(auto i : vc) {
    o << i << endl;
  }
  o << endl;
  return o;
}

////////////////////
// Informally, the problem is to maximize the sum of the values of the items in the knapsack so that the sum of the weights is less than or equal to the knapsack's capacity.
// It has a table with optimization that the outside vector has only size 2 (instead of N) which improves space requirements tremendously.

void knapsack(int N, int capacity, Vc & vc, int row, int section) {
  Vvic vii(2);
  for (auto & i : vii) {
    Vic vic(capacity+1);
    i = vic;
  }

  int value;
  for (int i=1; i <N + 1; ++i) { // N + 1
    for ( int x = 0; x < capacity + 1; ++x) {  //  capacity + 1
      int w = vc[i-1].count;
      if (x-w < 0)
	value = 0;
      else 
	value = (vii[0][x-w].i+vc[i-1].count);

      vii[1][x].i = max(vii[0][x].i, value);

      if (vii[0][x].i < value) {
	vii[1][x].l = vii[0][x-w].l;
	vii[1][x].l.push_back(vc[i-1].index);
      }
    }
    copy(vii[1].begin(), vii[1].end(), vii[0].begin());
    if  (vii[1][capacity].i == capacity)
      break;
  }

  for (auto i : vii[1][capacity].l) {
    VcI it = std::find_if (vc.begin(), vc.end(), [i](Customer & c) { return i==c.index; } );

    string & legend = (*it).legend;

    legend = "Row ";
    char str[12];
    sprintf(str, "%d", row);
    legend += str;
    legend += " Section ";
    sprintf(str, "%d", section);
    legend += str;

    (*it).count = 0;
  }
}

////////////////
int main(int argc, char ** argv) {

  string line;
  Vii vii;
  Vc vc;
  
  bool customers = false;
  int theatreCapacity = 0;
  int numberOfCustomers = 0;
  int N = 0;
  int maxBlock  = 0;
  
  while (!cin.eof()) {
    
    getline(cin, line);
    int len = line.length();
    if (!len) {
      customers = true;
      continue;
    }
    
    string buf;
    stringstream ss(line);
    
    if (!customers) {
      
      Vi seats; // Create vector to hold our seats
      
      while (ss >> buf) {
	int block = atoi(buf.c_str());
	seats.push_back(block);
	theatreCapacity += block;
	maxBlock = (block>maxBlock?block:maxBlock);
      }
      vii.push_back(seats);
    }
    else {
      string name;
      string legend;
      int count;
      ss >> name;
      ss >> count;

      if (count > theatreCapacity)
	legend = "Sorry, we can't handle your party.";
      else {
	numberOfCustomers += count;
	
	if (count > maxBlock) 
	  legend = "Call to split party.";
      }
      Customer customer(name, count, N, legend) ;
      vc.push_back(customer);
      N++;
    }
  }
    
  sort (vc.begin(), vc.end(), [](const Customer & lhs, const Customer & rhs) { return lhs.count < rhs.count; } );

  int row=0, section;
  for(auto vi : vii) {
    row++;
    section=0;
    for(auto capacity : vi) {
      section++;
      knapsack(N, capacity, vc, row, section);
    }
  }
  
  sort (vc.begin(), vc.end(), [](const Customer & lhs, const Customer & rhs) { return lhs.index < rhs.index; } );

  cout << vc << endl;

  return 0;
}
