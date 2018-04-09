#include<iostream>
#include<bits/stdc++.h>
#include<limits.h>
#define V 6
#define INF INT_MAX
using namespace std;

vector<vector<int> > paths;
vector<int> plength;
int timer =0;
int c=0;

struct node
{
	int num;
	int deg;
	int priority;
};

struct link
{
	int n1;
	int n2;
	int wt;
	int priority;
	int t1,t2;
};

node nodes[V];
vector<link> links; 

void degree(int G[V][V])
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
	return a.deg<b.deg;
}

bool cmp1(link a,link b)
{
	return a.wt>b.wt;
}


// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void printAllPathsUtil(int G[V][V],int u, int d, bool visited[],
                              int path[], int &path_index)
{
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;
 	
    // If current vertex is same as destination, then print
    // current path[]
    if (u == d)
    {	
    	
    	vector<int> p;
        for (int i = 0; i<path_index; i++)
        {
        	p.push_back(path[i]);
		}
		paths.push_back(p);
           // cout << path[i] << " ";
        //cout << endl;
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        int i;
        for (i = 0;i<V; ++i)
            if (!visited[i] && G[u][i]!=INF)
                printAllPathsUtil(G,i, d, visited, path, path_index);
    }
 
    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
}

void printAllPaths(int G[V][V],int s, int d)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
 
    // Create an array to store paths
    int *path = new int[V];
    int path_index = 0; // Initialize path[] as empty
 
    // Initialize all vertices as not visited
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Call the recursive helper function to print all paths
    printAllPathsUtil(G,s, d, visited, path, path_index);
}
 
void pathLength(int G[V][V],int prior[V][V],int src,int dest)
{

	paths.clear();
	plength.clear();
	printAllPaths(G,src,dest);
	int psize = paths.size();
		/*for(int i=0;i<paths.size();++i)
			{
				for(int j=0;j<paths[i].size();++j)
					cout<<paths[i][j]<<"  ";
				cout<<endl;
			}*/
			
			
			for(int i=0;i<paths.size();++i)
			{
				int temp=0;
				for(int j=0;j<paths[i].size()-1;++j)
					{
					
					temp+=prior[paths[i][j]][paths[i][j+1]];
					}
				plength.push_back(temp);
				//cout<<plength[i]<<endl;
			}		
}

int pathSelection(int G[V][V],int prior[V][V],int src,int dest,bool visited[])
{
	int n=plength.size();
	int max1[2],max2[2],max3[2];
	int m = INT_MIN;
	for(int i=0;i<n;i++)
	{
		if( plength[i] > m)
		{
		max1[0] = plength[i];
		max1[1] = i;
		m=plength[i];
		}
	}
	
	m=INT_MIN;
	
	for(int i=0;i<n;i++)
	{
		if( plength[i] > m && plength[i] != max1[0])
		{
		max2[0] = plength[i];
		max2[1] = i;
		m=plength[i];
		}
	}
	
	m=INT_MIN;
	for(int i=0;i<n;i++)
	{
		if( plength[i] > m && plength[i] != max1[0] && plength[i] != max2[0])
		{
		max3[0] = plength[i];
		max3[1] = i;
		m=plength[i];
		}
	}
	
	int u1=paths[max1[1]][0];
	int v1=paths[max1[1]][1];
	int u2=paths[max2[1]][0];
	int v2=paths[max2[1]][1];
	int u3=paths[max3[1]][0];
	int v3=paths[max3[1]][1];
	int tm1[2],tm2[2],tm3[2];
	for(int i=0;i<links.size();++i)
	{
		if((links[i].n1==u1 && links[i].n2==v1)||(links[i].n1==v1 && links[i].n2==u1) )
		{
			tm1[0]=links[i].t1;
			tm1[1]=links[i].t2;
			break;
		}
	}
	
	for(int i=0;i<links.size();++i)
	{
		if((links[i].n1==u2 && links[i].n2==v2)||(links[i].n1==v2 && links[i].n2==u2) )
		{
			tm2[0]=links[i].t1;
			tm2[1]=links[i].t2;
			break;
		}
	}
	
		for(int i=0;i<links.size();++i)
	{
		if((links[i].n1==u3 && links[i].n2==v3)||(links[i].n1==v3 && links[i].n2==u3) )
		{
			tm3[0]=links[i].t1;
			tm3[1]=links[i].t2;
			break;
		}
	}
	
	if((timer%42<tm1[0] || timer%42>tm1[1])&&!visited[v1])
		return v1; 
	else
	if((timer%42<tm2[0] || timer%42>tm2[1])&&!visited[v2])
		return v2;
	else 
	if((timer%42<tm3[0] || timer%42>tm3[1])&&!visited[v3])
		return v3; 
		
}

