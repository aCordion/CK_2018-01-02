#include "DFS.h"

void main() {
	system("title Depth First Search with Maze");
	char *mapdata[] = { "  ","бс" };
	pos xyPos[3];

	int map[10][MAX_X] = 
	{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1},
	{1,0,0,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1,0,1},
	{1,0,1,1,1,1,0,1,1,0,1,0,0,0,0,1,0,1,0,1},
	{1,0,1,0,0,1,0,1,0,0,1,0,1,1,0,1,0,0,0,1},
	{1,0,1,1,0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1},
	{1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1},
	{1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < MAX_X; x++) {
			cout << setw(2) << mapdata[map[y][x]];
		}
		cout << endl;
	}
	//MAP MAXSIZE
	xyPos[0].x = 20;
	xyPos[0].y = 10;
	//FROM
	xyPos[1].x = 1;
	xyPos[1].y = 8;
	//TO
	xyPos[2].x = 18;
	xyPos[2].y = 8;
	system("pause");
	DFS dfs(xyPos[0], xyPos[1], xyPos[2]);

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < MAX_X; x++) {
		dfs.mapCopy(y, x, map[y][x]);
		}
	}
	//dfs.TESTDRAW();
	dfs.Find();

	//dfs.draw();
	//y8,x1 to y8,x18
	system("pause");

}