// HuffmanText2.cpp: 定义应用程序的入口点。
//

#include "HuffmanText2.h"
#include<stdlib.h>
using namespace std;

int main() {
	int choice;
	char path[50];
	cout << "/********** 欢迎使用基于Huffman编码的文件压缩与解压 **********/" << endl;
	while (true) {
		cout << "压缩文件 [1]" << endl;
		cout << "解压文件 [2]" << endl;
		cout << "退出程序 [3]" << endl;
		while (true) {
			cout << "请输入操作 > ";
			cin >> choice;
			if (choice < 1 || choice >3)
				cout << "无效输入！\n" << endl;
			else
				cin.get();
			break;
		}
		switch (choice) {
		case 1:
			cout << "输入待压缩文件路径 > ";
			cin.get(path, 50);
			compressFile(path, "F:/testCode.bin", "F:/testCompress.txt");
			break;
		case 2:
			cout << "输入待解压文件路径 > ";
			cin.get(path, 50);
			uncompressFile(path, "F:/testCode.bin", "F:/testUncompress.txt");
			break;
		case 3:
			system("pause");
			return 0;
		default:
			cout << "路径错误！" << endl;
			break;
		}
		cout << endl;
	}
}

