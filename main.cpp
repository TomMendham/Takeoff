#include "mainwindow.h"
#include <QApplication>
#include "airport.h"
#include "flight.h"
#include <iostream>

void dijkstra(int graph[V][V], int src, int parent [V]);
int minDistance(int dist[], bool sptSet[]);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}


// Number of vertices in the graph
#define V 4


void fillFlightGri(std::vector<Flight*> Flights, int grid[V][V])
{
    for (int i = 0; i < Flights.size(); i++)
        if (Flights[i]->getDeparture == "London Heathrow")
        {
            for(int i = 0; i < Flights.size(); i++)
            {
                if (Flights[i]->getDestination == "Dubai International")
                {
                    grid[1][0] = Flights[i]->getDistance;
                    grid[0][1] = Flights[i]->getDistance;
                }
                if (Flights[i]->getDestination == "Sydney")
                {
                    grid[2][0] = Flights[i]->getDistance;
                    grid[0][2] = Flights[i]->getDistance;
                }
                if (Flights[i]->getDestination == "Kapetown")
                {
                    grid[3][0] = Flights[i]->getDistance;
                    grid[0][3] = Flights[i]->getDistance;
                }
            }
        }
        if (Flights[i]->getDeparture == "Dubai International")
        {
            for(int i = 0; i < Flights.size(); i++)
            {
                if (Flights[i]->getDestination == "Sydney")
                {
                    grid[1][2] = Flights[i]->getDistance;
                    grid[2][1] = Flights[i]->getDistance;
                }
                if (Flights[i]->getDestination == "Kapetown")
                {
                    grid[1][3] = Flights[i]->getDistance;
                    grid[3][1] = Flights[i]->getDistance;
                }
            }
        }

        if (Flights[i]->getDeparture == "Sydney")
        {
            for(int i = 0; i < Flights.size(); i++)
            {
                if (Flights[i]->getDestination == "Kapetown")
                {
                    grid[2][3] = Flights[i]->getDistance;
                    grid[3][2] = Flights[i]->getDistance;
                }
            }
        }
}



// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Funtion that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix
// representation
void dijkstra(int graph[V][V], int src, int parent [V])
{
    int dist[V];  // The output array. dist[i] will hold
                  // the shortest distance from src to i

    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[V];

    // Parent array to store shortest path tree
    //int parent[V];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    // print the constructed distance array
    //printSolution(dist, V, parent);
}
