#include <iostream>
#include <stdlib.h>
#include <queue>
#include <stdio.h>
#include "myBST.h"
#include "csphandler.h"
using namespace std;


int main()
{   BST b;
    int sig,ch;
    BST* root = b.inittree();
	do{
		cout<<"1)Insert user\n2)Delete user\n3)insert file in a user node\n4)delete file from a user node\n5)Inordertraversal\n6)FileTraversal\n\n";
		cin>>ch;
		int random = 1+(rand()%100);
		int UID;
		

		switch(ch){
			case 1 : cout<<"Your Generated UserID is "<<random<<" \nPlease note it down!\n";
					root = b.insertnode(root,random);
					break;

			case 2 : cout<<"Enter the node to be deleted\n";
					int key;
					cin>>key;
					root = b.delnode(root, key);
					break;
            
			case 3 :
					 cout<<"Your File Id is "<<random<<" \nPlease save it!\n"<<"Enter the UserID for the given file\n";
					  cin>>UID;
					  b.fndusr(root,UID,0,random);
					  break;

			case 4 : cout<<"Enter the UserID\n";
					 
					 int FID;
					 cin>>UID;
					 cout<<"Enter the FileID\n";
					 cin>>FID;

					 root = b.fndusr(root,UID,1,FID);
					 break;
            
			case 5 : b.inorder(root);
					 break;
			case 6 : cout<<"Enter the UserID whose files you want to see\n";
					 cin>>UID;
					 b.fndusr(root,UID,2);
					 break;
            
			default:  break;
		}
		cout<<"\nDo you want to continue?\nGive '1' for Yes and '0' for No\n";
		cin>>sig;
	}while(sig);
}
