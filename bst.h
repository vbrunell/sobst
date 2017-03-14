/*
 * Victor Brunell
 * Self Organizing Binary Search Trees
 * bst.h
*/

#ifndef SOBST
#define SOBST

#include <string>
#include <queue>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <utility>
using namespace std;

namespace sobst {

static int default_threshold_value = 1;

template <typename T>
class BST {

	public:

		BST(int th=default_threshold_value);
		BST(const string input, int th=default_threshold_value);
		BST(const BST&);
		BST(BST&&);
		~BST();
		void buildFromInputString(const string input);
		const BST & operator=(const BST & rhs);
		const BST & operator=(BST && rhs);
		bool empty();

/* --------------- Public Interfaces --------------
 *
 * They call the corresponding private versions of
 * the functions to perform certain tasks
*/
		void printInOrder() const;
		void printLevelOrder() const;
		int numOfNodes() const;
		int height() const;
		void makeEmpty();
		void insert(const T& v);
		void insert(T &&v);
		void remove(const T& v);
		bool contains(const T& v);
/* ------------------------------------------------ */

	private:

		struct BSTNode{
			int scount;
			BSTNode * left;
			BSTNode * right;
			T element;
			BSTNode(const T &theElement, BSTNode *lt, BSTNode *rt, int theCount = 0)
				: element{theElement}, scount{theCount}, left{lt}, right{rt} {}
			BSTNode(T && theElement, BSTNode *lt, BSTNode *rt, int theCount = 0)
				: element{std::move(theElement)}, scount{theCount}, left{lt}, right{rt} {}
		};

		BSTNode * root;
		int tvalue;

/* -------------- Recursive Implementations -------------- */
	void printInOrder(BSTNode *t, bool newLine) const;
	void printLevelOrder(BSTNode *t) const;
	void makeEmpty(BSTNode* &t);
	void insert(const T& v, BSTNode *&t);
	void insert(T&& v, BSTNode *&t);
	void remove(const T& v, BSTNode *&t);
	bool contains(const T& v, BSTNode *&t, BSTNode *&p);
	int numOfNodes(BSTNode *t) const;
	int height(BSTNode *t) const;
	BSTNode * clone(BSTNode *t) const;
	BSTNode * findMin( BSTNode * t ) const;
/* -------------------------------------------------------- */

	void rotateLChild( BSTNode * & t ) const;
	void rotateRChild( BSTNode * & t ) const;
};
	#include "bst.hpp"
}
#endif
