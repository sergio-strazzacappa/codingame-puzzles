#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODES 500

int N;
int L;
int E;

int adj[MAX_NODES][MAX_NODES];
int gateways[MAX_NODES];
int is_gateway[MAX_NODES];

void init();
void solve();
void debug_net();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%d%d%d", &N, &L, &E);

    // Initialize the adj matrix
    for (int i = 0; i < MAX_NODES; i++)
        for (int j = 0; j < MAX_NODES; j++)
            adj[i][j] = 0;

    // Initialize the is_gateway array
    for (int i = 0; i < MAX_NODES; i++)
        is_gateway[i] = 0;

    // Read the links and update the matrix
    for (int i = 0; i < L; i++) {
        int n1, n2;
        scanf("%d%d", &n1, &n2);
        adj[n1][n2] = 1;
        adj[n2][n1] = 1;
    }

    // Read the gateways
    for (int i = 0; i < E; i++) {
        int e;
        scanf("%d", &e);

        gateways[i] = e;
        is_gateway[e] = 1;
    }
}

void solve() {
    while (true) {
        int agent;
        scanf("%d", &agent);

        fprintf(stderr, "The agent is at node %d\n", agent);

        // 1. If a neighbor is adjacent to a gateway, cut that link
        // 2. Calculate the distances from each gateway to the agent
        // 3. Cut the link to  the neighbor of the agent closest to any gateway
        // 4. If two nodes are at the same distance, cut the one with least
        //    grade

        // Calculate the grade (number of incident edges) of each node
        int grades[MAX_NODES];

        for (int i = 0; i < N; i++)
            grades[i] = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (adj[i][j]) {
                    grades[i]++;
                    grades[j]++;
                }
            }
        }

        // Always cut from the agent to a neighbor
        int target_s = agent;
        int target_e = -1;

        // A gateway is adjacent to the agent
        for (int i = 0; i < E; i++) {
            if (adj[agent][gateways[i]])
                target_e = gateways[i];
        }

        if (target_e == -1) {
            // BFS search
            int distances[MAX_NODES];

            for (int i = 0; i < N; i++) {
                if (is_gateway[i])  distances[i] = 0;
                else                distances[i] = -1;
            }

            int queue[MAX_NODES];
            int parent[MAX_NODES];
            int head = 0;
            int tail = 0;
            bool found = false;

            for (int i = 0; i < N; i++)
                    parent[i] = -1;

            for (int i = 0; i < E; i++) {
                queue[tail++] = gateways[i];
                parent[gateways[i]] = gateways[i]; // Mark the roots as visited
            }

            while (head < tail && !found) {
                int current = queue[head++];

                for (int next = 0; next < N; next++) {
                    if (adj[current][next] && parent[next] == -1) {
                        parent[next] = current;

                        if (next == agent) {
                            found = true;
                            break;
                        }

                        distances[next] = distances[current] + 1;
                        queue[tail++] = next;
                    }
                }
            }

            // Search the link to cut
            int min_distance = INT_MAX;
            int min_grades = INT_MAX;
            for (int i = 0; i < N; i++) {
                if (adj[agent][i] && distances[i] != -1) {
                    if (distances[i] < min_distance) {
                        min_distance = distances[i];
                        target_e = i;
                        min_grades = grades[i];
                    } else if (distances[i] == min_distance && grades[i] < min_grades) {
                        target_e = i;
                        min_grades = grades[i];
                    }
                }
            }
        }

        printf("%d %d\n", target_s, target_e);

        // Update the links
        adj[target_s][target_e] = 0;
        adj[target_e][target_s] = 0;
    }
}

void debug_net() {
    fprintf(stderr, "Nodes:%d, Links:%d, Gateways:%d\n\n", N, L, E);
    fprintf(stderr, "----- EDGES -----\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(stderr, "%d -> %d (%d)", i, j, adj[i][j]);
            if (j < N - 1)
                fprintf(stderr, " ");
        }
        fprintf(stderr, "\n");
    }

    fprintf(stderr, "----- GATEWAYS -----\n");

    for (int i = 0; i < N; i++)
        if (is_gateway[i])
            fprintf(stderr, "%d\n", i);
}
