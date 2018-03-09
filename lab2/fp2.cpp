#include <fstream>
#include <iostream>
#include <vector>
#include<sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <set>
#include <map>
#include<queue>

using namespace std;
#define pb push_back
set<int> s;
map<int,int> mymap;
vector<int> sorted;
string removeCommas(string str)
{
    str.erase(remove(str.begin(), str.end(), ','), str.end());
    return str;
}
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}
bool cmp_desc(int a,int b)
{
    return (mymap[a]>mymap[b]);
}
int getSuvalort(int ele,vector<vector<int > >v)
{
    int size = v.size();
    int i;
    int suval = 0;
    for(i=0;i<size;i++)
    {
        int size1 = v[i].size();
        int j;
        for(j=0;j<size1;j++)
        {
            if(v[i][j]==ele)
            {
                suval++;
            }
        }
    }
    return suval;
}
struct node{
	int ctr;
	struct trie *next;
};

struct trie{
	struct node child[1001];
};

struct trie *getTrieNode()
{
	struct trie *temp;
	temp = (struct trie *)malloc(sizeof(struct trie));
	for(int i=1;i<=1000;i++){
		//temp->child[i] = malloc(sizeof(struct node));
		temp->child[i].ctr = 0;
		temp->child[i].next = NULL;
	}
	return temp;
}
void print_tree(struct trie *temp)
{
	if(temp == NULL)
		return;
	queue< pair <struct trie *, int > > q;
	q.push(make_pair(temp, 0));
	int i;
	while(!q.empty()){
		pair < struct trie *, int > tt = q.front();
		struct trie *t = tt.first;
		int val = tt.second;
		q.pop();
		for(i=1;i<=1000;i++){
			if(t->child[i].ctr > 0){
				cout << val << ":" << i << ":" << t->child[i].ctr << " ";
				q.push(make_pair(t->child[i].next, i));
			}
		}
		cout << endl;
	}
}
int main()
{
    string line;
    int i;
    int length = 0;
    int suvalort;
    cin >> suvalort;
    vector<vector<int > > v;
    ifstream myfile("transactions.txt");
    ifstream myfile2("transactions.txt");
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            length++;
        }
    }
    myfile.close();
    for(i=0;i<length;i++)
    {
        v.push_back(vector<int>());
    }
    if(myfile2.is_open())
    {
        int lno = 0;
        float num;
        while(getline(myfile2,line))
        {
            string fline = removeCommas(line);
            int count = 0;
            istringstream stream1;
            stream1.str(fline);
            while(stream1 >> num)
            {
                v[lno].pb(num);
                if(count==0)
                {
                    count++;
                }
                else
                {
                    s.insert(num);
                }
                
            }
            lno++;
        }
    }
    myfile2.close();
        set<int>::iterator it;
    for(it=s.begin();it!=s.end();it++)
    {
        int ele = *it;
        int supp = getSuvalort(ele,v);
        if(supp>=suvalort)
        {
            continue;
        }
        else
        {
            int j;
            s.erase(ele);
            for(j=0;j<v.size();j++)
            {
                v[j].erase(std::remove(v[j].begin(), v[j].end(), ele), v[j].end());
            }

        }
    }
    set<int>::iterator it2;
    for(it2=s.begin();it2!=s.end();it2++)
    {
        int ele = *it2;
     //   cout << "element" << ele << '\n';
        int s = getSuvalort(ele,v);
       // cout << "suvalort" << s << '\n';
        mymap[ele]=s;
        sorted.pb(ele);
    }
    int k;
    sort(sorted.begin(),sorted.end(),cmp_desc);
    for(k=0;k<sorted.size();k++)
    {
        //cout << sorted[k] << '\n';
    }
    int j;
    for(j=0;j<v.size();j++)
    {
        sort(v[j].begin(),v[j].end(),cmp_desc);
    }
    //tree part
    	struct trie *root = getTrieNode();

    for(i=0;i<v.size();i++){
		struct trie *temp = root;
		j = 0;
		while(j < v[i].size()){
			if(temp->child[v[i][j]].ctr == 0){
				temp->child[v[i][j]].next = getTrieNode();
				temp->child[v[i][j]].ctr = 1;
				temp = temp->child[v[i][j]].next;
				cout << "newly inserted" << v[i][j] << endl;
			}
			else{
				temp->child[v[i][j]].ctr += 1;
				temp = temp->child[v[i][j]].next;
				cout << "inserted" << v[i][j] << endl;
			}
			j += 1;
		}
	}
    	print_tree(root);


	cout << "Total Number of transactions = " << v.size() << endl;
	int sum = 0;
	for(i=1;i<=1000;i++){
		sum += root->child[i].ctr;
	}
	cout << "Number of transaction in tree = " << sum << endl;
	return 0;

}