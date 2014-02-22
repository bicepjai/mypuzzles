#include<stdio.h>
#include<stdlib.h>

typedef struct _node
{
	int data;
	struct _node *left,*right;
}node;

node *makenode(int);
void setleft(node *,int);
void setright(node *,int);
void preorder(node *);
void postorder(node *);
void inorder(node *);
int depth(node *,int);
int diameterOfTree(node * root);

node *q,*k;
int l=0,d=1;
int main()
{
	node *root,*p,*q;
	int x,f;
	// printf("\nEnter the root :");
	scanf("%d",&x);
	root=makenode(x);
	// printf("\nEnter the data(-1 to stop) :");
	scanf("%d",&x);
	while(x!=-1)
	{
		p=root;
		while(p!=NULL)
		{
			q=p;
			if(x<p->data)
			{
				p=p->left;
			}
			else
			{
				p=p->right;
			}
		}
		if(x<q->data)
		{
			setleft(q,x);
		}
		else
		{
			setright(q,x);
		}
		// printf("\nEnter the data(-1 to stop) :");
		scanf("%d",&x);
	}
	// printf("\nPreorder traversal is \n");
	preorder(root);
	
	// printf("\nPostorder traversal is \n");
	postorder(root);
	
	// printf("\nInorder traversal is \n");
	inorder(root);
	
	// printf("\nDepth of the tree is \n");
	f=depth(root,l);
	// printf("\n%d",f+1);
	
	// printf("\nDiameter of the tree is \n");
	f=diameterOfTree(root);
	// printf("\n%d",f);

	// printf("\n");
	return 1;
}
node *makenode(int x)
{
	node * temp;
	temp=(node *)malloc(sizeof(node));
	temp->data=x;
	temp->left=NULL;
	temp->right=NULL;
	return(temp);
}
void setleft(node *p,int x)
{
	node *temp;
	if(p==NULL)
	{
		// printf("Error");
	}
	temp=makenode(x);
	p->left=temp;
}
void setright(node *p,int x)
{
	node *temp;
	if(p==NULL)
	{
		// printf("Error");
	}
	temp=makenode(x);
	p->right=temp;
}
void inorder(node *p)
{
	if(p!=NULL)
	{
		inorder(p->left);
		// printf("%d\t",p->data);
		inorder(p->right);
	}
}
void postorder(node *p)
{
	if(p!=NULL)
	{
		postorder(p->left);
		postorder(p->right);
		// printf("%d\t",p->data);
	}
}
void preorder(node *p)
{
	if(p!=NULL)
	{
		// printf("%d\t",p->data);
		preorder(p->left);
		preorder(p->right);
	}
}
int depth(node *p,int l)
{
	if(p!=NULL)
	{
		// printf("\n d=%d l=%d",d,l);
		if(l>d)
			d=l;
		depth(p->left,l+1);
		depth(p->right,l+1);
	}
	return d;
}

int diameterOfTree(node * root) {
/* For your reference
   struct node {
	struct node *left,*right;
	int val;
};
*/
	int dl = 0, dr = 0, l=0;
	if (root->left != NULL)
		dl = depth(root->left,l) - 1;
	else
		dl = 0;
	// printf("\n dl = %d",dl);
	
	l=0;
	if(root->right != NULL)
		dr = depth(root->right,l) - 1;
	else
		dr = 0;
	// printf("\n dr = %d",dr);
	return dl + dr;
}