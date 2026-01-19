#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

struct Edge { int to, id; };

vector<int> low, tin;
vector<vector<Edge>> graph;
vector<bool> visited;
vector<bool> isCut;
vector<pair<int,int>> bridges;
int timer = 0;

void dfs(int node, int parentEdgeId = -1)
{
    visited[node] = true;
    tin[node] = low[node] = ++timer;

    int children = 0;

    for (auto [v, eid] : graph[node])
    {
        if (eid == parentEdgeId) continue;

        if (visited[v])
        {
            low[node] = min(low[node], tin[v]);
        } 
        else 
        {
            children++;
            dfs(v, eid);

            low[node] = min(low[node], low[v]);

            if (low[v] > tin[node])
            {
                bridges.push_back({node,v});
            }

            if (parentEdgeId = -1 && low[v] >= tin[node])
            {
                isCut[node] = true;
            }
        }
    }

    if (parentEdgeId == -1 && children >= 2)
    {
        isCut[node] = true;
    }
}

int main()
{
    

    return 0;
}