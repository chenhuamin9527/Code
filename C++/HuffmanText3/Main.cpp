// HuffmanText3.cpp: 定义应用程序的入口点。
//

#include "Huffman.h"
#include"Compress.h"
using namespace std;

int main() {
	cout << "==========Huffman文件压缩==========" << endl;
	char name[100];
	cout << "请输入文件名： ";
	cin >> name;
	Compress(name);
	return 0;
}
