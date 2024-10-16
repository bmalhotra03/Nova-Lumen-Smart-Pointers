// Author: Brij Malhotra
// Filename: P4.cpp
// Version: Version 1
// Description: Driver file for the implementation of the Nova class and its overloaded operators
//              using smart pointers and vectors to hold the pointers.
#include "lumen.h"
#include "nova.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <memory>

using namespace std;

// Creating pointers
unique_ptr<Nova> createUniquePtr();
shared_ptr<Nova> createSharedPtr();
Nova operator+(unsigned int x, const Nova&obj); // Commutativity for addition operator

void simulate();

int main(){
    simulate(); 
    return 0;
}

// Smart pointer declaration
unique_ptr<Nova> createUniquePtr(){
    int arrSize = rand() % 10;
    Lumen * arr = new Lumen[arrSize];

    for (int i = 0; i < arrSize; i++){
        arr[i] = Lumen(rand() % 100, rand() % 100, rand() % 100);
    }

    unique_ptr<Nova> Uptr(new Nova(arr, arrSize));
    return Uptr;
}

shared_ptr<Nova> createSharedPtr(){
    int arrSize = rand() % 10;
    Lumen * arr = new Lumen[arrSize];

    for (int i = 0; i < arrSize; i++){
        arr[i] = Lumen(rand() % 100, rand() % 100, rand() % 100);
    }
    
    shared_ptr<Nova> Sptr(new Nova(arr, arrSize));
    return Sptr;
}

