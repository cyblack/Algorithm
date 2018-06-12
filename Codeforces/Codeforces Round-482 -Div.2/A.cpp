
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char a[101];

int main(int argc, const char * argv[]) {
   
    scanf("%s",a);
    int sz = (int)strlen(a);
    
    for(int i=1;i<sz-1;i++){
        
        if(a[i]=='A') {
            if(  (a[i-1] =='B' && a[i+1] =='C') || (a[i-1] =='C' && a[i+1]=='B')  ){
                printf("Yes\n");
                return 0;
            }
        }else if(a[i]=='B'){
            if(  (a[i-1] =='A' && a[i+1] =='C') || (a[i-1] =='C' && a[i+1]=='A')  ){
                printf("Yes\n");
                return 0;
            }
        }else if(a[i]=='C'){
            if(  (a[i-1] =='B' && a[i+1] =='A') || (a[i-1] =='A' && a[i+1]=='B')  ){
                printf("Yes\n");
                return 0;
            }
        }
    }
    
    printf("No\n");
    
    return 0;
}

/*
 
 A,B,C가 양쪽으로 퍼질 때, 특정 순간에 ABC가 모두 모여있는 경우를 찾기
 
 결국 ABC/ACB/BAC/BCA/CAB/CBA 가 문자열에 있는 지 확인하기.
 
 */
