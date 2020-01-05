#include <stdio.h>

#define maxn 100
#define no_eage 0
#define INF 9999999
//Queue

typedef struct 
{
	int data[100];
	int front, rear;

}Queue;

void make_null_queue(Queue *Q){
	Q->front= 0;
	Q->rear = -1;
}
void push_queue(Queue *Q,int x){
	Q->rear++;
	Q->data[Q->rear]= x;
}
int top_queue(Queue *Q){
	return Q->data[Q->front];

}
void pop_queue(Queue *Q){
	Q->front++;
}
int empty_queue(Queue *Q){
	return Q->front > Q->rear;
}


typedef struct 
{
	int C[maxn][maxn];
	int F[maxn][maxn];
	int n;
}Graph;

void init_Graph(Graph *G,int n){
	int i,j=0;
	G->n=n;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			G->C[i][j]=0;
			G->F[i][j]=0;
		}
	}
}

typedef struct 
{
	int dir;
	int pre;
	int sigma;
}Lable;

Lable lables[maxn];

int min(int a,int b){
	if(a<b) return a;
	else return b;
}


void init_flow(Graph *G){
 	int i,j;
 	for(i=1;i<=G->n;i++){
 		for(j=1;j<=G->n;j++){
 			G->F[i][j]= 0;
 		}
 	}
 }
int FordFullkerson(Graph *G,int s ,int t){
	// khoi tao luon
	int sum_flow=0;
	int v;
	init_flow(G);
	Queue Q;
	//xoa nhan cac dinh
	int u=0;
	do{
		for(u=1;u<=G->n;u++){
			lables[u].dir =0;
		}
		lables[s].dir = +1;
		lables[s].pre =s;
		lables[s].sigma = INF;
		//
		make_null_queue(&Q);
		push_queue(&Q,s);
		//..
		int found =0;
		while(!empty_queue(&Q)){
			int x=top_queue(&Q);pop_queue(&Q);
			//printf("x=%d\n", x);
			for(v=1;v<=G->n;v++){
				//printf("F %d C %d\n",G->F[u][v],G->C[u][v]);
				if(lables[v].dir==0&&G->C[x][v]!=no_eage&&G->F[x][v] < G->C[x][v]){
					lables[v].dir = +1;
					lables[v].pre=x;
					lables[v].sigma = min(lables[x].sigma,G->C[x][v] - G->F[x][v]);
					push_queue(&Q,v);
				}
				if(lables[v].dir==0 && G->C[v][x]!=no_eage&& G->F[v][x]>0){
					lables[v].dir = -1;
					lables[v].pre=x;
					lables[v].sigma = min(lables[x].sigma,G->F[x][v]);
					push_queue(&Q,v);
				}
			}
			//printf("%d\n",lables[t].dir);
			if(lables[t].dir!=0){
				found =1;
				break;
			}
		}
		if(found==1){
			int x=t;
			int sigma = lables[t].sigma;
			sum_flow+= sigma;
			while(x!=s){
				int u=lables[x].pre;
				if(lables[x].dir>0){
					G->F[u][x]+=sigma;
				}else{
					G->F[u][x]-=sigma;
				}
				x=u;
			}
		}else break;




	}while(1);
	//lap gan nhan

	//thang luon

//thoat vong lap
	return sum_flow;
}

int main(){

	Graph G;
	int n,m,u,v,e,c;
	freopen("dt1.txt","r",stdin);
	scanf("%d%d",&n,&m);
	//printf("n= %d, m = %d\n",n,m );
	init_Graph(&G,n);
	for(e=0;e<m;e++){
		scanf("%d%d%d",&u,&v,&c);
		G.C[u][v]=c;
		//printf("%d \n",G.C[u][v]);
	}
	int max_flow= FordFullkerson(&G,1,n);
	printf("max_flow: %d \n",max_flow );
	printf("X0:");
	for(u=1;u<=n;u++){
		if(lables[u].dir!=0) printf(" %d",u);
	}
	printf("\nY0:");
	for(u=1;u<=n;u++){
		if(lables[u].dir==0) printf(" %d",u);
	}


	return 0;
}
