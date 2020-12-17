// HuffmanText2.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once
#include <iostream>  
#include <string>  
using namespace std;

//全局变量，重构Huffman树时需要
int leafArrIndex = 0;
int strIndex = 0;
int nodeIndex = 0;

/*Huffman结点*/
class TreeNode {
public:
	unsigned char it;                            //结点元素                 
	double weight;                              //结点权重
	int parent, lchild, rchild;                 //结点的父结点及左右子结点
	TreeNode() {
		parent = lchild = rchild = -1;
	}
	TreeNode(const unsigned char& data, const double& wt) {
		it = data;
		weight = wt;
		parent = lchild = rchild = -1;
	}
};

/*编码类 存放每个字母的编码*/
class Code {
public:
	char* ptr;
	const int length;
	Code() : length(20) { ptr = new char[length]; }
	~Code() { delete[] ptr; }
};

/*Huffman树*/
class HuffmanTree {
private:
	int maxSize;                                                                 //数组最大值  
	int findPosition(const unsigned char&) const;          //返回字符在arrayTree[]中的位置 
	void insert(const unsigned char&, const double&);  //插入结点  
	void buildHuffmanTree();                                           //创建哈夫曼树  
	void writeCodeToFile(const char*);                           //将Huffman树存储到树信息文件中   
	void writeTreeStructureToFile(const int&, FILE*);     //将树结构信息存储到树信息文件中
	void writeLeafToFile(const int&, FILE*);                    //将叶结点信息存储到树信息文件中

public:
	int currsize;                   //当前数组大小
	TreeNode* arrayTree;   //哈夫曼结点数组   
	Code* codeArray;         //存放每个叶结点的编码，大小为currsize  

	HuffmanTree() {
		maxSize = 1000;
		arrayTree = new TreeNode[maxSize];
		currsize = 0;
	}

	void run(const char*, const char*);                                              //编码用，建树 编码 写入树信息文件
	void reBuildHuffmanTree(const unsigned char*, const int*, int); //解码用，根据树信息文件重建Huffman树  
	void createHuffmanCode();                                                         //编解码均可用，创建Huffman编码   
	void reBuildArray(char**, unsigned char*, int);                         //解码用，重建结点数组
};

/*run函数的实现*/
void HuffmanTree::run(const char* inFilename, const char* outFilename) {
	FILE* fo;
	fopen_s(&fo, inFilename, "rb");                        //读入待压缩文件  读取二进制文件
	if (fo == NULL) {
		cerr << " Can not open！" << endl;
		exit(1);
	}
	unsigned char ch = fgetc(fo);                           //读取一个字符
	int pos;

	while (!feof(fo)) {                                              // 从文件当中读入字符 直到文件结束，并且统计字符个数
		pos = findPosition(ch);
		if (pos != -1)
			arrayTree[pos].weight++;
		else
			insert(ch, 1);                                             //新插入一个 权重为1
		ch = fgetc(fo);
	}
	buildHuffmanTree();                   //构造huffman树  
	createHuffmanCode();               //对统计字符进行编码  
	writeCodeToFile(outFilename); //将编码表存入文件  
	fclose(fo);
}

/*插入结点*/
void HuffmanTree::insert(const unsigned char& data, const double& wt) {
	if (2 * currsize - 1 > maxSize) return;
	arrayTree[currsize].it = data;
	arrayTree[currsize].weight = wt;
	currsize++;
}

/*找到字符ch在arrayTree[]中的位置*/
int HuffmanTree::findPosition(const unsigned char& ch) const {
	for (int i = 0; i < currsize; i++)
		if (arrayTree[i].it == ch)
			return i;
	return -1;
}

/*压缩用  构造huffmanTree*/
void HuffmanTree::buildHuffmanTree() {
	int i = currsize;
	int k;
	double wt1, wt2;
	int lnode = 0, rnode = 0;
	while (i < 2 * currsize - 1) {
		wt1 = wt2 = numeric_limits<double>::max();     //返回编译器允许的 double 型数的最大值
		k = 0;
		while (k < i) {
			if (arrayTree[k].parent == -1) {
				if (arrayTree[k].weight < wt1) {
					wt2 = wt1;
					rnode = lnode;
					wt1 = arrayTree[k].weight;                      //将 wt1 置为最小权重
					lnode = k;
				}
				else if (arrayTree[k].weight < wt2) {
					wt2 = arrayTree[k].weight;                      //将 wt2 置为第二小的
					rnode = k;
				}
			}
			k++;
		}
		arrayTree[i].weight = arrayTree[lnode].weight + arrayTree[rnode].weight;
		arrayTree[i].lchild = lnode;
		arrayTree[i].rchild = rnode;
		arrayTree[lnode].parent = arrayTree[rnode].parent = i;
		i++;
	}
}

