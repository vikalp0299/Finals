#include<cryptlib.h>
#include<filters.h>
#include<iostream>
#include<hex.h>
#include<sha.h>
using std::string;
using std::endl;
using std::cout;
using namespace CryptoPP;
string getSHA(string pass){
	SHA1 hash;
	
	string digest;
	StringSource(pass,true, new HashFilter(hash,new HexEncoder(new StringSink(digest))));
	return digest;
}
