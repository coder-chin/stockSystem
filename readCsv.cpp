#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	vector<vector<int>> arr;
	ifstream fp("60֧��Ʊ��Ϣ2.csv");
	string line;
	
	getline(fp, line);
	while(getline(fp, line)) {
		cout << line << endl;  //���ŷָ� 
	}
	return 0;
}

// https://www.jianshu.com/p/1172e2de7a7a
