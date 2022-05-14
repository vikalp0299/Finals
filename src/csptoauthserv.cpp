#include <iostream>
#include <stdio.h>
#include </usr/local/cpp-httplib-0.10.6/httplib.h>
#include <sys/stat.h>
#include <string>

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
			cout << "File doesn't exists\n";
			return;
		}
	}

	Client cli("localhost",17171);
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
		
		ifstream ifs (Fpath);
		stringstream buffer;
		buffer << ifs.rdbuf();

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
		if(auto res = cli.Post("/retrive",item)){
			Fpath += User;
			auto str = res->body;
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
		if(auto res = cli.Post("/Delete",item)){
			cout << res->body<<endl;
		}
		break;
	}
	case 2:
	{	/*Update*/
		ifstream ifs(Fpath);
		stringstream buffer;
		buffer << ifs.rdbuf();
		MultipartFormDataItems item = {
			{"FileLoc",User,"",""},
			{"File",buffer.str(),File,"application/octet-stream"}
		};
		cli.Post("/update",item);
		break;
	}
	default:
		break;
	}

}

