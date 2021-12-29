#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

/**
 * @brief A linked list node. It is a header linked list. It contains informatoin of a book.
 * 
 */
typedef struct node {
    char title[50];
	char author[50];
	char publisher[50];
	unsigned int stock;
	unsigned int year;
    struct node *next;
} Node;

/**
 * @brief Saves a list to a file name. If the file is not found it will create a new one.
 * 
 * @param head LInked List head
 * @param filename The filename to save to.
 */
void save_list(Node * head, char *filename);

/**
 * @brief Pushs/Adds a book to a linked list. Will segment fault if the given list is NULL
 * 
 * @param head An initialized list.
 * @param title Book property
 * @param author Book property
 * @param publisher Book property
 * @param stock Book property
 * @param year Book property
 */
void push_list(Node * head, char *title, char *author, char *publisher, int stock, int year);

/**
 * @brief Removes a list by a specified index of the element
 * 
 * @param head The linked list to navigate through
 * @param id The index
 */
void remove_list_by_id(Node *head, int id);

/**
 * @brief Prints a list to stdout
 * 
 * @param head THe linked list
 */
void print_list(Node * head);

/**
 * @brief Prints a node to stdout
 * 
 * @param node The node
 */
void print_node(Node * node);

/**
 * @brief Sorts a list based on the given key.
 * 
 * @param head The list to sort
 * @param key An interger ranging from 1 to 5 that determines the sorting method
 * \n 1 - Sorts by title
 * \n 2 - Sorts by author
 * \n 3 - Sorts by publisher
 * \n 4 - Sorts by year
 * \n 5 - Sorts by stock
 * 
 * Any other intergers will result in no changes.
 */
void sort_list(Node * head, int key);

/**
 * @brief Swaps two nodes in a linked list given its indexes. i and j are interchangable.
 * 
 * @param head The linked list to modify
 * @param i The first node
 * @param j The second node
 */
void swap_node(Node * head, int i, int j);

/**
 * @brief Copies the contents of a node to another node. It does not transfer the next pointers, only the contents
 * 
 * @param a The source node.
 * @param b The destivation node.
 */
void copy_node(Node * a, Node * b);

/**
 * @brief Edits a node from a linked list in a certain index.
 * 
 * @param head The head to navigate through.
 * @param index The index.
 */
void edit_node(Node * head, int index, char *title, char *author, char *publisher, int stock, int year);

/**
 * @brief Returns an interger that corresponds to the number of elements in the linked list
 * 
 * @param node The linked list to calculate
 * @return int - The size of the linked list
 */
int list_size(Node * node);

/**
 * @brief Get the node object from a linked list in a certain index. Will return NULL if the element does not exist
 * 
 * @param head The linked list to navigate through.
 * @param index The index of the element.
 * @return The node object or NULL.
 */
Node *get_node(Node *head, int index);

/**
 * @brief Initializes a linked list.
 * 
 * @param title Book property
 * @param author Book property
 * @param publisher Book property
 * @param stock Book property
 * @param year Book property
 * @return Node* The linked list.
 */
Node *init_list(char *title, char *author, char *publisher, int stock, int year);

/**
 * @brief Loads a linked list from a file
 * 
 * @param filename the filename to load from
 * @return Node* The loaded linked list.
 */
Node *load_list(char *filename);

#endif