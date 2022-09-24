#include "bst.h"

/*helper functin for delete node  */
void delete_n(Node* in) {
    if (in != NULL) {
        delete_n(in->get_left());
        delete_n(in->get_right());
        delete in;

    }
    
}

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
// TODO: Implement this
/*initialize the three pointers of a node */
	key = 0;
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
    delete_n(root);

}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
// TODO: Implement this
    Node* y = NULL;
    Node* x = root;
    /*traverse the bst until find the right place to insert node  */
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
    /*node out has not left child  */
    if (out->get_left() == NULL) {
        if (out->get_parent() == NULL) {
            root = out->get_right();
        } else if (out == (out->get_parent())->get_left()) {
            (out->get_parent())->add_left(out->get_right());
        } else {
             (out->get_parent())->add_right(out->get_right());
        } 
        if (out->get_right() != NULL) {
            (out->get_right())->add_parent(out->get_parent());
        }
    } 
    /*node out has no right child  */
    else if(out->get_right() == NULL) {
        if (out->get_parent() == NULL) {
            root = out->get_left();
        } else if (out == (out->get_parent())->get_right()) {
            (out->get_parent())->add_right(out->get_left());
        } else {
             (out->get_parent())->add_left(out->get_left());
        } 
        if (out->get_left() != NULL) {
            (out->get_left())->add_parent(out->get_parent()) ;
        }

    }
    /*the remaining two cases, in which out has two children */ 
    else {
        Node* y;
        y = get_min(out->get_right());
        if (y->get_parent() != out) {
            if (y->get_parent() == NULL) {
                root = y->get_right();
            } else if (y == (y->get_parent())->get_left()) {
                (y->get_parent())->add_left(y->get_right());
            } else {
                (y->get_parent())->add_right(y->get_right());
            } 
            if (y->get_right() != NULL) {
                (y->get_right())->add_parent(y->get_parent());
            }
            y->add_right(out->get_right());
            (y->get_right())->add_parent(y);
        } 
        if (out->get_parent() == NULL) {
            root = y;
        } else if (out == (out->get_parent())->get_left()) {
            (out->get_parent())->add_left(y);
        } else {
            (out->get_parent())->add_right(y);
        } 
        if (y != NULL) {
            y->add_parent(out->get_parent());
        }
        
        y->add_left(out->get_left());
        (y->get_left())->add_parent(y);
    }
    delete out;
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
        /*if current node's parent has right child, get its leftmost child */
    if (in->get_right() != NULL) {
        return get_min(in->get_right());
    }
    y = in->get_parent();
    /*if current node has no right sibling  */
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
        /*if current node's parent  has left child, get its rightmost child */
    if (in->get_left() != NULL) {
        return get_max(in->get_left());
    }
    y = in->get_parent();
    /*if current node has no left sibling */
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
	/*once the key matches, return its left or right child   */
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





