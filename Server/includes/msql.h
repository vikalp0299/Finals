#ifndef MSQL_H_
#define MSQL_H_
#pragma once
#include <string>
using std::string;

void connect();
void insertUser(int uid, string ipaddr,string);
void deleteUser(int uid);
int GetSR(string);
void insertFile(int fid, int uid, string hash,string version);
void deleteFile(int fid,int uid);
void updateFile(int fid,int uid, string hash, string version);
int getCount(int,string);
string getPass(int,string);
void updateCount(int,string); 
#endif
