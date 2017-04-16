#include <iostream>
#include <cstdio>

struct node{
    
    int value;
    node * L;
    node * R;
    node(){}
    node(int v){
        value=v;
        L=NULL;
        R=NULL;
    }
};

void print(struct node * root){
    
    if(root->L!=NULL) print(root->L);
    if(root->R!=NULL) print(root->R);
    printf("%d\n",root->value);
}

int main(int argc, const char * argv[]) {

    int tmp;
    scanf("%d",&tmp);
    struct node root;
    root.value=tmp;
    root.L=NULL;
    root.R=NULL;
    
    while(scanf("%d",&tmp)!=EOF){
        struct node * now = &root;
        
        while(true){
            
            if(now->value > tmp){
                if(now->L == NULL){
                    now->L = new node(tmp);
                    break;
                }
                now = now->L;
            }else{
                if(now->R == NULL){
                    now->R = new node(tmp);
                    break;
                }
                now = now->R;
            }
        }
    }
    print(&root);
    return 0;
}

/*
 
 
 전위 순위로 된 결과가 인풋으로 들어오는데
 들어오는 순서대로 이진검색트리를 만들면 된다.
 
 그 이후에 후위순회한 결과를 출력하면된다.

*/