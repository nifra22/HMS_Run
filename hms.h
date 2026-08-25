#ifndef HMS_H
#define HMS_H

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// PATIENT CLASS

class Patient
{
public:

    int patientID;
    std::string name;
    int age;
    std::string gender;

    Patient(int id = 0,
        std::string patientName = "",
        int patientAge = 0,
        std::string patientGender = "");

    void display() const;
};


// ============================================================
// DYNAMIC ARRAY
// ============================================================

class PatientArray
{
private:

    Patient* data;
    int size;
    int capacity;

public:

    PatientArray();
    ~PatientArray();

    // Prevent accidental copying of dynamic memory
    PatientArray(const PatientArray&) = delete;
    PatientArray& operator=(const PatientArray&) = delete;

    int getSize() const;

    void resize();

    int addPatient(const Patient& patient);

    int findPatientIndex(int patientID) const;

    Patient* getPatient(int index);

    void displayAllPatients() const;
};


// ============================================================
// HASH TABLE
// ============================================================

class HashTable
{
private:

    struct HashNode
    {
        int key;
        int arrayIndex;
        HashNode* next;

        HashNode(int patientID, int index);
    };

    HashNode** table;
    int capacity;

    int hashFunction(int key) const;

public:

    HashTable(int tableSize = 11);
    ~HashTable();

    // Prevent accidental copying
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    bool insert(int patientID, int arrayIndex);

    int search(int patientID) const;
};


// ============================================================
// APPOINTMENT QUEUE
// ============================================================
// FIFO = First In, First Out

class AppointmentQueue
{
private:

    int* data;
    int capacity;
    int front;
    int rear;
    int count;

public:

    AppointmentQueue(int queueSize = 10);
    ~AppointmentQueue();

    // Prevent accidental copying
    AppointmentQueue(const AppointmentQueue&) = delete;
    AppointmentQueue& operator=(const AppointmentQueue&) = delete;

    bool enqueue(int patientID);

    int dequeue();

    void display() const;
};


// ============================================================
// EMERGENCY STACK
// ============================================================
// LIFO = Last In, First Out

class EmergencyStack
{
private:

    int* data;
    int capacity;
    int top;

public:

    EmergencyStack(int stackSize = 10);
    ~EmergencyStack();

    // Prevent accidental copying
    EmergencyStack(const EmergencyStack&) = delete;
    EmergencyStack& operator=(const EmergencyStack&) = delete;

    bool push(int patientID);

    int pop();

    void display() const;
};


// ============================================================
// BINARY SEARCH TREE
// ============================================================

class MedicalRecordTree
{
private:

    struct TreeNode
    {
        int recordID;

        TreeNode* left;
        TreeNode* right;

        TreeNode(int id);
    };

    TreeNode* root;

    TreeNode* createNode(int recordID);

    TreeNode* insertNode(TreeNode* node, int recordID);

    bool searchNode(TreeNode* node, int recordID) const;

    void inorderTraversal(TreeNode* node) const;

    void deleteTree(TreeNode* node);

public:

    MedicalRecordTree();

    ~MedicalRecordTree();

    // Prevent accidental copying
    MedicalRecordTree(const MedicalRecordTree&) = delete;
    MedicalRecordTree& operator=(const MedicalRecordTree&) = delete;

    void insert(int recordID);

    bool search(int recordID) const;

    void displayInOrder() const;
};


// ============================================================
// HOSPITAL MANAGEMENT SYSTEM
// ============================================================

class HospitalManagementSystem
{
private:

    PatientArray patients;

    HashTable patientIndex;

    AppointmentQueue appointmentQueue;

    EmergencyStack emergencyStack;

    MedicalRecordTree medicalRecordTree;

    void registerPatient();

    void searchPatient();

    void displayPatients();

    void addAppointment();

    void processAppointment();

    void displayAppointments();

    void addEmergencyCase();

    void processEmergencyCase();

    void displayEmergencyCases();

    void addMedicalRecord();

    void searchMedicalRecord();

    void displayMedicalRecords();

    void displayMenu();

public:

    void run();
};


// ============================================================
// PATIENT IMPLEMENTATION
// ============================================================

Patient::Patient(int id,
    string patientName,
    int patientAge,
    string patientGender)
{
    patientID = id;
    name = patientName;
    age = patientAge;
    gender = patientGender;
}


