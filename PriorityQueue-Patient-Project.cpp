// PriorityQueue-Patient-Project.cpp
//  demonstrates priority queue with linkked list in a hospital patient scenario
#include <iostream>
#include <vector>
using namespace std;
////////////////////////////////////////////////////////////////
class Patient
{
private:
    int ssn, age, priority;
    string name, gender, medcondition;

public:
    //--------------------------------------------------------------
    Patient(int s, string n, int a, string g, string mc, int p) : // constructor
                                                                  ssn(s), name(n), age(a), gender(g), medcondition(mc), priority(p)
    {
    }
    //--------------------------------------------------------------
    void displayPatient() // function that displays the patient's information
    {
        cout << endl;
        cout << "Patient's Priority: " << priority; // displays Patient's Priority Number
        cout << ", ";
        cout << "SSN: " << ssn; // displays Patient's SSN#
        cout << ", ";
        cout << "Name: " << name; // displays Patient's Name
        cout << ", ";
        cout << "Age: " << age; // displays Patient's Age
        cout << ", ";
        cout << "Gender: " << gender; // displays Patient's Gender
        cout << ", \n";
        cout << "Medical Condition: " << medcondition; // displays Patient's Medical Condition
        cout << endl;
    }
    //--------------------------------------------------------------

    int getPriority() // get Priority number
    {
        return priority;
    }

    int getSSN() // get SSN
    {
        return ssn;
    }

    string getName() // get Name
    {
        return name;
    }

    string getMedCondtion() // get Medical Condition
    {
        return medcondition;
    }

    void setPriority(int priority)
    {
        this->priority = priority;
    }

}; // end class issue
////////////////////////////////////////////////////////////////
class Link
{
public:
    Patient *patient; // data item
    Link *pNext;      // next link in list

    Link(Patient *patient) : patient(patient), pNext(NULL) {}

    void displayLink()
    {
        patient->displayPatient();
    }
};
////////////////////////////////////////////////////////////////
class LinkList
{
private:
    Link *pFirst; // ptr to first link on list
    Link *sorted;

public:
    LinkList() : pFirst(NULL) {}

