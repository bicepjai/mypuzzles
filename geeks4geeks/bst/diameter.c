#include <stdio.h>
#include <stdlib.h>
 
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct node
{
    int data;
    struct node* left;
    struct node* right;
};
 
/* function to create a new node of tree and returns pointer */
struct node* newNode(int data);
 
/* returns max of two integers */
int max(int a, int b);
 
/* function to Compute height of a tree. */
int height(struct node* node);
 
/* Function to get diameter of a binary tree */
int diameter(struct node * tree)
{
   /* base case where tree is empty */
   if (tree == 0)
     return 0;
 
  /* get the height of left and right sub-trees */
  int lheight = height(tree->left);
  int rheight = height(tree->right);
 
  /* get the diameter of left and right sub-trees */
  int ldiameter = diameter(tree->left);
  int rdiameter = diameter(tree->right);
 
  /* Return max of following three
   1) Diameter of left subtree
   2) Diameter of right subtree
   3) Height of left subtree + height of right subtree + 1 */
  return max(lheight + rheight + 1, max(ldiameter, rdiameter));
} 

int maxDepth(struct node* node) 
{
   if (node==NULL) 
       return 0;
   else
   {
       /* compute the depth of each subtree */
       int lDepth = maxDepth(node->left);
       int rDepth = maxDepth(node->right);
 
       /* use the larger one */
       if (lDepth > rDepth) 
           return(lDepth+1);
       else return(rDepth+1);
   }
}

int getnodedia(struct node * root) {
  if (root==NULL) 
      return 0;
  else
		return (1+maxDepth(root->left) + maxDepth(root->right));
}

int mydiameter(struct node * tree)
{
   /* base case where tree is empty */
   if (tree == 0)
     return 0;
 
  /* get the height of left and right sub-trees */
	int rootdia = getnodedia(tree);
  int leftdia = getnodedia(tree->left);
  int rightdia = getnodedia(tree->right);

  return max(rootdia, max(leftdia, rightdia));
}


/* UTILITY FUNCTIONS TO TEST diameter() FUNCTION */
 
/*  The function Compute the "height" of a tree. Height is the 
    number f nodes along the longest path from the root node 
    down to the farthest leaf node.*/
int height(struct node* node)
{
   /* base case tree is empty */
   if(node == NULL)
       return 0;
 
   /* If tree is not empty then height = 1 + max of left 
      height and right heights */   
   return 1 + max(height(node->left), height(node->right));
} 
 
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newNode(int data)
{
  struct node* node = (struct node*)
                       malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
 
  return(node);
}
 
/* returns maximum of two integers */
int max(int a, int b)
{
  return (a >= b)? a: b;
}    
 
/* Driver program to test above functions*/
int main()
{
 
  /* Constructed binary tree is 
            1
          /   \
        2      3
      /  \
    4     5
  */
  struct node *root = newNode(1);
  root->left        = newNode(2);
  //root->right       = newNode(3);
  root->left->left  = newNode(4);
  root->left->right = newNode(5);
	root->left->right->right = newNode(5);
	root->left->right->right->right = newNode(5);
 
  printf("Diameter of the given binary tree is %d\n", diameter(root));
	printf(" MY Diameter of the given binary tree is %d\n",  mydiameter(root));
 
  getchar();
  return 0;
}