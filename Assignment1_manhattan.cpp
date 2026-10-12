/*Design a system to find the shortest path between two locations, similar to
Google Maps. Design with uninformed search algorithm and informed search
algorithm and analyse the result. Create a graph of at least 8–10 cities/nodes
Define: Distance between nodes (edge cost) Heuristic values (straight-line
distance to goal*/

#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;

struct Edge{
    string dest;
    int cost;
};

struct Node{
    int f;
    string city;
    bool operator>(const Node& other)const{
        return f>other.f;
    }
};


class Graph{
    public:
    unordered_map<string, vector<Edge>> graph;
    unordered_map<string, pair<int, int>> raw;
    unordered_map<string,int> heuristics;

    void addEdge(string src, string destination,int dist){
        graph[src].push_back({destination, dist});
        graph[destination].push_back({src,dist});
    }

    void addCoords(string city, int x, int y){
        raw[city]={x,y};

    }

    void Manhattan(string dest){

        int destx=raw[dest].first;
        int desty=raw[dest].second;

        for(auto place:raw){

            int x=place.second.first;
            int y=place.second.second;

            heuristics[place.first]=abs(x-destx)+abs(y-desty);
        }
    }

    void AStarSearch(string src, string dest){
        //need- f,g,h for each city(node), priority q with f as priority to store open nodes, smallest f node first,
        //close list - set, current node pointer- update each time- calculate new values from current node
        //all neighbours of current node, have to store previous node also
        //returns path array of cities
        
        unordered_map<string,int>g;//store g
        unordered_map<string,string>prev;//store previous node
        unordered_map<string,bool>closeList;//is node in closed list

        //priority_queue<  DataType,  ContainerType,  SortingRule  > openList;
        priority_queue<Node, vector<Node>, greater<Node>>openList;

        g[src]=0;
        openList.push({heuristics[src], src});

        while(!openList.empty()){
            //find neighbours- if edge in graph contains current city- it is neighbour
            //for every neighbour- check if neighbours not in closedList
            //if in closed list-continue, else- find h from heuristics map, find g from current city, find f

        
            //after pushing neighbours to open list, remove curr from openList

            string curr=openList.top().city;
            openList.pop();

            if(closeList[curr])continue;
            closeList[curr]=true;

            if(curr==dest){
                cout<<"Path:";
                //backtrack to give path
                vector<string> path;
                string s=dest;
                while(s!=src){
                    path.push_back(s);
                    s=prev[s];
                }
                path.push_back(src);

                for(int i=path.size()-1;i>=0;i--){
                    cout<<path[i];
                    cout<<" ";
                }

                cout<<"Total dist: "<<g[dest]<<endl;
                return;
            }

            for(Edge nghbr:graph[curr]){
                if(closeList[nghbr.dest]){//if dest node of that neghbouring edge is viewwed then continue
                    continue;
                }

                int newg=g[curr]+nghbr.cost;//calculate cost

                if(!g.count(nghbr.dest)||newg<g[nghbr.dest]){//if city is seen or shorter path
                    g[nghbr.dest]=newg;//update cost upto that node
                    prev[nghbr.dest]=curr;

                    int f=newg+heuristics[nghbr.dest];
                    openList.push({f,nghbr.dest});
                }


            }
                
        }
            

    }

    void UninformedSearch(string src, string dest){ //ucs
        
        unordered_map<string,int>g;//store g
        unordered_map<string,string>prev;//store previous node
        unordered_map<string,bool>closeList;//is node in closed list

        //priority_queue<  DataType,  ContainerType,  SortingRule  > openList;
        priority_queue<Node, vector<Node>, greater<Node>>openList;

        g[src]=0;
        openList.push({0, src});

        while(!openList.empty()){
            
            string curr=openList.top().city;
            openList.pop();

            if(closeList[curr])continue;
            closeList[curr]=true;

            if(curr==dest){
                cout<<"Path:";
                //backtrack to give path
                vector<string> path;
                string s=dest;
                while(s!=src){
                    path.push_back(s);
                    s=prev[s];
                }
                path.push_back(src);

                for(int i=path.size()-1;i>=0;i--){
                    cout<<path[i];
                    cout<<" ";
                }

                cout<<"Total dist: "<<g[dest]<<endl;
                return;
            }

            for(Edge nghbr:graph[curr]){
                if(closeList[nghbr.dest]){//if dest node of that neghbouring edge is viewwed then continue
                    continue;
                }

                int newg=g[curr]+nghbr.cost;//calculate cost

                if(!g.count(nghbr.dest)||newg<g[nghbr.dest]){//if city is seen or shorter path
                    g[nghbr.dest]=newg;//update cost upto that node
                    prev[nghbr.dest]=curr;

                    openList.push({newg,nghbr.dest});
                }


            }
                
        }
            


    }

};

int main() {
    Graph g; 
    
    g.addCoords("Nagpur", 10,20);       
    g.addCoords("Aurangabad", 30,40);
    g.addCoords("Solapur", 10,50);
    g.addCoords("Nashik", 45,22);
    g.addCoords("Pune", 12,80);
    g.addCoords("Mumbai", 15,68);
    g.addCoords("Hyderabad", 40,13);
    g.addCoords("Bangalore", 90,18);

        
    g.addEdge("Mumbai", "Pune", 150);
    g.addEdge("Mumbai", "Nashik", 170);
    g.addEdge("Pune", "Nashik", 210);
    g.addEdge("Pune", "Solapur", 250);
    g.addEdge("Pune", "Aurangabad", 250);
    g.addEdge("Nashik", "Aurangabad", 190);
    g.addEdge("Aurangabad", "Nagpur", 480);
    g.addEdge("Solapur", "Aurangabad", 310);
    g.addEdge("Solapur", "Hyderabad", 300);
    g.addEdge("Bangalore", "Nagpur", 580);
    g.addEdge("Bangalore", "Hyderabad", 570);

    
    string src = "Mumbai";
    string goal = "Nagpur";
    
    g.Manhattan("Nagpur");

    cout<<"Informed search:"<<endl;
    g.AStarSearch(src,goal);

    cout<<"Uninformed search:"<<endl;
    g.UninformedSearch(src,goal);
//print in a good cmptable
    
    return 0;

}



          