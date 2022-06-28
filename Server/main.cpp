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
namespace filesys = std::experimental::filesystem;
using namespace std;
using namespace httplib;




int main()
{  
	//BST b;
	//BST* root = b.inittree();
	User usr;
    User* root = usr.inittree();
	usr.Uinorder(root);
}
