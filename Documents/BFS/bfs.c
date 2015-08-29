#include<stdio.h>
#include<unistd.h>
#define MAX 50
int trap = 0;			//trap variable
int cost_array[50],ca = 0;	//temp cost and its array
int route[50],r = 0;	//temp route and its variable
int tcost = 0,prevcost = 0;			//temporary cost
int conn[50][50],cost[50][50]; //connections and cost matrix
int n = 8;	//maximum num of nodes
int np = 0;	//num of paths
int d = 6,r;
int opt_path = 0;

struct paths{
	int d[MAX];
	int top;
	int cost;
}p[MAX];


void push(struct paths *p,int d,int pindex){
	if(p[pindex].top == MAX-1){
		printf("paths OverFlow");
	}else{
		p[pindex].top++;
		p[pindex].d[p[pindex].top] = d;
	}
}

int pop(struct paths *p[],int pindex){
	if(p[pindex]->top == -1){
		printf("UnderFlow");
	}else{
		return p[pindex]->d[p[pindex]->top--];
	}
}

void copy_path_to_struct(struct paths *p,int pindex,int tp[],int c){
	int i;
	for(i = 0 ; i < r ; i++){
		push(p,tp[i],pindex);
	}
	p[pindex].cost = c;
}

void printpath(struct paths *p,int pindex){
	int i;
	for(i = 1;i<=p[pindex].top;i++){	
		printf("%d ",p[pindex].d[i]);
	}
}

int find_lowest_cost(struct paths *p,int i,int j){
	int rmin,lmin;
	int m = (i+j)/2;
	if(i == j){
		return p[i].cost;
	}
	rmin = find_lowest_cost(p,i,m);
	lmin = find_lowest_cost(p,m+1,j);
	if(rmin < lmin){
		return rmin;
	}else{
		return lmin;
	}
}

int calculate_optimum_path(struct paths *p,int i,int j){
	int min_cost = find_lowest_cost(p,i,j);
	for(i = 0; i<j ;i++){
		if(p[i].cost == min_cost){
			return i;
		}
	}

}

void printcost(struct paths *p,int pindex){
	printf("\nCost is %d",p[pindex].cost);
}

void initialize(struct paths *p,int pindex){
	p[pindex].top = 0;
	p[pindex].cost = 0;
}

void bfs(int row,int start){

	
}

void dfs(int row,int start){
	int i = row,j;
	//printf("\nrow = %d : looping from %d to %d\n",row,start,n-1);
	for(j = start;j < n && trap != 1; j++ ){
		if(conn[i][j] == 1){
			route[r++] = j;
			//printf("\n%d %d",i,j);
			cost_array[ca++] = cost[i][j];
			//printf("tcost before : %d cost added :%d\n",tcost,cost_array[ca-1]);
			tcost = tcost + cost[i][j];
			//printf("tcost added : %d\n",tcost);
			if(j == d){
				initialize(p,np);
				copy_path_to_struct(p,np,route,tcost);
				prevcost = cost_array[ca-1]+cost_array[ca-2];
				tcost = tcost - prevcost;
				np++;
				//printf("return from %d\n",i);
				//printf("cost deduct : %d tcost now :%d\n",prevcost,tcost);
				r = r-2;
				ca = ca - 2;
				return;
			}else{
				//printf("\n>>>call %d from %d\n",j,i);
				dfs(j,0);
				//printf("now on row : %d\n",i);
				if(i == 1){
					tcost = 0;
					r = 1;
					ca = 0;
				}
				if(j == n-1){
					//printf("return from %d\n",i);
					return;
				}
			}		
		}else if(conn[i][j] == 0){
			if(j == n-1){
				//printf("%dcont\n",j);
				int fl = p[np-2].top;
				//printf("return from %d\n",i);
				prevcost = cost_array[ca-1];
				tcost = tcost - prevcost;
				//printf("cost deduct : %d tcost now :%d\n",cost[i][j]+prevcost,tcost);
				r = r-1;
				ca = ca-1;
				return;
			}else{
				//printf("%dcont\n",j);
				continue;
			}
		}
	}
}



void main(){
	int i,j;
	/*
	initialize(p,0);	
	push(p,10,0);
	push(p,20,0);
	p[0].cost = 15;*/	
	
	/*printpath(p,0);
	printcost(p,0);
	*/
	for(i = 1;i < n; i++ ){
		for(j = 1;j < n; j++ ){
			if(i == 1 && j == 2){
				conn[i][j] = 1;		
				cost[i][j] = 9;
			}else if(i == 1 && j == 3){
				conn[i][j] = 1;
				cost[i][j] = 5;	
			}else if(i == 2 && j == 4){
				conn[i][j] = 1;
				cost[i][j] = 2;	
			}else if(i == 2 && j == 5){
				conn[i][j] = 1;
				cost[i][j] = 1;	
			}else if(i == 2 && j == 7){
				conn[i][j] = 1;
				cost[i][j] = 3;	
			}else if(i == 3 && j == 5){
				conn[i][j] = 1;	
				cost[i][j] = 6;
			}else if(i == 4 && j == 5){
				conn[i][j] = 1;	
				cost[i][j] = 1;
			}else if(i == 5 && j == 6){
				conn[i][j] = 1;	
				cost[i][j] = 2;
			}else{
				conn[i][j] = 0;
				cost[i][j] = 0;
			}
		}	
	}
	for(i = 1;i < n; i++ ){
		for(j = 1;j < n; j++ ){
			printf("%d  ",conn[i][j]);
		}	
		printf("\n");
	}
	printf("\n");
	/*for(i = 1;i < n; i++ ){
		for(j = 1;j < n; j++ ){
			printf("%d  ",cost[i][j]);
		}	
		printf("\n");
	}*/
	route[0] = 1;
	r++;
	dfs(1,1);
	//printf("%d",np);
	printf("Number of paths found : %d\n",np);
	
	for(i = 0;i < np; i++){
		printf("\nPath %d \n",i+1);
		printpath(p,i);
		printf("\nCost of Path %d",i+1);
		printcost(p,i);
		printf("\n");
	}

	opt_path = calculate_optimum_path(p,0,np-1);
	printf("\nOptimum Path is : ");
	printpath(p,opt_path);
	printf("\nCost of Optimum Path : %d\n",p[opt_path].cost);
	printf("\n");
}
