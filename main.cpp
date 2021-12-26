#include "general.h"

vector<hashList> hashTable(HASHLENGTH);  //�����ϣ��
vector<StockInfo> stocks(200);           //�洢200֧��Ʊ�Ļ�����Ϣ�;����Ʊ��Ϣ
vector<vector<edge>> e;                  //�ڽӱ� 
vector<int> d;                           //�ⲿ�㵽�ڲ������̾��� 
vector<int> vis;                         //�������
vector<fundPortfolio> ret;               //��С���������еĻ������
vector<score> scores;                    //���ֺ�����
vector<int> p;                           //���鼯���� 

int main()
{
	readStockInfo();   //���ļ����������� 
	string choice;

	while(true) {
		system("cls");
		cout << "============================================================" << endl;
		cout << "=======      ��ӭʹ�ù�Ʊ��ѯ�����ϵͳ V2.0         =======" << endl;
		cout << "=======                                              =======" << endl;
		cout << "=======              1. ��ѯ����                     =======" << endl;
		cout << "=======              2. ��������                     =======" << endl;
		cout << "=======              3. �˳�ϵͳ                     =======" << endl;
		cout << "=======                                              =======" << endl;
		cout << "============================================================" << endl;
		
		cout << "��������Ҫ���еĲ���(���벻�Ϸ����ݽ�����ˢ��ҳ��): ";
		cin >> choice;
		
		if(choice == "1") showSearchMenu();
		else if(choice == "2") showAnalyseMenu();
		else if(choice == "3") {
			cout << endl;
			cout << "��ӭ�´�ʹ�ã��˳���...." << endl;
			exit(0);
		}
	}
	return 0;
}

// ���ߺ��� 
int hashFun(string str) {
	int length = str.length();
	int sum = 0;
	
	for(int i = 0; i < length; i++) {
		sum += str[i];
	}
	
	return sum % 97;
}
double hashASL(vector<StockInfo> info, vector<hashList> list) {
	int num = info.size();
	double counter = 0;
	
	for(int i = 0; i < num; i++) {
		string name = info[i].stockCode;
		int index = hashFun(name);
		
		hashList stockNode = list[index]->next;
		counter++;
		
		while(stockNode) {
			if(stockNode->node.stockCode == name)  break;
			stockNode = stockNode->next;
			counter++;
		}
	}
	return counter/SIZE;
}
double bstASL(BinTree T, vector<StockInfo> info) {
	int num = info.size();
	
	double counter = 0;
	for(int i = 0; i < num; i++) {
		string code = info[i].stockCode;
		searchBST(T, code, counter);
	}
	
	return counter / num;
}
int encode(string str) {
	int length = str.length();
	int sum = 0;
	
	for(int i = 0; i < length; i++) {
		sum += str[i];
	}
	
	return sum;
}
bool kmp(string s, string t) {
	int m = t.length();
        int n = s.length();
        s = '0' + s;
        t = '0' + t;

        vector<int> next(m+1, 0);
        next[0] = -1;  //��ʼnext[0]==-1  next[1] = 0

        int j = 2, i = next[1];   //j���α꣬���������ƶ�  i�ǳ���Ϊj���ַ���ƥ��ǰ��ƥ�����󳤶� ʼ�յ���next[j]

        while(j <= m) {
            while(i!=-1 && t[i+1]!=t[j])  i = next[i];  //ƥ�䲻����һֱ����, ֱ��iΪ0

            if(i==-1) i = 0, j++;  //i���˵�0�Ļ���i=next[0]=-1, iҪ�ָ���0��j��������ɨ��

            else {    //next[j] = t[i+1]
                next[j] = i+1;
                i = next[j];
                j++;
            }
        }

        i = 1, j = 1;

        while(i<=n && j<=m) {
            while(j>=1 && t[j]!=s[i])  j = next[j-1]+1;  //��ƥ��Ļ��Ӵ��α���ƣ������α겻��

            if(!j) j = 1, i++;
            else i++, j++;
        }

        if(j<m) return false;  //jû�ߵ����˵��i�����ˣ�jû���� Ϊƥ��ɹ�

        else return true;
}
string format(int number) {
	string ret;
	if(number < 10) {
		ret = "0" + to_string(number);
	} else {
		ret = to_string(number);
	}
	
	return ret;
}
bool cmp(const fundPortfolio t1, const fundPortfolio t2) {
	if(t1.weight < t2.weight) return true;
	return false;
} 
bool cmpByScores(const fundPortfolio t1, const fundPortfolio t2) {
	if(t1.scoreSum > t2.scoreSum) return true;
	return false;
} 
int find(int x) {
	return x = p[x] ? x : p[x] = find(p[x]);
}

