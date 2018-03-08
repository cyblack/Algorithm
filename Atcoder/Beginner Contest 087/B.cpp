
#include <cstdio>

int main(int argc, const char * argv[]) {
    
    int a,b,c,x;
    
    scanf("%d %d %d %d",&a,&b,&c,&x);
    
    int sum= 0;

    //(100,500,50)
    for(int i=1;i<=a;i++){
        int tmp = x;
        if(500 * i > tmp) break;
        tmp  = tmp - (500*i);
        for(int j=1;j<=b;j++){
            int tmp2 = tmp;
            if(100*j > tmp2 ) break;
            tmp2 = tmp2 - (100*j);
            for(int k=1;k<=c;k++){
                if(tmp2 == 50*k){
                    sum++;
                    break;
                }
            }
        }
    }
    
    //case1 (50,100)
    
    for(int i=1;i<=b;i++){
        int tmp = x;
        if(100*i > tmp) break;
        tmp = tmp - (100*i);
        for(int j=1;j<=c;j++){
            if(tmp == 50*j) {
                sum++;
                break;
            }
        }
    }
    //case2(50,500)
    for(int i=1;i<=a;i++){
        int tmp = x;
        if(500*i > tmp) break;
        tmp = tmp - (500*i);
        for(int j=1;j<=c;j++){
            if(tmp == 50*j){
                sum++;
                break;
            }
        }
    }
    //case3(100,500)
    for(int i=1;i<=a;i++){
        int tmp = x;
        if(500*i > tmp) break;
        tmp = tmp - (500*i);
        for(int j=1;j<=b;j++){
            if(tmp == 100*j) {
                sum++;
                break;
            }
        }
    }
    
    //(100||50||500)
    
    if(x%500==0 && x/500 <=a) sum++;
    if(x%100==0 && x/100 <=b) sum++;
    if(x%50 ==0 && x/50 <=c) sum++;
    
    printf("%d\n",sum);
    return 0;
}
