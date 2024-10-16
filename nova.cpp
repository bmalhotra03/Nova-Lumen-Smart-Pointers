// Author: Brij Malhotra
// Filename: nova.cpp
// Version: Version 1
// Description: This is the class implementation of the Nova object


// Class invariant:
//    The Nova object takes in an array of lumen objects via Dependency Injection (Constructor Injection).
//    If a null array is given, default values will be taken which would be an array of 10 Lumen objects for
//    a Nova object. The client can invoke all public functions, however, this program explicitly tests the 
//    functionality of overloaded operators. Subtraction is not supported in the overloaded operations. The
//    operations that are available for the client to use are Addition: int + object, object + int, object + object,
//    post and pre increments for the objects, short cut addition += for objects with other objects or objects with 
//    integers. Additionally, all comparison operators are available for use too. The only operator that explicity
//    compares all values are the == operand to make sure both Novas are exactly the same. Comparisons can be done 
//    between one object and another, the quantity of measurement to be compared is a value that is codependent on 
//    the brightness, power and size of the Nova's contents.

#include "nova.h"
#include "lumen.h"

// Pre conditions: Array of lumen objects along with the size of the array
// If constructor is empty, default values will be taken to create the object.
// Post conditions: None
Nova :: Nova(Lumen * arr, int x){
    
    if (arr == nullptr || x < 0){
        arr = new Lumen[10];

        for (int i = 0; i < 10; i++){
            arr[i] = Lumen(1 + rand()%100, 1 + rand()%100, 1 + rand()%100);
        }
    }

    arrSize = x;
    lumenArr = arr;
    arr = nullptr;
}

// Copy constructor
// Pre conditions: A Nova object 'obj' exists.
// Post conditions: A new Nova object is created with the same values as obj. 
// A deep copy of obj's ptr array is made and assigned to the new object's ptr.
Nova :: Nova(const Nova& obj){
    
    arrSize = obj.arrSize;
    lumenArr = new Lumen[arrSize];
    max = obj.max;
    min = obj.min;

    for (int i = 0; i < arrSize; i++){
        lumenArr[i] = obj.lumenArr[i];
    }
}

// Destructor
// Pre conditions: A Nova object exists
// Post conditions: The 'ptr' array is deleted and set to nullptr. The object is destroyed.
Nova :: ~Nova(){
    delete [] lumenArr;
    lumenArr = nullptr;
}

// Assignment operator
// Pre conditions: A Nova object 'obj' exists.
// Post conditions: The calling Nova object is assigned the same values as 'obj'.
// 'obj's' 'ptr' array is transferred to the calling object's 'ptr', and 'obj.ptr' is set to nullptr.
void Nova :: operator=(const Nova& orig){
    if(this != &orig){
        delete [] lumenArr;
        arrSize = orig.arrSize;
        max = orig.max;
        min = orig.min;
        lumenArr = orig.lumenArr;

        novaCopy(orig);
    }
}

// Move assignment operator
// Pre conditions: A Nova object 'obj' exists.
// Post conditions: Based on the compiler, move semantics will be used using this operator
void Nova :: operator=(Nova&& obj){
    swap(arrSize, obj.arrSize);
    swap(max, obj.max);
    swap(min, obj.min);   
    swap(lumenArr, obj.lumenArr);
}

// Move copy constructor
// Pre conditions: A Nova object 'obj' exists.
// Post conditions: A new Nova object is created with the same values as obj. 
// A deep copy of obj's ptr array is made and assigned to the new object's ptr.
Nova :: Nova(Nova&& obj){
    max = obj.max;
    min = obj.min;
    arrSize = obj.arrSize;
    lumenArr = obj.lumenArr;

    obj.arrSize = 0;
    obj.lumenArr = nullptr;
}

// Nova copy function
void Nova :: novaCopy(const Nova& obj){
    arrSize = obj.arrSize;
    lumenArr = new Lumen[arrSize];

    for(int i = 0; i < obj.arrSize; i++){
        lumenArr[i].copy(obj.lumenArr[i]);
    }
}

// Nova glow function
// Pre conditions: 'ptr' is a valid array of 'Lumen' objects.
// Post conditions: The 'glow()' function of each of the first num objects in 'ptr' is called, 
// and 'max' and 'min' are updated to reflect the maximum and minimum return values of the 'glow()' function, respectively.
void Nova :: glow(int num){

    if(num > arrSize){
        num = arrSize;
    }
    
    for (int i = 0; i < num; i++){
        int temp = lumenArr[i].glow();

        if(temp > max){
            max = temp;
        }

        if(min == 0){
            min = temp;
        } else if(temp < min){
            min = temp;
        }
    }
}

// Pre-conditions: None.
// Post-conditions: Returns the current value of 'max'.
int Nova :: getMax(){
    return max;
}

// Pre-conditions: None.
// Post-conditions: Returns the current value of 'min'.
int Nova :: getMin(){
    return min;
}

// Pre-condition: 'ptr' is a valid array of 'Lumen' objects.
// Post-condition: If more than half of the 'Lumen' objects in ptr are active, 
// the 'increasePower()' function of each object in 'ptr' is called.
void Nova :: recharge(){
    
    int count = 0;
    
    for(int i = 0; i < arrSize; i++){
        if(lumenArr[i].isActive()){
            count++;
        }
    }

    if(count > arrSize/2){
        for(int i = 0; i < arrSize; i++){
            lumenArr[i].increasePower();
            if(!lumenArr[i].isStable()){
                lumenArr[i].reset();
            }
        }
    }
}

