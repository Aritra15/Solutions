#include<bits/stdc++.h>
using namespace std;
class DisjointSet{
    vector<int> rank,parent;
public:
    DisjointSet(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        for(int i=0;i<=n;i++){
            parent[i]=i;
        }
    }

    int findUltimateParent(int node){
        if(node==parent[node]){
            return node;
        }
        return parent[node]=findUltimateParent(parent[node]);
    }

    void UnionByRank(int u,int v){
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);

        if(ulp_u == ulp_v){
            return;
        }
        if(rank[ulp_u]<rank[ulp_v]){
            parent[ulp_u]=ulp_v;
        }
        else if(rank[ulp_u]>rank[ulp_v]){
            parent[ulp_v]=ulp_u;
        }
        else{
            parent[ulp_u]=ulp_v;
            rank[ulp_u]++;
        }
    }
};

int minSpanningTree(vector<pair<int,pair<int,int>>>&adj,int n) //tuple of weight,u,v and n is the number of vertices(1 based indexing)
{
    int weight =0;
    sort(adj.begin(),adj.end());
    DisjointSet ds(n+1);
    for(int i=0;i<adj.size();i++)
    {
        int wt = adj[i].first;
        int u = adj[i].second.first;
        int v = adj[i].second.second;
        int ulp_u = ds.findUltimateParent(u);
        int ulp_v = ds.findUltimateParent(v);
        if(ulp_u!=ulp_v){
            ds.UnionByRank(u,v);
            weight+=wt;
        }
    }
    return weight;
}

int specialMinimumSpanningTree(vector<pair<int, pair<int, int>>> &adj2, int n, pair<int, pair<int, int>> edge)
{
    int weight = 0;
    sort(adj2.begin(), adj2.end());
    DisjointSet ds(n + 1);
    ds.UnionByRank(edge.second.first, edge.second.second);
    weight += edge.first;
    for (int i = 0; i < adj2.size(); i++)
    {
        int wt = adj2[i].first;
        int u = adj2[i].second.first;
        int v = adj2[i].second.second;
        int ulp_u = ds.findUltimateParent(u);
        int ulp_v = ds.findUltimateParent(v);
        if (ulp_u != ulp_v)
        {
            ds.UnionByRank(u, v);
            weight += wt;
        }
    }
    return weight;
}

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        
    int m = edges.size();
    vector<pair<int, pair<int, int>>> adj;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        u = edges[i][0];
        v = edges[i][1];
        w = edges[i][2];
        adj.push_back({w, {u, v}});
    }

    vector<pair<int, pair<int, int>>> backUpGraph = adj;
    int minWeight = minSpanningTree(adj, n);

    
    vector<int> indicesOfPseudoCriticalEdges;
    vector<int> indicesOfCriticalEdges;

    
    int flag = 0;
    for (int i = 0; i < adj.size(); i++)
    {
        vector<pair<int, pair<int, int>>> adj2 = backUpGraph;
        adj2.erase(adj2.begin() + i);
       
        int weight = minSpanningTree(adj2, n);
        
        if (weight != minWeight)
        {
            indicesOfCriticalEdges.push_back(i);
        }
        else
        {
            
            int w = specialMinimumSpanningTree(adj2, n, backUpGraph[i]);
            if (w == minWeight)
            {
                indicesOfPseudoCriticalEdges.push_back(i);
            }
        }
    }
    vector<vector<int>> ans;
    ans.push_back(indicesOfCriticalEdges);
    ans.push_back(indicesOfPseudoCriticalEdges);
    return ans;
   
    }
};