    ~LinkList()
    {
        Link *pCurrent = pFirst;
        while (pCurrent != NULL)
        {
            Link *pOldCur = pCurrent;
            pCurrent = pCurrent->pNext;
            delete pOldCur;
        }
    }
    //-------------------------------------------------------------
    Link *getpFirst() // get pFirst
    {
        return pFirst;
    }
    //-------------------------------------------------------------
    bool isEmpty()
    {
        return pFirst == NULL;
    }
    //-------------------------------------------------------------
    void insert(int patSSN, string patName, int patAge, string patGender, string patMedCondition, int patPriority) // insert item
    {
        Patient *pat = new Patient(patSSN, patName, patAge, patGender, patMedCondition, patPriority);
        Link *pNewLink = new Link(pat);

        if (pFirst == NULL || pat->getPriority() < pFirst->patient->getPriority())
        {
            pNewLink->pNext = pFirst;
            pFirst = pNewLink;
        }
        else
        {
            Link *pCurrent = pFirst;
            while (pCurrent->pNext != NULL && pat->getPriority() >= pCurrent->pNext->patient->getPriority())
            {
                pCurrent = pCurrent->pNext;
            }
            pNewLink->pNext = pCurrent->pNext;
            pCurrent->pNext = pNewLink;
        }
    }
    //-------------------------------------------------------------
    Link *findPatSSN(int findSSN)
    {
        Link *pCurrent = pFirst;
        while (pCurrent != NULL)
        {
            if (pCurrent->patient->getSSN() == findSSN)
            {
                return pCurrent;
            }
            pCurrent = pCurrent->pNext;
        }
        return NULL;
    }
    //-------------------------------------------------------------
    Link *findPatName(string findName)
    {
        Link *pCurrent = pFirst;
        while (pCurrent != NULL)
        {
            if (pCurrent->patient->getName() == findName)
            {
                return pCurrent;
            }
            pCurrent = pCurrent->pNext;
        }
        return NULL;
    }
    //-------------------------------------------------------------
    Link *findPatPrior(int findPrior)
    {
        Link *pCurrent = pFirst;
        while (pCurrent != NULL)
        {
            if (pCurrent->patient->getPriority() == findPrior)
            {
                return pCurrent;
            }
            pCurrent = pCurrent->pNext;
        }
        return NULL;
    }
    //-------------------------------------------------------------
    void removeFirst()
    {
        Link *pTemp = pFirst;
        pFirst = pFirst->pNext;
        delete pTemp;
    }
    //-------------------------------------------------------------
    bool remove(int removeSSN)   // remove link with given key
    {                            //(assumes non-empty list)
        Link *pCurrent = pFirst; // search for link
        Link *pPrevious = pFirst;
        while (pCurrent->patient->getSSN() != removeSSN)
        {
            if (pCurrent->pNext == NULL)
                return false; // didn't find it
            else
            {
                pPrevious = pCurrent; // go to next link
                pCurrent = pCurrent->pNext;
            }
        }                                       // found it
        if (pCurrent == pFirst)                 // if first link,
            pFirst = pFirst->pNext;             // change first
        else                                    // otherwise,
            pPrevious->pNext = pCurrent->pNext; // bypass it
        delete pCurrent;                        // delete link
        return true;                            // successful removal
    }
    //-------------------------------------------------------------
    void displayList() // display the list
    {
        cout << "List (first-->last): \n";
        Link *pCurrent = pFirst; // start at beginning of list
        while (pCurrent != NULL) // until end of list,
        {
            pCurrent->displayLink();    // print data
            pCurrent = pCurrent->pNext; // move to next link
        }
        cout << endl;
    }
    //--------------------------------------------------------------
    bool uniquePatSSN(int uniqueSSN) // method that checks if SSN is Unique
    {
        Link *pCurrent = pFirst;
        while (pCurrent != NULL)
        {
            if (pCurrent->patient->getSSN() == uniqueSSN)
            {
                return true;
            }
            pCurrent = pCurrent->pNext; // move to next link
        }
        return false; // returns false when it is unique
    }
    //--------------------------------------------------------------
    bool uniquePatPrior(int uniquePrior) // method that checks if Priority is Unique
    {
        Link *pCurrent = pFirst;
        while (pCurrent != NULL)
        {
            if (pCurrent->patient->getPriority() == uniquePrior)
            {
                return true;
            }
            pCurrent = pCurrent->pNext; // move to next link
        }
        return false; // returns false when it is unique
    }
    //--------------------------------------------------------------
    /*Link *getTail(Link *cur)
    {
        while (cur != NULL && cur->pNext != NULL)
            cur = cur->pNext;
        return cur;
    }

    Link *partition(Link *head, Link *end, Link **newHead, Link **newEnd)
    {
        Link *pivot = end;
        Link *prev = NULL, *cur = head, *tail = pivot;
        // During the time of partition, both the head and end of the list
        // might change and the changes will be updated in the newHead and
        // newEnd variables
        while (cur != pivot)
        {
            if (cur->patient->getPriority() < pivot->patient->getPriority())
            {
                // The first node that will be having value less than the
                // pivot node value will become the new head
                if ((*newHead) == NULL)
                    (*newHead) = cur;
                prev = cur;
                cur = cur->pNext;
            }
            else // If the value of the cur node is greater than that of the pivot
            {
                // We will move the cur node to next of tail, and will update tail
                if (prev)
                {
                    prev->pNext = cur->pNext;
                }
                Link *tmp = cur->pNext;
                cur->pNext = NULL;
                tail->pNext = cur;
                tail = cur;
                cur = tmp;
            }
        }
        // If the data of the pivot node is smallest in the
        // current list, then we will make pivot as the head
        if ((*newHead) == NULL)
            (*newHead) = pivot;
        // newEnd will be updated to the current last node
        (*newEnd) = tail;
        // Finally, we will return the pivot node
        return pivot;
    }
    // Quick sort recursive function
    Link *quickSortRecur(Link *head, Link *end)
    {
        // base condition
        if (!head || head == end)
            return head;
        Link *newHead = NULL, *newEnd = NULL;
        // We will call the partition function and it will partition the list
        // and will also update newHead and newEnd
        // it will return the pivot node
        Link *pivot = partition(head, end, &newHead, &newEnd);
        // If our pivot is the smallest element in the current list
        // then there is no need to recur for the left part of the list
        if (newHead != pivot)
        {
            Link *tmp = newHead;
            while (tmp->pNext != pivot)
                tmp = tmp->pNext;
            tmp->pNext = NULL;
            // Now we will recur for the list before the pivot
            newHead = quickSortRecur(newHead, tmp);
            tmp = getTail(newHead);
            tmp->pNext = pivot;
        }
        // Now we will recur for the list after the pivot
        pivot->pNext = quickSortRecur(pivot->pNext, newEnd);
        return newHead;
    }
    // Ths is the function for quicksort.
    void quickSort(Link **headRef)
    {
        (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
        return;
    }*/
    //-------------------------------------------------------------
    void sortedInsert(Link* newnode)
    {
        // Special case for the head end
        if (sorted == NULL ||
            sorted->patient->getPriority() >= newnode->patient->getPriority())
        {
            newnode->pNext = sorted;
            sorted = newnode;
        }
        else
        {
            Link* pCurrent = sorted;
 
            /* Locate the node before the
               point of insertion */
            while (pCurrent->pNext != NULL &&
                   pCurrent->pNext->patient->getPriority() < newnode->patient->getPriority())
            {
                pCurrent = pCurrent->pNext;
            }
            newnode->pNext = pCurrent->pNext;
            pCurrent->pNext = newnode;
        }
    }
    
