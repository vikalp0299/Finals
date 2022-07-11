#include <iostream>
#include <queue>
#include <string>
#include <mysql.h>
#include "myBST2.h"
using namespace std;

User::User(){
    UID = 0;
    IP = "127.0.0.1";
    left=right=NULL;
    back=NULL;
}
User::User(int uid,string ip){
    UID =uid;
    IP = ip;
    left=right=NULL;
    back=NULL;

}
User* User::Uinsert(User* root,int uid,string ip){
    if(!root){
		cout<<"insertingUser"<<endl;
        return new User(uid,ip);
    }
    if(uid>root->UID){
        root->right = Uinsert(root->right,uid,ip);
    }else{
        root->left = Uinsert(root->left,uid,ip);
       
    }
    return root;
}
User* User::Uminvalnode(User* root){
    User* temp = root;
    while (temp && temp->left !=NULL){
        temp = temp->left;
    }
    return temp;
}
User* User::Udelete(User* root,int uid){
    if (root == NULL){
        return root;
    }
    if(root->UID > uid){
        root->left = Udelete(root->left,uid);

    }else if(root->UID <uid){
        root->right = Udelete(root->right,uid);
    }else{
        User* temp;
        if(root->left == NULL && root->right == NULL){
            return NULL;
        }else if(root->left == NULL){
            temp = root->right;
            free(root);
            return temp;
        }else if(root->right == NULL){
            temp = root->left;
            free(root);
            return temp;
        }
        temp = Uminvalnode(root->right);
        root ->UID = temp->UID;
        root ->IP = temp->IP;
        root->back = temp->back;
        root->right = Udelete(root->right,temp->UID);

    }
    return root;
}

bool User::Exists(User* root,int uid,int sig,int fid){
    
	File f;
    if(root==NULL){
        return false;
    }
    queue<User*>q;
    User* temp = NULL;
	
    q.push(root);
    while(!q.empty()){
        temp =q.front();
        q.pop();

        if(temp->UID !=uid &&(!temp->left)&&(!temp->right)){
			//cout<<"rasputin"<<endl;
            cout<<"User doesnt exists"<<endl;
            return false;
        }
		if(temp->UID >uid && (!temp->left)){
			return false;
		}
		if(temp->UID <uid && (!temp->right)){
			return false;
		}
        if(temp->UID == uid){
            cout<<"User found"<<endl;
            break;
        }
        if(temp->UID >uid){
            q.push(temp->left);
        }
        if(temp->UID < uid){
            q.push(temp->right);
        }
    }
	switch(sig){
		
		case 0: {
					return true;
				}
		case 1: {
					bool exists = f.FileExists(temp->back,fid);
					return exists;
				}	
		default: return false;
	}
}
User* User::Ufind(User* root, int uid,int sig,int fid,string hash,string version){
    File file;
    
    if(root==NULL){
        return root;
    }
    queue<User*>q;
    User* temp = NULL;
    q.push(root);
    while(!q.empty()){
        temp =q.front();
        q.pop();

        if(temp->UID !=uid &&(!temp->left)&&(!temp->right)){
            cout<<"User doesnt exists"<<endl;
            return root;
        }
        if(temp->UID == uid){
            cout<<"User found"<<endl;
            break;
        }
        if(temp->UID >uid){
            q.push(temp->left);
        }
        if(temp->UID < uid){
            q.push(temp->right);
        }
    }
    switch(sig){
        case 0 : cout<<"Inserting File\n";
                temp->back=file.Finsert(temp->back,fid,hash,version);
                break;
        
        case 1 : cout<<"Deleting File\n";
                temp->back=file.Fdelete(temp->back,fid);
                 break;
        case 2 : cout<<"Sending User Node\n";
                return temp;
                 break;
        default : break; 
    }
    return root;
}
void User::Uinorder(User* root){
    if(!root){
        return;
    }
	File F;
	
    Uinorder(root->left);
    cout<< "UID: "<<root->UID <<endl;
	cout<<"Its corresponding files:"<<endl;
	F.Finorder(root->back);
	cout<<endl<<endl;
    Uinorder(root->right);
}

