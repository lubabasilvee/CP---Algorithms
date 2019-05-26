#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)

typedef long long ll;

/*
    Lembrar de 4*N no tamanho da seg
    
    Lembrar de dar build
    
    Nós da seg [1,4*N-1], e nós do vetor [0,n-1]
    
    intervalos abertos [l,r)
*/

const int N = 1e5+10;

ll s[4*N];
ll v[N];
int n, q;

void build(int no = 1, int l = 0, int r = n){
    if(r-l==1){ 
        s[no] = v[l];
        return;
    }
    int mid = (l+r)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    s[no] = min(s[2*no],s[2*no+1]);
}

//mudar o valor, v[i] = x (nao aumentar em x)
void modify(int i, ll x, int no = 1, int l = 0, int r = n){
    if(r-l==1){
        s[no] = v[l] = x;
        return;
    }
    int mid = (l+r)/2;
    if(i<mid) modify(i,x,2*no,l,mid);
    else modify(i,x,2*no+1,mid,r);  
    s[no] = min(s[2*no],s[2*no+1]);
}

ll query(int lq, int rq, int no = 1, int l = 0, int r = n){
    if(rq<=l or r<=lq) return INT_MAX; //totalmente fora
    if(lq<=l and r<=rq) return s[no]; //range q estou totalmente dentro do range da query
    int mid = (l+r)/2;
    return min(query(lq,rq,2*no,l,mid),query(lq,rq,2*no+1,mid,r));
}

//resolve problema em: https://www.hackerearth.com/pt-br/practice/data-structures/advanced-data-structures/segment-trees/tutorial/

int main(){

    cin >> n >> q;
    
    fr(i,n) scanf("%lld", v+i);
    
    build();
    
    fr(qq,q){
        char c;
        scanf(" %c", &c);
        if(c=='q'){
            int l, r;
            scanf("%d%d", &l, &r);
            l--;
            printf("%lld\n", query(l,r));
        } else{
            int p, x;
            scanf("%d%d", &p, &x);
            p--;
            modify(p,x);
        }
    }
	
	return 0;
}

/*
input:
7 11
1 2 3 4 5 6 7
q 1 7
q 1 6
q 2 6
u 1 7
u 2 3
q 1 6
u 4 -10
q 3 5
u 7 -100
q 4 4
q 2 7

answer:
1
1
2
3
-10
-10
-100
*/
