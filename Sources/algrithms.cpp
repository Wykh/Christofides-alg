#include "includes.h"
#include "alhoritms.h"

cycle ApproxDoubleTree(Graph G)
{
    Graph T = Prim(G);
    DoDoubleEdges(T);    // make 2T graph from T graph by doubling edges
    cycle C = Fleury(T); // make eulear cycle
    DoHamiltonCycle(C);  // make Hamilton cycle from eulear cycle

    return C;
}

void DoHamiltonCycle(cycle& C)
{
    for (int i = 0; i < C.size() - 1; i++)
    {
        for (int j = C.size() - 2; j >= i + 1 ; j--)
        {
            if (C[i] == C[j])
            {
                C.erase(C.begin() + j);
            }
        }
    }
}

// Fleury algotithm

bool isEdgesEqual(iEdge e1, iEdge e2)
{
    return e1.second.first == e2.second.first && e1.second.second == e2.second.second;
}

// huinya, ebal rot
void deleteEdgeByValue(iEdges &es, iEdge &edge)
{
    iEdges::iterator deletedEdgeIterator;
    for (iEdges::iterator it = es.begin(); it < es.end(); it++)
    {
        if (isEdgesEqual(*it, edge))
        {
            deletedEdgeIterator = it;
            break;
        }
    }
    es.erase(deletedEdgeIterator);
}

// huinya
bool existsWayBetweenVertexes(iEdges edges, int from, int to, int cur = -1)
{
    if (cur == to)
        return true;

    int waysCnt = 0;
    int steps = 0;
    for (iEdge &edge : edges)
    {
        if (edge.first == -1)
            continue;

        int fstIndex = edge.second.first;  // first index of vertex of edge
        int sndIndex = edge.second.second; // second index of vertex of edge

        if (fstIndex == from)
        {
            edge.first = -1;
            steps++;
            waysCnt += existsWayBetweenVertexes(edges, sndIndex, to, sndIndex);
        }
        else if (sndIndex == from)
        {
            edge.first = -1;
            steps++;
            waysCnt += existsWayBetweenVertexes(edges, fstIndex, to, fstIndex);
        }
    }
    if (steps == 0)
        return false;
    return waysCnt;
}

bool isEdgeBridge(iEdges es, iEdge edge, int fromVert)
{
    int fstEdgeVert = edge.second.first;
    int sndEdgeVert = edge.second.second;

    int toVert;

    if (fstEdgeVert != fromVert)
    {
        toVert = fstEdgeVert;
    }
    else
    {
        toVert = sndEdgeVert;
    }

    deleteEdgeByValue(es, edge);

    return !existsWayBetweenVertexes(es, fromVert, toVert);
}

// pizda, fucked way, huinya
iEdge getNonBridgeEdgeFromVert(iEdges &edges, int vert)
{
    iEdge oneEdge;
    for (iEdge &edge : edges)
    {
        int fstIndex = edge.second.first;  // first index of vertex of edge
        int sndIndex = edge.second.second; // second index of vertex of edge

        if ((fstIndex == vert || sndIndex == vert))
        {
            bool edgeIsBridge = isEdgeBridge(edges, edge, vert);
            oneEdge = edge;
            if (!edgeIsBridge)
                return edge;
        }
    }
    return oneEdge;
    // throw "BLEAT CHO ZA HUINYA";
}

void DoStepOnGraphByEdge(iEdges &edges, cycle &way, int edgeInd)
{
    iEdges::iterator itCurEdge = edges.begin() + edgeInd;

    int fstIndex = (*itCurEdge).second.first;  // first index of vertex of edge
    int sndIndex = (*itCurEdge).second.second; // second index of vertex of edge

    way.push_back(fstIndex);
    way.push_back(sndIndex);

    edges.erase(itCurEdge);
}

//huinya
void DoStepOnGraphByEdgeButFromCurrentVertex(iEdges &edges, cycle &way, int edgeInd, int curVertex)
{
    iEdges::iterator itCurEdge = edges.begin() + edgeInd;

    int fstIndex = (*itCurEdge).second.first;  // first index of vertex of edge
    int sndIndex = (*itCurEdge).second.second; // second index of vertex of edge

    if (fstIndex != curVertex)
    {
        way.push_back(fstIndex);
    }
    else
    {
        way.push_back(sndIndex);
    }

    edges.erase(itCurEdge);
}

