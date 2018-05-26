
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int wsum[300001];
int esum[300001];

int main(int argc, const char * argv[]) {
 
    int n;
    string h;
    
    cin >> n;
    cin >> h;
    
    
    int sz = (int)h.size();
    for(int i=1;i<=sz;i++){
        if(h[i-1]=='W'){
            wsum[i] = wsum[i-1]+1;
            esum[i] = esum[i-1];
        }else{
            wsum[i] = wsum[i-1];
            esum[i] = esum[i-1]+1;
        }
       // printf("#%d %d %d\n",i,wsum[i],esum[i]);
    }
    int ans = 987654321;
    
    
    
    for(int i=1;i<=sz;i++){
        
        //현재 0번째를 고른다.
        if(ans > wsum[i-1] + esum[sz]-esum[i]){
            ans = wsum[i-1] + esum[sz]-esum[i];
        }
    }
    
    printf("%d\n",ans);
    
    return 0;
}



/*
 
 어떤 기준점을 대상으로 왼쪽 W개수와 오른쪽 e개수를 찾으면된다. 
 
 미리 누적합으로 계산해놓으면 편하다.

*/