void Patient::display() const
{
    cout << "Patient ID : " << patientID << endl;
    cout << "Name       : " << name << endl;
    cout << "Age        : " << age << endl;
    cout << "Gender     : " << gender << endl;
}


// ============================================================
// PATIENT ARRAY IMPLEMENTATION
// ============================================================

PatientArray::PatientArray()
{
    capacity = 5;
    size = 0;

    data = new Patient[capacity];
}


PatientArray::~PatientArray()
{
    delete[] data;
}


int PatientArray::getSize() const
{
    return size;
}


void PatientArray::resize()
{
    int newCapacity = capacity * 2;

    Patient* newData = new Patient[newCapacity];

    for (int i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }

    delete[] data;

    data = newData;

    capacity = newCapacity;
}


int PatientArray::addPatient(const Patient& patient)
{
    if (size == capacity)
    {
        resize();
    }

    data[size] = patient;

    int insertedIndex = size;

    size++;

    return insertedIndex;
}


int PatientArray::findPatientIndex(int patientID) const
{
    for (int i = 0; i < size; i++)
    {
        if (data[i].patientID == patientID)
        {
            return i;
        }
    }

    return -1;
}


Patient* PatientArray::getPatient(int index)
{
    if (index < 0 || index >= size)
    {
        return nullptr;
    }

    return &data[index];
}


void PatientArray::displayAllPatients() const
{
    if (size == 0)
    {
        cout << "\nNo patients registered.\n";
        return;
    }

    cout << "\n========== REGISTERED PATIENTS ==========\n";

    for (int i = 0; i < size; i++)
    {
        cout << "\nPatient " << i + 1 << endl;

        data[i].display();

        cout << "-----------------------------------------\n";
    }
}


// ============================================================
// HASH TABLE IMPLEMENTATION
// ============================================================

HashTable::HashNode::HashNode(int patientID, int index)
{
    key = patientID;
    arrayIndex = index;
    next = nullptr;
}


int HashTable::hashFunction(int key) const
{
    int result = key % capacity;

    if (result < 0)
    {
        result += capacity;
    }

    return result;
}


HashTable::HashTable(int tableSize)
{
    capacity = tableSize;

    table = new HashNode * [capacity];

    for (int i = 0; i < capacity; i++)
    {
        table[i] = nullptr;
    }
}


HashTable::~HashTable()
{
    for (int i = 0; i < capacity; i++)
    {
        HashNode* current = table[i];

        while (current != nullptr)
        {
            HashNode* temporary = current;

            current = current->next;

            delete temporary;
        }
    }

    delete[] table;
}


bool HashTable::insert(int patientID, int arrayIndex)
{
    int index = hashFunction(patientID);

    HashNode* current = table[index];

    while (current != nullptr)
    {
        if (current->key == patientID)
        {
            return false;
        }

        current = current->next;
    }

    HashNode* newNode = new HashNode(patientID, arrayIndex);

    newNode->next = table[index];

    table[index] = newNode;

    return true;
}


int HashTable::search(int patientID) const
{
    int index = hashFunction(patientID);

    HashNode* current = table[index];

    while (current != nullptr)
    {
        if (current->key == patientID)
        {
            return current->arrayIndex;
        }

        current = current->next;
    }

    return -1;
}


// ============================================================
// APPOINTMENT QUEUE IMPLEMENTATION
// ============================================================

AppointmentQueue::AppointmentQueue(int queueSize)
{
    capacity = queueSize;

    data = new int[capacity];

    front = 0;

    rear = -1;

    count = 0;
}


AppointmentQueue::~AppointmentQueue()
{
    delete[] data;
}


bool AppointmentQueue::enqueue(int patientID)
{
    if (count == capacity)
    {
        cout << "\nAppointment queue is full.\n";

        return false;
    }

    rear = (rear + 1) % capacity;

    data[rear] = patientID;

    count++;

    return true;
}


int AppointmentQueue::dequeue()
{
    if (count == 0)
    {
        return -1;
    }

    int patientID = data[front];

    front = (front + 1) % capacity;

    count--;

    return patientID;
}


void AppointmentQueue::display() const
{
    if (count == 0)
    {
        cout << "\nAppointment queue is empty.\n";

        return;
    }

    cout << "\n========== APPOINTMENT QUEUE ==========\n";

    int index = front;

    for (int i = 0; i < count; i++)
    {
        cout << "Patient ID: "
            << data[index] << endl;

        index = (index + 1) % capacity;
    }
}


// ============================================================
// EMERGENCY STACK IMPLEMENTATION
// ============================================================

