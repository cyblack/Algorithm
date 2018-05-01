
#include <cstdio>
int a[1001];
int main(int argc, const char * argv[]) {
   
    int n,m;
    
    scanf("%d %d",&n,&m);
    
    int mx = 10000;
    int sum = 0;
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        if(mx>a[i]) mx = a[i];
        sum+=a[i];
    }
    
    int left = m-sum;
    
    printf("%d\n",n+left/mx);
    
    return 0;
}