/*得到每种叶子结点的具体编码*/
void HuffmanTree::createHuffmanCode() {
	char tempCodeArray[100];                        //存放临时编码（初始倒序的编码）
	codeArray = new Code[currsize * 2 - 1];   //存放所有字符的编码
	int i = 0;
	int Len = currsize * 2 - 1;                           //全部结点个数
	int k, n, m, t;
	while (i < Len) {
		k = arrayTree[i].parent;
		n = 0;
		m = i;
		while (k != -1 && k < Len) {
			if (arrayTree[k].lchild == m)
				tempCodeArray[n++] = '0';         //为左子树时添加 0
			else if (arrayTree[k].rchild == m)
				tempCodeArray[n++] = '1';         //为右子树时添加 1

			m = k;
			k = arrayTree[m].parent;
		}
		for (t = 0; t < n; t++) {                        //使 codeArray 存放正确顺序的编码
			codeArray[i].ptr[t] = tempCodeArray[n - 1 - t];
		}
		codeArray[i].ptr[n] = '\0';
		i++;
	}
}

/*压缩用 将哈夫曼树写入文件*/
void HuffmanTree::writeCodeToFile(const char* outFilename) {
	FILE* fw;
	fopen_s(&fw, outFilename, "wb");
	fprintf(fw, "%d ", currsize * 2 - 1);                   //写入所有结点个数
	writeTreeStructureToFile(currsize * 2 - 2, fw); //从根结点写起，根结点保存在arrayTree最后
	fprintf(fw, " ");
	writeLeafToFile(currsize * 2 - 2, fw);               //从根结点起遍历，写入叶节点字符ASCII码
	fclose(fw);
}

/*压缩用  将哈夫曼树结构写入文件*/
void HuffmanTree::writeTreeStructureToFile(const int& num, FILE* fw) {
	if (arrayTree[num].lchild == -1) {
		fprintf(fw, "0");                         //根据树的顺序表示法 叶节点为0
		return;
	}
	else
		fprintf(fw, "1");                         // 内部子节点为1

	writeTreeStructureToFile(arrayTree[num].lchild, fw);
	writeTreeStructureToFile(arrayTree[num].rchild, fw);
}

/*压缩用 将叶节点信息写入文件*/
void HuffmanTree::writeLeafToFile(const int& num, FILE* fw) {
	if (arrayTree[num].lchild == -1) {          // 根据其为满二叉树的特性只判断左子树即可
		fprintf(fw, "%d ", arrayTree[num].it); //叶结点对应字母的ASCII码
		return;
	}
	writeLeafToFile(arrayTree[num].lchild, fw);
	writeLeafToFile(arrayTree[num].rchild, fw);
}

/*压缩文件*/
void compressFile(const char* sourceFilename, const char* codeFilename, const char* geneFilename) {
	HuffmanTree tree;
	tree.run(sourceFilename, codeFilename);
	FILE* fo;
	fopen_s(&fo, sourceFilename, "rb");
	FILE* fw;
	fopen_s(&fw, geneFilename, "wb");
	if (fo == NULL || fw == NULL) {
		cout << "文件打开失败!" << endl;
		return;
	}
	int decimal = 0;                            //将二进制转化为十进制
	int i, j, k = 0;
	int bits = 0;                                  //字符编码位数
	int temp[10000];
	memset(temp, 0, sizeof(temp));

	while (!feof(fo)) {
		decimal = 0;
		unsigned char one_byte = fgetc(fo);
		for (i = 0; i < tree.currsize; i++) {
			if (one_byte == tree.arrayTree[i].it) {
				bits += strlen(tree.codeArray[i].ptr);
				int len = strlen(tree.codeArray[i].ptr);
				if (bits < 8) {
					for (j = 0; j < len; j++)
						temp[k++] = tree.codeArray[i].ptr[j] - '0';
				}
				else if (bits >= 8) {
					for (j = 0; k < 8; j++)
						temp[k++] = tree.codeArray[i].ptr[j] - '0';
					for (; j < len; j++)
						temp[k++] = tree.codeArray[i].ptr[j] - '0';

					decimal += temp[0] * 128 + temp[1] * 64 + temp[2] * 32 + temp[3] * 16 + temp[4] * 8 + temp[5] * 4 + temp[6] * 2 + temp[7] * 1;

					for (j = 0; j < 8; j++)
						temp[j] = 0;                       //将已处理部分置为0，方便后面的数据使用数组空间

					for (j = 8; j < k; j++)
						temp[j - 8] = temp[j];        //将大于8位的部分向前移动
					k = bits = j - 8;

					unsigned char c = decimal;   //将不足 8 的倍数的部分抛弃，达到压缩作用
					fputc(c, fw);
					fflush(fw);
				}
			}
		}
	}
	if (bits) {             //循环结束后 防止还有未凑够 8 位的
		decimal += temp[0] * 128 + temp[1] * 64 + temp[2] * 32 + temp[3] * 16 + temp[4] * 8 + temp[5] * 4 + temp[6] * 2 + temp[7] * 1;
		unsigned char c = decimal;
		fputc(c, fw);
		fflush(fw);
	}
	fclose(fw);
	fclose(fo);
	cout << "压缩完成!" << endl;
}