void simulate() {
    
    // Create a vector to store heap-allocated nova objects
    vector<unique_ptr<Nova>> uniquePtrVector;
    vector<shared_ptr<Nova>> sharedPtrVector;

    // Add heap-allocated nova objects to the vectors
    uniquePtrVector.push_back(createUniquePtr());
    uniquePtrVector.push_back(createUniquePtr());
    sharedPtrVector.push_back(createSharedPtr());
    sharedPtrVector.push_back(createSharedPtr());

    // Add and remove heap-allocated nova objects to the vectors
    uniquePtrVector.push_back(createUniquePtr());
    sharedPtrVector.push_back(createSharedPtr());
    uniquePtrVector.pop_back();
    sharedPtrVector.pop_back();

    // Demonstrate copying of nova objects via call by value
    Nova novaObj1 = *uniquePtrVector[0];
    Nova novaObj2 = *sharedPtrVector[0];

    // Test operator overloading
    Nova novaObj3 = novaObj1 + 5;
    Nova novaObj4 = novaObj2 + novaObj1;

    // Test assignment operator and copy constructor and default values
    Nova novaObj5 = novaObj2;
    Nova novaObj6(novaObj4);

    // Call glow on each object so that we can retrieve values 
    novaObj1.glow(5);
    novaObj2.glow(5);
    novaObj3.glow(5);
    novaObj4.glow(5);
    novaObj5.glow(5);
    novaObj6.glow(5);

    // Print results and perform further operations as needed
    cout << endl << endl;
    cout << "Nova 1 max glow: " << novaObj1.getMax() << endl;
    cout << "Nova 2 max glow: " << novaObj2.getMax() << endl;
    cout << "Nova 3 max glow: " << novaObj3.getMax() << endl;
    cout << "Nova 4 max glow: " << novaObj4.getMax() << endl;
    cout << "Nova 5 max glow: " << novaObj4.getMax() << endl;
    cout << "Nova 6 max glow: " << novaObj4.getMax() << endl;
    cout << endl;

    // Comparison operators to be utilised: 
    cout << "Comparing Novas and retrieving results: " << endl << endl;

    if (novaObj1 > novaObj3){
        cout << "Nova 1 is a stronger Nova than Nova 3" << endl;
    } else {
        cout << "Nova 3 is a stronger Nova than Nova 1" << endl;
    }

    if (novaObj2 == novaObj4){
        cout << "Nova 2 and Nova 4 are equal in value." << endl;
    } else {
        cout << "Nova 2 and Nova 4 are not of the same values." << endl;
    }

    if (novaObj5 >= novaObj3){
        cout << "Nova 5 is either equal to or greater than Nova 3" << endl;
    } else {
        cout << "Nova 5 is weaker than Nova 3" << endl;
    }

    if (novaObj4 < novaObj6){
        cout << "Nova 4 is weaker than Nova 6" << endl;
    } else {
        cout << "Nova 6 is weaker than Nova 4" << endl;
    }

    cout << endl;

    cout << "Performing increment operations and short cut operations" << endl;
    novaObj1++;
    ++novaObj2;
    novaObj3 += 5;
    novaObj4 += novaObj2;
    novaObj5 = 50 + novaObj6;

    // Call glow on each object so that we can retrieve values 
    novaObj1.glow(5);
    novaObj2.glow(5);
    novaObj3.glow(5);
    novaObj4.glow(5);
    novaObj5.glow(5);
    novaObj6.glow(5);

    cout << "Retrieving new values based on operations: " << endl << endl;

    cout << "Nova 1 max glow: " << novaObj1.getMax() << endl;
    cout << "Nova 2 max glow: " << novaObj2.getMax() << endl;
    cout << "Nova 3 max glow: " << novaObj3.getMax() << endl;
    cout << "Nova 4 max glow: " << novaObj4.getMax() << endl;
    cout << "Nova 5 max glow: " << novaObj4.getMax() << endl;
    cout << "Nova 6 max glow: " << novaObj4.getMax() << endl;
    cout << endl << endl;

    // Comparison operators to be utilised: 
    cout << "Comparing Novas and retrieving results: " << endl << endl;

    if (novaObj1 > novaObj3){
        cout << "Nova 1 is a stronger Nova than Nova 3" << endl;
    } else {
        cout << "Nova 3 is a stronger Nova than Nova 1" << endl;
    }

    if (novaObj2 == novaObj4){
        cout << "Nova 2 and Nova 4 are equal in value." << endl;
    } else {
        cout << "Nova 2 and Nova 4 are not of the same values." << endl;
    }

    if (novaObj5 >= novaObj3){
        cout << "Nova 5 is either equal to or greater than Nova 3" << endl;
    } else {
        cout << "Nova 5 is weaker than Nova 3" << endl;
    }

    if (novaObj4 < novaObj6){
        cout << "Nova 4 is weaker than Nova 6" << endl;
    } else {
        cout << "Nova 6 is weaker than Nova 4" << endl;
    }

    cout << endl;

    cout << "Performing increment operations and short cut operations" << endl;
    novaObj6++;
    ++novaObj5;
    novaObj4 += 5;
    novaObj3 += novaObj2;
    novaObj1 = novaObj2 + 5;

    // Call glow on each object so that we can retrieve values 
    novaObj1.glow(5);
    novaObj2.glow(5);
    novaObj3.glow(5);
    novaObj4.glow(5);
    novaObj5.glow(5);
    novaObj6.glow(5);

    cout << "Retrieving new values based on operations: " << endl << endl;

    cout << "Nova 1 max glow: " << novaObj1.getMax() << endl;
    cout << "Nova 2 max glow: " << novaObj2.getMax() << endl;
    cout << "Nova 3 max glow: " << novaObj3.getMax() << endl;
    cout << "Nova 4 max glow: " << novaObj4.getMax() << endl;
    cout << "Nova 5 max glow: " << novaObj4.getMax() << endl;
    cout << "Nova 6 max glow: " << novaObj4.getMax() << endl;
    cout << endl << endl;

    // Comparison operators to be utilised: 
    cout << "Comparing Novas and retrieving results: " << endl << endl;

    if (novaObj1 > novaObj3){
        cout << "Nova 1 is a stronger Nova than Nova 3" << endl;
    } else {
        cout << "Nova 3 is a stronger Nova than Nova 1" << endl;
    }

    if (novaObj2 == novaObj4){
        cout << "Nova 2 and Nova 4 are equal in value." << endl;
    } else {
        cout << "Nova 2 and Nova 4 are not of the same values." << endl;
    }

    if (novaObj5 >= novaObj3){
        cout << "Nova 5 is either equal to or greater than Nova 3" << endl;
    } else {
        cout << "Nova 5 is weaker than Nova 3" << endl;
    }

    if (novaObj4 < novaObj6){
        cout << "Nova 4 is weaker than Nova 6" << endl;
    } else {
        cout << "Nova 6 is weaker than Nova 4" << endl;
    }

    cout << endl;
    // Step 8: Automatically deallocate memory when vectors go out of scope
}

// Commutativity addition operator
Nova operator+(unsigned int x, const Nova&obj){
    Lumen * test = nullptr;
    Nova temp(test, 0);
    temp = obj + x;
    return temp;
}