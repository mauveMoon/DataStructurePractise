#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Node{
public:
	string address;
	int data;
	string next_address;
	Node(string add, int id, string nadd){
		address = add;
		data = id;
		next_address = nadd;
	}
}; 

int main(){
	int n;
	string start;
	int rev;
	cin >> start >> n >> rev;
	
	string address;
	int data;
	string next_address;
	map<string, string> ars2ars;  // 地址对地址
	map<string, int> ars2data;   // 地址对数据 
	for(int i=0;i<n;i++){
		cin >> address >> data >> next_address;
		ars2ars[address] = next_address;
		ars2data[address] = data;
	}
	
	string f = start;
	vector<Node> arr;
	while(f != "-1"){
		Node t(f,  ars2data[f], ars2ars[f]);
		arr.push_back(t);
		f = ars2ars[f];
	}
		

	
	auto it = arr.begin();
	
	while(it+rev <= arr.end()){
		reverse(it, it+rev);
		it+=rev;
	}
	
	it = arr.begin();
	for(;it!=arr.end()-1;it++){
		it->next_address = (it+1)->address;
	}
	it->next_address = "-1";
	
	for(Node x:arr){
		cout << x.address << " " << x.data << " " << x.next_address << endl;
	}

	return 0;
}
