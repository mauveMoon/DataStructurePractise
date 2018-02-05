#include<iostream>
#include<list>
#include<vector>

using namespace std;

class Item{
public:
	int coef, expon;
	Item(int ic, int ie){
		coef = ic;
		expon = ie;
	}
};

list<Item> add(list<Item> poly1, list<Item> poly2);
list<Item> prod(list<Item> poly1, list<Item> poly2);

int main(){
	list<Item> poly1;
	list<Item> poly2;
	
	int n, m;
	int ic, ie;
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> ic >> ie;
		Item te(ic, ie);
		poly1.push_back(te);
	}
	cin >> m;
	for(int i=0;i<m;i++){
		cin >> ic >> ie;
		Item te(ic, ie);
		poly2.push_back(te);
	}
	list<Item> add_poly = add(poly1, poly2);
	list<Item> prod_poly = prod(poly1, poly2);
	
	vector<Item> add_poly_vec;
	vector<Item> prod_poly_vec;
	for(auto x:add_poly) add_poly_vec.push_back(x);
	for(auto x:prod_poly) prod_poly_vec.push_back(x);
	
	int add_size = add_poly_vec.size();
	int prod_size = prod_poly_vec.size();
	
	if(prod_size == 0){
		cout << 0 << " " << 0 << endl;
	}else{
		for(int i=0;i<prod_size - 1;i++){
			cout << prod_poly_vec[i].coef << " " << prod_poly_vec[i].expon << " ";
		}
		cout << prod_poly_vec[prod_size - 1].coef << " " << prod_poly_vec[prod_size - 1].expon << endl;
	}
	
	if(add_size == 0){
		cout << 0 << " " << 0 << endl;
	}else{
		for(int i=0;i<add_size - 1;i++){
			cout << add_poly_vec[i].coef << " " << add_poly_vec[i].expon << " ";
		}
		cout << add_poly_vec[add_size - 1].coef << " " << add_poly_vec[add_size - 1].expon << endl;
	}
	


	return 0;
} 

list<Item> add(list<Item> poly1, list<Item> poly2){
	list<Item> poly3;
	for(auto x:poly1) {
		Item new_item(x.coef, x.expon);
		poly3.push_back(new_item);
	}
	for(auto x:poly2){
		auto it = poly3.begin();
		for(;it!=poly3.end();it++){
			if(it->expon == x.expon){
				it->coef += x.coef;
				if(it->coef == 0) poly3.erase(it);
				break; 
			}else if(it->expon < x.expon){
				Item new_item(x.coef, x.expon);
				poly3.insert(it, new_item);
				break;
			}
		}
		if(it == poly3.end()){
			Item new_item(x.coef, x.expon);
			poly3.push_back(new_item);
		}
	}
	return poly3;
}

list<Item> prod(list<Item> poly1, list<Item> poly2){
	list<Item> poly3;
	
	for(auto it1 = poly1.begin();it1 != poly1.end();it1++){
		for(auto it2 = poly2.begin();it2 != poly2.end();it2++){
			Item thisItem(it1->coef*it2->coef, it1->expon+it2->expon);
//			cout << it1->coef << " " << it1->expon <<" " << it2->coef << " " << it2->expon << " " << thisItem.coef << " " << thisItem.expon << endl;
			if(thisItem.coef != 0){
				if(poly3.empty()) poly3.push_back(thisItem);
				else{
					auto it3 = poly3.begin();
					for(;it3!=poly3.end();it3++){
						if(it3->expon == thisItem.expon){
							it3->coef += thisItem.coef;
							if(it3->coef == 0) poly3.erase(it3);
							break; 
						}else if(it3->expon < thisItem.expon){
							poly3.insert(it3, thisItem);
							break;
						}
					}
					if(it3 == poly3.end()){
						poly3.push_back(thisItem);
					}
				}
			}
		}
	}
	return poly3;
}
