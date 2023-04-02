#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100

void read_graph(FILE* file, int graph[][MAX_NODES], int* num_nodes) {
    char line[256];
    int row = 0;

    // Read each line of the file
    while (fgets(line, sizeof(line), file)) {
        int col = 0;
        char* token = strtok(line, " ");
        while (token) {
            // Convert token to integer
            int value = atoi(token);
            // Store value in graph
            graph[row][col++] = value;
            // Store value in opposite cell to create a loop
            if (col-1 <= row) {
                graph[col-1][row] = value;
            }
            // Move to next token
            token = strtok(NULL, " ");
        }
        // Move to next row
        row++;
    }

    // Set num_nodes to the number of rows
    *num_nodes = row;
}

void write_dot(FILE* file, int graph[][MAX_NODES], int num_nodes) {
    fprintf(file, "digraph G {\n");
    // Add all nodes
    for (int i = 0; i < num_nodes; i++) {
        fprintf(file, "  %d;\n", i);
    }
    // Add edges with labels
    for (int i = 0; i < num_nodes; i++) {
        for (int j = i; j < num_nodes; j++) {
            if (graph[i][j]) {
                fprintf(file, "  %d -> %d [dir=none, label=%d];\n", i, j, graph[i][j]);
            }
        }
    }
    fprintf(file, "}\n");
}

int main() {
    char filename[100];
    int graph[MAX_NODES][MAX_NODES] = {0};
    int num_nodes = 0;

    printf("Enter the filename:\n");
    scanf("%s",filename);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error. Unable to open file.\n");
        return 1;
    }
    read_graph(file, graph, &num_nodes);
    fclose(file);
    file = fopen("graph.dot", "w");
    if (file == NULL) {
        fprintf(stderr, "Error. Unable to open file.\n");
        return 1;
    }
    write_dot(file, graph, num_nodes);
    fclose(file);
    system("dot -Tpng graph.dot -o graph.png");
    return 0;
}
