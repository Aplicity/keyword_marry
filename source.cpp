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
	if (str == tree[nr].str) return;	//����˹ؼ���֮ǰ�в��������ô����
	else if (str < tree[nr].str) {	//����ȵ�ǰ���ڵ���ֵ���С����ô��������
		if (tree[nr].left == -1) {	//������Ϊ�գ���ô�½��ڵ�
			tree[nr].left = ++totNode;
			tree[tree[nr].left].str = str;
			return;
		}
		else Insert(tree[nr].left, str);	//������գ���ô�ݹ���ȥ
	}
	else {	//������ڵ��ڵ�ǰ�ڵ���ֵ�����ô��������
		if (tree[nr].right == -1) {	//������Ϊ�գ���ô�½��ڵ�
			tree[nr].right = ++totNode;
			tree[tree[nr].right].str = str;
			return;
		}
		else Insert(tree[nr].right, str);	//������գ���ô�ݹ���ȥ
	}
}

void BuildTree()	//��������
{
	freopen("keys.txt", "r", stdin);	//����ؼ����ļ�	
	scanf("%d", &nkey); totNode = 0; vis.clear(); 
	for (int i = 0; i <= MaxN; i++) {	//�������г�ʼ����ֵΪ����
		tree[i].left = tree[i].right = -1;
		tree[i].str = "";
	}
	root = -1;
	for (int i = 1; i <= nkey; i++) {
		string str;
		cin >> str;		//���뵱ǰ�ؼ���
		for (int j = 0; j < str.length(); j++)	//������ǰ�ؼ���ΪȫСд 
			str[j] = tolower(str[j]);	//�����������������ִ�Сд�����������
		if (root == -1) {	//�����ǰΪ��������ôֱ���������ڵ���
			root = 0;
			tree[root].str = str;
		}
		else Insert(root, str);	//�����ǰ���ǿգ���ôֱ�Ӳ���
	}		
	fclose(stdin);
}

bool Find(int nr, string str)	//Ѱ�ҵ�ǰ�����Ƿ�����ڹؼ�����
{
	//cout << tree[nr].str << " " << str << endl;
	if (tree[nr].str == str) return true;	//��������ô�����ҵ�
	else if (str < tree[nr].str) {	//���С�ڵ�ǰ�ڵ㣬��ô��������
		if (tree[nr].left == -1) return false;
		else return Find(tree[nr].left, str);
	}
	else {
		if (tree[nr].right == -1) return false;//������������
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
		for (int i = 0; i < strlen(s); i++) str += s[i];	//���뵱ǰ����
		for (int i = 0; i < strlen(s); i++) str[i] = tolower(str[i]);
		if (!vis[str] && Find(root, str)) {	//�ж��Ƿ����ҵ��������Ƿ�֮ǰ�ҹ�
			vis[str] = true;	//�ҹ��ĵ��ʾͲ���������
			cnt++;	//��¼�ؼ���һ��ƥ�����˶��ٸ�
		}
	}
	printf("�ؼ��ʵ�ƥ���ʣ�%.2lf%%\n", cnt * 100.00 / nkey);
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
