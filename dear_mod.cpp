#include<iostream>
#include<limits.h>
#include<bits/stdc++.h>
#include<iomanip>

using namespace std;
#define V 6
#define INF INT_MAX
#define sleepTime 5
//number of vertices
 //network topology
int ie[6];//importer-->0 exporter-->1
int deg[6];//degree of the vertices
int packetFlag=1;

struct node
{
	int deg;
	int ie;
	int num;
};

node nodes[6];

int spt[6][6];

int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
void printPath(int parent[], int j,int graph[6][6])
{
    if (parent[j]==-1)
        return;
 
    printPath(parent, parent[j],graph);
 
    spt[j][parent[j]]=spt[parent[j]][j]=graph[j][parent[j]];
}
 
int printSolution(int dist[], int n, int parent[],int graph[6][6],int src1)
{
    int src = src1;					//////////////////////////////////change 3
    for (int i = 0; i < V; i++)
    {
        printPath(parent, i,graph);
    }
}
 
void dijkstra(int graph[6][6], int src1)	
{
    int dist[6];  
 
    bool sptSet[6];
 
    int parent[6];
     for (int i = 0; i < V; i++)
    {
        parent[src1] = -1;    				/////////////////////////////////////////change 1
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
 
    dist[src1] = 0;					////////////////////////////////////////change 2
 
    for (int count = 0; count < V-1; count++)
    {

        int u = minDistance(dist, sptSet);
 
        sptSet[u] = true;
 

        for (int v = 0; v < V; v++)

            if (!sptSet[v] && graph[u][v]!=INF &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }
 
    printSolution(dist, V, parent,graph,src1);		//////////////////////////////////////////change 4
}
 


void degree(int G[6][6])
{
	for(int i=0;i<V;++i)
	{	
		int count=0;
		for(int j=0;j<V;++j)
		{
			if(G[i][j]!=INF)
			count++;
		}
		nodes[i].deg=count;
	}
}

bool cmp(node a,node b)
{
	return a.deg>b.deg;
}

void transTime(int G[V][V],int spt[V][V],int src,int dest)
{
	int i=src;
	int timer=0;
	bool visited[V];
	for(int k=0;k<V;++k)
		visited[k]=false;
		
	visited[src]=true;
	while(i!=dest)
	{	
		int min = INF;
		int minind;
		
		for(int j=0;j<V;++j)
		{
			if(spt[i][j]!=0 && spt[i][j]!=INF)
			{
				if(spt[i][j]<min && !visited[j])
				{
					min=spt[i][j];
					minind=j;
				}
			}
			else
			if(spt[i][j]==0)
			{
				if(G[i][j]<min && !visited[j])
				{
					min=G[i][j];
					minind=j;
				}
			}
		}
		if(spt[i][minind]==0)
			timer+=sleepTime;
		else
			timer+=1;
		visited[minind]=true;
		if(min==INF)
		{
			timer=INF;
			packetFlag=0;
			break;
			}	
		i=minind;
	}
	cout<<"Time Taken for transmission: "<<timer<<endl;
}

void randCondition(int spt[V][V])
{
	int i,j;
	srand (time(NULL));	
	bool flag=false;
	while(!flag)
	{
		i=rand()%6;
		j=rand()%6;
		if(spt[i][j]!=INF && spt[i][j]!=0)
			flag=true;
	}
	spt[i][j]=spt[j][i]=(3*spt[i][j])/4;
	flag=false;
	while(!flag)
	{
		i=rand()%6;
		j=rand()%6;
		if(spt[i][j]!=INF && spt[i][j]!=0)
			flag=true;
	}
	spt[i][j]=spt[j][i]=(3*spt[i][j])/4;
	flag=false;
	while(!flag)
	{
		i=rand()%6;
		j=rand()%6;
		if(spt[i][j]!=INF && spt[i][j]!=0)
			flag=true;
	}
	spt[i][j]=spt[j][i]=INF;
	
}

int main()
{		



		int src,dest,srcpkts;



		
		for(int i=0;i<V;++i)
			{
			nodes[i].ie=0;
			nodes[i].num=i;
			nodes[i].deg=0;
		}
		
		for(int i=0;i<V;++i)
    		{
    			for(int j=0;j<V;++j)
    			spt[i][j]=INF;
		}
		
		
		
		//int G[6][6] = {{INF,40,20,10,50,INF},{40,INF,10,INF,5,INF},{20,10,INF,10,INF,INF},{10,INF,10,INF,INF,INF},{50,5,INF,INF,INF,10},{INF,INF,INF,INF,10,INF}}; old graph
		int G[6][6] = {{INF,15,20,INF,INF,INF},
						{15,INF,10,INF,25,INF},
						{20,10,INF,10,INF,INF},
						{INF,INF,10,INF,INF,INF},
						{INF,25,INF,INF,INF,10},
						{INF,INF,INF,INF,10,INF}};

		/*cout<<"\n\nEnter the traffic information:\n";

		for(int i=0;i<V;i++)
		for(int j=0;j<V;j++)
		cin>>G[i][j];*/

		cout<<"\nEnter the source(0-5):";cin>>src;
		cout<<"\nEnter the destination(0-5):";cin>>dest;

		cout<<"\nEnter the number of packets to be sent:";cin>>srcpkts;
		
		degree(G);//funtion to find degrees of vertices

		//to find the exporter node for a given source

		int er = 0;
		if( src == 0 ) er = 1;
		else if(src == 1) er = 1;
		else if(src == 2) er = 2;
		else if(src == 3) er = 2;
		else if(src == 4) er = 1;
		else if(src == 5) er = 1;


		sort(nodes,nodes+V,cmp);
		cout<<"Vertex"<<"      "<<"Degree\n";
		for(int i=0;i<V;++i)
		cout<<nodes[i].num<<"             "<<nodes[i].deg<<endl;
		nodes[er].ie=1;
		int x = nodes[er].num;
		for(int i=0;i<V;++i)
		{
			if(G[x][i]==INF && x!=i)
			{
				for(int j=0;j<V;++j)                //to be seen
				{
					if(j==i)
					{
						nodes[j].ie=1;
						break;
					}
				}
			}
				
		}
		//int src;
		for(int i=0;i<V;++i)
		{
			if(nodes[i].ie==1)
			{
			dijkstra(G,nodes[i].num);
			break;
		}
		}

		//dijkstra(G,src);
		
		for(int i=0;i<V;++i)
	 	{
	 		for(int j=0;j<V;++j)
	 		{
	 		if(G[i][j]!=INF && spt[i][j]==INF)
	 			spt[i][j]=0;
		 	}
	  	}
	  	
	  	cout<<"SPT:\n\n";
	  	cout<<"\n\n";


		for(int i=0;i<V;++i)
		{	
		for(int j=0;j<V;++j)
		{
			if(spt[i][j]!=INF)
			cout<<setw(5)<<spt[i][j]<<"  ";
			else
			cout<<setw(5)<<"INF"<<"  ";
		}
		cout<<endl;
	 	}
	 	
	 	cout<<"\n\n";
	  	
	  	randCondition(spt);


		float ratio;int sptc = 0,trfc = 0;

		for(int j = 0;j<V;j++)
		{
			if(spt[er][j] != 0 &&  spt[er][j] != INF)sptc++;
			if(G[er][j] != INF ) trfc++;
			
		}

		//cout<<endl<<endl<<sptc<<"  "<<trfc;

		ratio = (float)sptc/(float)trfc;

		
		


	//int timer = 0;


	
	  	//while(timer < 10){
	  cout<<"\n\n\nThe topology of the modified network :";//( after "<< timer<<" seconds):\n";	
		
		
		cout<<"\n\n";


		for(int i=0;i<V;++i)
		{	
		for(int j=0;j<V;++j)
		{
			if(spt[i][j]!=INF)
			cout<<setw(5)<<spt[i][j]<<"  ";
			else
			cout<<setw(5)<<"INF"<<"  ";
		}
		cout<<endl;
	 	}
	 	
	 	cout<<"\n\n";
	 	transTime(G,spt,src,dest);

		if(packetFlag==1)
		cout<<"\n\nThe number of packets received:"<<ceil(ratio*srcpkts)<<"\n\n"; 
		//sleep(3);timer+=3;
	 		//}		
	 	else
	 	cout<<"\n\nThe number of packets received:"<<0<<"\n\n"; 


		return 0;

}
