#include<iostream>
#include<vector>

using namespace std;

int main(){
	int n;
	cin >> n;
	int thisSum = 0, maxSum = 0, thisNum, first=0, last=0;
	bool allNag = true;
	vector<int> ans;
	vector<int> temp;
	for(int i=0;i<n;i++){
		
		cin >> thisNum;
		if(i == 0) first = thisNum;
		if(i == n-1) last = thisNum;
		if(thisNum >= 0) allNag = false;
		
		thisSum += thisNum;
		if(thisSum < 0 && thisNum < 0){
			temp.clear();
			thisSum = 0;
		}else{
			temp.push_back(thisNum);
		}
		if(thisSum > maxSum){
			ans.clear();
			maxSum = thisSum;
			for(auto x:temp) ans.push_back(x);
		}
	}
	if(allNag) cout << 0 << " " << first << " " << last << endl;
	else if(!allNag && maxSum == 0) cout << 0 << " " << 0 << " " << 0 << endl;
	else cout << maxSum << " " << ans[0] << " " << ans[ans.size() -1]<< endl;
	
	return 0;
}
