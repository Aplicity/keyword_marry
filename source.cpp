#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <cctype>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

const int MaxN = 1000;
int nkey, totNode, root;
map <string, bool> vis;
char s[MaxN + 5];
struct TREE {
	int left, right;
	string str;
}tree[MaxN + 5];

void Insert(int nr, string str)
{
	if (str == tree[nr].str) return;	//如果此关键字之前有插入过，那么忽略
	else if (str < tree[nr].str) {	//如果比当前根节点的字典序小，那么走左子树
		if (tree[nr].left == -1) {	//左子树为空，那么新建节点
			tree[nr].left = ++totNode;
			tree[tree[nr].left].str = str;
			return;
		}
		else Insert(tree[nr].left, str);	//如果不空，那么递归下去
	}
	else {	//如果大于等于当前节点的字典序，那么走右子树
		if (tree[nr].right == -1) {	//右子树为空，那么新建节点
			tree[nr].right = ++totNode;
			tree[tree[nr].right].str = str;
			return;
		}
		else Insert(tree[nr].right, str);	//如果不空，那么递归下去
	}
}

void BuildTree()	//建树函数
{
	freopen("keys.txt", "r", stdin);	//读入关键字文件	
	scanf("%d", &nkey); totNode = 0; vis.clear(); 
	for (int i = 0; i <= MaxN; i++) {	//对树进行初始化，值为空树
		tree[i].left = tree[i].right = -1;
		tree[i].str = "";
	}
	root = -1;
	for (int i = 1; i <= nkey; i++) {
		string str;
		cin >> str;		//读入当前关键字
		for (int j = 0; j < str.length(); j++)	//调整当前关键字为全小写 
			str[j] = tolower(str[j]);	//这样才能做到不区分大小写，程序更智能
		if (root == -1) {	//如果当前为空树，那么直接塞到根节点上
			root = 0;
			tree[root].str = str;
		}
		else Insert(root, str);	//如果当前树非空，那么直接插入
	}		
	fclose(stdin);
}

bool Find(int nr, string str)	//寻找当前单词是否出现在关键字中
{
	//cout << tree[nr].str << " " << str << endl;
	if (tree[nr].str == str) return true;	//如果相等那么返回找到
	else if (str < tree[nr].str) {	//如果小于当前节点，那么走左子树
		if (tree[nr].left == -1) return false;
		else return Find(tree[nr].left, str);
	}
	else {
		if (tree[nr].right == -1) return false;//否则走右子树
		else return Find(tree[nr].right, str);
	}
}

void Dfs(int root)
{
	if (root == -1) return ;
	Dfs(tree[root].left);
	cout << tree[root].str << endl;
	Dfs(tree[root].right);
}

void Solve()
{
	//Dfs(root);
	freopen("article.txt", "r", stdin);
	int cnt = 0;
	while (~scanf("%s", s)) {
		string str = "";
		for (int i = 0; i < strlen(s); i++) str += s[i];	//读入当前单词
		for (int i = 0; i < strlen(s); i++) str[i] = tolower(str[i]);
		if (!vis[str] && Find(root, str)) {	//判断是否能找到，并且是否之前找过
			vis[str] = true;	//找过的单词就不用再找了
			cnt++;	//记录关键词一共匹配上了多少个
		}
	}
	printf("关键词的匹配率：%.2lf%%\n", cnt * 100.00 / nkey);
	fclose(stdin);
}

int main()
{
	freopen("out.txt", "w", stdout);
	BuildTree();
	Solve();
	fclose(stdout);
	return 0;
}