    void insertionSort(Link* headref)
    {
        // Initialize sorted linked list
        sorted = NULL;
        Link *pCurrent = pFirst;
 
        // Traverse the given linked list
        // and insert every node to sorted
        while (pCurrent != NULL)
        {
            // Store next for next iteration
            Link* next = pCurrent->pNext;
 
            // Insert current in sorted
            // linked list
            sortedInsert(pCurrent);
 
            // Update current
            pCurrent = next;
        }
 
        // Update head_ref to point to
        // sorted linked list
        pFirst = sorted;
    }
    //-------------------------------------------------------------
    /*bool updatePriorAltTry(int oldPrior, int newPrior)
    {
        Link *pCurrent = pFirst;
        Link *position;
        position = findPatPrior(oldPrior);
        if (position != NULL)
        {
            for (int i = 1; i < position->patient->getPriority(); i++)
            {
                pCurrent = pCurrent->pNext;
            }
            pCurrent->patient->setPriority(newPrior);
            cout << "Patient's Priority was updated successfully." << endl;
            return true;
        }
        else
        {
            cout << "Priority not found." << endl;
            return false;
        }
    }*/

    void updatePrior(int oldPrior, int newPrior)
    {
        Link *pCurrent = pFirst;
        while (pCurrent != NULL)
        {
            if (pCurrent->patient->getPriority() == oldPrior)
            {
                pCurrent->patient->setPriority(newPrior);
                cout << "Priority " << oldPrior << " successfully changed to Priority " << newPrior << "."<< endl;
                return;
            }

            pCurrent = pCurrent->pNext;
        }

        cout << "Priority " << oldPrior << " does not exist in the queue of patients." << endl;
    }
    //-------------------------------------------------------------
    void menu() // display the menu
    {
        cout << "Menu: " << endl;
        cout << "1. Add a Patient" << endl;
        cout << "2. Remove a Patient" << endl;
        cout << "3. Display Patients" << endl;
        cout << "4. Update Patient's Priority" << endl;
        cout << "5. Search for a Patient" << endl;
        cout << "6. Quit" << endl
             << endl;
    }
};
////////////////////////////////////////////////////////////////
int main()
{
    LinkList theList; // make new list
    char choice;
    int ssn, age, priority;
    string name, gender, medcondition;
    bool rmvname;

    theList.insert(211544241, "Morty Sharpin", 30, "Male", "Cardiac arrest", 4);
    theList.insert(821582186, "Jaquelyn Lindsell", 21, "Female", "Severe trauma from a car accident", 2);
    theList.insert(323760921, "Preston Vogl", 24, "Male", "Acute abdominal pain", 10);

    theList.menu(); // display menu
    cout << "Enter choice: ";
    cin >> choice;

    while (choice != '6')
    {
        switch (choice)
        {
        case '1': // insert
        {
            // prints multiple - to visually divide each case when chosen
            for (int i = 1; i <= 80; i++)
            {
                cout << "-";
            }
            cout << endl
                 << endl;

            cout << "Enter the Patient's Social Security Number: ";
            cin >> ssn;
            cin.ignore();

            while (theList.uniquePatSSN(ssn))
            {
                cout << "Warning: Social Security Number has already been entered" << endl;
                cout << endl;
                cout << "Enter the Patient's Social Security Number: ";
                cin >> ssn;
                cin.ignore();
            }

            cout << "Enter the Patient's Name: ";
            getline(cin, name);
            cout << "Enter the Patient's Age: ";
            cin >> age;
            cout << "Enter the Patient's Gender: ";
            cin >> gender;
            cin.ignore();
            cout << "Enter the Patient's Medical Condition: ";
            getline(cin, medcondition);
            cout << "Enter the Priority of the Patient: ";
            cin >> priority;

            while (theList.uniquePatPrior(priority))
            {
                cout << "Warning: Priority Number has already in use" << endl;
                cout << endl;
                cout << "Enter the Priority of the Patient: ";
                cin >> priority;
                cin.ignore();
            }

            theList.insert(ssn, name, age, gender, medcondition, priority);
            cout << endl
                 << "Patient was added to the queue.";
            cout << endl
                 << endl;

            break;
        }
        case '2': // remove first
        {
            if (!theList.isEmpty())
            {
                theList.removeFirst();
                cout << endl;
                cout << "Patient was tended to." << endl;
            }
            else
            {
                cout << "The queue is empty, cannot tend to any patients." << endl;
            }
            cout << endl;
            theList.displayList();
            cout << endl;
            break;
        }
        case '3': // display all
        {
            // prints multiple - to visually divide each case when chosen
            for (int i = 1; i <= 80; i++)
            {
                cout << "-";
            }

            cout << endl
                 << endl;

            if (!theList.isEmpty())
            {
                theList.displayList();
            }
            else
            {
                cout << "Queue is empty, nothing to display" << endl;
            }

            cout << endl;
            break;
        }
        case '4': // update priority
        {
            // prints multiple - to visually divide each case when chosen
            for (int i = 1; i <= 80; i++)
            {
                cout << "-";
            }

            cout << endl
                 << endl;

            if (!theList.isEmpty())
            {
                int oldprior, newprior;
                cout << "Enter Patient's Priority to be changed: ";
                cin >> oldprior;
                cout << "Enter Patient's new Priority: ";
                cin >> newprior;

                theList.updatePrior(oldprior, newprior);
                //theList.quickSort(&theList.getpFirst());
                theList.insertionSort(theList.getpFirst());
            }
            else
            {
                cout << "The queue is empty.";
            }
            break;
        }
        case '5': // search
        {
            // prints multiple - to visually divide each case when chosen
            for (int i = 1; i <= 80; i++)
            {
                cout << "-";
            }

            cout << endl
                 << endl;

            if (!theList.isEmpty())
            {
                int findssn;
                string findname;
                char srchchoice;

                cout << "Search for a Patient\n"
                        "1. Via Social Security Number\n"
                        "2. Via Name\n"
                        "Enter Option: ";
                cin >> srchchoice;
                switch (srchchoice)
                {
                case '1':
                {
                    cout << "Enter the Patient's SSN: ";
                    cin >> findssn;
                    Link *searchLink = theList.findPatSSN(findssn);
                    if (searchLink != NULL)
                    {
                        searchLink->displayLink();
                    }
                    else
                    {
                        cout << "A patient with the Social Security number of " << findssn << " was not found." << endl;
                    }
                    break;
                }
                case '2':
                {
                    cin.ignore();
                    cout << "Enter the Patient's Name: ";
                    getline(cin, findname);
                    Link *searchLink = theList.findPatName(findname);
                    if (searchLink != NULL)
                    {
                        searchLink->displayLink();
                    }
                    else
                    {
                        cout << "A patient with the name of " << findname << " was not found." << endl;
                    }
                    break;
                }
                default:
                    cout << "Invalid choice!" << endl;
                }
            }
            else
            {
                cout << "Queue is empty, cannot search." << endl;
            }
            cout << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
        }
        theList.menu();
        cout << "Enter choice: ";
        cin >> choice;
    }
    return 0;
}