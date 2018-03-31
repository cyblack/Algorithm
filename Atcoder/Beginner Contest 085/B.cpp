#include <cstdio>
bool  d[101];
int main(int argc, const char * argv[]) {
   
    int n,ans = 0;
    
    scanf("%d",&n);
    for(int i=0,t;i<n;i++){
        scanf("%d",&t);
        if(!d[t]){
            d[t]=true;
            ans++;
        }
    }
    
    printf("%d\n",ans);
    return 0;
}
