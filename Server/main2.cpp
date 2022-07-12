#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <queue>
#include </usr/local/cpp-httplib-0.10.6/httplib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <experimental/filesystem>
#include "myBST2.h"
#include "csphandler.h"
#include "msql.h"
#include "shachk.h"

namespace filesys = std::experimental::filesystem;
using namespace std;
using namespace httplib;

bool pathchk(string &s){
	struct stat buff;
	if(stat(s.c_str(),&buff) == 0 )
		return true;
	return false;
	
}

int main(){

	User usr;
	User* root = usr.inittree();
	
	Server svr;
	string r_addr;
	int UID,FID;
	
	


	svr.Get("/hi",[&](const Request &req, Response &res){
		r_addr = req.get_header_value("REMOTE_ADDR");
		string s = "Welcome!\nAre you a new user?\nPlease type 'Yes' or 'No'";
	res.set_content(s,"text/plain");
	});

	
	svr.Post("/reply",[&](const Request &req,Response &res){
		auto reply = req.body;
		if(reply == "Yes" || reply =="yes"){
			bool exists;
			do{	//check if the new UID already exists or not.		
				
				UID = ((rand()%rand())+(rand()%rand()))%100;
				exists= usr.Exists(root,UID,0,0);
			}while(exists);
			//insert the new value to the tree and sql.
			root = usr.Uinsert(root,UID,r_addr);
			insertUser(UID,r_addr);
			string path = "/home/authenticator/Desktop/tmpstorage/"+to_string(UID);
			mkdir(path.c_str(),0777);
			res.set_content(to_string(UID),"text/plain");
		}
		else{//Ask for User ID
			string s = "What is your User ID?";
			res.set_content(s,"text/plain");
		}
		
	});
	



	svr.Post("/UID",[&] (const	Request &req,Response &res){
		//Recieve the user Id
		UID = stoi(req.body);
		bool exists = false;
		cout<<UID<<endl;
		
		cout<<exists;
		if(!usr.Exists(root,UID,0,0)){//if the UserID isnt there
			string s= "DISCONNECTING!\nNot a correct UID!\nPlease check!!!\n";
			res.set_content(s,"text/plain");	
		}
		else{//if the UserID is there
			string s = "Please select from the following options\n";
			res.set_content(s,"text/plain");
		}

});




	svr.Get("/FID",[&](const Request &req, Response &res){
		int fid;
		bool exists=true;
		do{ 
			
			fid=((rand()%100)+(rand()%100))%100;
			exists = usr.Exists(root,UID,1,fid);
		}while(exists);	
		res.set_content(to_string(fid),"text/plain");			

});




	svr.Post("/insert",[&] (const Request &req, Response &res){
		//get file and info from DO
		auto file = req.get_file_value("File");
		auto filename = file.filename;
		auto hash = req.get_file_value("Hash");
		auto version = req.get_file_value("Version");
		
		//save info to the mysql db
		insertFile(stoi(filename),UID,hash.content,version.content);
		
		//save info to bst of bst
		root = usr.Ufind(root,UID,0,stoi(filename),hash.content,version.content);
	string path = "/home/authenticator/Desktop/tmpstorage/"+to_string(UID)+"/"+filename;
		
	
			switch(0){
				case 0:{
						ofstream out(path);
						out<<file.content;							
						
				}
				case 1:{
						string hash = getMySHA(path.c_str());
						cout<<"Recieved: "<<hash<<endl;
						fileTransferHandler(UID,stoi(filename),0);
						break;					
				}
			}

					
		
	string s = "The File has been inserted to CSP\n";
	res.set_content(s,"plain/text");
});




	svr.Post("/delete",[&](const Request &req , Response &res){
		auto fid = req.body;
		//delete the temp file if it exists
		string fpath = "/home/authenticator/Desktop/tmpstorage/"+to_string(UID)+"/"+fid;
		if(pathchk(fpath)){
			bool status = filesys::remove(fpath);
		}
		//delete from sqldb
		deleteFile(stoi(fid),UID);

		//delete from tree
		root = usr.Ufind(root,UID,1,stoi(fid),"","");

		//delete from csphandler
		fileTransferHandler(UID,stoi(fid),1);
	
		string s = "The file has been deleted!\n";
		res.set_content(s,"text/plain");
	
});




	svr.Post("/update" ,[&](const Request &req , Response &res){
		auto hash =  req.get_file_value("Hash");
		auto version = req.get_file_value("Version");
		auto File = req.get_file_value("File");

		//update hash and version detail on sqldb
		updateFile(stoi(File.filename),UID,hash.content,version.content);

		//update on tree
		root = usr.Update(root,stoi(File.filename),UID,hash.content,version.content);
		//update the temp file and send to update the file in csp 
		string path = "/home/authenticator/Desktop/tmpstorage/"+to_string(UID)+"/"+File.filename;
		//cout<<path<<endl;
		
			switch(0){
				case 0:{
					ofstream out(path);
					out<<File.content;
					
				}
				case 1:{
					fileTransferHandler(UID,stoi(File.filename),2);
					break;
				}			
			}
		
		

});




	svr.Post("/audit",[&](const Request &req, Response &res){
		auto fid = req.body;
		
			switch(0){
				case 0:{
					fileTransferHandler(UID,stoi(fid),3);
					
				}
				case 1:{
						string path = "/home/authenticator/Desktop/tmpstorage/"+to_string(UID)+"/"+fid;
						string hash = getMySHA(path.c_str());
						cout<<hash<<endl;
						
						string stored = usr.GetHash(root,UID,stoi(fid));
						cout<<"Stored HASH:"<<stored<<endl;

						int status = strcmp(hash.c_str(),stored.c_str());
						if (status == 0){
							res.set_content("SAFE","text/plain");
									
						}else{
							res.set_content("Tampered","text/plain");				
						}
						break;
				}
			}
		

});
	svr.listen("DOhandler",17174);
}
