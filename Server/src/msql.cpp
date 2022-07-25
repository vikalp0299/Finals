#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <cstring>
#define BUF_LEN 20
#define MAX 100


using namespace std;

MYSQL* conn;

void connect(){
	conn = mysql_init(0);
	if((conn = mysql_real_connect(conn,"localhost","root","83bb9542","Storage",3306,NULL,0)) == NULL){
        return ;
    }
}

void insertUser(int uid, string ipaddr,string passhash){
	
	connect();
	
	string s;
    s="INSERT INTO User(UID,IP,PasswordHash,Counter) VALUES("+to_string(uid)+",\""+ipaddr+"\",\""+passhash+"\","+to_string(0)+")";
	mysql_query(conn,s.c_str());
	cout<<s<<endl;
   


}
int getCount(int uid,string ip){
	connect();
	MYSQL_ROW row;
	MYSQL_RES *res;
	string s;
	s= "Select Counter from User where UID ="+to_string(uid)+" and IP =\""+ip+"\"";
	
	mysql_query(conn,s.c_str());
	res= mysql_use_result(conn);
	row = mysql_fetch_row(res);
	
	return atoi(row[0]);
	
}
void updateCount(int uid,string ip){
	
	MYSQL_ROW row;
	MYSQL_RES *res;
	string s;
	int count = getCount(uid,ip);
	count++;
	connect();
	cout<<count<<endl<<"code reach check"<<endl;
	s= "Update User Set Counter = "+to_string(count)+" where UID = "+to_string(uid);
	cout<<s<<endl;
	mysql_query(conn,s.c_str());
	 

}
string getPass(int uid,string ip){
	connect();
	MYSQL_ROW row;
	MYSQL_RES *res;
	
	string s;
	s= "Select PasswordHash from User where UID = "+to_string(uid)+" and IP =\""+ip+"\"";
	mysql_query(conn,s.c_str());
	res= mysql_use_result(conn);
	row = mysql_fetch_row(res);
	return row[0];
}
void deleteUser(int uid){
	connect();
	MYSQL_ROW row;
	MYSQL_RES *res;
	//MYSQL_STMT *stmt;
	//MYSQL_BIND bnd[2];
	
	string s = "Delete From Files Where UID = "+to_string(uid);
	mysql_query(conn,s.c_str());
	s.clear();
	s = "Delete From User Where UID = "+to_string(uid);
	mysql_query(conn,s.c_str());
	connect();
	s="select* from Files order by SR,FID";
	mysql_query(conn,s.c_str());
	res = mysql_use_result(conn);
	int i =1;
	string SR;
	
	while((row=mysql_fetch_row(res))!=NULL){
			SR =row[0];
			cout<<SR<<endl;
			connect();
			string q = "Update Files Set SR = "+to_string(i)+" Where SR = "+SR;
			cout<<q<<endl;
			mysql_query(conn,q.c_str());
			i++;
	}
}

int GetSR(string table){
	connect();
	MYSQL_ROW row;
	MYSQL_RES *res;
	int SR = 1;
	string s;
	s= "Select * from "+table+" order by SR DESC limit 1";
	mysql_query(conn,s.c_str());
	res= mysql_use_result(conn);
	row = mysql_fetch_row(res);
	
	if(row !=NULL){
		SR = atoi(row[0])+1;
	}
	return SR;
	
}



void updateFile(int fid,int uid, string hash, string version){
	
	//MYSQL_ROW row;
	//MYSQL_RES *res;
	//MYSQL_STMT *stmt;
	//MYSQL_BIND bnd[2];
	
	string s;
	connect();	
	s = "Update Files SET Hash = \""+hash+"\", Version =\""+version+"\" WHERE FID = "+to_string(fid)+" AND UID = "+to_string(uid);
	//s =  "INSERT into Verhash(SR,UID,FID,Hash,Version) Values("+to_string(sr)+","+to_string(uid)+","+to_string(fid)+",\""+hash+"\",\""+version+"\")";
	cout<<s<<endl;
	mysql_query(conn,s.c_str());
	


	//s.clear();
    


}


void insertFile(int fid,int uid,string hash,string version){
	
	int sr;
	sr = GetSR("Files");
	connect();
	cout<<sr<<endl;
	string s;
    s="INSERT INTO Files(SR,FID,UID,Hash,Version) VALUES("+to_string(sr)+","+to_string(fid)+","+to_string(uid)+",\""+hash+"\",\""+version+"\")";
	//cout<<s;
	mysql_query(conn,s.c_str());

}
void deleteFile(int fid,int uid){
	connect();
	MYSQL_ROW row;
	MYSQL_RES *res;
	//MYSQL_STMT *stmt;
	//MYSQL_BIND bnd[2];
	string s= "Select SR From Files Where FID = "+to_string(fid)+" and UID= "+to_string(uid);
	mysql_query(conn,s.c_str());
	res =mysql_use_result(conn);
	row = mysql_fetch_row(res);
	int Row = atoi(row[0]);
	cout<<Row<<endl;
	s.clear();
	connect();
	s= "Select * from Files order by SR DESC limit 1";
	mysql_query(conn,s.c_str());
	res= mysql_use_result(conn);
	row = mysql_fetch_row(res);
	int sr = atoi(row[0]);
	connect();
	s = "Delete From Files Where FID = "+to_string(fid)+" and UID= "+to_string(uid);
	mysql_query(conn,s.c_str());
	s.clear();
	int i;
	for(i=Row; i<=sr;i++){
		connect();
		s = "Update Files Set SR = "+to_string(i)+" Where SR = "+to_string(i+1);
		mysql_query(conn,s.c_str());
		s.clear();
	}
	
}

