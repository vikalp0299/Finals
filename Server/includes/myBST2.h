#ifndef MYBST2_H_
#define MYBST2_H_

#include <string>
using std::string;


class File{
    private:
    int FID;
    File* left,*right;
	string Hash,Version;
public:
    File();
    File(int,string,string);
    File* Finsert(File*,int,string hash ={},string version={});
    File* Fdelete(File*,int);
    File* Fminvalnode(File*);
    File* Ffind();
    void Finorder(File* root);
	File* FSearch(File*, int,int,string hash ={}, string version = {});
	bool FileExists(File*,int);
	string GetHash(File*);
	string Freturnfiles(File*);
};

class User{
    private:
    int UID;
    string IP;
    User* left,*right;
    File* back;
public:
    User();
    User(int,string);
    User* Uinsert(User*,int,string);
    User* Udelete(User*, int);
    User* Uminvalnode(User*);
    User* Ufind(User*, int,int,int fid =0,string hash = {},string version ={});
    void Uinorder(User*);
	User* inittree();
	bool Exists(User*, int,int,int);
	User* Update(User*, int,int,string,string);
	string GetHash(User*,int,int);
	File* GetBack(User*);
};
 

#endif