// this is huinya but is just copied from del
int getIndexOfEdge(iEdges &es, iEdge edge)
{
    int i = 0;
    for (iEdges::iterator it = es.begin(); it != es.end(); it++, i++)
    {
        if (isEdgesEqual(*it, edge))
        {
            return i;
        }
    }
}

cycle Fleury(Graph &G)
{
    iEdges edgesG = G.es;
    cycle way;

    DoStepOnGraphByEdge(edgesG, way, 0); // delete edge and write edges's vertexes to the `way`
    while (edgesG.size() != 0)
    {
        int prevVert = way[way.size() - 1];
        iEdge nextEdge = getNonBridgeEdgeFromVert(edgesG, prevVert);
        int nextEdgeInd = getIndexOfEdge(edgesG, nextEdge);
        DoStepOnGraphByEdgeButFromCurrentVertex(edgesG, way, nextEdgeInd, prevVert);
    }

    return way;
}

void DoDoubleEdges(Graph &G)
{
    for (iEdge &edge : G.es)
    {
        G.es.push_back(edge);
    }
}

// PRIM algorithm

iEdge getGraphMinEdge(iEdges es)
{
    iEdge minEdge = es[0];

    for (iEdge &curEdge : es)
    {
        int curEdgeLen = curEdge.first;
        int minEdgeLen = minEdge.first;
        if (curEdgeLen < minEdgeLen)
        {
            minEdge = curEdge;
        }
    }

    return minEdge;
}

void markEdgeVertexesAsUsed(std::vector<bool> &usedVerts, iEdge edge)
{
    int fstIndex = edge.second.first;  // first index of vertex of edge
    int sndIndex = edge.second.second; // second index of vertex of edge

    usedVerts[fstIndex] = usedVerts[sndIndex] = true;
}

bool isAllVertexesUsed(std::vector<bool> usedVerts)
{
    for (bool vert : usedVerts)
    {
        if (vert == false)
            return false;
    }
    return true;
}

void addEdgeToGraph(Graph &G, iEdge edge)
{
    G.es.push_back(edge);              // Add edge to graph
    int fstIndex = edge.second.first;  // first index of vertex of edge
    int sndIndex = edge.second.second; // second index of vertex of edge
    G.m[fstIndex][sndIndex] = edge.first;
    G.m[sndIndex][fstIndex] = edge.first;
}

Graph Prim(Graph G)
{
    int mSize = G.m.size();                                 // size of matrix - count of vertexes
    iMatrix emptyMatrix(mSize, std::vector<int>(mSize, 0)); // init matrix with zeroes
    Graph T;
    T.m = emptyMatrix;
    std::vector<bool> usedVerts(mSize, false);

    iEdge minEdge = getGraphMinEdge(G.es);
    addEdgeToGraph(T, minEdge);
    markEdgeVertexesAsUsed(usedVerts, minEdge);

    while (!isAllVertexesUsed(usedVerts))
    {
        iEdges possibleEdges; // edges insendent to used vertexes
        for (int i = 0; i < usedVerts.size(); i++)
        {
            // find used vertex
            if (usedVerts[i] == true)
            {
                // see all edges
                for (iEdge &edge : G.es)
                {
                    int fstIndex = edge.second.first;  // first index of vertex of edge
                    int sndIndex = edge.second.second; // second index of vertex of edge

                    // one of vertexes of edge in T graph and both vertexes are not used
                    if ((fstIndex == i || sndIndex == i) && !(usedVerts[fstIndex] && usedVerts[sndIndex]))
                    {
                        possibleEdges.push_back(edge);
                    }
                }
            }
        }
        iEdge minEdge = getGraphMinEdge(possibleEdges);
        addEdgeToGraph(T, minEdge);
        markEdgeVertexesAsUsed(usedVerts, minEdge);
    }

    return T;
}