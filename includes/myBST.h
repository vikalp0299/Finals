#ifndef MYBST_H_
#define MYBST_H_
class BST{
private:
    int ID;
    BST *left, *right, *back;
public:
    BST();
    BST(int);
    BST* insertnode(BST*, int);
    void inorder(BST*);
    BST* fndusr(BST*,int,int,int);
    BST* fndusr(BST*,int,int);
    BST* delnode(BST*,int);
    BST* minvalnode(BST*);
    BST* inittree();
};
#endif
