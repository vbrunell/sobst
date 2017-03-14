/*
 * Victor Brunell
 * Self Organizing Binary Search Trees
 * bst.h
*/

#include "bst.h"

/* ---Public Interfaces --- */

template <typename T>
BST<T>::BST(int th) : root{nullptr}, tvalue{th}
{}

template <typename T>
BST<T>::BST(const string input, int th) : root{nullptr}, tvalue{th}
{
	buildFromInputString( input );
}

template <typename T>
BST<T>::BST(const BST & rhs) : root{nullptr}
{
	root = clone(rhs.root);
}

// move constructor
template <typename T>
BST<T>::BST(BST&& rhs) : root{rhs.root}, tvalue{rhs.tvalue}
{
	rhs.root = nullptr;
	rhs.tvalue = 0;
}

// destructor
template <typename T>
BST<T>::~BST()
{
	makeEmpty();
}

template <typename T>
void BST<T>::buildFromInputString(const string input)
{
	// Make vector of T element tokens
	vector<T> tokens;
	istringstream theStream( input );

	// Place tokens from stream into vector
	copy(	istream_iterator<T>(theStream),
			istream_iterator<T>(),
			back_inserter<vector <T> >(tokens));

	if( !empty() )
	{
		makeEmpty();

		// Insert vector tokens into bst
		for( int i = 0; i < tokens.size(); i++ )
			insert( tokens.at(i) );
	}
	else
	{
		// Insert vector tokens into bst
		for( int i = 0; i < tokens.size(); i++ )
			insert( tokens.at(i) );
	}
}

template <typename T>
const BST<T> & BST<T>::operator=(const BST & rhs)
{
	if( this != &rhs )
	{
		makeEmpty();
		this->root = clone( rhs.root );
	}
	return *this;
}

// move assignment operator
template <typename T>
const BST<T> & BST<T>::operator=(BST && rhs)
{
	if( this != &rhs )
	{
		makeEmpty();
		std::swap(root, rhs.root);
		rhs.root = nullptr;
	}
	return *this;
}

template <typename T>
bool BST<T>::empty()
{
	bool isEmpty;
	if(root == nullptr)
		isEmpty = true;
	else
		isEmpty = false;
	return ( isEmpty );
}

/*
 *	The following public interfaces call the corresponding
 *	private versions of the functions to perform certain
*/

template <typename T>
void BST<T>::printInOrder() const
{
	printInOrder( root, true );
}

template <typename T>
void BST<T>::printLevelOrder() const
{
	printLevelOrder( root );
}

template <typename T>
int BST<T>::numOfNodes() const
{
	return numOfNodes( root );
}

template <typename T>
int BST<T>::height() const
{
	return height( root );
}

// delete all nodes from the tree
template <typename T>
void BST<T>::makeEmpty()
{
	makeEmpty( root );
}

template <typename T>
void BST<T>::insert(const T& v)
{
	insert( v, root );
}

// insert v into the tree (move instead of copy)
template <typename T>
void BST<T>::insert(T &&v)
{
	insert( std::move(v), root );
}

template <typename T>
void BST<T>::remove(const T& v)
{
	remove( v, root );
}

// search the tree for v
template <typename T>
bool BST<T>::contains(const T& v)
{
	return contains( v, root, root );
}


/* --- Private Interfaces ---
 *
 * All implemented recursively except
 * the function printLevelOrder(BSTNode *t).
*/

template <typename T>
void BST<T>::printInOrder(BSTNode *t, bool newLine ) const
{
 	if(t == nullptr)
		return;

	printInOrder(t->left, false);
	cout << t->element << " ";
	printInOrder(t->right, false);

	if( newLine )
		cout << "\n";
}

template <typename T>
void BST<T>::printLevelOrder(BSTNode * t) const
{
	if( t == nullptr )
	{
		cout << endl;
		return;
	}

	queue<BSTNode*> q;
	q.push(t); // Add root

	while ( !q.empty() )
	{
		// Print element
		BSTNode * t1 = q.front();
		cout << t1->element << " ";

		if ( t1->left != nullptr ) // Add left child
			q.push(t1->left);

		if ( t1->right != nullptr ) // Add right child
			q.push(t1->right);

		q.pop(); // Remove current node from queue
	}
	cout << endl;
}