// �������
void showSearchMenu() {
	bool flag = true;
	while(flag) {
		system("cls");
		cout << "============================================================" << endl;
		cout << "=======     1. ���ڹ�ϣ��Ĺ�Ʊ������Ϣ��ѯ          =======" << endl;
  		cout << "=======     2. ����KMP�Ĺ�Ʊ��ַ��ѯ                 =======" << endl;
  		cout << "=======     3. ���ڶ����������Ĺ�Ʊ������Ϣ��ѯ      =======" << endl;
  		cout << "=======     4. ���ڵ�����Ĺ�Ʊ�۸���Ϣ��ѯ          =======" << endl;
  		cout << "=======     5. �����ϼ��˵�                          =======" << endl;
  		cout << "============================================================" << endl;
  		cout << endl;
  		
  		cout << "��������Ҫִ�еĹ��ܣ�";
  		int opt;  
		cin >> opt;
  		switch(opt) {
  			case 1:
  				searchBaseInfo();
  				break;
  			case 2:
  				searchWebsite();
  				break;
  			case 3:
  				searchByBST();
  				break;
  			case 4:
  				searchByLinkList();
  				break;
  			case 5:
  				flag = false;
  				break;
		}
	}
}
void showAnalyseMenu() {
	bool flag = true;
	while(flag) {
		system("cls");
		cout << "============================================================" << endl;
		cout << "=======     1. ����ֱ�Ӳ�������Ĺ�Ʊ�۸����        =======" << endl;
  		cout << "=======     2. ���ڿ�������Ĺ�Ʊ�۸����            =======" << endl;
  		cout << "=======     3. ���ڼ�ѡ������Ĺ�Ʊ�۸����        =======" << endl;
  		cout << "=======     4. ����Floyd�Ĺ�Ʊ����Լ���             =======" << endl;
  		cout << "=======     5. ����Prim��С�������Ĺ�Ʊ����ɸѡ      =======" << endl;
		cout << "=======     6. ���ڶ���ͼ�Ĺ�Ʊ����ɸѡ              =======" << endl;
		cout << "=======     7. ����Kruskal��С�������Ĺ�Ʊ����ɸѡ   =======" << endl;
		cout << "=======     8. ���ڶ����������Ĺ�Ʊ������Ϣɾ��      =======" << endl;
  		cout << "=======     9. �����ϼ��˵�                          =======" << endl;
  		cout << "============================================================" << endl;
  		cout << endl;
  		
  		cout << "��������Ҫִ�еĹ��ܣ�";
  		int opt;  
		cin >> opt;
  		switch(opt) {
  			case 1:
  				analyseByInsertSort();
  				break;
  			case 2:
  				analyseByQuickSort();
  				break;
  			case 3:
  				analyseBySelectionSort();
  				break;
  			case 4:
  				analyseByFloyd();
  				break;
  			case 5:
  				analyseByPrim();
  				break;
  			case 6:
  				analyseByBigraph();
  				break;
  			case 7:
  				anylyseByKruskal();
  				break;
  			case 8:
  				deleteBSTNode();
  				break;
  			case 9:
  				flag = false;
  				break;
		}
	}
}

