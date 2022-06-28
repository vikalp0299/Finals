#include <iostream>
#include <httplib.h>
#include "shachk.h"

using namespace std;
using namespace httplib;

int main(){
	Client cli("localhost",4444);
	string s = getMySHA("text.txt");
	cout<<s<<endl;
}































