#include "myBST.h"
#include <iostream>
#include <mysql.h>
#include <queue>
using namespace std;
BST* BST:: minvalnode(BST* root){
    BST* temp=root;
    while(temp && temp->left!=NULL){
        temp=temp->left;
    }
    return temp;

}

BST* BST::delnode(BST* root, int val){
    if(root == NULL){
        return root;
    }

    if(root->ID>val)
        root->left=delnode(root->left,val);
    else if(root->ID < val)
        root->right=delnode(root->right,val);
    else{
        if(root->left==NULL && root->right==NULL){
            return NULL;
        }
        else if (root->left == NULL) {
			BST* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			BST* temp = root->left;
			free(root);
			return temp;
		}
        BST* temp = minvalnode(root->right); 
        root->ID=temp->ID;
        root->back=temp->back;
        root->right=delnode(root->right,temp->ID);
    }
    
    return root;

}

BST::BST(){
    ID=0;
    left=right=back=NULL;
}
BST::BST(int val){
    ID=val;
    left=right=back=NULL;
}

BST* BST :: insertnode(BST* root, int val){
    if(!root){
        return new BST(val);
    }

    if(val>root->ID){
        root->right=insertnode(root->right,val);
    }
    else{
        root->left=insertnode(root->left,val);
    }
    return root;
}

void BST::inorder(BST* root){
    if(!root)
        return;
    inorder(root->left);
    cout<<root->ID<< " ";
    inorder(root->right);

}

BST* BST::fndusr(BST* root, int UID,int sig){
	
	fndusr(root,UID,sig,0);
	return root;
}

BST* BST::fndusr(BST* root, int UID,int sig,int FID=0 ){
 
  if(root==NULL){
      return root;
    }
   queue<BST*>q;
   BST* temp =NULL;
   q.push(root);
   while(!q.empty()){
       temp=q.front();
       q.pop();
       

      if(temp->ID != UID && (!temp->left) && (!temp->right) ){
            cout<<"USER DOESNT EXISTS\n";
            return root;
        } 
        if(temp->ID==UID){
           cout<<"Usr Found\n";
           break;
        }
        if(temp->ID > UID){
            
            q.push(temp->left);
        }
        if(temp->ID < UID ){
            
            q.push(temp->right);
       
        }
    }
    
        

    switch(sig){
        case 0 : cout<<"Inserting File\n";
                temp->back=insertnode(temp->back,FID);
                break;
        
        case 1 : cout<<"Deleting File\n";
                temp->back=delnode(temp->back,FID);
                 break;
        case 2 : cout<<"Traversing\n";
                inorder(temp->back);
                 break;
        default : break; 
    }
    return root;
}

BST* BST::inittree(){
    //initializes tree from db
    MYSQL  *conn; 
    MYSQL_ROW row;
    MYSQL_RES *res;
    BST* temp = NULL;

    int UID,FID;
    conn =mysql_init(0);
    if((conn = mysql_real_connect(conn,"localhost","root","83bb9542","storage",3306,NULL,0))==NULL){
        perror("Connection can't be established");
        return NULL;
    }

    mysql_query(conn,"Select * FROM User ORDER by Joined ASC");
    res = mysql_use_result(conn);
    while((row=mysql_fetch_row(res))!=NULL){
        UID = atoi(row[0]);
        temp = insertnode(temp,UID);
    }
    mysql_query(conn,"Select FID,UserID FROM Files ORDER by AddedAt ASC");
    res = mysql_use_result(conn);
    while((row=mysql_fetch_row(res))!=NULL){
        FID=atoi(row[0]);
        cout<<FID<<" ";
        UID = atoi(row[1]);
        temp = fndusr(temp,UID,0,FID);
    }    

    
    return temp;


}