// ����ʵ�� 
// ¼���Ʊ������Ϣ 
void readStockInfo() {
 	ifstream in("��Ʊ������Ϣ����/A�ɹ�˾���.csv");   //��ȡ�ļ�, �����ļ��� 
 	string row;
 	
 	getline(in, row); 			//��һ���Թ�
 	
 	int i = 0;      			//��Ʊ������Ϣ�����±�
 	string path1 = "��Ʊ�ǵ�����/";
 	string path2 = ".txt";
 	string fullPath;
 	
 	while(getline(in, row)) {
	 //�ַ������Զ��ŷָ��
	 stringstream ss(row);  
	 string str;  //�൱��һ���м仺��
	 vector<string> lineArray;
	 
	 while(getline(ss, str, ',')) lineArray.push_back(str);
	 
	 stocks[i].stockCode = lineArray[0];
	 stocks[i].shortName = lineArray[1];
	 stocks[i].cate1 = lineArray[3];
	 stocks[i].cate2 = lineArray[4];
	 stocks[i].date = lineArray[7];
	 stocks[i].website = lineArray[12];
	 stocks[i].majorBusiness = lineArray[15];
	 stocks[i].businessScope = lineArray[16];
	 
	 fullPath = path1 + lineArray[0] + path2;  //�����ļ�·��
	 ifstream fp(fullPath);
	 string line;
	
	 getline(fp, line);  //������һ��
	 getline(fp, line);  //��ʽ��ȡ, ������ֻ�����һ�յ� 
	 
	 vector<string> arr;
	 istringstream s(line);
	 while(getline(s, str, ' '))  arr.push_back(str);
	 
	 stocks[i].recentInfo[0] = arr[1];
	 stocks[i].recentInfo[1] = arr[2];
	 stocks[i].recentInfo[2] = arr[8];
	 
	 stocks[i].detail = new changeData;
	 dataLink head = stocks[i].detail;
	 
	 head->date = arr[0];
	 head->openingPrice = arr[1];
	 head->closingPrice = arr[2];
	 head->changePercent = stod(arr[9], 0);
	 head->next = NULL;
	 
	//��ȡtxt�ļ���ÿһ�ж���Ҫ¼�룬�վ����Ӳ���
	 while(getline(fp, line)) {
		 vector<string> arr;
		 istringstream s(line);
	 	 while(getline(s, str, ' '))  arr.push_back(str);
	 	
	 	 dataLink node = new changeData;
	 	 node->date = arr[0];
		 node->openingPrice = arr[1];
		 node->closingPrice = arr[2];
		 node->changePercent = stod(arr[9], 0);
		 node->next = NULL;
		
		 head->next = node;
		 head = head->next;
	 }
	 i++;
	}
	
	for(int i = 0; i < 200; i++) {
		stocks[i].score = 0;
	}
	
	ifstream infile("��Ʊ������Ϣ����/60֧��Ʊ��Ϣ2.csv");
	string scope;
	
	getline(infile, scope);
	getline(infile, scope);   //����ǰ���� 
	
	score scoreNode;
	scores.push_back(scoreNode);  // Ŀ�������±��1��ʼ 
		
	while(getline(infile, scope)) {
		stringstream ss(scope);
		string str;
	
		vector<string> arr;
		while(getline(ss, str, ',')) arr.push_back(str);
		
		score scoreNode;
		scoreNode.name = arr[0];
		scoreNode.score = stod(arr[2], 0);
		scores.push_back(scoreNode);
		
		for(int i = 0; i < 200; i++) {
			if(stocks[i].stockCode == arr[1]) {
				stocks[i].score = stod(arr[2], 0);
				break;
			}
		}
	}   //stocks[200]����������������
	
	// ����ǵ����Ͷ�Ӧ������ 
	for(int i = 0; i < 200; i++) {
		dataLink head = stocks[i].detail;
		double maxChangePercent = head->changePercent;
		string date;
		while(head) {
			if(maxChangePercent < head->changePercent) {
				maxChangePercent = head->changePercent;
				date = head->date;
			}
			head = head->next;
		}
		stocks[i].maxChangePercent = maxChangePercent;
		stocks[i].maxDate = date;
	}
}
// ������ϣ�� 
void createHashTable() {
	//��ʼ����ϣ��
	for(int i = 0; i < HASHLENGTH; i++) {
		hashTable[i] = new hashNode;  //����ǵ�new  �ɹ����������� 
		hashTable[i]->next = NULL;  
	}
	
	for(int i = 0; i < SIZE; i++) {
		string str = stocks[i].stockCode;   //��ϣ�������Ĵ��� 
		int index = hashFun(str);
		
		if(!hashTable[index]->next) {       //������
			hashList insertNode = new hashNode;
			
			insertNode->node.stockCode = stocks[i].stockCode;
			insertNode->node.shortName = stocks[i].shortName;
			insertNode->node.cate1 = stocks[i].cate1;
			insertNode->node.cate2 = stocks[i].cate2;
			insertNode->node.date = stocks[i].date;
			insertNode->node.website = stocks[i].website;
			insertNode->node.majorBusiness = stocks[i].majorBusiness;
			insertNode->node.businessScope = stocks[i].businessScope;
			insertNode->next = NULL;
			
			hashTable[index]->next = insertNode;
		} 
		else {
			// ���ڣ�����  ͷ�巨
			hashList head = hashTable[index]->next;   // ��Ҫ���� 
			hashList insertNode = new hashNode;

			insertNode->node.stockCode = stocks[i].stockCode;
			insertNode->node.shortName = stocks[i].shortName;
			insertNode->node.cate1 = stocks[i].cate1;
			insertNode->node.cate2 = stocks[i].cate2;
			insertNode->node.date = stocks[i].date;
			insertNode->node.website = stocks[i].website;
			insertNode->node.majorBusiness = stocks[i].majorBusiness;
			insertNode->node.businessScope = stocks[i].businessScope;
			
			insertNode->next = head;
			hashTable[index]->next = insertNode;
		}
	}
}
// ��ϣ���һ�����Ϣ
void searchBaseInfo() {
	createHashTable();
	
	string number;
	int flag1 = 1;
	
	cout << "��������Ҫ��ѯ�Ĺ�Ʊ���루���磺cn_600519����";
	
	while(flag1 && cin >> number) {
		int index = hashFun(number);
		
		if(!hashTable[index]->next) {
			cout << "�����ڸù�Ʊ��" << endl;
		} 
		else {
			hashList stockNode = hashTable[index]->next;
			while(stockNode) {
				if(stockNode->node.stockCode == number) {
					cout << "���ҳɹ���" << endl;
					cout << "��Ʊ���ƣ�" << stockNode->node.shortName << endl;
					cout << "��Ʊ���룺" << stockNode->node.stockCode << endl;
					cout << "һ����ҵ��" << stockNode->node.cate1 << endl;
					cout << "������ҵ��" << stockNode->node.cate2 << endl;
					cout << "��Ӫҵ��" << stockNode->node.majorBusiness << endl;
					flag1 = 0;
					break;
				}
				stockNode = stockNode->next;
			}
			if(!flag1) cout << "���ҳɹ���ASLΪ��" << hashASL(stocks, hashTable) << endl;
			else cout << "�����ڸù�Ʊ������������" << endl;
		}
		
		int isBreak = 0;
		while(!isBreak) {
			cout << "��ȷ���Ƿ��������(yes/no): ";
			string isGo;
			cin >> isGo;
			if(isGo == "no") {
				flag1 = 0;
				isBreak = 1;
			}
			else if(isGo == "yes") {
				cout << "��������Ҫ��ѯ�Ĺ�Ʊ���루���磺cn_600519����";
				break;
			}
			else cout << "���벻�Ϸ������������룡" << endl;
		}	
	}
} 
// KMP��ַ����
void searchWebsite() {
	int isExit = 0;
	
	while(!isExit) {
		cout << "��������ַ�ؼ���: ";
		string keywords;
		cin >> keywords;
		
		int flag = 0;
		
		for(int i = 0; i < SIZE; i++) {
			if(kmp(stocks[i].website, keywords)) {
				cout << "ƥ��ɹ���\n\n"; 
				cout << "��Ʊ���ƣ�" << stocks[i].shortName << "   " << " ��Ʊ���룺" << 
				stocks[i].stockCode << endl << endl;
				flag = 1;
				break;
			}
		}
		
		if(!flag) cout << "��Ǹ�����޸���ַ�����Ϣ" << endl;
		
		int isBreak = 0;
		while(!isBreak) {
			cout << "��ȷ���Ƿ��������(yes/no): ";
			string isGo;
			cin >> isGo;
			if(isGo == "no") {
				isExit = 1;
				isBreak = 1;
			}
			else if(isGo == "yes") {
				cout << "��������ַ�ؼ��֣�";
				break;
			}
			else cout << "���벻�Ϸ������������룡" << endl;
		}	
	}	
}
// ���ڶ�����������ѯ 
void searchByBST() {
	BinTree T = NULL;
	
	createBST(T, stocks);
	// ������ϣ�
	
	int isExit = 0;
	while(!isExit) {
		string toSearch;
		cout << "������Ҫ��ѯ�Ĺ�Ʊ���룺";
		cin >> toSearch;
		
		double times = 0;
		BinTree node = searchBST(T, toSearch, times);
		if(!node) {    //����Ϊ�� 
			cout << "��ѯʧ�ܣ������ڸù�Ʊ��" << endl;
		} else {
			cout << "���һ�չ�Ʊ��Ϣ���£�" << endl; 
			cout << "���̼� " << node->data.recentInfo[0] << endl;
			cout << "���̼� " << node->data.recentInfo[1] << endl;
			cout << "�ǵ��� " << node->data.recentInfo[2] << endl;
			cout << "���ҳɹ���ASLΪ" << bstASL(T, stocks) << endl;
		}
		
		int isBreak = 0;
		while(!isBreak) {
			cout << "��ȷ���Ƿ��������(yes/no): ";
			string isGo;
			cin >> isGo;
			if(isGo == "no") {
				isExit = 1;
				isBreak = 1;
			}
			else if(isGo == "yes") {
				break;
			}
			else cout << "���벻�Ϸ������������룡" << endl;
		}	
	}
}
// ����BST
void createBST(BinTree &T, vector<StockInfo> stocksInfo) {
	for(int i = 0; i < SIZE; i++) {
		insertBST(T, i, stocksInfo);  // i�ǵڼ���
	}
}
// ����ڵ� 
void insertBST(BinTree& root, int i, vector<StockInfo> stocksInfo) {
	if(!root) {  // Ҷ�ӽ�� 
		root = new TNode;
		root->data = stocks[i];
		root->left = NULL;
		root->right = NULL;
	}
	else {
		if(stocks[i].stockCode < root->data.stockCode) {
			insertBST(root->left, i, stocksInfo);
		} else if(stocks[i].stockCode > root->data.stockCode) {
			insertBST(root->right, i, stocksInfo);
		}
	}
}
// ���ݹ�Ʊ�����ڶ���������������
BinTree searchBST(BinTree T, string key, double& times) {
	if(T == NULL || key == T->data.stockCode){
		times++;
		return T;
	}
    else if(key < T->data.stockCode) {  //�ݹ��������������
    	times++;
    	return searchBST(T->left, key, times);
	}        
    else {							    //�ݹ��������������
    	times++;
		return searchBST(T->right, key, times);
	}                                     
}
// ���ڵ�����Ĺ�Ʊ�۸���Ϣ��ѯ 
void searchByLinkList() {
	int isExit = 0;
	
	while(!isExit) {
		cout << "������Ҫ��ѯ�����ڣ�";
		string date;
		cin >> date;
		
		dataLink link = getLinkByDate(date);
	
		if(!link->next) cout << "�������ݲ����ڣ�" << endl;
		
		else {
			link = link->next;
			printf("%-10s%-10s%-10s%-10s%-10s\n", "��Ʊ����", "��Ʊ����", "���̼�", "���̼�", "�ǵ���");
			
			while(link) {
				printf("%-10s", link->stockCode.c_str());
				printf("%-10s", link->shortName.c_str());
				printf("%-10s", link->openingPrice.c_str());
				printf("%-10s", link->closingPrice.c_str());
				printf("%-10f", link->changePercent);
				printf("\n");
				link = link->next;
			}	
		}
		
		int isBreak = 0;
		while(!isBreak) {
			cout << "��ȷ���Ƿ��������(yes/no): ";
			string isGo;
			cin >> isGo;
			if(isGo == "no") {
				isExit = 1;
				isBreak = 1;
			}
			else if(isGo == "yes") {
				break;
			}
			else cout << "���벻�Ϸ������������룡" << endl;
		}	
	}
}
// �������ڻ�ȡ���й�Ʊ����Ĺ�Ʊ��Ϣ 
dataLink getLinkByDate(string date) {
	dataLink link = new changeData;
	link->next = NULL;
	dataLink p = link; //�α� 
	
	for(int i = 0; i < SIZE; i++) {
		dataLink head = stocks[i].detail; //�õ���Ԫ������� 
		while(head) {
			if(head->date == date) {
				dataLink node = new changeData;
				node->stockCode = stocks[i].stockCode;
				node->shortName = stocks[i].shortName;
				node->openingPrice = head->openingPrice;
				node->closingPrice = head->closingPrice;
				node->changePercent = head->changePercent;
				p->next = node;
				p = p->next;
				break;
			}
			head = head->next;
		}
	}
	
	return link;
}

