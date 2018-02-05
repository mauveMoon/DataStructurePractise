#include<iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	int thisSum = 0, maxSum = 0, thisNum;
	for(int i=0;i<n;i++){
		cin >> thisNum;
		thisSum += thisNum;
		if (thisSum < 0) thisSum = 0;
		if(thisSum > maxSum) maxSum = thisSum;
	}
	cout << maxSum << endl;
	return 0;
}
