#include <bits/stdc++.h> 

using namespace std;
 
#define ll long long
#define fi first
#define se second
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
#define el '\n'

int main() {
	srand((unsigned)time(0));

    ofstream inv;
    inv.open("inventory.txt");

	for(int i=0; i<27; i++){
		if(rand()%4 == 0) inv << "0:0" << '\n';
		else inv << (rand() % 27 + 1) << ":" << (rand() % 64 + 1) << '\n';
	}

    inv.close();
}