EmergencyStack::EmergencyStack(int stackSize)
{
    capacity = stackSize;

    data = new int[capacity];

    top = -1;
}


EmergencyStack::~EmergencyStack()
{
    delete[] data;
}


bool EmergencyStack::push(int patientID)
{
    if (top == capacity - 1)
    {
        cout << "\nEmergency stack is full.\n";

        return false;
    }

    top++;

    data[top] = patientID;

    return true;
}


int EmergencyStack::pop()
{
    if (top == -1)
    {
        return -1;
    }

    int patientID = data[top];

    top--;

    return patientID;
}


void EmergencyStack::display() const
{
    if (top == -1)
    {
        cout << "\nNo emergency cases.\n";

        return;
    }

    cout << "\n========== EMERGENCY CASES ==========\n";

    for (int i = top; i >= 0; i--)
    {
        cout << "Patient ID: "
            << data[i] << endl;
    }
}


// ============================================================
// BINARY SEARCH TREE IMPLEMENTATION
// ============================================================

MedicalRecordTree::TreeNode::TreeNode(int id)
{
    recordID = id;

    left = nullptr;

    right = nullptr;
}


MedicalRecordTree::TreeNode*
MedicalRecordTree::createNode(int recordID)
{
    return new TreeNode(recordID);
}


MedicalRecordTree::TreeNode*
MedicalRecordTree::insertNode(
    TreeNode* node,
    int recordID)
{
    if (node == nullptr)
    {
        return createNode(recordID);
    }

    if (recordID < node->recordID)
    {
        node->left =
            insertNode(node->left, recordID);
    }
    else if (recordID > node->recordID)
    {
        node->right =
            insertNode(node->right, recordID);
    }

    return node;
}


bool MedicalRecordTree::searchNode(
    TreeNode* node,
    int recordID) const
{
    if (node == nullptr)
    {
        return false;
    }

    if (node->recordID == recordID)
    {
        return true;
    }

    if (recordID < node->recordID)
    {
        return searchNode(node->left, recordID);
    }

    return searchNode(node->right, recordID);
}


void MedicalRecordTree::inorderTraversal(
    TreeNode* node) const
{
    if (node == nullptr)
    {
        return;
    }

    inorderTraversal(node->left);

    cout << node->recordID << " ";

    inorderTraversal(node->right);
}


void MedicalRecordTree::deleteTree(TreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    deleteTree(node->left);

    deleteTree(node->right);

    delete node;
}


MedicalRecordTree::MedicalRecordTree()
{
    root = nullptr;
}


MedicalRecordTree::~MedicalRecordTree()
{
    deleteTree(root);
}


void MedicalRecordTree::insert(int recordID)
{
    root = insertNode(root, recordID);
}


bool MedicalRecordTree::search(int recordID) const
{
    return searchNode(root, recordID);
}


void MedicalRecordTree::displayInOrder() const
{
    cout << "\n========== MEDICAL RECORDS ==========\n";

    inorderTraversal(root);

    cout << endl;
}


// ============================================================
// HOSPITAL MANAGEMENT SYSTEM IMPLEMENTATION
// ============================================================

void HospitalManagementSystem::registerPatient()
{
    int id;
    string name;
    int age;
    string gender;

    cout << "\nEnter Patient ID: ";
    cin >> id;

    if (patientIndex.search(id) != -1)
    {
        cout << "Error: Patient ID already exists.\n";

        return;
    }

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n');

    cout << "Enter Patient Name: ";
    getline(cin, name);

    cout << "Enter Patient Age: ";
    cin >> age;

    if (age < 0)
    {
        cout << "Invalid age.\n";

        return;
    }

    cin.ignore(
        numeric_limits<streamsize>::max(),
        '\n');

    cout << "Enter Patient Gender: ";
    getline(cin, gender);

    Patient newPatient(
        id,
        name,
        age,
        gender);

    int arrayIndex =
        patients.addPatient(newPatient);

    patientIndex.insert(
        id,
        arrayIndex);

    cout << "\nPatient registered successfully.\n";

    cout << "Patient stored at array index: "
        << arrayIndex << endl;
}