// ����ֱ�Ӳ�����Ѫ�Ĺ�Ʊ�۸����
void analyseByInsertSort() {
	int isExit = 0;
	
	while(!isExit) {
		string date;
		cout << "�������ѯ���ڣ�"; 
		cin >> date;
		
		dataLink link = getLinkByDate(date);
		
		if(!link->next) {
			cout << "�������ݲ����ڣ�" << endl;
		} 
		else {
			cout << "1. ���ݿ��̼�����" << endl;
			cout << "2. �������̼�����" << endl;
			cout << "3. �����ǵ�������" << endl;
			cout << "����������ʽ��";
			int option;
			cin >> option;
			switch(option) {
				case 1:
					sortByOpeningPrice(link);
					break;
				case 2:
					sortByClosingPrice(link);
					break;
				case 3:
					sortByChangePercent(link);
					break;
			}
		}
		
		int isBreak = 0;
		while(!isBreak) {
			cout << "��ȷ���Ƿ����(yes/no): ";
			string isGo;
			cin >> isGo;
			if(isGo == "no") {
				isExit = 1;
				isBreak = 1;
			}
			else if(isGo == "yes") {
				break;
			}
			else cout << "���벻�Ϸ������������룡" << endl;
		}	
	}
}
// ���ݿ��̼�����
void sortByOpeningPrice(dataLink L) {
	dataLink p, pre, q;
	p = L->next->next;		 // �ȱ�����L�ĵڶ���Ԫ�أ���Ϊ��һ��Ҫ��L���ֻ��һ��Ԫ�ص������  
	L->next->next = NULL;	 // ��L���ֻ��һ��Ԫ�ص������
	
   // ��L�ĵڶ���Ԫ�ؿ�ʼ��������Lֱ����β 
	while(p){
		q = p->next;
		pre = L;	// ����pre������L
		
		while(pre->next !=NULL && stod(pre->next->openingPrice, 0) > stod(p->openingPrice, 0)) // ����pre��ָ��������L��ֱ���ҵ���p��Ľڵ� 
			pre = pre->next; 
		p->next = pre->next;
		pre->next = p;
		p = q;	
	}
	
	int index = 1;
	L = L->next;
	ofstream outfile("�۸���ǵ���������-���̼۽���.csv", ios::out);
	outfile << "���" << "," << "��Ʊ����" << "," << "��Ʊ����" << "," << "���̼�" << "," << "���̼�"
	<< "," << "�ǵ���" << endl;
	printf("%-4s%-10s%-10s%-10s%-10s%-10s\n", "���", "��Ʊ����", "��Ʊ����", "���̼�", "���̼�", "�ǵ���");
	
	while(L) {
		printf("%-4d", index);
		printf("%-10s", L->stockCode.c_str());
		printf("%-10s", L->shortName.c_str());
		printf("%-10s", L->openingPrice.c_str());
		printf("%-10s", L->closingPrice.c_str());
		printf("%-10f", L->changePercent);
		printf("\n");
		
		outfile << index << "," << L->stockCode << "," << L->shortName << "," << L->openingPrice << ","
		<< L->closingPrice << "," << L->changePercent << endl;
		
		L = L->next;
		index++;
	}
	outfile.close();
}
// �������̼�����
void sortByClosingPrice(dataLink L) {
	dataLink p, pre, q;
	p = L->next->next;		 // �ȱ�����L�ĵڶ���Ԫ�أ���Ϊ��һ��Ҫ��L���ֻ��һ��Ԫ�ص������  
	L->next->next = NULL;	 // ��L���ֻ��һ��Ԫ�ص������
	
	// ��L�ĵڶ���Ԫ�ؿ�ʼ��������Lֱ����β 
	while(p){
		q = p->next;
		pre = L;	// ����pre������L��
		while(pre->next !=NULL && stod(pre->next->closingPrice, 0) > stod(p->closingPrice, 0)) // ����pre��ָ��������L��ֱ���ҵ���p��Ľڵ� 
			pre = pre->next; 
		p->next = pre->next;
		pre->next = p;
		p = q;	
	}
	
	int index = 1;
	L = L->next;
	ofstream outfile("�۸���ǵ���������-���̼۽���.csv", ios::out);
	outfile << "���" << "," << "��Ʊ����" << "," << "��Ʊ����" << "," << "���̼�" << "," << "���̼�"
	<< "," << "�ǵ���" << endl;
	printf("%-4s%-10s%-10s%-10s%-10s%-10s\n", "���", "��Ʊ����", "��Ʊ����", "���̼�", "���̼�", "�ǵ���");
	 
	while(L) {
		printf("%-4d", index);
		printf("%-10s", L->stockCode.c_str());
		printf("%-10s", L->shortName.c_str());
		printf("%-10s", L->openingPrice.c_str());
		printf("%-10s", L->closingPrice.c_str());
		printf("%-10f", L->changePercent);
		printf("\n");
		
		outfile << index << "," << L->stockCode << "," << L->shortName << "," << L->openingPrice << ","
		<< L->closingPrice << "," << L->changePercent << endl;
		
		L = L->next;
		index++;
	}
	outfile.close();
}
// �����ǵ�������
void sortByChangePercent(dataLink L) {
	dataLink p, pre, q;
	p = L->next->next;		// �ȱ�����L�ĵڶ���Ԫ�أ���Ϊ��һ��Ҫ��L���ֻ��һ��Ԫ�ص������  
	L->next->next = NULL;	// ��L���ֻ��һ��Ԫ�ص������
	
	// ��L�ĵڶ���Ԫ�ؿ�ʼ��������Lֱ����β 
	while(p){
		q = p->next;
		pre = L;	// ����pre������L��
		while(pre->next !=NULL && pre->next->changePercent > p->changePercent) // ����pre��ָ��������L��ֱ���ҵ���p��Ľڵ� 
			pre = pre->next; 
		p->next = pre->next;
		pre->next = p;
		p = q;	
	}
	
	int index = 1;
	L = L->next;
	ofstream outfile("�۸���ǵ���������-�ǵ�������.csv", ios::out);
	outfile << "���" << "," << "��Ʊ����" << "," << "��Ʊ����" << "," << "���̼�" << "," << "���̼�"
	<< "," << "�ǵ���" << endl;
	
	printf("%-4s%-10s%-10s%-10s%-10s%-10s\n", "���", "��Ʊ����", "��Ʊ����", "���̼�", "���̼�", "�ǵ���");
	while(L) {
		printf("%-4d", index);
		printf("%-10s", L->stockCode.c_str());
		printf("%-10s", L->shortName.c_str());
		printf("%-10s", L->openingPrice.c_str());
		printf("%-10s", L->closingPrice.c_str());
		printf("%-10f", L->changePercent);
		printf("\n");
		
		outfile << index << "," << L->stockCode << "," << L->shortName << "," << L->openingPrice << ","
		<< L->closingPrice << "," << L->changePercent << endl;
		L = L->next;
		index++;
	}
	outfile.close();
}
// ���ڿ�������Ĺ�Ʊ�۸����
void analyseByQuickSort() {
	int isExit = 0;
	
	while(!isExit) {
		string cate;
		cout << "������һ����ҵ��";
		cin >> cate;
		
		vector<StockInfo> industry;    //����ҵ�Ĺ�Ʊ
		industry.push_back(stocks[0]); //���pushһ����ȥ 
		
		for(int i = 0; i < 200; i++) {
			if(stocks[i].cate1 == cate && stocks[i].score > 0) {
				industry.push_back(stocks[i]);
			}
		}
		quickSort(industry, 1, industry.size()-1);
		int n = industry.size();
		
		
		for(int i = 1; i < n; i++) {
			cout << i << "   " << industry[i].stockCode << "   " << industry[i].shortName << 
			"   " << industry[i].maxChangePercent << "   " << industry[i].maxDate << endl;
		}
		
		int isBreak = 0;
		while(!isBreak) {
			cout << "��ȷ���Ƿ����(yes/no): ";
			string isGo;
			cin >> isGo;
			if(isGo == "no") {
				isExit = 1;
				isBreak = 1;
			}
			else if(isGo == "yes") {
				break;
			}
			else cout << "���벻�Ϸ������������룡" << endl;
		}	
	}
}
void quickSort(vector<StockInfo> &industry, int low, int high) {
	if(low < high) {
		int pivitloc = partition(industry, low, high);
		quickSort(industry, low, pivitloc-1);
		quickSort(industry, pivitloc+1, high);
	}
}
int partition(vector<StockInfo> &industry, int low, int high) {
	industry[0] = industry[low];   
	double pivotkey = industry[low].maxChangePercent;

    while(low < high)
	{ 
	   while(low < high && industry[high].maxChangePercent < pivotkey )  
	   	--high;
       industry[low] = industry[high];
       while (low < high && industry[low].maxChangePercent >= pivotkey )  
	   	++low;
       industry[high] = industry[low];
    }
    industry[low] = industry[0]; 
    return low;
}
// ���ڼ�ѡ������Ĺ�Ʊ�۸����
void analyseBySelectionSort() {
	ifstream in("��Ʊ������Ϣ����/60֧��Ʊ��Ϣ2.csv");
	string row;
	
	getline(in, row);
	getline(in, row);
	vector<vector<string>> arr1;

	while(getline(in, row)) {
		stringstream ss(row);
		string str;
	
		vector<string> arr;
		while(getline(ss, str, ',')) arr.push_back(str);
		arr1.push_back(arr);
	}  //�������ݷŵ� arr1 ���� 
	
	int num = arr1.size();
	for(int i = 0; i < num-1; i++) {
		int k = i;
		for(int j = i+1; j < num; j++) {
			if(stod(arr1[j][2]) > stod(arr1[k][2])) k = j;
		}
		if(k != i) swap(arr1[i], arr1[k]);
	}  //������������  OK��
	 
	vector<StockInfo> arr2;
	for(int i = 0; i < 200; i++) {
		if(stocks[i].score > 0)  arr2.push_back(stocks[i]);
	}
	
	int n = arr2.size();
	for(int i = 0; i < n-1; i++) {
		int k = i;
		for(int j = i+1; j < n; j++) {
			if( stod(arr2[j].recentInfo[1]) > stod(arr2[k].recentInfo[1]) ) k = j;
		}
		if(k != i) swap(arr2[i], arr2[k]);
	}  //�������̼�����  OK!
	
	
	int isExit = 0;
	while(!isExit) {
		printf("%-5s%-10s%-10s%-10s", "���", "��Ʊ����", "��Ʊ����", "����");
		printf("%-5s%-10s%-10s%-10s\n", "���", "��Ʊ����", "��Ʊ����", "���̼�");
		
		ofstream scoreSort("��������.csv", ios::out);
		scoreSort << "���" << "," << "��Ʊ����" << "," << "��Ʊ����" << "," << "����" << endl;
		ofstream priceSort("���̼�����.csv", ios::out);
		priceSort << "���" << "," << "��Ʊ����" << "," << "��Ʊ����" << "," << "���̼�" << endl;
		
		for(int i = 0; i < 60; i++) {
			printf("%-5d", i+1); 
			printf("%-10s", arr1[i][0].c_str());
			printf("%-10s", arr1[i][1].c_str());
			printf("%-10s", arr1[i][2].c_str());
			cout << "|";
			printf("%-5d", i+1); 
			printf("%-10s", arr2[i].stockCode.c_str());
			printf("%-10s", arr2[i].shortName.c_str());
			printf("%-10s", arr2[i].recentInfo[1].c_str());
			cout << endl;
			
			scoreSort << i+1 << "," << arr1[i][0] << "," << arr1[i][1] << "," << arr1[i][2] << endl;
			priceSort << i+1 << "," << arr2[i].stockCode << "," << arr2[i].shortName << "," << arr2[i].recentInfo[1] << endl;
		}
	
		scoreSort.close();
		priceSort.close();
		
		int isBreak = 0;
		while(!isBreak) {
			cout << "�������������Լ��� ";
			string isGo;
			cin >> isGo;
			if(isGo!="") {
				isExit = 1;
				isBreak = 1;
			}
		}	
	}	
}
// ����Floyd�Ĺ�Ʊ����Լ���
void analyseByFloyd() {	
	vector<vector<int>> graph(N+1, vector<int>(N+1, 0)); //60ֻ��Ʊ�ڽӾ��� 
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++) {
			graph[i][j] = INF;   //����
		} 
			
	for(int i = 1; i <= N; i++) {
		graph[i][i] = 0; 
	} 	//��ʼ���ڽӾ��� 
	
	ifstream in("��Ʊ������Ϣ����/60֧��Ʊ��Ϣ1.csv");
	string row;
	getline(in, row);
	
	while(getline(in, row)) {
		stringstream ss(row);
		string str;
		
		vector<string> arr;
		while(getline(ss, str, ',')) arr.push_back(str);
		
		int dot1 = stoi(arr[0]);
		int dot2 = stoi(arr[1]);
		int dis = stoi(arr[2]);
		graph[dot1][dot2] = dis;
		graph[dot2][dot1] = dis;
	}
	
	for(int k = 1; k <= N; k++) {
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				if(graph[i][k] + graph[k][j] < graph[i][j])
					graph[i][j] = graph[i][k] + graph[k][j];
			}
		}
	}
	
	int isExit = 0;
	
	while(!isExit) {
		cout << "�����������������֣��ֱ��ʾͼ�������ڵ㣺";
		int node1, node2;
		cin >> node1 >> node2;
		cout << "���·��Ϊ" << graph[node1][node2] << endl;
			
		int isBreak = 0;
		while(!isBreak) {
			cout << "��ȷ���Ƿ����(yes/no): ";
			string isGo;
			cin >> isGo;
			if(isGo == "no") {
				isExit = 1;
				isBreak = 1;
			}
			else if(isGo == "yes") {
				break;
			}
			else cout << "���벻�Ϸ������������룡" << endl;
		}	
	}
}
// ����Prim��С�������Ĺ�Ʊ����ɸѡ
void analyseByPrim() {
	vis.assign(N+1, false);
	d.assign(N+1, INF);
	e.resize(N+1);
	
	ifstream in("��Ʊ������Ϣ����/60֧��Ʊ��Ϣ1.csv");
	string row;
	getline(in, row);
	
	while(getline(in, row)) {
		stringstream ss(row);
		string str;
		
		vector<string> arr;
		while(getline(ss, str, ',')) arr.push_back(str);
		//�ַ���ת���� https://chinese.freecodecamp.org/news/string-to-int-in-c-how-to-convert-a-string-to-an-integer-example/
		int dot1 = stoi(arr[0]);
		int dot2 = stoi(arr[1]);
		int dis = stoi(arr[2]);
		
		e[dot1].push_back({dot2, dis});
		e[dot2].push_back({dot1, dis});
	}
	MST();   //��ʱ��С�������Ѿ�������
	
	sort(ret.begin(), ret.end(), cmp);
	int num = ret.size();
	
	cout << "�ߵ�Ȩֵ��" << ret[1].weight << " �ߵĽ��1��" <<  scores[ret[1].fund1].name << " �ߵĽ��2��" << scores[ret[1].fund2].name << endl;

	vector<fundPortfolio> arr; //ȨֵΪ2�� 
	for(int i = 0; i <= num; i++) {
		if(ret[i].weight == 2) arr.push_back(ret[i]);
	}
	
	int n = arr.size();
	for(int i = 0; i < n; i++) {
		arr[i].scoreSum = scores[arr[i].fund1].score + scores[arr[i].fund2].score;
	}
	sort(arr.begin(), arr.end(), cmpByScores);
	
	cout << "�ߵ�Ȩֵ��" << arr[0].weight << " �ߵĽ��1��" <<  scores[arr[0].fund1].name << " �ߵĽ��2��" << scores[arr[0].fund2].name << endl;
	cout << "�ߵ�Ȩֵ��" << arr[1].weight << " �ߵĽ��1��" <<  scores[arr[1].fund1].name << " �ߵĽ��2��" << scores[arr[1].fund2].name << endl;
	
	cout << "�������������Լ��� ";
	string isGo;
	cin >> isGo;
}
// Prim �����㷨 
void MST() {
	d[1] = 0;   //�ʼ�ڲ���һ���ռ�
	int fund1 = 0;
	int fund2 = 0;
	
	//ÿһ��ѡһ���ڲ����ⲿ��С�ı� 
	for(int i = 1; i <= N; i++) {
		int min = INF;
		
		for(int k = 1; k <= N; k++) {
			if(!vis[k] && d[k] < min) {
				min = d[k];
				fund2 = k;
			}
		}
		
		for(int k = 1; k <= N; k++) {
			if(vis[k]) {
				int n = e[k].size();
				for(int j = 0; j < n; j++) {
					if(e[k][j].w == min && e[k][j].v == fund2) fund1 = k;
				}
			}
		}
		
		vis[fund2] = 1;
		
		for(const edge& item : e[fund2]) {
			int v = item.v, w = item.w;
			d[v] = d[v] < w ? d[v] : w;
		}
		
		struct fundPortfolio funds;
		funds.fund1 = fund1;
		funds.fund2 = fund2;
		funds.weight = min;
		
		ret.push_back(funds);
	}
}
// ����Kruskal��С�������Ĺ�Ʊ����ɸѡ
void anylyseByKruskal() {
	vector<Edge> es;
		
	ifstream in("��Ʊ������Ϣ����/60֧��Ʊ��Ϣ1.csv");
	string row;
	getline(in, row);
	
	while(getline(in, row)) {
		stringstream ss(row);
		string str;
		
		vector<string> arr;
		while(getline(ss, str, ',')) arr.push_back(str);
		//�ַ���ת���� https://chinese.freecodecamp.org/news/string-to-int-in-c-how-to-convert-a-string-to-an-integer-example/
		int dot1 = stoi(arr[0]);
		int dot2 = stoi(arr[1]);
		int dis = stoi(arr[2]);
		
		es.push_back({dot1, dot2, dis});
	}
	sort(es.begin(), es.end(), [](const Edge& x, const Edge& y) {
                return x.w < y.w;
    });
    
    int m = es.size();
    
    p.resize(m);
    for(int i = 0; i <= N; i++) p[i] = i;
    vector<fundPortfolio> res;
    
    for(int i = 0; i < m; i++) {
    	int u = es[i].u;
    	int v = es[i].v;
    	int w = es[i].w;
    	
    	int fu = find(u);
    	int fv = find(v);
    	
    	if(fu == fv) continue;
    	p[fu] = fv;
    	fundPortfolio tmp;
    	tmp.fund1 = fu;
    	tmp.fund2 = fv;
    	tmp.weight = w;
    	res.push_back(tmp);
	}
	cout << "�ߵ�Ȩֵ��" << res[0].weight << " �ߵĽ��1��" <<  scores[res[0].fund1].name << " �ߵĽ��2��" << scores[res[0].fund2].name << endl;
	
	vector<fundPortfolio> arr; //ȨֵΪ2�� 
	for(int i = 0; i <= m; i++) {
		if(res[i].weight == 2) arr.push_back(res[i]);
	}
	
	int n = arr.size();
	for(int i = 0; i < n; i++) {
		arr[i].scoreSum = scores[arr[i].fund1].score + scores[arr[i].fund2].score;
	}
	sort(arr.begin(), arr.end(), cmpByScores);
	
	cout << "�ߵ�Ȩֵ��" << arr[0].weight << " �ߵĽ��1��" <<  scores[arr[0].fund1].name << " �ߵĽ��2��" << scores[arr[0].fund2].name << endl;
	cout << "�ߵ�Ȩֵ��" << arr[1].weight << " �ߵĽ��1��" <<  scores[arr[1].fund1].name << " �ߵĽ��2��" << scores[arr[1].fund2].name << endl;
	
	cout << "�������������Լ��� ";
	string isGo;
	cin >> isGo;
}
// ���ڶ���ͼ�Ĺ�Ʊ����ɸѡ
void analyseByBigraph() {
	
}
// ɾ�������������ڵ㹦�����
void deleteBSTNode() {
	BinTree T = NULL;
	createBST(T, stocks); //�������
	
	cout << "������Ҫɾ���Ĺ�Ʊ���룺";
	string toDelete;
	cin >> toDelete;
	
	BinTree ret = NULL;
	BinTree node = deleteBST(T, toDelete, ret);
	printResult(ret);
	
	cout << "�������������Լ��� ";
	string isGo;
	cin >> isGo;
}
// ɾ���ڵ�
BinTree deleteBST(BinTree& BST, string str, BinTree& ret) {
	BinTree ptr;
 
    if (BST == NULL)  //Ҫɾ���Ľ�㲻����
    	cout << "Not Found\n" << endl; 
	 
    else {					                  //Ҫɾ���Ľ�����
		if (str == BST->data.stockCode) {     //�ҵ���Ҫɾ���Ľ��
            if (BST->left && BST->right)      //��������������
            {
                ptr = FindMin(BST->right);    //ѡ������������С���
                BST->data = ptr->data;        //������������С���ȡ����ɾ�����
                BST->right = deleteBST(BST->right, BST->data.stockCode, ret);      //ɾ��ԭ��������������С���
            }
            else                              //�����������ڿ���
            {
                if (BST->left == NULL)        //����������Ϊ����(��ʱ�����ҽ��Ҳ�ǿ���)
                    BST = BST->right;
                else                          //����������Ϊ����
                    BST = BST->left;
            }
            ret = BST;
	    }
	    //�ݹ��������������ɾ�����
        else if(str < BST->data.stockCode) {
        	BST->left = deleteBST(BST->left, str, ret);
		}
		//�ݹ��������������ɾ�����
        else {
        	BST->right = deleteBST(BST->right, str, ret);
		}
    }
    
    return BST;
}
// ������Сֵ
BinTree FindMin(BinTree BST) {
    if (BST != NULL) {
        while (BST->left)      //���������������ھ�
            BST = BST->left;
    }
    
    return BST;
}
// ��ӡ���½ڵ�����ҽڵ���Ϣ 
void printResult(BinTree node) {
	cout << "��ǰ�½ڵ�Ϊ: " << endl;
	cout << node->data.shortName << "   " << node->data.stockCode << "   " << node->data.recentInfo[0] 
	<< "   " << node->data.recentInfo[1] << "   " << node->data.recentInfo[2] << endl << endl;
	
	if(node->left) {
		cout << "����Ϊ��" << endl;
		cout << node->left->data.shortName << "   " << node->left->data.stockCode << "   " 
		<< node->left->data.recentInfo[0] << "   " << node->left->data.recentInfo[1] << "   " 
		<< node->data.recentInfo[2] << endl << endl;
	}

	else cout << "����������" << endl << endl;
	
	if(node->right) {
		cout << "�Һ���Ϊ��" << endl;
		cout << node->right->data.shortName << "   " << node->right->data.stockCode << "   " 
		<< node->right->data.recentInfo[0] << "   " << node->right->data.recentInfo[1] << "   " 
		<< node->right->data.recentInfo[2] << endl << endl;
	}
	
	else cout << "�������Һ���" << endl << endl;
}














