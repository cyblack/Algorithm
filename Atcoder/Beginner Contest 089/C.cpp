
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int box[5]={0,};

int main(int argc, const char * argv[]) {
 
    int n;
    
    scanf("%d",&n);
    
    string h;
    
    for(int i=0;i<n;i++){
        cin >> h;
        if(h[0]=='M') box[0]++;
        else if(h[0]=='A') box[1]++;
        else if(h[0]=='R') box[2]++;
        else if(h[0]=='C') box[3]++;
        else if(h[0]=='H') box[4]++;
    }

    long long sum = 0;
    
    
    for(int i=0;i<5;i++){
        for(int j=i+1;j<5;j++){
            for(int k=j+1;k<5;k++){
                sum += (long long)box[i] * box[j] * box[k];
            }
        }
    }
  
    printf("%lld\n",sum);
    return 0;
}

/*
 M A R C H 
 순서를 유지 한 채 
 
 가능한 경우의 수 고르기.
 
 */
