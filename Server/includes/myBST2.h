#ifndef MYBST2_H_
#define MYBST2_H_

#include <string>
using std::string;

class File{
    private:
    int FID;
    string hash,version;
    File* left,*right;
    public:
    File();
    File(int,string,string);
    File* Finsert(File*,int,string,string);
    File* Fdelete(File*,int);
    File* Fminvalnode(File*);
    File* Ffind();
    void Finorder(File* root);
	File* FSearch(File*, int,int,string,string);
	bool FileExists(File*,int);
	string GetHash(File*);
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
    User* Ufind(User*, int,int,int,string,string);
    void Uinorder(User*);
	User* inittree();
	bool Exists(User*, int,int,int);
	User* Update(User*, int,int,string,string);
	string GetHash(User*,int,int);
	
};

#endif