template <typename T>
void BST<T>::makeEmpty(BSTNode* &t)
{
	if( t != nullptr )
	{
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}
	t = nullptr;
}

template <typename T>
void BST<T>::insert(const T& v, BSTNode *&t)
{
	if( t == nullptr ) // If open position, add new node
		t = new BSTNode{ v, nullptr, nullptr };
    else if( v < t->element ) // Move down left branch
		insert( v, t->left );
	else if( v > t->element ) // Move down right branch
		insert( v, t->right );
	else // Do nothing if duplicate element
		;
}

template <typename T>
void BST<T>::insert(T&& v, BSTNode *&t)
{
	if( t == nullptr )
		t = new BSTNode{ std::move(v), nullptr, nullptr };
    else if( v < t->element )
		insert( std::move(v), t->left );
	else if( v > t->element )
		insert( std::move(v), t->right );

}

template <typename T>
void BST<T>::remove(const T& v, BSTNode *&t)
{
	if( t == nullptr ) // do nothing if item not found
		return;
    if( v < t->element ) // Move down left branch
		remove( v, t->left );
	else if( v > t->element ) // Move down right branch
		remove( v, t->right );
	else if( t->left != nullptr && t->right != nullptr ) // two children
	{
		t->element = findMin( t->right )->element;
		remove( t->element, t->right );
	}
	else
	{
		BSTNode *oldNode = t;
		// Select correct branch to replace node with
		t = ( t->left != nullptr ) ? t->left : t->right;
		delete oldNode;
	}
}

template <typename T>
bool BST<T>::contains(const T& v, BSTNode *&t, BSTNode *&p)
{
	if( t == nullptr )
		return false;
   else if( v < t->element ) // Move down left branch
		return contains( v, t->left, t );
	else if( v > t->element )  // Move down right branch
		return contains( v, t->right, t );
	else
	{
		t->scount++;

		if( t->scount >= tvalue )
		{
			t->scount = 0;
			if( t == p ) // Check if found node is root, do nothing
				;
			else         // Else, perform rotation
			{
				// Cases for rotation
				if( t == nullptr )
					;
				else if( p->left == nullptr )
					rotateRChild( p );
				else if( p->right == nullptr )
					rotateLChild( p );
				else if( !(p->left->element < t->element) && !(t->element < p->left->element) )
					rotateLChild( p );
				else
					rotateRChild( p );
			}
		}
		return true;
	}
}

template <typename T>
int BST<T>::numOfNodes(BSTNode *t) const
{
	if ( t == nullptr )
		return 0;

	return 1 + numOfNodes( t->left ) + numOfNodes( t->right);
}

template <typename T>
int BST<T>::height(BSTNode *t) const
{
	if( t == nullptr )
		return -1;
	else
		return 1 + max( height( t->left ), height( t->right ) ); }

template <typename T>
typename BST<T>::BSTNode * BST<T>::clone(BSTNode *t) const
{
	 if( t == nullptr )
		return nullptr;
	 else
		return new BSTNode{ t->element, clone( t->left ), clone( t->right), t->scount };
}

template <typename T>
typename BST<T>::BSTNode * BST<T>::findMin( BSTNode *  t ) const
{
	if( t == nullptr )
		return nullptr;
	if( t->left == nullptr )
		return t;
	return findMin( t->left );
}

template <typename T>
void BST<T>::rotateLChild( BSTNode * & t ) const
{
	BSTNode * t1 = t->left; // Set t1 to parent->left
	t->left = t1->right;    // Set parent->left to parent->left->right
	t1->right = t;          // Set parent->left->right to parent
	t = t1;                 // Set parent to parent->left
}

template <typename T>
void BST<T>::rotateRChild( BSTNode * & t ) const
{
	BSTNode * t1 = t->right;
	t->right = t1->left;
	t1->left = t;
	t = t1;
}
