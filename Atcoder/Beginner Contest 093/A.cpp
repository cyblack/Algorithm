
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string h;

int main(int argc, const char * argv[]) {
  
 
    cin >> h;
    
    sort(h.begin(),h.end());
    
    if(h=="abc") cout << "Yes";
    else cout << "No";
    
    return 0;
}
