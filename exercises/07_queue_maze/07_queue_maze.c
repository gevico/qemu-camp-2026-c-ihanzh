#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
    0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0,
};

typedef struct {
    int row;
    int col;
} Point;

static int valid(int row, int col) { return row >= 0 && row < MAX_ROW && col >= 0 && col < MAX_COL; }

int main(void) {
    // TODO: 在这里添加你的代码
    int visited[MAX_ROW][MAX_COL] = {0};
    Point parent[MAX_ROW][MAX_COL];
    Point queue[MAX_ROW * MAX_COL];
    int front = 0;
    int rear = 0;
    Point start = {0, 0};
    Point target = {4, 4};
    int found = 0;

    if (maze[start.row][start.col] != 0 || maze[target.row][target.col] != 0) {
        printf("No path!\n");
        return 0;
    }

    visited[start.row][start.col] = 1;
    parent[start.row][start.col].row = -1;
    parent[start.row][start.col].col = -1;
    queue[rear++] = start;

    while (front < rear) {
        Point cur = queue[front++];
        if (cur.row == target.row && cur.col == target.col) {
            found = 1;
            break;
        }
        const int dr[] = {0, 1, 0, -1};
        const int dc[] = {-1, 0, 1, 0};
        for (int i = 0; i < 4; i++) {
            int nr = cur.row + dr[i];
            int nc = cur.col + dc[i];
            if (!valid(nr, nc)) {
                continue;
            }
            if (visited[nr][nc]) {
                continue;
            }
            if (maze[nr][nc] != 0) {
                continue;
            }
            visited[nr][nc] = 1;
            parent[nr][nc] = cur;
            queue[rear++] = (Point){nr, nc};
        }
    }

    if (!found) {
        printf("No path!\n");
        return 0;
    }

    for (Point p = target; p.row != -1 && p.col != -1; p = parent[p.row][p.col]) {
        printf("(%d, %d)\n", p.row, p.col);
    }

    return 0;
}
