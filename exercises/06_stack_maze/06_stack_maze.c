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
Point stack[MAX_ROW * MAX_COL];
int top = -1;

// 方向：上、右、下、左
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main(void)
{
	// DFS 用栈求解迷宫
	stack[++top] = (Point){0, 0};
	visited[0][0] = 1;

	while (top >= 0) {
		Point cur = stack[top];

		if (cur.row == MAX_ROW - 1 && cur.col == MAX_COL - 1) {
			// 找到终点，输出路径（从终点到起点）
			for (int i = top; i >= 0; i--) {
				printf("(%d, %d)\n", stack[i].row, stack[i].col);
			}
			return 0;
		}

		int found = 0;
		for (int d = 0; d < 4; d++) {
			int nr = cur.row + dr[d];
			int nc = cur.col + dc[d];
			if (nr >= 0 && nr < MAX_ROW && nc >= 0 && nc < MAX_COL &&
			    maze[nr][nc] == 0 && !visited[nr][nc]) {
				visited[nr][nc] = 1;
				stack[++top] = (Point){nr, nc};
				found = 1;
				break;
			}
		}

		if (!found) {
			top--; // 回溯
		}
	}

	printf("No path!\n");
	return 0;
}
