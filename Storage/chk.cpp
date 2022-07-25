#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include </usr/local/cpp-httplib-0.10.6/httplib.h>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <string.h>
#include<experimental/filesystem>

namespace filesys = std::experimental::filesystem;
using namespace std;
using namespace httplib;

string dump_headers(const Headers &headers) {
  string s;
  char buf[BUFSIZ];

  for (const auto &x : headers) {
    //cout<<x.first<<endl;
    snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
    s += buf;
  }

  return s;
}

bool pathchk(string &s){
	struct stat buff;
	if(stat(s.c_str(),&buff) == 0 )
		return true;
	return false;
	
}

int main(){

 	#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
		SSLServer svr ("./Storage.pem","./Storage-key.pem");
	#else
  		Server svr;
	#endif
  stringstream buffer;
  string r_addr, r_port;
  int UID,FID;  
  svr.Get("/hi",[&](const Request &req, Response &res){
    res.set_content("Connection established ","text/plain");
  });
 
	svr.Post("/insert", [&](const Request &req, Response &res){
			auto file = req.get_file_value("File");
			auto filename = file.filename;
			auto fileloc = req.get_file_value("FileLoc");
			auto UID = fileloc.content;
			string fpath = "/home/storage/Desktop/storage/"+UID;
			if(!pathchk(fpath)){
				mkdir(fpath.c_str(),0777);
				cout<<"Directory Created"<<endl;			
			}

			fpath+="/"+filename;
			
			ofstream ofs(fpath);
			ofs<<file.content;	
			cout<<"File added"<<endl;
			res.set_content("done","text/plain");	
	});
  
	svr.Post("/delete",[&](const Request &req, Response &res){
			auto uid = req.get_file_value("UID");
			auto uidf=uid.content;
			auto fid = req.get_file_value("FID");
			auto fidf=fid.content;
	
			string fpath = "/home/storage/Desktop/storage/"+uidf+"/"+fidf;
			
			if(pathchk(fpath)){
				
				bool status = filesys::remove(fpath);
				if(status ==true)	
					res.set_content("Done","text/plain");
				else
					res.set_content("CheckFilenumber","text/plain");			
			}
			else{
				res.set_content("Nonexistent","text/plain");		
			}	
			cout<<"Deleted"<<endl;

 	});
	svr.Post("/update",[&](const Request &req, Response &res){
		auto loc = req.get_file_value("FileLoc");
		auto uid = loc.content;
		auto file = req.get_file_value("File");
		auto filename = file.filename;
		string fpath = "/home/storage/Desktop/storage/";
		fpath+=uid+"/"+filename;
		if(pathchk(fpath)){
			bool status = filesys::remove(fpath);
			if(status){
				cout<<"Removed"<<endl;	
			}
			
		}
		ofstream out(fpath);
		out<<file.content;
		cout<<"File Updated"<<endl;
		
		
	});
	
	svr.Post("/retrieve", [&](const Request &req, Response &res){
		auto user = req.get_file_value("UID");
		auto file = req.get_file_value("FID");
		string path =  "/home/storage/Desktop/storage/"+user.content+"/"+file.content;
		
		ifstream ifs(path);
		stringstream buffer;
		buffer<<ifs.rdbuf();
		
		res.set_content(buffer.str(),"plain/text");
		cout<<"File Sent"<<endl;
});
    
    svr.listen("authHandler",17171);
    
}
