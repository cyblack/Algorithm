

#include <cstdio>

int main(int argc, const char * argv[]) {
   
    int a,b;
    
    scanf("%d %d",&a,&b);
    
    int ans = 0;
    for(int i=a;i<=b;i++){
        
        int val[5];
        int cnt = 0;
        int tmp= i;
        while(tmp){
            
            val[cnt++] = tmp%10;
            tmp/=10;
            
        }
        if(val[0] == val[4] && val[1] == val[3]) ans++;
        
    }
    printf("%d\n",ans);
    return 0;
}
