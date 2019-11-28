#include <stdio.h>

#define MAX 100
#define INFINITY 9999999
#define NO_EDGE 0

typedef int ElementType;

int d[MAX];


int mark[MAX];
int pi[MAX];
int p[MAX];
typedef struct
{
    int data[MAX];
    int front, rear;    
}Queue;
void make_null_queue(Queue *Q){
    Q->front=0;
    Q->rear = -1;
}
void push(Queue *Q,int x){
    Q->rear++;
    Q->data[Q->rear]=x;
}
int top(Queue *Q){
    return Q->data[Q->front];
}
void pop(Queue *Q){
    Q->front++;
}
int empty(Queue *Q){
    return Q->front > Q->rear;
}

typedef struct
{
    ElementType data[MAX];
    int size;
}list;

typedef struct 
{
    int n;
    int a[MAX][MAX];
}Graph;

void make_null(list *L){
    L->size = 0;
}
void push_back(list *L,ElementType X){
    L->data[L->size] =X;
    L->size++;
}
ElementType element_at(list *L,int i){
    return L->data[i-1];
}
int count_list(list *L){
    return L->size;
}

void print_list1(list *L){
	int i;
    for (i = 0; i < L->size; i++)
    {
        printf("%d  ",element_at(L,i+1));
    }
    
}


// graph
void init_graph(Graph *G,int n){
    int i,j;
    G->n = n;
    for ( i = 1; i <=n ; i++)
    {
        for (j  = 1; j <= n; j++)
        {
            G->a[i][j]=NO_EDGE;
        } 
    }
}
void print_graph(Graph *G,int n){
	int i=0,j=0;
	for ( i = 1; i <= n; i++){
		for (j = 1; j <=n; j++)
		{
			printf("%d  ",G->a[i][j]);
		}
		printf("\n");
	}	
}
void add_edge(Graph *G,int x,int y){
		G->a[x][y]++;
}
int adjacent(Graph *G,int x,int y){
    return G->a[x][y] !=0;
}
int degree(Graph *G,int x){
    int y,deg=0;
    for (y = 1; y <= G->n; y++)
    {
        if (G->a[x][y]>0)
        {
            deg++;
        }
        
    }
    return deg;
}
int degrees(Graph *G,int x){
    int y,deg=0;
    for (y = 1; y <= G->n; y++)
    {
        deg += G->a[x][y];
        
    }
    return deg;
}

list neighbors(Graph *G,int x){
    int y,j;
    list l;
    make_null(&l);
    for (y = 1; y <= G->n; y++)
    {
        if(adjacent(G,x,y)){
            push_back(&l,y);
        }
    }
    return l;
}

list ranking(Graph *G){
	Queue Q;
	make_null_queue(&Q);
	int d[MAX];
	int x,u;
	for(u=1;u<=G->n;u++){
		d[u]=0;
	}
	for(x=1;x<=G->n;x++){
		for(u=1;u<=G->n;u++){
			if(G->a[x][u]!=0){
				d[u]+=1;
			}
		}
	}
	list S1;
	make_null(&S1);
	for(u=1;u<=G->n;u++){
		if(d[u]==0){
			push(&Q,u);
		}
	}
	int k=1,i;
	while(!empty(&Q)){
		int u = top(&Q);pop(&Q);
		push_back(&S1,u);
		list l = neighbors(G,u);	
		for(i=1;i<=l.size;i++){
			int a =	element_at(&l,i);
					d[a]--;
					if(d[a]==0){
						push(&Q,a);
					}
				}
			}
//	print_list1(&S1);
	return S1;
	
}
int max(int a,int b){
	if (a>b) return a;
	else return b;
}
int min(int a,int b){
	if (a<b) return a;
	else return b;
}
int main(){
	freopen("dt.txt", "r", stdin);
	Graph G;
	int n,u,x,v,j;
	//1. doc do thi
	//FILE* file =
	//freopen("DuAnXayNha.txt","r",stdin);
	scanf("%d",&n);
	init_graph(&G,n+2);
	
	d[n+1]=0;
	
	for(u=1;u<=n;u++){
		scanf("%d",&d[u]);
		do{
			scanf("%d",&v);
			if(v>0){
				add_edge(&G,v,u);
			}
		}while(v>0);
	}
	int CV,date;
	scanf("%d%d",&CV,&date);
	
	
	//2 them cung noi anpha va bat vao =0
	for(u=1;u<=n;u++){
		int deg_neg=0;
		for(x=1;x<=n;x++){
			if(G.a[x][u]>0){
				deg_neg++;
			}
			if(deg_neg==0){
				add_edge(&G,n+1,u);
			}
		}
	}
		//3 them cung noi beta va bat ra =0
	for(u=1;u<=n;u++){
		int deg_pos=0;
		for(v=1;v<=n;v++){
			if(G.a[u][v]>0){
				deg_pos++;
			}
			if(deg_pos==0){
				add_edge(&G,u,n+2);
			}
		}
	}
	//xeptobo
	list L = ranking(&G);
	//5 t[u
	int t[MAX];
	t[n+1]=0;
	for(j=2;j<=L.size;j++){
		int u = element_at(&L,j);
		t[u]=-99999;
		for(x=1;x<=G.n;x++){
			if(G.a[x][u]>0){
				t[u]=max(t[u],t[x]+d[x]);
			}
		}
	}	
	//T[u
	int T[MAX];
	T[n+2]=t[n+2];
	for(j=L.size-1;j>=1;j--){
		int u = element_at(&L,j);
		T[u]=99999;
		for(v=1;v<=G.n;v++){
			if(G.a[u][v]>0){
				T[u]=min(T[u],T[v]-d[u]);
			}
		}
	}		
	
	
	(date<T[CV])?printf("YES"):printf("NO");
	
	return 0;
}
