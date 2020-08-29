/*
implementation of the self balancing functionality of the AVL tree

*/

/* Node is defined as :
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; */


int balance_factor(node* n)
{
    int l(n->left? n->left->ht : -1), r(n->right ? n->right->ht : -1);
    
    return l - r;
}

void update_height(node* n)
{
    if(!n)
        return;
    
    int 
        l(n->left ? n->left->ht : -1),
        r(n->right ? n->right->ht : -1),
        h;
    
    h = max(l,r);
    
    n->ht = h<0? 0 : h+1;
    //cout << "    node " << n->val << " new ht = " << n->ht << endl;
}

node * insert(node * root,int val)
{
    //cout << "inserting " << val << endl;
	if(! root)
        return new node({val,NULL,NULL,0});
    
    //cout << "  current node is "<< root->val << endl;
    
    if(root->val > val)
    {
   //     cout << "  to left of node " << root->val << endl;
        root->left = insert(root->left,val);
    }
    else if (root->val < val)
    {
    //cout << "  to right of node " << root->val << endl;
        root->right = insert(root->right,val);
    }
    else   
        return root;
    
    update_height(root);
    //cout << "  node " << root -> val << " ht = " << root->ht << endl;
    
    int bf(balance_factor(root));
    //cout << "  node " << root -> val << " bf = " << bf << endl;
    
    if(bf == 2)
    {//left
        bf = balance_factor(root->left);
        if(bf == 1)
        {
            //ll rotation
            node 
                        *a(root),
                        *br(root->left->right);
                    root = root->left;//b
                    root->right = a;
                    a->left = br;
                    update_height(root->right);
                    update_height(root);
        }
        else if(bf == -1)
        {
                    //lr rotation
                    node
                        *c (root->left->right), 
                        *cl(c->left),
                        *cr(c->right);
                    c->right = root;//a
                    c->left = root->left;//b
                    c->right->left = cr;
                    c->left->right = cl;
                    root = c;
                    
                    update_height(root->right);
                    update_height(root->left);
                    update_height(root);
        }
    }
    else if(bf == -2)
    {
        bf = balance_factor(root->right);
        if(bf == 1)
        {
                    //rl(root);
                    node
                        *c (root->right->left), 
                        *cl(c->left),
                        *cr(c->right);
                    c->left = root;//a
                    c->right = root->right;//b
                    c->right->left = cr;
                    c->left->right = cl;
                    root = c;
                    
                    update_height(root->right);
                    update_height(root->left);
                    update_height(root);
        }
        else if(bf == -1)
        {
                    //rr(root); 
                    node 
                        *a(root),
                        *bl(root->right->left);
                    root = root->right;//b
                    root->left = a;
                    a->right = bl;
                    update_height(root->left);
                    update_height(root);
        }
    }
    
    //cout << "done for node " << root->val << "\n";
    return root;
}