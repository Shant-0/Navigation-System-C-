#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXV  17
#define INF   (INT_MAX/4)
#define DIRLEN 32

/* -------------------------------------------
   NODE NAMES (MUST MATCH EXACTLY)
 ------------------------------------------- */
const char *names[MAXV] = {
    "PunchGate",
    "Joint01",
    "Joint02",
    "Joint03",
    "Joint04",
    "Ground",
    "WiFi",
    "LectureGallery",
    "MBA",
    "Class107-111",
    "Class112-115",
    "Pigeonhole",
    "PrayerHall",
    "Journal",
    "Auditorium",
    "StairsCafe",
    "Gate"
};

/* Enum for readability */
enum {
    V_PUNCH = 0,
    V_J01,
    V_J02,
    V_J03,
    V_J04,
    V_GND,
    V_WIFI,
    V_LG,
    V_MBA,
    V_C107,
    V_C112,
    V_PIGE,
    V_PRAY,
    V_JOURNAL,
    V_AUDIT,
    V_STCAFE,
    V_GATE
};

/* -------------------------------------------
   ADJACENCY LIST EDGE STRUCTURE
 ------------------------------------------- */
typedef struct Edge {
    int to;
    int weight;             
    char dir[DIRLEN];       
    struct Edge *next;
} Edge;

Edge *adj[MAXV] = {0};

/* Add directed edge */
void add_edge_dir(int from, int to, int w, const char *dir) {
    Edge *e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->weight = w;
    strncpy(e->dir, dir, DIRLEN-1);
    e->dir[DIRLEN-1] = '\0';
    e->next = adj[from];
    adj[from] = e;
}

/* Opposite compass direction */
const char* opposite(const char *d) {
    if (strcmp(d,"North")==0) return "South";
    if (strcmp(d,"South")==0) return "North";
    if (strcmp(d,"East")==0)  return "West";
    if (strcmp(d,"West")==0)  return "East";
    if (strcmp(d,"North-East")==0) return "South-West";
    if (strcmp(d,"South-West")==0) return "North-East";
    if (strcmp(d,"North-West")==0) return "South-East";
    if (strcmp(d,"South-East")==0) return "North-West";
    return d;
}

/* Add undirected edge using auto reverse direction */
void add_edge_und(int a, int b, int w, const char *dir_ab) {
    add_edge_dir(a, b, w, dir_ab);
    add_edge_dir(b, a, w, opposite(dir_ab));
}

/* -------------------------------------------
   BUILD GRAPH EXACTLY AS CONFIRMED
 ------------------------------------------- */
void build_graph(void) {
    for (int i = 0; i < MAXV; i++) adj[i] = NULL;

    add_edge_und(V_PUNCH, V_J01, 35, "North");

    add_edge_und(V_J01, V_AUDIT, 55, "West");
    add_edge_und(V_J01, V_GND, 45, "North-West");
    add_edge_und(V_J01, V_J04, 70, "North");
    add_edge_und(V_J01, V_J02, 115, "West");
    add_edge_und(V_J01, V_STCAFE, 85, "West");

    add_edge_und(V_PRAY, V_J04, 15, "West");


    add_edge_und(V_J04, V_PIGE, 20, "West");
    add_edge_und(V_J04, V_GND, 45, "South-West");

    add_edge_und(V_PIGE, V_C107, 25, "West");

    add_edge_und(V_C107, V_GATE, 15, "West");

    add_edge_und(V_GND, V_GATE, 35, "North");
    add_edge_und(V_GND, V_AUDIT, 35, "South");
    add_edge_und(V_GND, V_WIFI, 20, "West");
    add_edge_und(V_GND, V_STCAFE, 45, "South-West");

    add_edge_und(V_GATE, V_C112, 15, "West");

    add_edge_und(V_C112, V_J03, 10, "West");

    add_edge_und(V_J03, V_WIFI, 45, "South");
    add_edge_und(V_J03, V_MBA, 15, "West");
    add_edge_und(V_J03, V_LG, 45, "South-West");
    add_edge_und(V_J03, V_STCAFE, 70, "South");

    add_edge_und(V_LG, V_J02, 30, "South");
    add_edge_und(V_LG, V_JOURNAL, 45, "South");

    add_edge_und(V_J02, V_JOURNAL, 15, "South");
    add_edge_und(V_J02, V_STCAFE, 30, "East");
    add_edge_und(V_J02, V_AUDIT, 60, "East");

    add_edge_und(V_STCAFE, V_WIFI, 25, "North");
}

