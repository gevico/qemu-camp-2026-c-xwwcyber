#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	{0, 1, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0},
};

typedef struct {
	int row;
	int col;
} Point;

int visited[MAX_ROW][MAX_COL];
Point parent[MAX_ROW][MAX_COL];
Point queue[MAX_ROW * MAX_COL];
int front = 0, rear = 0;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main(void)
{
	// BFS
	queue[rear++] = (Point){0, 0};
	visited[0][0] = 1;
	parent[0][0] = (Point){-1, -1};

	while (front < rear) {
		Point cur = queue[front++];

		if (cur.row == MAX_ROW - 1 && cur.col == MAX_COL - 1) {
			// 回溯路径
			Point path[MAX_ROW * MAX_COL];
			int len = 0;
			Point p = cur;
			while (p.row != -1) {
				path[len++] = p;
				p = parent[p.row][p.col];
			}
			// 输出从终点到起点
			for (int i = 0; i < len; i++) {
				printf("(%d, %d)\n", path[i].row, path[i].col);
			}
			return 0;
		}

		for (int d = 0; d < 4; d++) {
			int nr = cur.row + dr[d];
			int nc = cur.col + dc[d];
			if (nr >= 0 && nr < MAX_ROW && nc >= 0 && nc < MAX_COL &&
			    maze[nr][nc] == 0 && !visited[nr][nc]) {
				visited[nr][nc] = 1;
				parent[nr][nc] = cur;
				queue[rear++] = (Point){nr, nc};
			}
		}
	}

	printf("No path!\n");
	return 0;
}
