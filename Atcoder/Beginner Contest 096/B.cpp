
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;


int main(int argc, const char * argv[]) {
    
    int k;
    vector<int> v(3);
    
    scanf("%d %d %d %d",&v[0],&v[1],&v[2],&k);
    
    sort(v.begin(),v.end());
    
    for(int i=0;i<k;i++) v[2] *=2;
    
    printf("%d\n",v[0]+v[1]+v[2]);
    
    return 0;
}

/*
 
 최대값만 찾으면된다.

 최대값에 포문대신에 2^(k-1)을 곱해줘도된다.
 
 sum is a+b+c + max(a,b,c)*(1<<(k-1))
*/