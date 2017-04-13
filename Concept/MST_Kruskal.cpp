#include <cstdio>
#include <algorithm>
using namespace std;
int p[10001];
struct Edge{
    int from, to ,cost;
    //오름차순1
    bool operator <(const Edge &A)const{
        return cost < A.cost;
    }
    
}edge[100001];

//오름차순2
bool comp(struct Edge &A, struct Edge &B){
    return A.cost < B.cost;
}

int Find(int x) {
    return x==p[x] ? x : p[x]=Find(p[x]);
}

void Union(int x, int y){
    p[Find(x)] = Find(y);
}

int main(int argc, const char * argv[]) {
    
    int n,m;
    
    scanf("%d %d",&n,&m);
    
    for(int i=1;i<=n;i++) p[i]=i;
    
    for(int i=0;i<m;i++) scanf("%d %d %d",&edge[i].from,&edge[i].to,&edge[i].cost);
    
    //sort(edge,edge+m); // 오름차순1
    sort(edge,edge+m,comp); //오름차순2
   
    
    int ans = 0;
    int cnt = 0;
    for(int i=0; ;i++){
        
        int u = Find(edge[i].from);
        int v = Find(edge[i].to);
        if(u!=v){
            ans+=edge[i].cost;
            p[u]=v;
            cnt++;
            // Union(u,v);
        }
        if(cnt==n-1) break;
    }
    
    printf("%d\n",ans);
    return 0;
}


/*

 union - find를 이용한 MST크루스칼 알고리즘
 
 1. Union-find (disjoint-set) - 집합을 의미함
 
 Union하는 경우에 그래프에서 노드를 이어붙이는 형태로 생성 
 하지만 최악의 경우에는 배열의 형태를 보이는데, 그러한 경우 Union-find 자료구조를 이용하는 의미가 없다.
 해결방안은 루트를 하나로 두고 나머지를 다 이어 붙이는 형태로 표현한다.(1을 루트로 하였을때, 2,3,4,5,6,7은 모두 부모를 1로 잡는 형태)
 
 2. 스패닝 트리 : 어떤 그래프에서 간선을 골라, 간선의 가중치의 합이 최소인 , 모든 그래프가 연결된 트리이다( 정점 : V , 간선 : V-1)
 
 가장 작은 간선부터 같은 집합으로 표현하면서 수행할 수 있다.
 

*/