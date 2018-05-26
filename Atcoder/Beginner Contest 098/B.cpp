
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
bool check[31];
int main(int argc, const char * argv[]) {
    
    
    int n;
    string h;
    
    scanf("%d",&n);
    cin >> h;
    int ans = 0;
    for(int i=0;i<n;i++){
        
        //왼쪽끝 i 번째까지
        int tmp = 0;
        for(int j=0;j<=i;j++){
            check[h[j]-'a']=true;
        }
        for(int j=i+1;j<n;j++){
            if(check[h[j]-'a']){
                check[h[j]-'a'] = false;
                tmp++;
            }
        }
        
        
        if(ans < tmp ) ans = tmp;
        for(int i=0;i<31;i++){
            check[i]=false;
        }
        
        
        
    }
    
    printf("%d\n",ans);
    return 0;
}

/*
 
 직접구현하기
 왼쪽 오른쪽에서 공통된 부분찾기
*/