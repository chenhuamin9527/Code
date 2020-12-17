#include <iostream>
using namespace std;
#include <stdlib.h>  
#include <time.h>
const int Max = 10;   

int a[Max + 1] = {0};
void Creat( );

void Creat( )
{
	srand(time(NULL));      
	for (int i = 1; i <= Max; i++)
		a[i] = 1 + rand( ) % Max; 
}

int main( )
{
    int k;
	Creat( );
	for (int i = 1; i <= Max; i++)
		cout<<a[i]<<"  ";
	cout<<endl;
	k = 1 + rand( ) % Max;

	return 0;
}