#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include </usr/local/cpp-httplib-0.10.6/httplib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string>
#include<experimental/filesystem>
namespace filesys = std::experimental::filesystem;
using namespace std;
using namespace httplib;


bool pathexists(string &s){
	struct stat buffer;
	if(stat(s.c_str(),&buffer)==0)
		return true;
	return false ;
}

void error(const char *msg){
	perror(msg);
	cout<<endl;
	exit(0);
}


void fileTransferHandler(int UID,int FID,int signal){
	//sleep(3);
	
	string User,File,path,Fpath;
	User = to_string(UID);
	File = to_string(FID);
	Fpath ="/home/authenticator/Desktop/tmpstorage/";
	if(signal == 0 || signal == 2){	
		Fpath+=User+"/";
	
		if(!pathexists(Fpath)){
			cout << "Directory doesn't exist\n";
			return;
		}
		Fpath += File;
		if(!pathexists(Fpath)){
			cout<<endl<<Fpath<<endl;
			cout << "File doesn't exists\n";
			return;
		}
	}
	#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
		auto schema = "https://CSPhandler:17171";
	#else
		auto schema = "http://CSPhandler:17171";
	#endif
	Client cli(schema);
	cli.set_ca_cert_path("/usr/local/cpp-httplib-0.10.6/example/ca-bundle.crt");
	cli.enable_server_certificate_verification(false);
	if(auto res = cli.Get("/hi")){
		cout<<res->status<<endl;
		cout<<res->body<<endl;
	}
	else{
		res.error();
	}

	
	switch (signal)
	{
	case 0:{
		/* Insert code */
		//cout<<Fpath;
		ifstream ifs(Fpath);
		stringstream buffer;
		
		buffer<<ifs.rdbuf();
		//cout<<sen<<endl;
		//cout<<1<<endl;
		MultipartFormDataItems item = {
			{"FileLoc",User,"",""},
			{"File",buffer.str(),File,"application/octet-stream"}
		};
		cli.Post("/insert",item);
		
		break;
	}

	case 3:{
		/*Audit*/
		MultipartFormDataItems item ={
			{"UID",User,"",""},
			{"FID",File,"",""}
		};
		if(auto res = cli.Post("/retrieve",item)){
			Fpath += User;
			auto str = res->body;
			//cout<<str<<endl;
			if(!pathexists(Fpath)){
				mkdir(Fpath.c_str(),0777);
			}
			Fpath += "/"+File;
			ofstream ofs(Fpath); 
			ofs << str;
		}
		break;
	}
	case 1: { /*Delete*/
		MultipartFormDataItems item ={
			{"UID",User,"",""},
			{"FID",File,"",""}
		};
		if(auto res = cli.Post("/delete",item)){
			cout << res->body<<endl;
		}
		break;
	}
	case 2:
	{	/*Update*/
		//cout<<Fpath<<endl;
		
		ifstream ifs(Fpath);
		stringstream buffer;
		buffer<<ifs.rdbuf();
		
		//cout <<User<<endl;
		MultipartFormDataItems item = {
			{"FileLoc",User,"",""},
			{"File",buffer.str(),File,"application/octet-stream"}
		};
		auto res=cli.Post("/update",item);
		//cout<<endl<<"CECELION"<<endl;
		break;
	}
	default:
		break;
	}

}

