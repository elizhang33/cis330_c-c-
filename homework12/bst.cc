#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
// TODO: Implement this
/*initialize the three pointers of a node */
	key = -1;
	parent = NULL;
	left = NULL;
	right = NULL;

}
// Constructor
Node::Node(int in) {
// TODO: Implement this
/*initialize the three pointers of a node and also give the key a input value */
	key = in;
	parent = NULL;
	left = NULL;
	right = NULL;
}
// Destructor
Node::~Node() {
// TODO: Implement this
}

// Add to parent of current node 
void Node::add_parent(Node* in) {
// TODO: Implement this
	parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
// TODO: Implement this
	left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
// TODO: Implement this
	right = in;
}

// Get key
int Node::get_key()
{
// TODO: Implement this
	return key;
}
// Get parent node
Node* Node::get_parent()
{
// TODO: Implement this
	return parent;
}
// Get left node
Node* Node::get_left()
{
// TODO: Implement this
	return left;
}
// Get right node
Node* Node::get_right()
{
// TODO: Implement this
	return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
// TODO: Implement this
	if (in != NULL) {
		inorder_walk(in->get_left(), to);
		in->print_info(to);
		inorder_walk(in->get_right(), to);
	} 
}

// Constructor
BST::BST()
{
// TODO: Implement this
	root = NULL;
}
// Destructor
BST::~BST()
{
// TODO: Implement this

}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
// TODO: Implement this
	Node* y = NULL;
	Node* x = root;
	while (x != NULL) {
		y = x;
		if (in->get_key() < x->get_key()) {
			x = x->get_left();
		} else {
			x = x->get_right();
		}
	}
	in->add_parent(y);
	if (y == NULL) {
		root = in;
	} else if (in->get_key() < y->get_key()) {
		y->add_left(in);
	} else {
		y->add_right(in);
	}
	
}
// Delete a node to the subtree
void BST::delete_node(Node* out)
{
// TODO: Implement this
	Node* y;
	Node* x;
	if (out->get_left() == NULL || out->get_right() == NULL) {
		y = out;
	} else {
		y = get_succ(out);
	}
	if (y->get_left() != NULL) {
		x = y->get_left();
	} else {
		x = y->get_right();
	}
	if (x != NULL) {
		x->add_parent(y->get_parent());
	}
	if (y->get_parent() == NULL) {
		root = x;
	} else if (y == (y->get_parent())->get_left() ){
		(y->get_parent())->add_left(x);
	} else {
		(y->get_parent())->add_right(x);
	}
	if (y != out) {
		Node* node;
		if (out->get_parent() == NULL) {
			root = node;
		} else if ((out->get_parent())->get_left() == out ){
			(out->get_parent())->add_left(node);
		} else {
			(out->get_parent())->add_right(node);
		}
		if (out->get_left() != NULL){
			(out->get_left())->add_parent(node);
		}
		if (out->get_right() != NULL){
			(out->get_right())->add_parent(node);
		}
	}
}
// minimum key in the BST
Node* BST::tree_min()
{
// TODO: Implement this
	
	return get_min(root);
}
// maximum key in the BST
Node* BST::tree_max()
{
// TODO: Implement this
	
	return get_max(root);
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
// TODO: Implement this
/*the left most node of the subtree is the minimum */
	while (in->get_left() != NULL) {
		in = in->get_left();
	}
	return in;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
// TODO: Implement this
/*the right most node of the subtree is the maximum */
	while (in->get_right() != NULL) {
		in = in->get_right();
	}
	return in;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{
// TODO: Implement this
	Node* y = NULL;
	if (in->get_right() != NULL) {
		return get_min(in->get_right());
	}
	y = in->get_parent();
	while (y != NULL && in == y->get_right()) {
		in = y;
		y = y->get_parent();
	}
	return y;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
// TODO: Implement this
	Node* y = NULL;
	if (in->get_left() != NULL) {
		return get_max(in->get_left());
	}
	y = in->get_parent();
	while (y != NULL && in == y->get_left()) {
		in = y;
		y = y->get_parent();
	}
	return y;
}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
// TODO: Implement this
	inorder_walk(root, to);
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
// TODO: Implement this
	
	Node* x = NULL;
	x = root;
	while (x != NULL && search_key != x->get_key()) {
		if (search_key < x->get_key()) {
			x = x->get_left();
		} else {
			x = x->get_right();
		}

	}
	return x;
}
// ---------------------------------------





