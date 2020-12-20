#include<iostream>
#include"Compress.h"
#include"Unpack.h"
using namespace std;
void choose()
{
    cout<<"------------"<<endl;
    cout<<"1.压缩文件."<<endl;
    cout<<"2.解压文件."<<endl;
    cout<<"3.退出."<<endl;
    cout<<"------------"<<endl;
}
int main()
{
    int choice;
    choose();
    while(cin>>choice){
        if(choice==1){
            Compress test;
            test.ReadFile();
            test.start();
        }
        else if(choice==2){
            Unpack test2;
            test2.ReadFile();
            test2.start();
        }
        else{
            exit(0);
        }
        choose();
    }

    return 0;
}