/* -------------------------------------------
   HELPER FUNCTIONS
 ------------------------------------------- */
int index_of(const char *s) {
    for (int i = 0; i < MAXV; i++)
        if (strcmp(s, names[i]) == 0) return i;
    return -1;
}

void normalize(char *s) {
    int L = strlen(s);
    while (L > 0 && (s[L-1]=='\n'||s[L-1]=='\r')) s[--L]='\0';
    while (*s==' '||*s=='\t') memmove(s, s+1, strlen(s));
}

/* -------------------------------------------
   DIJKSTRA
 ------------------------------------------- */
void dijkstra(int src, int dst, int parent[], char parent_dir[][DIRLEN], int *out_dist) {
    int dist[MAXV], vis[MAXV];

    for (int i=0;i<MAXV;i++){
        dist[i]=INF; vis[i]=0; parent[i]=-1; parent_dir[i][0]='\0';
    }

    dist[src]=0;

    for(int it=0;it<MAXV;it++){
        int v=-1;
        for(int i=0;i<MAXV;i++)
            if(!vis[i] && (v==-1 || dist[i]<dist[v])) v=i;
        if(v==-1 || dist[v]==INF) break;

        vis[v]=1;
        if(v==dst) break;

        for(Edge *e=adj[v];e;e=e->next){
            if(dist[v]+e->weight < dist[e->to]){
                dist[e->to] = dist[v]+e->weight;
                parent[e->to] = v;
                strncpy(parent_dir[e->to], e->dir, DIRLEN);
            }
        }
    }

    *out_dist = dist[dst];
}

/* -------------------------------------------
   PRINT ROUTE
 ------------------------------------------- */
void print_route(int src, int dst, int parent[], char parent_dir[][DIRLEN], int total) {
    if(total >= INF){
        printf("\nNo path found between %s and %s.\n\n", names[src], names[dst]);
        return;
    }

    int path[MAXV], top=0;
    int cur=dst;
    while(cur!=-1){
        path[top++] = cur;
        cur = parent[cur];
    }

    if(path[top-1] != src){
        printf("\nNo path found.\n\n");
        return;
    }

    printf("\nTotal distance: %d units\n\n", total);
    printf("Step-by-step navigation:\n");

    for(int i=top-1;i>0;i--){
        int from = path[i];
        int to   = path[i-1];

        /* find weight */
        int w = -1;
        for(Edge *e=adj[from];e;e=e->next){
            if(e->to==to){w=e->weight; break;}
        }

        printf("  → From %-15s go %-12s to %-15s (%d)\n",
               names[from],
               parent_dir[to],
               names[to],
               w);
    }

    printf("\n-------------- ROUTE COMPLETE --------------\n\n");
}

/* -------------------------------------------
   PRINT ALL KNOWN NODES (beautiful)
 ------------------------------------------- */
void print_known_nodes() {
    printf("Known nodes:\n");
    printf("--------------------------------------------\n");

    for(int i=0;i<MAXV;i++){
        printf("  • %s\n", names[i]);
    }

    printf("--------------------------------------------\n\n");
}

/* -------------------------------------------
   MAIN LOOP
 ------------------------------------------- */
int main() {
    build_graph();

    char a[128], b[128];
    int parent[MAXV];
    char parent_dir[MAXV][DIRLEN];
    int dist;

    printf("==========================================\n");
    printf("        CAMPUS NAVIGATION SYSTEM\n");
    printf("==========================================\n\n");

    print_known_nodes();

    while(1){
        printf("Enter start node (or type 'exit'): ");
        if(!fgets(a,sizeof(a),stdin)) break;
        normalize(a);
        if(strcmp(a,"exit")==0) break;

        printf("Enter target node (or type 'exit'): ");
        if(!fgets(b,sizeof(b),stdin)) break;
        normalize(b);
        if(strcmp(b,"exit")==0) break;

        int s = index_of(a);
        int t = index_of(b);

        if(s<0){
            printf("\nInvalid start node: %s\n", a);
            print_known_nodes();
            continue;
        }
        if(t<0){
            printf("\nInvalid target node: %s\n", b);
            print_known_nodes();
            continue;
        }
        if(s==t){
            printf("\nYou are already at %s.\n\n", names[s]);
            continue;
        }

        dijkstra(s,t,parent,parent_dir,&dist);
        print_route(s,t,parent,parent_dir,dist);
    }

    printf("\nExiting navigation system.\n");
    return 0;
}