void printNode(int G[V][V],int prior[V][V],int src, int dest)
{
	
	int s=src;
	bool visited[V];
	for(int i=0;i<V;++i)
		visited[i]=false;
	while(s!=dest)
	{	
		visited[s]=true;
		bool flag=false;
		for(int k=0;k<V;++k)
		{
			if(G[s][k]!=INF)
				flag=true;
				
		}
		if(!flag)
		{
			cout<<"Last Node: "<<s<<endl;
			cout<<"Packets Lost\n";
			return;
		}
		pathLength(G,prior,s,dest);
		cout<<s<<"  ";
		
		s=pathSelection(G,prior,s,dest,visited);
		
		timer=timer +5;	
	}
	cout<<s<<endl;
	cout<<"Time taken: "<<timer<<endl;
}

void randCondition(int G[V][V])
{
	int i,j;
	srand (time(NULL));	
	bool flag=false;
	while(!flag)
	{
		i=rand()%6;
		j=rand()%6;
		if(G[i][j]!=INF && G[i][j]!=0)
			flag=true;
	}
	G[i][j]=G[j][i]=(3*G[i][j])/4;
	flag=false;
	while(!flag)
	{
		i=rand()%6;
		j=rand()%6;
		if(G[i][j]!=INF && G[i][j]!=0)
			flag=true;
	}
	G[i][j]=G[j][i]=(3*G[i][j])/4;
	flag=false;
	while(!flag)
	{
		i=rand()%6;
		j=rand()%6;
		if(G[i][j]!=INF && G[i][j]!=0)
			flag=true;
	}
	G[i][j]=G[j][i]=INF;
	
}


int main()
{
	int src,dest,srcpkts,t=0;
	cout<<"\nEnter the source(0-5):";cin>>src;
	cout<<"\nEnter the destination(0-5):";cin>>dest;
	cout<<"\nEnter the number of packets to be sent:";cin>>srcpkts;
	for(int i=0;i<V;++i)
			{
			nodes[i].num=i;
			nodes[i].deg=0;
			nodes[i].priority=0;
		}
	
		int G[V][V] = {{INF,15,20,INF,10,INF},
						{15,INF,10,INF,25,INF},
						{20,10,INF,10,INF,INF},
						{INF,INF,10,INF,INF,INF},
						{10,25,INF,INF,INF,10},
						{INF,INF,INF,INF,10,INF}};
						
		int prior[V][V]= {{INF,INF,INF,INF,INF,INF},
						{INF,INF,INF,INF,INF,INF},
						{INF,INF,INF,INF,INF,INF},
						{INF,INF,INF,INF,INF,INF},
						{INF,INF,INF,INF,INF,INF},
						{INF,INF,INF,INF,INF,INF}};
						
			printAllPaths(G,src,dest);
			int psize = paths.size();
			vector<int> plength(psize);
						
			cout<<"\n\n";
			randCondition(G);
			
			cout<<"\n\nThe modified graph:\n\n";
			for(int i=0;i<V;i++)
			{
				for(int j=0;j<V;j++)
				{	if(G[i][j]!=INF)
					cout<<G[i][j]<<" ";
					else
					cout<<"INF"<<" ";}
				
				cout<<"\n";
			}
			
			degree(G);//funtion to find degrees of vertices
			sort(nodes,nodes+V,cmp);
			
			for(int i=0;i<V;++i)
			{
				nodes[i].priority=i+1;
			}
			cout<<"Node:\n";
			for(int i=0;i<V;++i)
			{
				cout<<"Node-"<<nodes[i].num<<"    "<<nodes[i].priority<<endl;
			}
		for(int i=0;i<V;++i)
		{
			for(int j=0;j<i;++j)
			{
				if(G[i][j]!=INF)
				{
					link l;
					l.n1=i;
					l.n2=j;
					l.wt=G[i][j];
					links.push_back(l);
				}
			}
		}
		
	
		sort(links.begin(),links.end(),cmp1);
		
		for(int i=0;i<links.size();++i)
		{
			links[i].priority=i+1;
			prior[links[i].n1][links[i].n2]=prior[links[i].n2][links[i].n1]=i+1;
		}
		
			
			for(int i=0;i<links.size();++i)
			{
				links[i].t1=t;
				links[i].t2=t+5;
				t=t+6;
			}
					
		cout<<"\n\nLinks:\n";
		for(int i=0;i<links.size();++i)
		{
			cout<<links[i].n1<<"  "<<links[i].n2<<" - "<<links[i].priority<<"      Time: "<<links[i].t1<<" - "<<links[i].t2<<endl;
		}
		
		cout<<"\n\n\n";
		printNode(G,prior,src,dest);			
			
				
}

// problems with node 4
// sleep duration needs to be increased
// packets received formula

