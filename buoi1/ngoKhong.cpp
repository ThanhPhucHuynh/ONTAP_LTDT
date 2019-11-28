#include <stdio.h>

#define MAX 100
#define max 100
#define white 0
#define black 1
#define gray 2
typedef int ElementType;
int mark[max];
int color[max];
int cycle;
typedef struct 
{
    int data[max];
    int size;
}Stack;

void make_null_stack(Stack *S){
    S->size = 0 ;
}

void push(Stack *S,int x){
    S->data[S->size]= x;
    S->size++;
}
int top(Stack *S){
    return S->data[S->size -1];
}
void pop(Stack *S){
    S->size--;
}
int empty(Stack *S){
    return S->size==0;
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




// graph
void init_graph(Graph *G,int n){
    int i,j;
    G->n = n;
    for ( i = 1; i <=n ; i++)
    {
        for (j  = 1; j <= n; j++)
        {
            G->a[i][j]=0;
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
    if(G->a[x][y] !=0 && G->a[y][x]!=0){
    		G->a[x][y] += 1 ;
  		 	G->a[y][x] += 1;
	}else{
		G->a[x][y] = 1;
    	G->a[y][x] = 1;
	}
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

void dfs(Graph *G,int x,int p){
	color[x]=gray;
	int j;
	list l= neighbors(G,x);
	for(j=1;j<=l.size;j++){
		int y=element_at(&l,j);
		
		
		
	//	printf("color[%d]: %d\n",y,color[y]);
		
		if(y==p){
			continue;	
		}else{
			if(color[y]==gray){
			cycle =1;//ton tai 1 chu trinh
			return;
		}
		if(color[y]==white){
			dfs(G,y,x);
		}
  }



}
color[x]=black;
}
//ktra toan dthi
int contains_cycle(Graph *G){
	int j;
	for(j=1;j<=G->n;j++){
		color[j]=white;
		
	}
	cycle =0;
	for(j=1;j<=G->n;j++){
		if(color[j]==white){
			dfs(G,j,0);
		}
		
	}
	return cycle;
}


int main(){
	
	freopen("dt.txt", "r", stdin); //Khi n?p bài nh? b? dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int j;
	for (j = 1; j <= n; j++)
		mark[j] = 0;
//	for (j = 1; j <= n; j++)
//		if (mark[j] == 0)
//        depth_first_search(&G,j);
//	printf("%d\n",contains_cycle(&G));
	(contains_cycle(&G)==1)?printf("YES"):printf("NO");
	
	return 0;
}
