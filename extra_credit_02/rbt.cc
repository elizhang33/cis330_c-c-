#include "rbt.h"
/*credit to CLRS textbook, chapter 13 red-black tree*/


// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
// TODO: Implement this
/*initialize the three pointers of a node */
	key = 0;
    color = 1;
	parent = nullptr;
	left = nullptr;
	right = nullptr;

}
// Constructor
Node::Node(int in) {
// TODO: Implement this
/*initialize the three pointers of a node and also give the key a input value */
	key = in;
    color = 1;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
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

/* Change the color of current node */
void Node::change_color(int col) {
    color = col;
}
 
// Get key
int Node::get_key()
{
// TODO: Implement this
	return key;
}

int Node::get_color()
{
    return color;
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
    to << key << " " << color << endl;
}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Walk the subtree from the given node
void RBT::inorder_walk(Node* in, ostream& to)
{
// TODO: Implement this
	if (in != nil) {
		inorder_walk(in->get_left(), to);
		in->print_info(to);
		inorder_walk(in->get_right(), to);
	} 
}
 
// Constructor
RBT::RBT()
{
// TODO: Implement this
    nil = new Node(-1);
    nil->change_color(0);
    nil->add_parent(nullptr);
    nil->add_right(nullptr);
    nil->add_left(nullptr);
	root = nil;
    
}

/*helper functin for delete node  */
void RBT::delete_n(Node* in) {
    if (in != nil) {
        delete_n(in->get_left());
        delete_n(in->get_right());
        delete in;
    }  
} 

// Destructor
RBT::~RBT()
{
// TODO: Implement this
    delete_n(root);
    delete nil;
}

// rotate left at node x
void RBT::left_rotate(Node* x) {
    Node* y = x->get_right();
    x->add_right(y->get_left());
    if (y->get_left() != nil) {
        y->get_left()->add_parent(x);
    }
    y->add_parent(x->get_parent());
    if (x->get_parent() == nullptr) {
        root = y;
    } else if (x == x->get_parent()->get_left()) {
        x->get_parent()->add_left(y);
    } else {
        x->get_parent()->add_right(y);
    }
    y->add_left(x);
    x->add_parent(y);
}

// rotate right at node x
void RBT::right_rotate(Node* x) {
    Node* y = x->get_left();
    x->add_left(y->get_right());
    if (y->get_right() != nil) {
        y->get_right()->add_parent(x);
    }
    y->add_parent(x->get_parent());
    if (x->get_parent() == nullptr) {
        root = y;
    } else if (x == x->get_parent()->get_right()) {
        x->get_parent()->add_right(y);
    } else {
        x->get_parent()->add_right(y);
    }
    y->add_right(x);
    x->add_parent(y);
}

/* helper function for insert_node */
void RBT::insert_fixup(Node* in) {
    Node* y;
    while (in->get_parent()->get_color() == 1 && in->get_parent() != nil && in->get_parent()->get_parent() != nil && in->get_parent()->get_parent()->get_left() != nil && in->get_parent()->get_parent()->get_right() != nil) {
        if (in->get_parent() == in->get_parent()->get_parent()->get_left()) {
            y = in->get_parent()->get_parent()->get_right();
            if (y->get_color() == 1) {
                in->get_parent()->change_color(0);
                y->change_color(0);
                in->get_parent()->get_parent()->change_color(1);
                in = in->get_parent()->get_parent();
            } else {
                if(in == in->get_parent()->get_right()) {
                    in = in->get_parent();
                    left_rotate(in);
                } 
                in->get_parent()->change_color(0);
                in->get_parent()->get_parent()->change_color(1);
                right_rotate(in->get_parent()->get_parent());
            }
        } else {
            y = in->get_parent()->get_parent()->get_left();
             if (y->get_color() == 1) {
                in->get_parent()->change_color(0);
                y->change_color(0);
                in->get_parent()->get_parent()->change_color(1);
                in = in->get_parent()->get_parent();
            } else {
                if(in == in->get_parent()->get_left()) {
                    in = in->get_parent();
                    right_rotate(in);
                }
                in->get_parent()->change_color(0);
                in->get_parent()->get_parent()->change_color(1);
                left_rotate(in->get_parent()->get_parent());
            }
        }
    }   
    root->change_color(0);
}

// Insert a node to the subtree
void RBT::insert_node(Node* in)
{
// TODO: Implement this
    Node* y = nil;
    Node* x = root;
    //traverse the Rbt until find the right place to insert node  
    while (x != nil) {
            y = x;
            if (in->get_key() < x->get_key() && in->get_left() != nil && in->get_right() != nil) {
                    x = x->get_left();
            } else {
                    x = x->get_right();
            }
    }
    in->add_parent(y);
    if (y == nil) {
            root = in;
    } else if (in->get_key() < y->get_key()) {
            y->add_left(in);
    } else {
            y->add_right(in);
    }
    in->add_left(nil);
    in->add_right(nil);
    in->change_color(1);

   if (in->get_parent() == nullptr) {
        in->change_color(0);
        return;
    }
    if (in->get_parent()->get_parent() == nullptr) {
        return ;
    }

    insert_fixup(in);
   
}

/* helper funtion for delete */
void RBT::rb_transplant(Node* u, Node* v) {
    if (u->get_parent() == nil) {
        root = v;
    } else if (u == u->get_parent()->get_left()) {
        u->get_parent()->add_left(v);
    } else {
        u->get_parent()->add_right(v);
    }
    v->add_parent(u->get_parent());
}


/* helper function for delete */
void RBT::delete_fixup(Node* in) {
    Node* w;
    while (in != root && in->get_color() == 0 && in->get_parent() != nil && in->get_parent()->get_left() && in->get_parent()->get_right() != nil) {
        if (in == in->get_parent()->get_left()) {
            w = in->get_parent()->get_right();
            if (w->get_color() == 1) {
                w->change_color(0);
                in->get_parent()->change_color(1);
                left_rotate(in->get_parent());
                w = in->get_parent()->get_right();
            }
            if (w->get_left()->get_color() == 0 && w->get_right()->get_color() == 0) {
                w->change_color(1);
                in = in->get_parent();
            }else if (w->get_right()->get_color() == 0) {
                w->get_left()->change_color(0);
                w->change_color(1);
                right_rotate(w);
                w = in->get_parent()->get_right();
            } else {
                w->change_color(in->get_parent()->get_color());
                in->get_parent()->change_color(0);
                w->get_right()->change_color( 0);
                left_rotate(in->get_parent());
                in = root;
            }
        } else {
             w = in->get_parent()->get_left();
            if (w->get_color() == 1) {
                w->change_color(0);
                in->get_parent()->change_color(1);
                right_rotate(in->get_parent());
                w = in->get_parent()->get_left();
            }
            if (w->get_right()->get_color() == 0 && w->get_left()->get_color() == 0) {
                w->change_color(1);
                in = in->get_parent();
            }else if (w->get_left()->get_color() == 0) {
                w->get_right()->change_color( 0);
                w->change_color(1);
                left_rotate(w);
                w = in->get_parent()->get_left();
            } else {
                w->change_color(in->get_parent()->get_color());
                in->get_parent()->change_color(0);
                w->get_left()->change_color(0);
                right_rotate(in->get_parent());
                in = root;
            }

        }
    }
    in->change_color(0);
}


// Delete a node to the subtree
void RBT::delete_node(Node* out)
{
// TODO: Implement this
    Node* y = nil;
    Node* x = nil;
    y = out;

    int y_ori_color = y->get_color();
    
    if (out->get_left() == nil) {
        x = out->get_right();
        rb_transplant(out, out->get_right());
    } else if(out->get_right() == nil) {
        x = out->get_left();
        rb_transplant(out, out->get_left());
    } else {
        y = get_min(out->get_right());
        y_ori_color = y->get_color();
        x = y->get_right();
        if (y->get_parent() == out) {
            x->add_parent(y);
        } else {
            rb_transplant(y, y->get_right());
            y->add_right(out->get_right());
            y->get_right()->add_parent(y);
        }
        rb_transplant(out, y);
        y->add_left(out->get_left());
        y->get_left()->add_parent(y);
        y->change_color(out->get_color());
        }
    if (y == root && y_ori_color == 0) {
        if (x == nil) {
            delete_fixup(y);
        }else{
            delete_fixup(x);
        } 
    }
    delete out;
}

// minimum key in the RBT
Node* RBT::tree_min()
{
// TODO: Implement this
    if (root == nil) {
        return root;
    }
	
	return get_min(root);
}
// maximum key in the RBT
Node* RBT::tree_max()
{
// TODO: Implement this
    if (root == nil) {
        return root;
    }
	
	return get_max(root);
}
// Get the minimum node from the subtree of given node
Node* RBT::get_min(Node* in)
{
// TODO: Implement this
/*the left most node of the subtree is the minimum */
	while (in != nil && in->get_left() != nil) {
		in = in->get_left();
	}
	return in;
}
// Get the maximum node from the subtree of given node
Node* RBT::get_max(Node* in)
{
// TODO: Implement this
/*the right most node of the subtree is the maximum */
	while (in != nil && in->get_right() != nil) {
		in = in->get_right();
	}
	return in;
}

// Get successor of the given node
Node* RBT::get_succ(Node* in)
{
// TODO: Implement this
	Node* y = nil;
    //if current node's parent has right child, get its leftmost child
    if (in->get_right() != nil && in != nil) {
        return get_min(in->get_right());
    }
    y = in->get_parent();
    //if current node has no right sibling  
    while (y != nil && in == y->get_right() ) {
        in = y;
        y = y->get_parent();
    }
    return y;

}
// Get predecessor of the given node
Node* RBT::get_pred(Node* in)
{
// TODO: Implement this
	Node* y = nil;
        /*if current node's parent  has left child, get its rightmost child */
    if (in->get_left() != nil) {
        return get_max(in->get_left());
    }
    y = in->get_parent();
    /*if current node has no left sibling */
    while (y != nil && in == y->get_left()) {
        in = y;
        y = y->get_parent();
    }
    return y;
}
// Walk the RBT from min to max
void RBT::walk(ostream& to)
{
// TODO: Implement this
	inorder_walk(root, to);
}
// Search the tree for a given key
Node* RBT::tree_search(int search_key)
{
// TODO: Implement this
	
	Node* x;
	x = root;
	/*once the key matches, return its left or right child   */
	while (x != nil && search_key != x->get_key()) {
		if (search_key < x->get_key()) {
			x = x->get_left();
		} else {
			x = x->get_right();
		}

	}
	return x;
}
// ---------------------------------------





