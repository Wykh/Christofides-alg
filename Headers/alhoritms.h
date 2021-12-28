#include "includes.h"
#include "structures.h"

void Brute();

// Simple Christofides–Serdyukov algorithm, error x2
cycle ApproxDoubleTree(Graph G);

int CaclCycleLen(Graph G, cycle C);

void Greedy();

Graph Prim(Graph G);

void DoDoubleEdges(Graph &G);

cycle Fleury(Graph &G);

void DoHamiltonCycle(cycle &C);
