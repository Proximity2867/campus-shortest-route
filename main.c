#include <stdio.h>
#include <string.h>

#define MAX 20
#define INF 999999

int graph[MAX][MAX];
char location[MAX][50];
int n = 0;
int source = -1;

int distance[MAX];
int parent[MAX];
int visited[MAX];

void enterGraph();
void displayMatrix();
void selectSource();
void dijkstra();
void displayPaths();
void displayDistances();
void displayPath(int vertex);
int findMinimumVertex();

int main()
{
    int choice;

    do
    {
        printf("\nCampus Shortest Route Finder\n");
        printf("1. Enter Campus Graph\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Select Source Location\n");
        printf("4. Find Shortest Distance\n");
        printf("5. Display Shortest Paths\n");
        printf("6. Display Distance from Source to All Locations\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterGraph();
                break;

            case 2:
                displayMatrix();
                break;

            case 3:
                selectSource();
                break;

            case 4:
                dijkstra();
                break;

            case 5:
                displayPaths();
                break;

            case 6:
                displayDistances();
                break;

            case 7:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice. Please enter a number from 1 to 7.\n");
        }

    } while (choice != 7);

    return 0;
}

void enterGraph()
{
    int i, j, value;

    printf("\nEnter number of locations: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of locations.\n");
        n = 0;
        return;
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter name of location %d: ", i + 1);
        scanf(" %[^\n]", location[i]);
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }

    printf("\nEnter distance between connected locations.\n");
    printf("Enter 0 if there is no direct road.\n");

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            printf("Distance between %s and %s: ",
                   location[i], location[j]);

            scanf("%d", &value);

            if (value < 0)
            {
                printf("Distance cannot be negative.\n");
                value = 0;
            }

            if (value == 0)
            {
                graph[i][j] = INF;
                graph[j][i] = INF;
            }
            else
            {
                graph[i][j] = value;
                graph[j][i] = value;
            }
        }
    }

    source = -1;

    printf("Campus graph entered successfully.\n");
}

void displayMatrix()
{
    int i, j;

    if (n == 0)
    {
        printf("Please enter the campus graph first.\n");
        return;
    }

    printf("\nAdjacency Matrix\n\n");

    printf("%-22s", "");

    for (i = 0; i < n; i++)
        printf("%-22s", location[i]);

    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("%-22s", location[i]);

        for (j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                printf("%-22s", "INF");
            else
                printf("%-22d", graph[i][j]);
        }

        printf("\n");
    }
}

void selectSource()
{
    int choice;

    if (n == 0)
    {
        printf("Please enter the campus graph first.\n");
        return;
    }

    printf("\nLocations\n");

    for (int i = 0; i < n; i++)
        printf("%d. %s\n", i + 1, location[i]);

    printf("Enter source location number: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > n)
    {
        printf("Invalid location number.\n");
        return;
    }

    source = choice - 1;

    printf("Source location selected: %s\n", location[source]);
}

int findMinimumVertex()
{
    int min = INF;
    int vertex = -1;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && distance[i] < min)
        {
            min = distance[i];
            vertex = i;
        }
    }

    return vertex;
}

void dijkstra()
{
    int u;
    int newDistance;

    if (n == 0)
    {
        printf("Please enter the campus graph first.\n");
        return;
    }

    if (source == -1)
    {
        printf("Please select a source location first.\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        distance[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }

    distance[source] = 0;

    printf("\nDijkstra's Algorithm\n");
    printf("Source: %s\n\n", location[source]);

    for (int count = 0; count < n; count++)
    {
        u = findMinimumVertex();

        if (u == -1)
            break;

        visited[u] = 1;

        printf("Selected: %s, Distance: %d\n",
               location[u], distance[u]);

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] &&
                graph[u][v] != INF &&
                distance[u] != INF)
            {
                newDistance = distance[u] + graph[u][v];

                if (newDistance < distance[v])
                {
                    distance[v] = newDistance;
                    parent[v] = u;

                    printf("Updated %s: %d\n",
                           location[v], distance[v]);
                }
            }
        }
    }

    printf("\nShortest distances calculated successfully.\n");
}

void displayPath(int vertex)
{
    if (vertex == -1)
        return;

    if (parent[vertex] != -1)
    {
        displayPath(parent[vertex]);
        printf(" -> ");
    }

    printf("%s", location[vertex]);
}

void displayPaths()
{
    if (n == 0)
    {
        printf("Please enter the campus graph first.\n");
        return;
    }

    if (source == -1)
    {
        printf("Please select a source location first.\n");
        return;
    }

    if (distance[source] != 0)
    {
        printf("Please run Dijkstra's Algorithm first.\n");
        return;
    }

    printf("\nShortest Paths from %s\n\n", location[source]);

    printf("%-25s %-20s %s\n",
           "Destination",
           "Distance",
           "Path");

    for (int i = 0; i < n; i++)
    {
        if (i == source)
            continue;

        printf("%-25s ", location[i]);

        if (distance[i] == INF)
        {
            printf("%-20s No path\n", "INF");
        }
        else
        {
            printf("%-20d ", distance[i]);
            displayPath(i);
            printf("\n");
        }
    }
}

void displayDistances()
{
    if (n == 0)
    {
        printf("Please enter the campus graph first.\n");
        return;
    }

    if (source == -1)
    {
        printf("Please select a source location first.\n");
        return;
    }

    if (distance[source] != 0)
    {
        printf("Please run Dijkstra's Algorithm first.\n");
        return;
    }

    printf("\nDistance from %s\n\n", location[source]);

    printf("%-25s %s\n", "Location", "Shortest Distance");

    for (int i = 0; i < n; i++)
    {
        printf("%-25s ", location[i]);

        if (distance[i] == INF)
            printf("INF\n");
        else
            printf("%d\n", distance[i]);
    }
}