File::File(){
    FID = 0;
    left=right=NULL;
	Hash = Version = {};
	
}
File::File(int fid,string hash,string version){
    FID =fid;
	left=right = NULL;
	Hash = hash;
	Version = version;
	
}
File* File::Finsert(File* root,int fid,string hash,string version ){
    if(!root){
        return new File(fid,hash,version);
    }
    if(fid>root->FID){
        root->right = Finsert(root->right,fid,hash);
    }else{
        root->left = Finsert(root->left,fid,hash);
    }
    return root;
}
File* File::Fminvalnode(File* root){
    File* temp = root;
    while (temp && temp->left !=NULL){
        temp = temp->left;
    }
    return temp;
}
File* File::Fdelete(File* root, int fid){
    if (root == NULL){
        return root;
    }
    if(root->FID > fid){
        root->left = Fdelete(root->left,fid);

    }else if(root->FID <fid){
        root->right = Fdelete(root->right,fid);
    }else{
        File* temp;
        if(root->left == NULL && root->right == NULL){
            return NULL;
        }else if(root->left == NULL){
            temp = root->right;
            free(root);
            return temp;
        }else if(root->right == NULL){
            temp = root->left;
            free(root);
            return temp;
        }
        temp = Fminvalnode(root->right);
        root ->FID = temp->FID;
        root->right = Fdelete(root->right,temp->FID);

    }
    return root;
}
void File::Finorder(File* root){
	if(!root){
        return;
    }
    Finorder(root->left);
    cout<< "FID: "<<root->FID <<endl;
	
    Finorder(root->right);
}
File* File::FSearch(File* root,int fid,int sig,string hash, string version){
	if(root==NULL){
        return root;
    }
    queue<File*>q;
    File* temp = NULL;
    q.push(root);
    while(!q.empty()){
        temp =q.front();
        q.pop();

        if(temp->FID !=fid &&(!temp->left)&&(!temp->right)){
            cout<<"File doesnt exists"<<endl;
            return root;
        }
        if(temp->FID == fid){
            cout<<"File found"<<endl;
            break;
        }
        if(temp->FID >fid){
            q.push(temp->left);
        }
        if(temp->FID < fid){
            q.push(temp->right);
        }
    }
	switch(sig){
		case 0: {
					temp->Hash = hash;
					temp->Version = version;
					break;
				}
		case 1: { return temp;}
	}
	return root;
}

User* User::inittree(){
    //initializes tree from db
    MYSQL  *conn; 
    MYSQL_ROW row, row2;
    MYSQL_RES *res,*res2;
    User* temp = NULL;
	//cout <<1;
    int UID,FID;
	string ip,hash,version;
    conn =mysql_init(0);
    if((conn = mysql_real_connect(conn,"localhost","root","83bb9542","Storage",3306,NULL,0))==NULL){
        perror("Connection can't be established");
        return NULL;
    }

    mysql_query(conn,"Select UID,IP FROM User ORDER by Joined ASC");
    res = mysql_use_result(conn);
    while((row=mysql_fetch_row(res))!=NULL){
        UID = atoi(row[0]);
		ip = row[1];
        temp = Uinsert(temp,UID,ip);
		
		}
    
    mysql_query(conn,"Select FID,UID,Hash,Version FROM Files ORDER by SR");
    res = mysql_use_result(conn);
    while((row=mysql_fetch_row(res))!=NULL){
        FID=atoi(row[0]);
        cout<<FID<<" ";
        UID = atoi(row[1]);
		hash = row[2];
		version = row [3];
        temp = Ufind(temp,UID,0,FID,hash,version);
    }    

    
    return temp;


}
User* User::Update(User* root,int fid,int uid,string hash, string version){
	User* temp;
	File file;
	temp=Ufind(root,uid,2);
	temp->back = file.FSearch(temp->back,fid,0,hash,version);
	return root;
}

bool File::FileExists(File* root, int fid){
		if(root==NULL){
        return false;
    }
    queue<File*>q;
    File* temp = NULL;
	
    q.push(root);
    while(!q.empty()){
        temp =q.front();
        q.pop();

        if(temp->FID !=fid &&(!temp->left)&&(!temp->right)){
			//cout<<"rasputin"<<endl;
            cout<<"User doesnt exists"<<endl;
            return false;
        }
		if(temp->FID >fid && (!temp->left)){
			return false;
		}
		if(temp->FID <fid && (!temp->right)){
			return false;
		}
        if(temp->FID == fid){
            cout<<"User found"<<endl;
            break;
        }
        if(temp->FID >fid){
            q.push(temp->left);
        }
        if(temp->FID < fid){
            q.push(temp->right);
        }
    }
	return true;
}

string User::GetHash(User* root,int uid, int fid){
	File F;
	User* temp = Ufind(root,uid,2,fid);
	File* ftemp =F.FSearch(temp->back,fid,1);
	string hash = F.GetHash(ftemp);
	//cout<<hash<<endl;
	return hash;
	
}
string File::GetHash(File* root){
	//cout<<root->Hash<<endl;
	return  root->Hash;

}		

