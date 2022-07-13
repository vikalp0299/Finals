#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <httplib.h>
#include "shachk.h"
#include "crypto.h"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <fstream>

using namespace std;
using namespace httplib;
void getlist(){
	cout<<"1.Insert File\n2.Delete File\n3.Update\n4.Audit\n5.Exit...\n";
}
int main(){
	string UID,FID;
	#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
		auto schema = "https://Authenticator:17174";
	#else
		auto schema = "http://Authenticator:17174";
	#endif
	Client cli(schema);
	cli.set_ca_cert_path("/usr/local/cpp-httplib-0.10.8/example/ca-bundle.crt");
	cli.enable_server_certificate_verification(false);
	if(auto res = cli.Get("/hi")){
		cout << res->body <<endl;
		string resp;
		cin>>resp;
		if(auto res = cli.Post("/reply",resp,"text/plain")){
			if(resp == "Yes" || resp == "yes"){			
				UID = res->body;
				cout<<"The Obtained UID is "<<UID<<endl;
			}else{
				cout<<res->body<<endl;
				cin>>UID;
				
			}
			if(auto res = cli.Post("/UID",UID,"text/plain")){
					cout<<res->body<<endl;
					string out = res->body;
					vector<string>chk;
					boost::split(chk,out.c_str(),boost::is_any_of("\n"));
					if(chk[0] == "DISCONNECTING!"){exit(0);}
					
					do{
						getlist();
						int sig;
						cin >>sig;
						switch(sig){
							case 1: {
									cout<<"Enter the full path to the file"<<endl;	
									string fpath,hash,directory;
									vector<string>splt;
									cin >>fpath;
									boost::split(splt,fpath.c_str(),boost::is_any_of("/"));
									for (int i=0;i<splt.size()-1;i++)
										directory = directory+splt[i]+"/";
									//cout<<directory<<endl;
									
									switch(0){
										case 0: {
													encrypt(directory,splt[splt.size()-1]);
										}
										case 1:{
													fpath = "/home/do/Desktop/Finals/Client/Files/enc/enc_"+splt[splt.size()-1];
													//cout<<fpath<<endl;
													hash = getMySHA(fpath.c_str());
													cout<<"Hash to be sent: "<<hash<<endl;
										}

									}
									//Get the FID
									auto res =  cli.Get("/FID");
									FID =res->body;									
									cout << "The obtained FID  is : "<< FID <<endl;
									//send data
									ifstream ifs (fpath);
									stringstream buffer;	
									buffer<<ifs.rdbuf();
									MultipartFormDataItems item = {
										{"File",buffer.str(),FID,"application/octet-stream"},
										{"Hash",hash,"",""},
										{"Version","1.1.1.1","",""}
									};
									if(auto res = cli.Post("/insert",item))
										cout<<res->body<<endl;						
									
								break;
							}
							case 2: {
									//Enter the file ID
									cout<<"ENTER THE FID TO DELETE THE FILE"<<endl;
									cin >>FID;
									cout<<endl;
									if(auto res = cli.Post("/delete",FID,"text/plain"))
										cout<<res->body<<endl;					
								break;
							}
							case 3: {
									string version;
									cout<<"ENTER THE FID TO UPDATE THE FILE"<<endl;
									cin>>FID;
									cout<<endl;
									cout<<"ENTER THE UPDATED FILE PATH"<<endl;
									string fpath,hash,directory;
									vector<string>splt;
									cin>>fpath;
									cout<<"ENTER THE LATEST VERSION FOR THE FILE"<<endl;
									cin>>version;
									boost::split(splt,fpath.c_str(),boost::is_any_of("/"));
									
									for (int i=0;i<splt.size()-1;i++)
										directory = directory+splt[i]+"/";
										
									switch(0){
										case 0: {
													encrypt(directory,splt[splt.size()-1]);
										}
										case 1:{
													fpath = "/home/do/Desktop/Finals/Client/Files/enc/enc_"+splt[splt.size()-1];
													//cout<<fpath<<endl;
													hash = getMySHA(fpath.c_str());
													cout<<"Hash to be sent: "<<hash<<endl;
										}
										
									}
								
								ifstream ifs(fpath);
								stringstream buffer;
								buffer<<ifs.rdbuf();
								MultipartFormDataItems item ={
									{"File",buffer.str(),FID,"application/octet-stream"},
									{"Hash",hash,"",""},
									{"Version",version,"",""}
								};
								
									if(auto res = cli.Post("/update",item))
										cout<<res->body<<endl;
									
								break;
							}
							case 4: {
										cout<<"ENTER THE FID TO AUDIT THAT FILE"<<endl;
										cin>>FID;
										if(auto res = cli.Post("/audit",FID,"text/plain"))
												cout<<res->body<<endl;
								break;
							}
							case 5: {
								cout<<"BYE..."<<endl;
								exit(0);
							}
						}
					}while(1);
				}
		}
}
	else{
		res.error();
	}
	


}































