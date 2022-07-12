#include <iostream>
#include <httplib.h>
#include "shachk.h"
#include "crypto.h"
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;
using namespace httplib;
void getlist(){
	cout<<"1.Insert File\n2.Delete File\n3.Update\n4.Audit\n5.Exit...\n";
}
int main(){
	string UID;
	Client cli("Authenticator",17174);
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
				if(auto res = cli.Post("/UID",UID,"text/plain")){
					cout<<res->body<<endl;
					do{
						getlist();
						int sig;
						cin >>sig;
						switch(sig){
							case 1: {
									cout<<"Enter the full path to the file"<<endl;	
									string fpath,hash;
									vector<string>splt;
									cin >>fpath;
									boost::split(splt,fpath.c_str(),boost::is_any_of("/"));
									
									switch(0){
										case 0: {
													encrypt(splt[splt.size()-1]);
										}
										case 1:{
													fpath = "/home/do/Desktop/Finals/Client/Files/enc/enc_"+splt[splt.size()-1];
													cout<<fpath<<endl;
													hash = getMySHA(fpath.c_str());
													cout<<"Hash to be sent: "<<hash<<endl;
										}

									}
									
								break;
							}
							case 2: {break;}
							case 3: {break;}
							case 4: {break;}
							case 5: {
								cout<<"BYE..."<<endl;
								exit(0);
							}
						}
					}while(1);
				}
			}
		}
}
	else{
		res.error();
	}
	


}































