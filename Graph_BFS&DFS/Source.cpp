#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 20;

struct Node {
	int dinhKe;
	int trongSo;
	Node* link;
};

struct MaTranKe {
	int mtk[MAX][MAX];
	int soDinh;
};

struct DanhSachKe {
	Node* dsk[MAX];
	int soDinh;
};

bool docMaTranKe(const char* file, MaTranKe& mt) {
	FILE* f = fopen(file, "rt");
	if (f == NULL) return false;
	fscanf(f, "%d", &mt.soDinh);
	for (int i = 0; i < mt.soDinh; i++) {
		for (int j = 0; j < mt.soDinh; j++) {
			fscanf(f, "%d", &mt.mtk[i][j]);
		}
	}
	fclose(f);
	return true;
}

void xuatMaTranKe(MaTranKe mt) {
	for (int i = 0; i < mt.soDinh; i++)
	{
		cout << endl;
		for (int j = 0; j < mt.soDinh; j++) {
			cout << mt.mtk[i][j] << " ";
		}
	}
}

bool docDanhSach(const char* fileName, DanhSachKe& ds) {
	FILE* f = fopen(fileName, "rt");
	if (f == NULL)
		return false;

	for (int i = 0; i < MAX; i++)
	{
		ds.dsk[i] = NULL;
	}

	fscanf(f, "%d", &ds.soDinh);

	for (int i = 0; i < ds.soDinh; i++)
	{
		int soDinhKe;
		fscanf(f, "%d", &soDinhKe);
		for (int j = 0; j < soDinhKe; j++)
		{
			Node* p = new Node;
			fscanf(f, "%d%d", &p->dinhKe, &p->trongSo);
			p->link = NULL;
			if (ds.dsk[i] == NULL)
				ds.dsk[i] = p;
			else {
				Node* t = ds.dsk[i];
				while (t->link != NULL) {
					t = t->link;
				}
				t->link = p;
			}
		}
	}
	fclose(f);
	return true;
}

void xuatDanhSach(DanhSachKe ds) {
	for (int i = 0; i < ds.soDinh; i++)
	{
		cout << "\n(" << i << "): ";
		Node* p = ds.dsk[i];
		while (p != NULL) {
			cout << "(" << p->dinhKe << "," << p->trongSo << ")" << " ";
			p = p->link;
		}
	}
}

void BFS_MT(int dinhBatDau, MaTranKe mt) {
	vector<bool> visited(mt.soDinh, false);
	queue<int> hangDoi;

	hangDoi.push(dinhBatDau);
	visited[dinhBatDau] = true;

	while (hangDoi.empty() == false) {
		int v = hangDoi.front();
		hangDoi.pop();
		cout << v << " ";

		for (int i = 0; i < mt.soDinh; i++)
		{
			if (mt.mtk[v][i] != 0 && visited[i] == false) {
				hangDoi.push(i);
				visited[i] = true;
			}
		}
	}
}


vector<bool>visited_MT(9, false);
void DFS_MT(int dinhBatDau, MaTranKe mt) {
	cout << dinhBatDau << " ";
	visited_MT[dinhBatDau] = true;

	for (int i = 0; i < mt.soDinh; i++)
	{
		if (mt.mtk[dinhBatDau][i] != 0 && visited_MT[i] == false)
			DFS_MT(i, mt);
	}
}

void BFS_DS(int dinhBatDau, DanhSachKe ds) {
	vector<bool> visited(ds.soDinh, false);
	queue<int> hangDoi;

	hangDoi.push(dinhBatDau);
	visited[dinhBatDau] = true;

	while (hangDoi.empty() == false) {
		int v = hangDoi.front();
		hangDoi.pop();
		cout << v << " ";

		Node* p = ds.dsk[v];
		while (p) {
			if (visited[p->dinhKe] == false) {
				hangDoi.push(p->dinhKe);
				visited[p->dinhKe] = true;
			}
			p = p->link;
		}
	}
}

vector<bool>visited_DS(9, false);
void DFS_DS(int dinhBatDau, DanhSachKe ds) {
	cout << dinhBatDau << " ";
	visited_DS[dinhBatDau] = true;

	Node* p = ds.dsk[dinhBatDau];
	while (p) {
		if (visited_DS[p->dinhKe] == false)
			DFS_DS(p->dinhKe, ds);
		p = p->link;
	}
}

int main() {
	DanhSachKe DSK_Co_Huong;
	if (docDanhSach("DSK_CoHuong.txt", DSK_Co_Huong)) {
		cout << "DANH SACH KE CO HUONG:";
		xuatDanhSach(DSK_Co_Huong);

		int dinhBatDau;
		do {
			cout << "\n\nNhap dinh bat dau duyet BFS: ";
			cin >> dinhBatDau;
		} while (dinhBatDau < 0 || dinhBatDau >= DSK_Co_Huong.soDinh);

		cout << "BFS cua danh sach ke co huong: "; BFS_DS(dinhBatDau, DSK_Co_Huong);
		
		cout << "\n\n";

		int dinhBatDauDFS;
		do {
			cout << "\nNhap dinh bat dau duyet DFS: ";
			cin >> dinhBatDauDFS;
		} while (dinhBatDauDFS < 0 || dinhBatDauDFS >= DSK_Co_Huong.soDinh);
		cout << "DFS cua ma tran co huong: "; DFS_DS(dinhBatDauDFS, DSK_Co_Huong);

	}
	else
		cout << "\nKhong doc duoc danh sach!!!";

	cout << "\n\n--------------------------------------------------------------------------------------------\n\n";

	MaTranKe MTK_Co_Huong;
	if (docMaTranKe("MTK_CoHuong.txt", MTK_Co_Huong)) {
		cout << "MA TRAN KE CO HUONG: ";
		xuatMaTranKe(MTK_Co_Huong);

		int dinhBatDauBFS;
		do {
			cout << "\n\nNhap dinh bat dau duyet BFS: ";
			cin >> dinhBatDauBFS;
		} while (dinhBatDauBFS < 0 || dinhBatDauBFS >= MTK_Co_Huong.soDinh);

		cout << "BFS cua ma tran co huong: "; BFS_MT(dinhBatDauBFS, MTK_Co_Huong);

		cout << "\n\n";

		int dinhBatDauDFS;
		do {
			cout << "\nNhap dinh bat dau duyet DFS: ";
			cin >> dinhBatDauDFS;
		} while (dinhBatDauDFS < 0 || dinhBatDauDFS >= MTK_Co_Huong.soDinh);
		cout << "BFS cua ma tran co huong: "; DFS_MT(dinhBatDauDFS, MTK_Co_Huong);
		
	}
	else
		cout << "\nKhong doc duoc ma tran!!!";


	cout << "\n\n";
	return 0;
}