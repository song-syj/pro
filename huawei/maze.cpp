#include<iostream>
#include<cstring>

using namespace std;
char maze[21][21]; // 输入的迷宫
char map[21][21]; // 记录匹配过的那些点,避免重复
char word[101]; // 搜索的单词
char *str; // 指向下一个搜索字母
int m, n;

/*
 * 该函数使用深度优先搜索，可以参照算法导论第22章图的搜索算法
 *返回值： true 表示搜索到，false表示没有搜索到相关匹配的路径
 */

bool dfs(int i, int j)
{
	if(*str == '\0' )			// 搜索完毕
		return true;
	
	if(i < 0 || j < 0
	   || i >= m || j >= n)		// 超出迷宫范围
		return false;
	if(map[i][j]  != 0)			// 这个点之前搜索过，避免重复
		return false;
	map[i][j]++;				// 记录搜索点
	
	if(maze[i][j] == *str) {	// 迷宫中当前的字符匹配word中当前字符
		str++;					// 指针指向下一个要匹配的字符
		if(dfs(i-1,j) || dfs(i+1,j) 
		   || dfs(i,j+1) || dfs(i,j-1)) // 搜索该位置上下左右的点
			return true;				// 如果有其中一条路径搜索到，返回true
		str--;							// 没有搜索到，将str往前推移，搜索其他方向路径
	}

	map[i][j]--; //没有搜索到，不能标志该点为正确路径的点，重新标志位0
	return false;
}

int main()
{
	int i, j;
	bool flag;
	
	while(cin >> m >> n) {
		cin >> word;
		for(i = 0; i < m; i++){
			for(j = 0; j < n; j++) {
				cin >> maze[i][j];
			}
		}

		flag = false;
		memset(map, 0, sizeof(map));
		
		for(i = 0; i < m; i++){
			for(j = 0; j < n; j++) {
				if(maze[i][j] == word[0]) {
					str = word;
					flag = dfs(i, j);
					
					if(flag == true)
						break;
				}
			}
			
			if(flag == true)
				break;
		}
		
		if(flag)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	
	return 0;
}
