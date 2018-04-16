#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, const char * argv[]) {
   
    
    int a,b;
    string c;
    bool ok = true;
    
    cin >> a >> b;
    cin >> c;
    
    
    for(int i=0;i<a;i++){
        if(!('0' <= c[i] && c[i] <='9')) ok = false;
    }
    if(c[a]!='-') ok = false;
    for(int i=a+1;i<a+b+1;i++){
        if(!('0' <= c[i] && c[i] <='9')) ok = false;
    }
    
    if(ok) printf("Yes\n");
    else printf("No\n");
    return 0;
}

/*
 
 특정 위치값이 0~9인지 확인하는법

*/