void HospitalManagementSystem::searchPatient()
{
    int id;

    cout << "\nEnter Patient ID to search: ";
    cin >> id;

    int arrayIndex =
        patientIndex.search(id);

    if (arrayIndex == -1)
    {
        cout << "\nPatient not found.\n";

        return;
    }

    Patient* patient =
        patients.getPatient(arrayIndex);

    if (patient != nullptr)
    {
        cout << "\n========== PATIENT FOUND ==========\n";

        patient->display();

        cout << "Array Index: "
            << arrayIndex << endl;
    }
}


void HospitalManagementSystem::displayPatients()
{
    patients.displayAllPatients();
}


void HospitalManagementSystem::addAppointment()
{
    int id;

    cout << "\nEnter Patient ID for appointment: ";
    cin >> id;

    if (patientIndex.search(id) == -1)
    {
        cout << "Patient does not exist.\n";

        return;
    }

    if (appointmentQueue.enqueue(id))
    {
        cout << "Patient added to appointment queue successfully.\n";
    }
}


void HospitalManagementSystem::processAppointment()
{
    int id =
        appointmentQueue.dequeue();

    if (id == -1)
    {
        cout << "\nNo patients are waiting for an appointment.\n";

        return;
    }

    cout << "\nProcessing appointment for Patient ID: "
        << id << endl;
}


void HospitalManagementSystem::displayAppointments()
{
    appointmentQueue.display();
}


void HospitalManagementSystem::addEmergencyCase()
{
    int id;

    cout << "\nEnter Emergency Patient ID: ";
    cin >> id;

    if (patientIndex.search(id) == -1)
    {
        cout << "Patient does not exist.\n";

        return;
    }

    if (emergencyStack.push(id))
    {
        cout << "Emergency case added successfully.\n";
    }
}


void HospitalManagementSystem::processEmergencyCase()
{
    int id =
        emergencyStack.pop();

    if (id == -1)
    {
        cout << "\nNo emergency cases available.\n";

        return;
    }

    cout << "\nProcessing Emergency Patient ID: "
        << id << endl;
}


void HospitalManagementSystem::displayEmergencyCases()
{
    emergencyStack.display();
}


void HospitalManagementSystem::addMedicalRecord()
{
    int recordID;

    cout << "\nEnter Medical Record ID: ";
    cin >> recordID;

    if (medicalRecordTree.search(recordID))
    {
        cout << "Medical record already exists.\n";

        return;
    }

    medicalRecordTree.insert(recordID);

    cout << "Medical record added successfully.\n";
}


void HospitalManagementSystem::searchMedicalRecord()
{
    int recordID;

    cout << "\nEnter Medical Record ID to search: ";
    cin >> recordID;

    bool found =
        medicalRecordTree.search(recordID);

    if (found)
    {
        cout << "Medical record found.\n";
    }
    else
    {
        cout << "Medical record not found.\n";
    }
}


void HospitalManagementSystem::displayMedicalRecords()
{
    medicalRecordTree.displayInOrder();
}


void HospitalManagementSystem::displayMenu()
{
    cout << "\n\n============================================\n";
    cout << "       HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "============================================\n";

    cout << "1.  Register Patient\n";
    cout << "2.  Search Patient\n";
    cout << "3.  Display All Patients\n";
    cout << "4.  Add Appointment\n";
    cout << "5.  Process Appointment\n";
    cout << "6.  Display Appointment Queue\n";
    cout << "7.  Add Emergency Case\n";
    cout << "8.  Process Emergency Case\n";
    cout << "9.  Display Emergency Cases\n";
    cout << "10. Add Medical Record\n";
    cout << "11. Search Medical Record\n";
    cout << "12. Display Medical Records\n";
    cout << "0.  Exit\n";

    cout << "============================================\n";
}


void HospitalManagementSystem::run()
{
    int choice;

    do
    {
        displayMenu();

        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n');

            cout << "\nInvalid input. Please enter a number.\n";

            continue;
        }

        switch (choice)
        {
        case 1:
            registerPatient();
            break;

        case 2:
            searchPatient();
            break;

        case 3:
            displayPatients();
            break;

        case 4:
            addAppointment();
            break;

        case 5:
            processAppointment();
            break;

        case 6:
            displayAppointments();
            break;

        case 7:
            addEmergencyCase();
            break;

        case 8:
            processEmergencyCase();
            break;

        case 9:
            displayEmergencyCases();
            break;

        case 10:
            addMedicalRecord();
            break;

        case 11:
            searchMedicalRecord();
            break;

        case 12:
            displayMedicalRecords();
            break;

        case 0:
            cout << "\nThank you for using the "
                << "Hospital Management System.\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);
}


#endif