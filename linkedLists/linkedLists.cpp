#include <iostream>
#include <string>


class Node
{

  public:
    std::string data;     // Holds the actual number in the node

    Node *next;     // Does the actual linking
    
    Node(std::string data)    // Constructor for nodes
    {
      this ->data = data;
      this ->next = nullptr;

      std::cout << "DEBUG: Node Made\n";      // Debug Messages
    }
};

class LinkedList
{
private:
  Node *head = nullptr;       // Establishes the member for the front of the list. Uses nullptr in initialization because it needs a value.

public:
  LinkedList()    // Default Constructor
  {
    head = nullptr;

    std::cout << "DEBUG: Linked List made\n";      // Debug messages
  }

  ~LinkedList()     // Destructor
  {
    Node *current = head;
    while (current != nullptr)
    {
      Node *nextNode = current->next;
      delete current;
      current = nextNode;
      std::cout << "DEBUG: Node Destroyed\n";      // Debug message
    }
    std::cout << "DEBUG: Linked List destroyed\n";       // Debug message
  }

  void append(std::string value)    // Appends a new node at the end of the LinkedList
  {
    Node *newNode = new Node(value);

    if(head == nullptr)
    {
      head = newNode;
      return;
    }

    Node *temp = head;      // Temp pointer used for shuffling around data

    while(temp->next != nullptr)
    {
      temp = temp->next;
    }

    temp->next = newNode;
  }

  void insert(std::string value, int p_nodePosition)      // Function to insert a new node. Indexed beginning at 0. User enters 1st, 2nd, 3rd, etc.
  {
    Node *newNode = new Node (value);

    if (p_nodePosition == 1 || head == nullptr)      // Checks if we are inserting into an empty list. Makes the new node the head, if true.
    {
      head = newNode;
      return;
    }
    
    Node *current = head;       // Current pointer used for checking against a node.
    int i = 2;
    while(current != nullptr && i < p_nodePosition) // Iterates through the nodes, adding 1 to i for every loop. Once we get to proper position, it stops.
    {
      current = current->next;
      i++;
    }

    if(current == nullptr)          // Checks if the position is out of bounds. Prevents memory leaks.
    {
      std::cout << "DEBUG: Position out of bounds\n";
      delete newNode;
      return;
    }
    
    newNode->next = current->next;          // The inserted node's next 'link' is copied from what we want BEFORE the new node.
    current->next = newNode;                // The prior node's next 'link' is now a pointer to the new node.

  }

  void delNode(int p_nodePosition)
  {
    Node *current = head;

    if(head == nullptr)
    {
      std::cout << "DEBUG: Delete: No nodes available for deletion.\n";
      return;
    }
    if(p_nodePosition == 1)
    {
      delete current;
      return;
    }
    int i = 2;
    while(current != nullptr && i < p_nodePosition)
    {
      current = current->next;
      i++;
    }
    if(current == nullptr)
    {
      std::cout << "DEBUG: Delete: Position chosen out of bounds\n";
      return;
    }

    Node* nodeToDelete = current->next;       // Basically, the what other temp pointers were. Just holds the value we want to delete.
    current->next = nodeToDelete->next;       // Relinks the two nodes where there would be a gap. 
    delete nodeToDelete;      // TECHNICALLY, dont have to do this for the program to work atp. Good to have the memory mgmt though.
  }

  void printList()    // Iterates over each Node and prints its data
  {
    Node *temp = head;
    while(temp != nullptr)      // Checks if the list is empty as it iterates through the Nodes
    {
      std::cout << temp->data << " -> ";
      temp = temp->next;
    }
    std::cout << "DEBUG: NULL" << std::endl;       // NULL signifies the end of the list
  }
};





int main()      // Main function...every cpp program needs it.
{
  LinkedList list;

  list.append("Dale");
  list.append("Ricky");
  list.append("Bobby");
  list.append("Chuck");
  list.append("Danny");
  std::cout << "The Top 5 Racers at this moment are: \n";
  list.printList();


  std::cout << "--AND SOMEBODY SNATCHES THIRD FROM OUTTA NOWHERE\n";
  list.insert("Garfunkle", 3);
  list.printList();


  std::cout << "AND A DRIVERS WRECKS INTO A BALL OF FLAMES\n";
  list.delNode(4);
  list.printList();

}
