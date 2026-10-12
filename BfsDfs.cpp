#include<iostream>
#include<queue>
using namespace std;

class SearchGraph{
    int rows,cols;
    int adjmatrix[10][10];

    public:
    SearchGraph(int m, int n){
        rows=m;
        cols=n;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                adjmatrix[i][j]=0;
            }

        }

    }

    void newEdge(int u, int v){
        adjmatrix[u][v]=1;
        adjmatrix[v][u]=1;
    }

    void BFS(int start){
        bool visited[10] = {false};
        queue<int> q;
        visited[start]=true;
        q.push(start);

            while(!q.empty()){
                int node=q.front();
                q.pop();
                cout<<node<<" ";

            for(int nbr=0; nbr<cols; nbr++){
                if(adjmatrix[node][nbr]==1 && !visited[nbr]){
                    visited[nbr]=true;
                    q.push(nbr);
                }
            }
        }
    }

    void dfs_recursive(int node, bool visited[]){
        visited[node]=true;
        cout<<node<<" ";
        for(int nbr=0;nbr<cols; nbr++){
            if(adjmatrix[node][nbr]==1 && !visited[nbr]){
                dfs_recursive(nbr, visited);

            }
        }
    }

    void DFS(int start) {
        bool visited[10] = {false};
        dfs_recursive(start, visited);
    }

};

int main(){
    int m,n;
    cout<<"Enter number of rows and columns: ";
    cin>>m>>n;
    SearchGraph g(m,n);

    g.newEdge(0,1);
    g.newEdge(0,2);
    g.newEdge(1,2);
    g.newEdge(1,5);
    g.newEdge(2,3);
    g.newEdge(3,4);
    
    cout<<"BFS starting from 0: ";
    g.BFS(0);
    cout<<"DFS starting from 0: ";
    g.DFS(0);
    return 0;
}



