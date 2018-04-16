

#include <cstdio>
struct node{
    int c,s,f;
};
int main(int argc, const char * argv[]) {
    
    
    int n;
    struct node train[501];
    scanf("%d",&n);
    
    for(int i=0;i<n-1;i++){
        scanf("%d %d %d",&train[i].c,&train[i].s,&train[i].f);
    }
    
    for(int i=0;i<n-1;i++){
        int arrive = train[i].s + train[i].c;
        for(int j=i+1;j<n-1;j++){
            if(arrive <= train[j].s) arrive = train[j].s +train[j].c;
            else if( ( (arrive-train[j].s) % train[j].f) == 0) arrive += train[j].c;
            else arrive = (arrive/train[j].f + 1) * train[j].f + train[j].c;
        }
        printf("%d\n",arrive);
    }
    printf("0\n");
    return 0;
}


/*
 
 
 기차는 Ceremony(S)이후에 매 F초 마다 출발한다. 다음역까지의 시간은 C초가 걸린다.
 
 특정 역에 도착한 시간을 X라 하면
 
 X가 그 역의 Ceremony보다 작거나 같은 경우는 Ceremony(S)시간에 출발하면된다.
 
 하지만 X가 Ceremony시간보다 큰 경우는 2가지로 나뉘어진다.
 
 도착시간을 변경을 해야하는 경우 :
 
 53초에 도착했고 S : 40, F: 4라면  56초에 출발해야한다 
 
 일반화 : X = (X/f +1) * F + S
 
 도착시간을 변경 안해도 되는 경우 :
 
 56초에 도착했고 S : 40, F:4라면 56초에 그대로 출발하면된다
 
 X-S시간이 F로 나누어떨어진다면 그 시간에 그대로 출발하면된다.

*/
