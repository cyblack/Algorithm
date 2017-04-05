#include <cstdio>
using namespace std;

struct node {
    int value;
}heap[1001];

int hs;
void swap(struct node &A, struct node &B){
    struct node tmp =A;
    A=B;
    B=tmp;
}

void push(int x){
    
    heap[++hs].value = x; // 힙의 마지막에 노드를 생성
    
    for(int i=hs; i>1 ;i/=2){ //마지막에 생성됬으니 올라갈 준비를 해야함
        if(heap[i/2].value < heap[i].value){ // 부모 < 나 이면 swap
            swap(heap[i/2],heap[i]);
        }else{ // 부모 >= 나 이면 swap 안해도됨
            break;
        }
    }
}

struct node pop(){
    
    struct node ans = heap[1]; //가장 앞부분 값 미리 저장해두고
    heap[1] = heap[hs--]; // 가장 마지막 값을 맨위로 올린다.
    
    for(int i=1;i*2 <=hs;){//맨위에서 자기자리 찾기위해 내려가야함 / 마지막 위치에서는 자기자리 보다 한칸위에서 결정이 끝남 /스왑해버리면 리프노드가 되면서 끝
        if(heap[i].value > heap[i*2].value && heap[i].value > heap[i*2+1].value){ // 자식 2개가 모두 나보다 작을때는 종료
            break;
        }else if(heap[i*2].value > heap[i*2+1].value){ // 자식두개중에 한개는 무조건 나보다 큰값이 있고 둘중에 큰값을 찾아 스왑해야 힙구조가 유지됨
            swap(heap[i*2],heap[i]);
            i = i*2;
        }else{ //자식중에 오른쪽이 더크므로 변경
            swap(heap[i*2+1],heap[i]);
            i = i*2+1;
        }
    }
    return ans;
}