
#include <cstdio>
using namespace std;
int d[31][31];
int f[31];
int s[31];
int t[31];

int dfs(int first,int second,int third){
    
    int sum = 0;
    
    for(int i=1;i<=30;i++) {
        
        sum += f[i] * d[i][first];
        sum += s[i] * d[i][second];
        sum += t[i] * d[i][third];
    }
    return sum;
}
int main(int argc, const char * argv[]) {
    
    int n,c,num;
    
    scanf("%d %d",&n,&c);
    
    for(int i=1;i<=c;i++){
        for(int j=1;j<=c;j++){
            scanf("%d",&d[i][j]);
        }
    }
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&num);
            int tmp = (i+j)%3;
            if(tmp==0) f[num]++;
            else if(tmp==1) s[num]++;
            else t[num]++;
        }
    }
    int ans = 987654321;
    for(int i=1;i<=c;i++){
        for(int j=1;j<=c;j++){
            if(i==j) continue;
            for(int k=1;k<=c;k++){
                if(i==k || j==k) continue;
                int tmp = dfs(i,j,k);
                if(ans > tmp) ans = tmp;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}

/*
 
 
 N*N격자판은 %3으로 나누기 때문에 0,1,2숫자만 가질 수 있다.
 
 0끼리 c(i,j)값이 같아야하고 나머지와는 달라야한다.
 나머지 또한 같다.
 
 C는 최대 30이므로, 30C3의 모든 경우의 수가 나오는데 6120으로 충분하다.
 
 0,1,2번 값을 결정한 후 
 
 D에서 값을 찾을때에는 d[현재값][결정한값] 형태로 구하면 된다.
 
 1~30가지 숫자중에 개수를 미리 알면 줄일 수 있다.
 
( (1~30)각 개수 * d배열 값) ) 을 각 0,1,2마다 해주면 된다.
 
 
 */
