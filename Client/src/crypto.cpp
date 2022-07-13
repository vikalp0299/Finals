#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <cryptopp/files.h>
using CryptoPP::FileSink;
using CryptoPP::FileSource;

#include <cryptopp/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include <cryptopp/filters.h>
using CryptoPP::PK_EncryptorFilter;
using CryptoPP::PK_DecryptorFilter;

#include <cryptopp/osrng.h>
using CryptoPP::AutoSeededRandomPool;

#include <cryptopp/integer.h>
using CryptoPP::Integer;

#include <cryptopp/pubkey.h>
using CryptoPP::PublicKey;
using CryptoPP::PrivateKey;

#include <cryptopp/eccrypto.h>
using CryptoPP::ECP;    // Prime field
using CryptoPP::EC2N;   // Binary field
using CryptoPP::ECIES;
using CryptoPP::ECPPoint;
using CryptoPP::DL_GroupParameters_EC;
using CryptoPP::DL_GroupPrecomputation;
using CryptoPP::DL_FixedBasePrecomputation;

#include <cryptopp/pubkey.h>
using CryptoPP::DL_PrivateKey_EC;
using CryptoPP::DL_PublicKey_EC;

#include <cryptopp/asn.h>
#include <cryptopp/oids.h>
namespace ASN1 = CryptoPP::ASN1;

#include <cryptopp/cryptlib.h>
using CryptoPP::PK_Encryptor;
using CryptoPP::PK_Decryptor;
using CryptoPP::g_nullNameValuePairs;

void PrintPrivateKey(const DL_PrivateKey_EC<ECP>& key, ostream& out = cout);
void PrintPublicKey(const DL_PublicKey_EC<ECP>& key, ostream& out = cout);

void SavePrivateKey(const PrivateKey& key, const string& file = "/home/do/Desktop/Finals/Client/Keys/ecies.private.key");
void SavePublicKey(const PublicKey& key, const string& file = "/home/do/Desktop/Finals/Client/Keys/ecies.public.key");

void LoadPrivateKey(PrivateKey& key, const string& file = "/home/do/Desktop/Finals/Client/Keys/ecies.private.key");
void LoadPublicKey(PublicKey& key, const string& file = "/home/do/Desktop/Finals/Client/Keys/ecies.public.key");


void encrypt(string dir,string str){
	AutoSeededRandomPool prng;
	ECIES<ECP>::Decryptor d0(prng, ASN1::secp256r1());
	//PrintPrivateKey(d0.GetKey());

    ECIES<ECP>::Encryptor e0(d0);
   // PrintPublicKey(e0.GetKey());

	string enc_str= "/home/do/Desktop/Finals/Client/Files/enc/enc_"+str;
	str = dir+str;

	SavePrivateKey(d0.GetPrivateKey());
    SavePublicKey(e0.GetPublicKey());
	//StringSource ss1 (message, true, new PK_EncryptorFilter(prng, e0, new StringSink(em0) ) );
	FileSource source(str.c_str(),true, new PK_EncryptorFilter(prng,e0, new HexEncoder(new FileSink(enc_str.c_str()))));

	
}
void decrypt(string str){
	AutoSeededRandomPool prng;
	ECIES<ECP>::Decryptor d1;
    LoadPrivateKey(d1.AccessPrivateKey());
    d1.GetPrivateKey().ThrowIfInvalid(prng, 3);
    
    ECIES<ECP>::Encryptor e1;
    LoadPublicKey(e1.AccessPublicKey());
    e1.GetPublicKey(). ThrowIfInvalid(prng, 3);
	
	string dec_str = "dec_"+str;
	FileSource source(str.c_str(),true,new HexDecoder(new PK_DecryptorFilter(prng,d1,new FileSink(dec_str.c_str()))));
}


void SavePrivateKey(const PrivateKey& key, const string& file)
{
    FileSink sink(file.c_str());
    key.Save(sink);
}

void SavePublicKey(const PublicKey& key, const string& file)
{
    FileSink sink(file.c_str());
    key.Save(sink);
}

void LoadPrivateKey(PrivateKey& key, const string& file)
{
    FileSource source(file.c_str(), true);
    key.Load(source);
}

void LoadPublicKey(PublicKey& key, const string& file)
{
    FileSource source(file.c_str(), true);
    key.Load(source);
}
/*int main(){
encrypt("/home/do/Desktop/Finals/Client/text.txt")
}*/

