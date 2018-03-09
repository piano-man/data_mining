#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
typedef pair<vector<int>, vector<int> > tpair;
vector<int> adj[4000];
set<tpair> res;
map < vector<int>, int > fin;
int n;
int mxid;
float conf;
int arr[30];
float thresh;
void getData() {
	ifstream in("transactions.txt");
	string str;
	int i;
	while(getline(in, str)) {
		++n;
		int num = 0;
		for(i = 0; i < str.size(); i++) {
			if(str[i] == ' ') {
				mxid = max(mxid, num);
				adj[n].pb(num);
				num = 0;
			}
			else {
				num = num * 10 + str[i] - '0';
			}
		}
		if(num) {
			mxid = max(mxid, num);
			adj[n].pb(num);
		}
	}
	in.close();
}

int getCount(vector<int> &v) {
	int c = 0;
	int i, j;
	for(i = 1; i <= n; i++) {
		int id = 0;
		for(j = 0; j < adj[i].size(); j++) {
			if(adj[i][j] == v[id]) {
				id++;
			}
			if(id == v.size()) {
				c++;
				break;
			}
		}
	}
	return c;
}
void getFirstLevel(vector< vector<int> > &data, vector<int> &occur) {
	int i;
	for(i = 1; i <= mxid; i++) {
		vector<int> temp;
		temp.pb(i);
		int val = getCount(temp);
		if(val > thresh) {
			data.pb(temp);
			occur.pb(val);
		}
	}
}
int getCommon(vector <int> &v1, vector <int> &v2, vector <int> &res) {
	int i = 0, j = 0;
	int c = 0;
	while(i < v1.size() && j < v2.size()) {
		if(v1[i] == v2[j]) {
			res.pb(v1[i]);
			i++;
			j++;
			c++;
		}
		else if(v1[i] < v2[j]) {
			res.pb(v1[i]);
			i++;
		}
		else {
			res.pb(v2[j]);
			j++;
		}
	}
	while(i < v1.size()) {
		res.pb(v1[i]);
		i++;
	}
	while(j < v2.size()) {
		res.pb(v2[j]);
		j++;
	}
	return c;
}
void printVector(vector<int> v) {
	int i;
	for(i = 0; i < v.size(); i++) {
		cout << v[i] << "  ";
	}
    cout << endl;
}
void printData2(vector <vector<int> > &data, vector<int> &occur) {
	int i, j;
	for(i = 0; i < data.size(); i++) {
		for(j = 0; j < data[i].size(); j++) {
			cout << data[i][j] << " ";
		}
		cout << occur[i] << endl;
	}
}
void calcVal(int id, vector<int> v, int cur) {
	if(id == v.size()) {
		int i, j;
		for(i = 0; i < id - 1; i++) {
			vector<int> v1, v2;
			for(j = 0; j <= i; j++) {
				v1.pb(arr[j]);
			}
			for(j = i + 1; j < id; j++) {
				v2.pb(arr[j]);
			}
			sort(v1.begin(), v1.end());
			sort(v2.begin(), v2.end());
			//printVector(v1);
			//printVector(v2);
			float val1 = cur;
			val1/=getCount(v1);
			//cout << getCount(v1) << " " << val1 << endl;
			//cout << endl;
			if(val1 > conf) {
				res.insert(mp(v1, v2));
			}
		}
		return;
	}
	int i, j;
	for(i = 0; i < v.size(); i++) {
		int f = 1;
		for(j = 0; j < id; j++) {
			if(arr[j] == v[i]) {
				f = 0;
			}
		}
		if(f) {
			arr[id] = v[i];
			calcVal(id + 1, v, cur);
		}
	}
}
void apriori() {
	vector< vector <int> > data; vector<int> occur;
	getFirstLevel(data, occur);
	//printData2(data, occur);
	int i, j;
	int c = 0;
	while(data.size() > 1) {
		occur.clear();
		vector< vector<int> > nData;
		for(i = 0; i < data.size(); i++) {
			for(j = i + 1; j < data.size(); j++) {
				vector<int> k;
				int p = getCommon(data[i], data[j], k);
				//cout << i << " " << j << " " << p << endl;
				if(p >= c) {
					int r = getCount(k);
					if(r > thresh) {
						nData.pb(k);
						occur.pb(r);
						fin[k] = r;
					}
				}
			}
		}
		data.clear();
		for(i = 0; i < nData.size(); i++) {
			data.pb(nData[i]);
		}
		c++;
	}
	map< vector<int>, int > :: iterator it;
	for(it = fin.begin(); it != fin.end(); it++) {
		printVector(it->ff);
		//if((it->ff)[0] == 1 && (it->ff)[1] == 2)
		calcVal(0, it->ff, it->ss);
	}
}
void printData() {
	int i;
	for(i = 1; i <= n; i++) {
		int j;
		for(j = 0; j < adj[i].size(); j++) {
			cout << adj[i][j] << " " ;
		}
		cout << endl;
		cout << endl;
	}
}
int main() {
	getData();
	float val;
	cin >> val;
	thresh = val*n;
	cin >> conf ;
	apriori();
	set<tpair> :: iterator it;
	/*for(it = res.begin(); it != res.end(); it++) {
		vector<int> v1, v2;
		v1 = it->ff;
		v2 = it->ss;
		printVector(v1);
		cout << "======> ";
		printVector(v2);
		vector<int> k;
		getCommon(v1, v2, k);
		float sup = getCount(k);
		sup/=n;
		float conf = getCount(v1);
		conf/=n;
		conf = sup/conf;
		cout << " " << sup << " " << conf << endl;
	}*/
	return 0;
}