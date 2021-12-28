#include "includes.h"
#pragma once

typedef std::vector<std::vector<int> > iMatrix;
typedef std::vector<iMatrix > iMatrixes;
typedef std::pair<int, int> iPair;
typedef std::pair<int, iPair> iEdge;
typedef std::vector<iEdge> iEdges;

typedef std::vector<int> cycle;

struct Graph
{
    iMatrix m;
    iEdges es;

    Graph(){};

    Graph(iMatrix m)
    {
        this->m = m;

        iEdges es; // init edges without zero edges
        for (int i = 0; i < m.size(); i++)
        {
            for (int j = i + 1; j < m.size(); j++)
            {
                iPair vertPair; // vertexes pair
                vertPair.first = i;
                vertPair.second = j;

                iEdge edge;
                edge.first = m[i][j];
                edge.second = vertPair;
                es.push_back(edge);
            }
        }

        this->es = es;
    }

    Graph(iEdges e)
    {
        this->es = e;
    }
};
