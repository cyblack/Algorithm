
#include <iostream>
#include <algorithm>
using namespace std;
int main(int argc, const char * argv[]) {
   
    int A,B;
    cin >> A >> B;
    
    cout << max(A*B, max(A-B, A+B));
    
    
    return 0;
}

/*
최대값 찾기
*/