// Operator overloading for addition

// This addition adds an integer to each lumen object's values that change the overall value of a Nova
// Pre conditions: An integer is being added to an object
// Post conditions: Nova object's lumens have updated values respective to the integer
Nova Nova :: operator+(unsigned int x) const {
    
    for (int i = 0; i < arrSize; i++){
        lumenArr[i] = lumenArr[i] + x;
    }

    return *this;
}

// This addition adds up the values of one Nova object to another 
// Pre conditions: A Nova object is being added to another Nova object
// Post conditions: Nova object's values are updated according to the addition
Nova Nova :: operator+(const Nova& obj) const {

    int size = arrSize < obj.arrSize? arrSize : obj.arrSize;
    
    for (int i = 0; i < size; i++){
        lumenArr[i] += obj.lumenArr[i];
    }

    return *this;
}

// This updates the internal values of the Nova by +1
// Pre conditions: A Nova object is being incremented
// Post conditions: Nova object has updated values
Nova Nova :: operator++(){ // Pre increment
    return *this + 1;
}

// This updates the internal values of the Nova by +1
// Pre conditions: A Nova object is being incremented
// Post conditions: Nova object has updated values AFTER its usage
Nova Nova :: operator++(int x){ // Post increment
    Nova temp(*this);
    *this + 1;
    return temp;
}

// Shortcut addition for object and int
// Pre conditions: A Nova object is being added to an int
// Post conditions: Same as above addition for object and int
Nova Nova :: operator+=(unsigned int x){
    return *this + x;
}

// Shortcut addition for object and object
// Pre conditions: A Nova object is being added to another Nova object
// Post conditions: Same as above addition for object and object
Nova Nova :: operator+=(const Nova& obj){
    return *this + obj;
}

// Operator overloading for comparison

// This compares overall stats of the Nova's contents
// Pre conditions: A Nova object is being compared to another Nova object
// Post conditions: Boolean value is returned based on the conditions
bool Nova :: operator>(const Nova& obj){
    int stat;
    int objStat;

    for (int i = 0; i < arrSize; i++){
        stat += lumenArr[i].getStat();
    }

    for (int i = 0; i < obj.arrSize; i++){
        objStat += obj.lumenArr[i].getStat();
    }

    return (stat > objStat);
}

// This compares overall stats of the Nova's contents
// Pre conditions: A Nova object is being compared to another Nova object
// Post conditions: Boolean value is returned based on the conditions
bool Nova :: operator>=(const Nova& obj){
    return (*this > obj || *this == obj);
}

// This compares overall stats of the Nova's contents
// Pre conditions: A Nova object is being compared to another Nova object
// Post conditions: Boolean value is returned based on the conditions
bool Nova :: operator<(const Nova& obj){
    return !(*this > obj || *this == obj);
}

// This compares overall stats of the Nova's contents
// Pre conditions: A Nova object is being compared to another Nova object
// Post conditions: Boolean value is returned based on the conditions
bool Nova :: operator<=(const Nova& obj){
    return !(*this < obj || *this == obj);
}  

// This compares overall stats of the Nova's contents
// Pre conditions: A Nova object is being compared to another Nova object
// Post conditions: Boolean value is returned based on the conditions
bool Nova :: operator==(const Nova& obj){
    if (arrSize != obj.arrSize) return false;   // Base case to see if array sizes are the same, if not, it is known Novas are not the same

    for (int i = 0; i < arrSize; i++){
        if(lumenArr[i] != obj.lumenArr[i]){
            return false;
        }
    }

    return true;
}

// This compares overall stats of the Nova's contents
// Pre conditions: A Nova object is being compared to another Nova object
// Post conditions: Boolean value is returned based on the conditions
bool Nova :: operator!=(const Nova& obj){
    return !(*this == obj);
}

// Implementation invariant:
//    The client is not able to control the lumen object glow directly. There are no set functions, 
//    once values have been given to initialize an object, the functions will be invoked upon those values only.
//    Client does not know whether the object is stable or active, all they receive is an integer value 
//    related to the glow(int) function and its conditions based on their input, only int number of objects
//    in the nova object will have glow() invoked on them. The functions getMax() and getMin() allow the user
//    to query the nova object and to retrieve the maximum and minimum glow values of the objects in it. The
//    recharge() function can be called and the power will be recharge IF and ONLY IF more than half of the 
//    Lumen objects in the Nova object are inactive. Consistent unstable objects may be replaced. 

// Implementation invariant:
//    The client is not able to control the lumen object glow directly. Values for Nova objects are retrieved from
//    Constructor Injection via the Client. The program returns values based on glow being called on each object. The
//    overloaded operators are used both in the Lumen class and Nova class. When an addition happens, the values of power,
//    brightness, and size of the lumens in the Nova have their values updated by the integer or the other Nova object's 
//    lumen values. For the comparison, a statistic value based on brightness, size, and power is returned which is used to
//    determine whether a Nova is stronger than another or not. This is done by adding up all the statistical values of lumens
//    within a Nova and then the overall values are compared. 