/*解压用 将信息写入类的数组中，与压缩时格式保持一致*/
void HuffmanTree::reBuildArray(char** HC, unsigned char* value, int Num) {
	int j = 0;
	for (int i = 0; i < Num; i++) {
		if (arrayTree[i].it != NULL) {        //当信息不为空，即当其是叶节点时
			HC[j] = codeArray[i].ptr;        //写入Huffman编码
			value[j] = arrayTree[i].it;        //写入叶节点信息
			j++;
		}
	}
}

/*由信息构建Huffman树 解压时需要*/
void HuffmanTree::reBuildHuffmanTree(const unsigned char* str, const int* arr, int i) {
	if (str[strIndex] != '\0') {
		if (str[strIndex] == '1') {                                           //判断它是子节点
			strIndex++;
			int m = nodeIndex;
			int n = nodeIndex + 1;
			arrayTree[i].lchild = m;                                       //定义其左节点
			arrayTree[i].rchild = n;                                        //定义其右节点
			arrayTree[m].parent = arrayTree[n].parent = i;  //左右节点的根节点
			nodeIndex += 2;
			arrayTree[i].it = NULL;                                        //将父节点的信息设为空

			reBuildHuffmanTree(str, arr, m);
			reBuildHuffmanTree(str, arr, n);
		}
		else {                                                                      //判断它为叶节点
			strIndex++;
			arrayTree[i].it = arr[leafArrIndex];                     //写入其字符信息
			leafArrIndex++;
			return;
		}
	}
	else return;
}

/*解压文件*/
void uncompressFile(const char* geneFilename, const char* codeFilename, const char* backFilename) {
	int Len = 0;                                      //从树信息文件读取的所有结点个数
	unsigned char treeStruCode[255];  //从树信息文件读取的树结构编码
	int leafASCII[255] = { 0 };                //从树信息文件读取的叶的字符的ASCII码
	int i = 0;
	HuffmanTree HT;

	FILE* fr;
	fopen_s(&fr, codeFilename, "rb");
	fscanf_s(fr, "%d", &Len);                  //从树信息文件读取所有结点的个数保存在 len 中
	fscanf_s(fr, "%s", treeStruCode, sizeof(treeStruCode));
	while (fscanf_s(fr, "%d", &leafASCII[i]) != EOF)    //判断是否读完所有叶结点
		i++;

	int cur = (Len + 1) / 2;
	HT.currsize = cur;
	HT.reBuildHuffmanTree(treeStruCode, leafASCII, Len - 1);   //根结点在 arrayTree 的最后

	HT.createHuffmanCode();

	char* HC[200] = { 0 };
	unsigned char value[200] = { 0 };
	HT.reBuildArray(HC, value, Len);

	FILE* fo;
	fopen_s(&fo, geneFilename, "rb");
	FILE* fw;
	fopen_s(&fw, backFilename, "wb");
	if (fo == NULL || fw == NULL) {
		printf("文件打开失败！");
		return;
	}

	int decToBinInt[10];                 //保存 从压缩文件读取的十进制转化的二进制的整数形式
	char decToBinChar[1000];       //保存 从压缩文件读取的十进制转化的二进制的字符形式
	i = 0;
	int j = 0, k, temp = 0;
	while (!feof(fo)) {
		int data = fgetc(fo);
		if (data == -1) break;

		memset(decToBinInt, 0, sizeof(decToBinInt));
		i = 0;
		while (data) {                                  //将读取的压缩后的十进制数转化为二进制
			decToBinInt[i++] = data % 2;
			data = data / 2;
		}

		i = temp;
		for (k = 7; k >= 0; i++, k--) {     //将二进制数字转化为字符
			if (decToBinInt[k])
				decToBinChar[i] = '1';
			else
				decToBinChar[i] = '0';

			decToBinChar[i + 1] = '\0';

			for (j = 0; j < HT.currsize; j++) {
				if (strcmp(decToBinChar, HC[j]) == 0) {
					fputc(value[j], fw);
					fflush(fw);
					i = -1;
				}
			}
		}
		if (i) temp = i;
		else temp = 0;
	}
	fclose(fw);
	fclose(fo);
	fclose(fr);
	cout << "解压完成!" << endl;
}

