#include <stdio.h>
#include <string.h>

struct memorie {
    int size;
    int internal_fragmentation;
    char status[10];  // Array instead of pointer to avoid modifying string literals
};

struct Request {
    int job_number;
    int requestedMemory;
};

void printMemoryState(struct memorie memories[], int m) {
    printf("\nMemory Blocks:\n");
    printf("---------------------------------------------------\n");
    printf("| %-3s | %-6s | %-10s | %-5s |\n", "ID", "Size", "Status", "IF");
    printf("---------------------------------------------------\n");
    for (int i = 0; i < m; i++) {
        printf("| %-3d | %-6d | %-10s | %-5d |\n", i, memories[i].size, memories[i].status, memories[i].internal_fragmentation);
    }
    printf("---------------------------------------------------\n");
}

void printRequests(struct Request requests[], int n) {
    printf("\nMemory Requests:\n");
    printf("---------------------------\n");
    printf("| %-3s | %-6s |\n", "Job", "ReqMem");
    printf("---------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| %-3d | %-6d |\n", requests[i].job_number, requests[i].requestedMemory);
    }
    printf("---------------------------\n");
}

int main(void) {
    struct memorie memories[] = {
        {200, 0, "Free"},
        {50,  0, "Free"},
        {30,  0, "Free"},
        {700, 0, "Free"}
    };
    
    int m = sizeof(memories) / sizeof(memories[0]);

    struct Request memories_request[] = {
        {1, 20},
        {2, 200},
        {3, 500},
        {4, 50}
    };

    int n = sizeof(memories_request) / sizeof(memories_request[0]);

    for (int j = 0; j < n; j++) {
        int mem_request = memories_request[j].requestedMemory;
        
        for (int i = 0; i < m; i++) {
            if (strcmp(memories[i].status, "Free") == 0 && memories[i].size >= mem_request) {
                memories[i].internal_fragmentation = memories[i].size - mem_request;
                strcpy(memories[i].status, "Busy");  // Use strcpy to modify char array
                break;
            }
        }
    }

    // Print final state
    printRequests(memories_request, n);
    printMemoryState(memories, m);

    return 0;
}
