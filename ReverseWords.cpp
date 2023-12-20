#include <iostream>

using namespace std;

void Reverse(char ch[],int s, int e){
	while(s<=e) swap(ch[s++],ch[e--]);
}

int main() {
	char ch[]="Fuck   that little   bitch   cuz    I'm an albatroz";
	cout << ch << endl;
	
	int pos=0, i;
	for(i=0;ch[i]!='\0';i++){
		if(ch[i]==' '){
			Reverse(ch,pos,i-1);
			pos=i+1;
		}
	}
	Reverse(ch,pos,i-1);
	Reverse(ch,0,i-1);

  	cout << ch << endl;
	return 0;
}