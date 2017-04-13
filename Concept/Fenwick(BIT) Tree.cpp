#include <cstdio>
#include <vector>
using namespace std;

long long sum(vector<long long> &tree, int i){
    
    long long ans = 0;
    while(i>0){
        ans += tree[i];
        i -= (i&-i);
    }
    return ans;
}

void update(vector<long long> &tree, int i, long long diff){
    while(i<tree.size()){
        tree[i] += diff;
        i += (i&-i);
    }
}

/*
 
 Fenwick Tree == Binary Indexed Tree(BIT)
 
 어떤 수를 이진수로 표현가능해야함
 
 e.g. 12 = 1100(2) ,  3 = 11(2)
 
 ***** 마지막 1이 나타내는 값을 L[i] (2의 제곱형태) *****
 
 L[12] = 4
 L[3] = 1

 
 Tree[i] = A[i] 부터 앞으로 L[i]개의 합이 저장되어있다.
 
 e.g. Tree[12] = a[12] 부터 앞으로 L[12](4)개
 즉, a[12] + a[11] + a[10] + a[9]
 
 L[i] = i & -i로 표현가능하다
 
 e.g. 
    -num = ~num +1
    num = 10011010111010
   ~num = 01100101000101
   -num = 01100101000110
 num&-num = 00000000000010
 
 
 1. sum
    A[1]+...+A[12]는 어떻게 구할까?
    12 = 1100(2)
    
    A[1]+...+A[12] = Tree[1100] + Tree[1000]
 
    L[i]는 개수인데 idx에서 빼는 것과 이진수에서 1의 가장 마지막수를 없애는 것과 동치이다.
 
    i~j 구간의 합은 S[j] - S[i-1]로 표현, BIT도 똑같다.
 
 
 2. update
 
    어떤 수를 변경한 경우에는 그 수를 담당하는 구간을 모두 업데이트 해야함
    
    e.g. 6번째값을 변경한 경우(6 == 110(2))
 
    tree 사이즈 까지 해당하는 부분에 대해 모두 업데이트
    idx += (idx & -idx)
 
*/