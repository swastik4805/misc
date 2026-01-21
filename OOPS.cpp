#include<bits/stdc++.h>
#include<iostream>
#include <numeric>
typedef signed long long ll;
typedef unsigned long long ull;
typedef long double ld;
using namespace std;


// class - describes the structure
// abstraction- a concept where you make something easy by hiding the complicated stuff
// encapsulation- granting access to pivate data only through controlled public interfaces
// inheritance- we can create derieved classes that inherit properties from their parent classes
// polymorphism- we can treat multiple different objects as their base object type

// Constructors- initiates the object of a class
	class Person{
		private:
			string first,last;
		public:
			person(string first, string last){
				this->first=first;
				this->last=last;
			}
			Person p()=default // this keeps the ability to create an object like 'Person P' in the main()
	}

	int main(){ 
		Person p("swastik","chatterjee"); // this way we don't have to create a assignVariableName function.
	}

-------------------------------------------------------------------------------------------------------- 
 Inheritance- 
 	class Person{
		private:
			string first,last;
		public:
			Person(string first, string last){
				this->first=first;
				this->last=last;
			}
			Person()=default;
			void setFirstName(string first){this->first=first;}
			void setLastName(string last){this->last=last;}
			void printName(){cout<<first<<" "<<last;}
	};

	class Employee: public Person{
		string department;
		public:
			Employee(string first, string last, string department): 
				Person(first,last),department(department){}// here the first and last are derieved from Person class

			string getDepartment(){return department;}
			void setDepartment(){
				this->department=department;
			}
	};

	int main(){
		#ifndef ONLINE_JUDGE
	    freopen("input.txt","r",stdin);
	    freopen("output.txt","w",stdout);
	   #endif
	 

		Employee e("swastik","chatterjee","Amazon");

		// e.setFirstName("Swastik");
		// e.setLastName("Chatterjee");
		e.printName();
		cout<<endl;
		cout<<e.getDepartment();
	}



	// Runtime-

	class People{
	public:
		string talk;
		People(string talk){
			this->talk=talk;
		}
		People()=default;
		void doWork(){
			cout<<"People Doing work";
		}
	};

	class Man: public People{
	public:
		void doWork(){
			cout<<"Doing work that is specific to a man only";
		}
	};

	int main(){
		Man m;
		People p;
		p.doWork();
		cout<<endl;
		m.doWork();
	}



	---------virtual function---------------
	class instrument{
	public:
		virtual void makeSound(){
			cout<<"instrument playing"<<end;
		}
		/*
		virtual void makeSound()=0; this is a pure virtual function.
		it forces all the derievclasses to make a makeSound()
		function of their own. This way the instrument class becomes an
		abstract class (it has atleast 1 pure virtual function).
		*/
	};
	for abstract classes we cant create instances of that class

	class piano : public instrument{
	public:
		void makeSound(){
			cout<<"piano playing"<<endl;
		}
	};
	int main(){
		instrument* i1=new piano();
		i1->makeSound(); // it will print- piano playing
		// if we remove the virtual keyword from the base class- it will print instrument playing.
		//virtual function says, if there is no member function
		//makeSound() in the piano class, execute the function
		//from the instrument class.
	}


	copy Constructors are invoked when a new object is created
	and used in an existing object.
	Book book3(book1);  <- example
	It is also used when the compiler makes a temp object- when we are
	passing an object to a function by value (not by reference)
	void function(Book book1){
		....
	} 



	Threading in C++
	#include <threads>
	void function1(string num){}
	void function2(){}
	int main(){
		threads worker1(function1,"chhono");
		threads worker2(function2);
	}







void allocateMemory(int **ptr){
    *ptr = (int *)malloc(sizeof(int));
    if (*ptr == NULL) {
        printf("Memory allocation failed\n");
        exit(1); // Exit the program if memory allocation fails
    }
}
int main(){
    int *ptr = NULL;
    // Call the allocateMemory() function to allocate memory
    allocateMemory(&ptr);
    *ptr = 5;
    printf("%d", *ptr);
    // Don't forget to free the allocated memory when done
    free(ptr);
    return 0;
}

int* allocated_with_malloc = malloc(5 * sizeof(int)); //allocated_with_malloc[] is a normal array. use it like that
int* allocated_with_calloc = calloc(5, sizeof(int));


Swap two numbers with pointers-------------------------
swap(int *a, int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}
int main(){
	int a=2; int b=3;
	swap(&a,&b);
}





Mutex:

A mutex (short for mutual exclusion) is a synchronization primitive used to protect shared resources in multi-threaded or 
multi-process programs.
It allows only one thread at a time to access a shared resource or critical section, ensuring that concurrent access does 
not lead to data corruption or race conditions.
Mutexes are often used to coordinate access to shared data in multi-threaded applications.
A Mutex is like a bathroom key. Only the person with the key can enter; everyone else must wait outside until the key is returned.

Smart Locking---------
What if your code throws an error or returns after you lock a mutex but before you unlock it? The mutex stays locked forever, and your program "deadlocks."
RAII (Resource Acquisition Is Initialization). std::lock_guard automatically unlocks the mutex when it goes out of scope (just like your Timer struct does!).

struct Timer{
    chrono::time_point<std::chrono::high_resolution_clock> start, end;
    chrono::duration<float> duration;

    Timer(){
        start=chrono::high_resolution_clock::now();
    }
    ~Timer(){
        end=chrono::high_resolution_clock::now();
        duration=end-start;
        cout<<"Timer took "<<duration.count()<<endl;
    }
};


Condition Variables (Efficient Waiting)------------
When ever a thread uses a while loop that checks s_Finished(a condition) constantly. This is called "Busy Waiting" and it wastes CPU cycles.
A Condition Variable allows a thread to go to sleep and be "woken up" by another thread only when something changes.





busy wait vs condition variable----------------
void doWork(){
    int i=0;
    cout<<"Thread id"<<this_thread::get_id()<<endl;
    while(!s_Finished){  // this is busy waiting
        cout<<i<<". Working...\n";
        i++;
        this_thread::sleep_for(1s);
    }
}


void worker_thread() {
    std::unique_lock<std::mutex> lk(cv_m);
    while (!ready) {
        cv.wait(lk); 
    }
    // Once we exit the loop, we know 'ready' is true
    cout << "Worker thread is now running!" << endl;
}
The "Magic" of cv.wait()
In your first version (Busy Waiting), the while loop was "hot." The CPU was executing the ! and s_Finished check billions of times per second.
In the condition_variable version, when the code reaches cv.wait(lk), the thread is completely suspended by the Operating System (OS).
Busy Waiting: The thread is in a RUNNING state. It is actively using the CPU and consuming power.
Condition Variable: The thread is put into a WAITING/BLOCKED state. The OS removes the thread from the CPU entirely. It consumes zero CPU cycles while it sits there.

Feature,--------------Busy Waiting (while(!s_Finished)),------------CV Waiting (cv.wait)----------
CPU Usage,					100% of one core,								0%
Responsiveness,					Instant,						Very fast (depends on OS scheduler)
Battery Impact,				Extremely High (Bad),					Minimal (Excellent)
Thread State,					Running,								Blocked/Waiting





------------------Memory Management-------------------


smart pointers----------------------->
//smart pointers do better memory management by dellocating memory manually.
// unique_ptr and shared_ptr are the two types.

Unique pointer---------------------
This is the most efficient smart pointer. It says: "I am the only one who owns this memory. You cannot copy me."
Use case: A single manager for a resource (like a specific hardware driver).
Performance: Zero overhead. It’s as fast as a raw pointer.
// Memory is automatically deallocated when uniquePtr goes out of scope
#include <memory>
void uniqueExample() {
    // Allocation
    std::unique_ptr<int> uPtr = std::make_unique<int>(25);
    
    // std::unique_ptr<int> uPtr2 = uPtr; // ERROR! Cannot copy ownership.
    
    std::cout << *uPtr << std::endl;
} // uPtr goes out of scope, memory is DELETED automatically here.








shared pointer---------------------------
This allows multiple pointers to point to the same memory. It keeps a Reference Count (a counter of how many people are using it).
The Logic: When the count hits zero, the memory is deleted.
Use case: A shared resource used by multiple threads or different parts of an app (like a shared configuration object).

void sharedExample() {
    std::shared_ptr<int> sPtr1 = std::make_shared<int>(100);
    {
        std::shared_ptr<int> sPtr2 = sPtr1; // Count becomes 2
        std::cout << "Count: " << sPtr1.use_count() << std::endl;
    } // sPtr2 destroyed, Count becomes 1
    
    std::cout << "Count: " << sPtr1.use_count() << std::endl;
} // sPtr1 destroyed, Count becomes 0, memory DELETED.








Difference Between Mutex and Semaphores:
Mutex:----------------------
Binary semaphore (0 or 1 state).
Primarily used for mutual exclusion.
Typically used to protect access to a single shared resource.
Provides ownership; the thread that locks a mutex must unlock it.
Less complex and lightweight.

Semaphore:-----------------
Can have a count greater than 1.
Used for more general synchronization and coordination.
Can be used to control access to multiple resources or allow a fixed number of threads to access a resource.
Does not provide ownership; any thread can increment or decrement a semaphore.
Can be more complex to use in some scenarios.

Deadlocks:
Deadlocks occur in multi-threaded or multi-process systems when two or more threads or processes are unable to proceed 
because each is waiting for the other(s) to release a resource they need.
Deadlocks typically involve a circular waiting condition where Thread A is waiting for a resource held by Thread B, and 
Thread B is waiting for a resource held by Thread A.
Preventing deadlocks can involve techniques like resource allocation strategies, avoiding circular wait conditions, or using 
deadlock detection and recovery mechanisms.

Preventing Deadlocks:
preventing deadlocks include:------------
Resource Allocation Graph: Use a graph-based algorithm to detect potential circular waits and avoid them.
Resource Ordering: Establish a predefined order in which resources must be acquired to avoid circular waits.
Timeouts: Set timeouts on resource requests to release resources if they are not acquired within a certain time.
Deadlock Detection: Periodically check for deadlocks and take corrective action if one is detected.
Avoidance Algorithms: Use algorithms like Bankers Algorithm to ensure that resource allocation cannot lead to a deadlock.

Virtual Memory:-------------
Virtual memory is a memory management technique used by modern operating systems to provide the illusion of a larger and 
contiguous memory space to processes.
It allows processes to use more memory than is physically available by using a combination of RAM and disk storage.
The operating system manages the mapping of virtual addresses used by processes to physical addresses in RAM and, if necessary, 
swaps data between RAM and disk.

Advantages of Using Threads over Processes:
Threads are lighter in terms of resource overhead compared to processes since they share the same memory space and resources.
Faster Communication: Inter-thread communication is faster and more efficient than inter-process communication (IPC) since 
threads share memory.
Parallelism: Threads can run in parallel and are well-suited for tasks that can be divided into subtasks running concurrently.
Resource Sharing: Threads within the same process can easily share data and resources.
Synchronization: Threads can synchronize more easily through mechanisms like mutexes and semaphores.
Context Switching: Context switching between threads is faster compared to processes due to shared memory space.







structure vs union --------------------
A structure is a user-defined data type provided to us in C and C++. It is a data type that is used to create 
custom types according to users’ needs. It is a collection of more than one variable of different data types, 
which are all allocated specific memory.
A union is also one of the user-defined data types provided to us in C and C++. Like structure, a union can store more 
than one variable of different data types. But in a union, every data member declared is not individually allocated memory.
Here we skip on using extra memory, and we allocate memory of the largest size data variable as the memory of the union. 
Whenever we update a data member, all other data members get updated with the same new value if they are of the same data 
type or a garbage value is assigned to them.
This does not allow us to update and access all data members simultaneously but saves us memory.


//In C and C++, if you declare a struct or union but don't explicitly initialize its members in the main function or elsewhere, the 
//members will contain indeterminate (garbage) values. The space for the struct or union itself is allocated, 


---------------------------------------------------------------------------------------------------------------------------

there is a class shape. it has three variable radius, length, breadth. it will have a pure virtual function 
calculateArea(). Two sub classes will be derieved from there named circle and rectangle. they will override the 
calculateArea function.

// Base class
class Shape {
protected:
    double radius,length,breadth;
public:
    Shape(double r, double l, double b) : radius(r), length(l), breadth(b) {}

    virtual double calculateArea() const = 0;

    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    Circle(double r) : Shape(r, 0, 0) {}

    double calculateArea() const override {
        return 3.14 * radius * radius;
    }
};

class Rectangle : public Shape {
public:
    Rectangle(double l, double b) : Shape(0, l, b) {}

    double calculateArea() const override {
        return length * breadth;
    }
};
int main() {
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);
    cout << "Area of Circle: " << circle.calculateArea() << endl;
    cout << "Area of Rectangle: " << rectangle.calculateArea() << endl;
}



Another way->----------------------------------------------------
class shape {
public:
    int radius, length, breadth;

    shape(int l, int b) : length(l), breadth(b), radius(0) {}

    shape(int r) : length(0), breadth(0), radius(r) {}

    virtual int calculateArea() const = 0;
};

class circle : public shape {
public:
    circle(int r) : shape(r) {}

    int calculateArea() const override {
        return static_cast<int>(22.0 / 7 * radius * radius);
    }
};

class rectangle : public shape {
public:
    rectangle(int l, int b) : shape(l, b) {}

    int calculateArea() const override {
        return length * breadth;
    }
};

int main() {
    circle c(5);
    rectangle r(3, 5);

    cout << "Area of Circle: " << c.calculateArea() << endl;
    cout << "Area of Rectangle: " << r.calculateArea() << endl;

    return 0;
}

Another way----------------------------Myway------------------------------->
class shape{
public:
    int radius,length, breadth;
public:
    shape(int l, int b){
        length=l;
        breadth=b;
    }
    shape(int r){
        radius=r;
    }
    virtual int calculateArea() const=0;
};

class circle: public shape{
public:
    circle(int r):shape(r){}; // this line is very very important.
    int calculateArea() const override{
        return 22/7*radius*radius;
    }
};

class rectangle: public shape{
    public:
    rectangle(int l, int b):shape(l,b){};
    int calculateArea() const override{
        return length*breadth;
    }
};

int main(){
    circle c(5);
    rectangle r(3,5);
    cout<<c.calculateArea();
    cout<<r.calculateArea();
}




Playing with pointers->
	// Dynamic array allocation using pointers
    int *dynamicArray = new int[5] {1, 2, 3, 4, 5};
    // Accessing dynamic array elements using pointer notation
    for (int i = 0; i < 5; ++i) cout << *(dynamicArray + i) << " ";
    // Don't forget to delete the dynamic array to avoid memory leaks
    delete[] dynamicArray;

Declare an int with pointer-> int* a = new int(); 

array of pointer holding 5 integer pointers-> int* ptr[5];

dereferenceing = adding '*'

creating 2d array with pointers--------------------------->
	int rows = 3; int columns = 4;

    // Dynamically allocate memory for rows
    int** myArray = new int*[rows];
    // Dynamically allocate memory for columns
    for (int i = 0; i < rows; ++i) {
        myArray[i] = new int[columns];
    }

    

char *ptr = "Hello Unstoppable";
cout << ptr; 		// Hello Unstopable
cout <<*ptr; 		//H




int arr[5]={10,20,30,40,50};
int *ptr=&arrr[0];
cout<<*ptr;  		//10
cout<<*(ptr+1)		//20
cout<<ptr    		//address of first element of arr


feature 	                  char* ptr                                         int* ptr
cout << ptr      Prints the content (string) until \0.           Prints the hexadecimal address.
cout << *ptr            Prints the first character only.        Prints the first integer only.
Reason                 Specialized overload for C-strings.        Standard pointer behavior.


1.....................................
int arr[] = {10, 20, 30, 40};
int *p = arr;
std::cout << *(p++) << std::endl; // Prints 10, then p moves to 20
std::cout << *(++p) << std::endl; // p moves to 30, then prints 30

2.......................................
int arr[5];
cout << sizeof(arr) << endl; // Prints size of whole array (e.g., 20 bytes)
void func(int a[]) {
    cout << sizeof(a) << endl; // Prints size of a POINTER (e.g., 8 bytes)
}
Rule: Arrays "decay" into pointers when passed to functions

3.......................................
int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;
    
    std::cout << *(ptr + 3) << " ";
    
    char *c_ptr = (char*)ptr;
    std::cout << *(int*)(c_ptr + 4) << std::endl;
    
}
Answer: 40 20
Explanation: 
1. ptr + 3 moves the pointer by 3 x {sizeof(int)}. 
Since int is 4 bytes, it moves 12 bytes forward to the value 40.
2. c_ptr is a char*. When you do c_ptr + 4, it moves exactly 4 bytes forward (because sizeof(char) is 1).
3. Since the first int (10) took up 4 bytes, moving 4 bytes lands you exactly at the start of the second int (20).

4.........................................
int main() {
    const char *suit[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    const char **p = suit;

    p++;               // Move to "Diamonds"
    std::cout << *p << " "; 
    std::cout << **p << std::endl; 
}

Answer: Diamonds D
Explanation:
suit is an array of pointers. 
p is a pointer to the first pointer.
p++ moves p to point to the address of the second string ("Diamonds").
*p dereferences p once, giving you the char* (the whole string "Diamonds").
**p dereferences twice. It goes to the string and picks the first character: 'D'.

5..........................................
int main() {
    char str[] = "Qualcomm";
    char *p = str;

    std::cout << sizeof(str) << " ";
    std::cout << sizeof(p) << " ";
    std::cout << strlen(p) << std::endl;
}
Answer: 9 8 8
Explanation:sizeof(str): Includes the hidden null-terminator \0 at the end of "Qualcomm". 8 + 1 = 9 bytes.
sizeof(p): p is a pointer. On a 64-bit system, all pointers are 8 bytes.
strlen(p): This counts characters until the null-terminator. Qualcomm has 8 characters.

6............................................
int main() {
    const char *ptr[] = {"Qualcomm", "Snapdragon", "Adreno"};
    const char **p = ptr;

    p += 2;
    std::cout << *p + 2 << std::endl;
    return 0;
}
When you say const char **p = ptr;, p is pointing to the first pointer in the array (ptr[0]).
p is the address of ptr[0].
*p is the value stored in ptr[0], which is the address of the string "Qualcomm".
**p is the character at that address, which is 'Q'.
p += 2 moves the pointer to point to "Adreno". 
*p dereferences it to get the string "Adreno" (a char*). 
*p + 2 performs pointer arithmetic on that string, moving the start point forward by 2 characters ('A', 'd'). 
Thus, it prints starting from 'r'.


Level,				Mental Command,						Result
p,			"""Where am I in the list?""",		The address of the first string box (ptr[0]).
*p,			"""Jump into that box!""",			"You are now at the start of the string ""Qualcomm""."
*p + 4,		"""Walk 4 steps forward.""",		You are now standing in front of the 'c'.
*(*p + 4),	"""Grab what's inside!""",			You have the character 'c'.





//createing a class and calling it through a pointer-> heap vs stack-----------------------------------------
class MyClass {
public:
    void display() {
        cout << "Hello from MyClass!" << endl;
    }
};

int main() { 
    MyClass* ptr = new MyClass; // Creating an object of MyClass dynamically. 
    							//this created the memory on the heap
    ptr->display(); // Accessing the member function through the pointer
    delete ptr;
    return 0;
}

int main(){ // this is how you not use pointer to create an object. 
			//this creates the memory on the stack
	MyClass mc;
    mc.display();
}




// malloc allocates memory in the heap
int * ptr;
ptr = (int *)malloc(sizeof(int));   

// making an array with malloc
int * ptr;
ptr=(int*) malloc(sizeof(int)*len);
free(ptr);



Stack - All the variables that are declared inside any function take memory from the stack.
		MyClass obj;
		automatically delets itself
		Stack allocation is straightforward and efficient but comes with limitations, 
		such as a fixed size for the stack and objects being automatically deallocated 
		when they go out of scope (e.g., when a function ends).

Heap - It is unused memory in the program that is generally used for dynamic memory allocation.
		new keyword
		malloc()
		delete() or free() is needed to deallocate



malloc- insuffient memory-> returns NULL
		free() keyword is used to deallocate mem
		more execution time
		after allocation, mem size can be reallocated with realloc()
		assigns memory in heap

new- insuffient menory->throws exception
	delete keyword is neededeto deallocate mem
	less execution time
	once allocated, mem size cannot be altered
	assigns memory in heap




calloc is used to allocate memory to an array.
It can also be done with malloc.
int *arr = (int *)calloc(5, sizeof(int));

You cant create an object for an abstract class


// The program will show the use of new and delete  
int main (){  
    int* m = NULL;  // Pointer initialization to null  
  
    // Request memory for the variable  
    // using new operator  
    m = new(nothrow) int; //nothrow will give back a null pointer in case of 
    //any problem instead of throwing an exception 
    if (!m)  
        cout<< "allocation of memory failed\n";
    else{
        *m=29;  // Store value at allocated address.  
        //So we can understand that printing m will print the address of m.
        //that is why to print the value we de-reference it with *
        cout<< "Value of m: " << *m <<endl;  
        //printing &m will print the address of the pointer variable.
    }  
    // Request block of memory  
    // using new operator  
    float *f = new float(75.25);  
    cout<< "Value of f: " << *f <<endl;  
    // Request block of memory of size   
    int size = 5;  
    int *arr = new(nothrow) int[size];  
    if (!arr)  
        cout<< "allocation of memory failed\n";  
    else{  
        for (int i = 0; i< size; i++)  
            arr[i] = i+1;  
  
        cout<< "Value store in block of memory: ";  
        for (int i = 0; i< size; i++)  
            cout<<arr[i] << " ";  
    }  
  
    // freed the allocated memory  
    delete m;  
    delete f;
    // freed the block of allocated memory  
    delete[] arr;
    return 0;  
}  




// Declaring a constructor virtual is not permitted. Destructors can be made virtual.
Virtual destructors are useful when you might potentially delete an instance of a derived class through a pointer to base class
// One cannot inherit a constructor.
// Constructor addresses cannot be referenced to.

//read about copy-constructor. 

--------------------------------------------------------------------------------------------------
//static variables->
class MyClass{
public:
    static int count;
};

class MyClass2 {
public:
    static int count;
};
static int count;  // This is a global variable

MyClass::count = 42;     // Accessing MyClass's static member
MyClass2::count = 123;   // Accessing MyClass2's static member
::count = 987;           // Accessing the global static variable

if you have a static member variable inside a class, it is associated with the class itself 
rather than with any specific instance 
of the class. 
Static member variables are shared among all instances of the class, and they can also be 
accessed without creating an object of 
the class.
you can have static variables with the same name in both a base class and a derived class.
However, these variables will be completely independent of each other.

MyClass::staticVariable = 42;



--------------------------------------------------------------------------------------------------------

//Enums----->
enum week { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };  
int main(){  
    week day;  
    day = Friday;  
    cout << "Day: " << day+1<<endl;  
    return 0;  
}

//friend functions----->
If a function is defined as a friend function in C++, then the protected and private data of a class can be accessed using the function.
class Box    {    
    private:    
        int length;    
    public:    
        Box(): length(0) { }    
        friend int printLength(Box); //friend function    
};    
int printLength(Box b){    
   b.length += 10;    
    retrn b.length;    
}    



//default arguments-------->
int sum(int x, int y, int z=0, int w=0) // Here there are two values in the default arguments   
{ // Both z and w are initialised to zero   
    return (x + y + z + w); // return sum of all parameter values  
}  
int main()  
{  
    cout << sum(10, 15) << endl; // x = 10, y = 15, z = 0, w = 0  
    cout << sum(10, 15, 25) << endl; // x = 10, y = 15, z = 25, w = 0  
    cout << sum(10, 15, 25, 30) << endl; // x = 10, y = 15, z = 25, w = 30  
    return 0;  
}  




//Dynamic binding-> in this concept, which methed to call is decided at the runtime. It is also
called late binding. See a YT video for example. 





----------------------------------------------------------------------------
---------------------------LINUX FILE SYSTEM--------------------------------
Everything is a file
The Linux file structure follows the Filesystem Hierarchy Standard (FHS).

















---------------------------------------------------
Monitering-
1. first jump to payments(cronjobs, failed payments, slack notifications, jira ticket)
2. Health checkup endpoint (pings the server in intervals to check if the server is alive)
3. Metric system (can do around with kafka. when an exception is thrown, it is not only given to the user, it also trigers a log to the system.)

----------------SYSTEM DESIGN------(ALEX_YU)------------------
Non relational databases are grouped into
four categories: 
key-value stores, 
graph stores, 
column stores, and 
document stores.

multi-masters and circular replication are some of the methods used to transfer data from a master node to another node to keep it up to date

sql vs noSql (speed)

✅ SQL → Better for structured data, transactions, reporting, analytics.
✅ NoSQL → Better for high-scale apps, flexible schema, caching, unstructured data.

horizantal scaling vs vertical scaling

layer 7 vs layed 4 load balancer

is a through table required between two concrete tables in a DB design



CDN vs Dynamic Content Caching:-
When to Use Each?
✅ Use CDN for
✔ Images, videos, CSS/JS
✔ Product pages that don’t change frequently
✔ Large files served worldwide
Cache Key	URL/file path
Personalization-	Not personalized (same file for everyone)

✅ Use Dynamic Caching for
✔ Personalized dashboards (e.g., user carts)
✔ API responses that are same for short time (e.g., trending products for 5 mins)
✔ Computation-heavy results that can be reused
Cache Key	Custom key (e.g., user_id:cart)
Personalization-	Can be personalized per user/session


These algos are used in rate-limiter
• Token bucket
• Leaking bucket
• Fixed window
• Sliding window log
• Sliding window counter

Sliding window log algorithm for the rate-limiting is based on rejecting request using a Sliding window based on total no of requests that come in.
not on the successful requests. this is because, during trafic spikes, if we store the time stamps of only the successfully processed requests, the systems
might think there is ample space in the system and keep on accepting more and more requests because it doesnt know the total count of requests we have rejected.
and it might crash. so we also store the timestamp of every requests in redis and then decide whether to accept or reject a request.


Ideas to read about-

Redis rate limiter uses Lua and sorted set.break down the DB into two different microservice. one for read and another for write.
with this you will be able to scale both of them horizantally.

windows has FileSystemWatcher and macOS has FSEvents to track local file changes.

there is a thing called fingerprinting which is actually a hash of a file. that is an unique valie and can be used to compare two files if they are the same.
remember that there is a "trust but verify approach" where we need a client maching to give use some data which we are expecting.
We take it from the client but we also once verify it from our side if it is true.



#todo: read them -
1. design a search/ranking system
2. design a chat/messenger system
3. read about bijective functions- (something related to one to one mapping in shortUrl to longUrl)
4. redis has a high availiability mode. read about that once (Enable high availability with build in replication for recovery).
5. Dynamo: Amazon’s Highly Available Key-value Store:
https://www.allthingsdistributed.com/files/amazon-dynamo-sosp2007.pdf
6. Cassandra - A Decentralized Structured Storage System:
http://www.cs.cornell.edu/Projects/ladis2009/papers/Lakshman-ladis2009.PDF

Vector Clock is a [server, version] pair associated with a data item. If there are two writes happening at the same time in a distributed system, it can be used to check if one version preeceds, succeeds or is in conflict with others.



gossip protocol- Hinted handoff is used to handle temporary failures. if one server is down, shift to anothe server. when it is back, shift back to the prev one.
anti-entropy protocol is used to handle permanent failures. Anti-entropy involves comparing each piece of data on replicas and updating
each replica to the newest version. A Merkle tree is used for inconsistency detection and
minimizing the amount of data transferred.
#todo: read about mechanism of Merkle tree.

needs:
	ability to store big databases
	dataset partition
	incremental scalablity
	Hetereogineity
solved by- [CONSISTENT HASHING]



needs:
	high available reads
solved by [DATA REPLICATION, MULTI-DATA CENTER SETUP]



needs:
	high available writes
solved by [VERSIONING AND CONFLICT RESOLUTION WITH VECTOR CLOCKS]



------------------Design Unique ID Generator------------------
• IDs must be unique.
• IDs are numerical values only.
• IDs fit into 64-bit.
• IDs are ordered by date.
• Ability to generate over 10,000 unique IDs per second.

1. Multi-master replication- This approach uses the databases’ auto_increment feature. Instead of increasing the next ID
by 1, we increase it by k, where k is the number of database servers in use. It is not scalable. Doesnt increase with the time-constraint given.

2. UUID (Universally unique identifier)- UUID is a 128-bit number used to identify
information in computer systems. UUID has a very low probability of getting collusion.
IDs do not go up with time, IDs could be non-numeric, UUID is 128 bit. requirement is 64 bit.

3. Ticket Server- The idea is to use a centralized auto_increment feature in a single database server.
It has a single point of failure.

4. Twitter snowflake approach- Here we take advantage of how a  ID is segregated. We divide and conquer.
• Sign bit: 1 bit. It will always be 0. This is reserved for future uses. It can potentially be
used to distinguish between signed and unsigned numbers.
• Timestamp: 41 bits. Milliseconds since the epoch or custom epoch. We use Twitter
snowflake default epoch 1288834974657, equivalent to Nov 04, 2010, 01:42:54 UTC.
• Datacenter ID: 5 bits, which gives us 2 ^ 5 = 32 datacenters.
• Machine ID: 5 bits, which gives us 2 ^ 5 = 32 machines per datacenter.
• Sequence number: 12 bits. For every ID generated on that machine/process, the sequence
number is incremented by 1. The number is reset to 0 every millisecond.

Clock synchronization. In our design, we assume ID generation servers have the same
clock. This assumption might not be true when a server is running on multiple cores. The
same challenge exists in multi-machine scenarios. however, it is important to understand the problem exists.
Network Time Protocol is the most popular solution to this problem.



--------------Design URL Shortner----------------------------
Functional requirements:- (features)
	-create a short URL from a long URL
		-optionally support a custom alias
		-optionally support a expiraton time
	-be redirected from a long URL to a short URL

Non-functional requirements:- (qualities)
	-low latency on redirects (~200ms)
	-scale to support a 100M DAU & 1B URLs
	-Ensure uniqueness of short codes (/...) to avoid collusions
	-(cAP)High availability, eventual consistency for URL shortning, Partition tolerance is a must
		(so we fight between availability and consistency)

Core Entities:-
	Original URLs
	Short URLs
	User

API:-
	//short a url
	POST /urls -> shortUrl
	{
		originalURL,
		alias?,
		expiratonTime?
	}

	//redirection
	GET/ {shortUrl} -> redirect to originalURL


When the GET endpoint is called-
remember about HTTP 302(temporaray caching redirect) 
301(permanent caching redirect)
Try to use 302 in any system. It helps to track the workings if everything is working fine.
It might be used to log the requests in your ened or also might work in showing analytics to the user (if there are any requirements like that)



Hash + collision resolution while getting the shortUrl:-
	To shorten a long URL, we should implement a hash function that hashes a long URL to a 7-
character string. To resolve hash collisions, we can recursively append a new
predefined string until no more collision is discovered. A technique called bloom filters can improve
performance. A bloom filter is a space-efficient probabilistic technique to test if an element is
a member of a set.

When we say that i am going to use the base62 encoding to geneerate the shortUrl, then it means,
user is going to give me  {longURL}, i am going to say to my system what is the next counter?
system lets say gives me 100, I am then going to base62(100) and get lets say "1TF".
then that {longURL} is going to be mapped to "1TF" and 100 will be  the id of the row.
So in this approach we will need a distributed unique ID generator. This can be easily done with a redis instance saperately.
Or you can use the Twitter Snowflake approach.

but in the hash+collision resolution, we use the {shortURL} as the ID only.





---------------DESIGN WEB CRAWLER----------------------
Design a web crawler to extract text data from the web and save it for a LLM to use it.
your crawler can run for only 5 days.

Functional requirements:
	crawl the full web starting from seed urls.
	extract text data and store.

scale:
	10B web pages
	2MB /page
	5 days to scrape
	unlimited resources (with reason)

non-functional requirements:
	fault tolerant
	politeness
	scale to 10B pages
	efficient crawl under 5 days

core-entities:
	Text data
	domain metadata (for robots.txt)
	url metadata (url itself and whether we have crawled it or not)

Interface:
	input: set of seed urls
	output: text data

dataflow:
	Take seed urls from a frontier and IP from DNS
	fetch HTML
	extract text from HTML
	store that text in DB
	extract the urls in the text and add to frontier
	repeat the steps again

#todo: remember to read difference between kafka and sqs.



Handling politeness:-
1. Front Queues (Prioritization)
The Front Queues handle Priority. Not all URLs are equal; a page on CNN.com is generally more important than a random blog post.
The Mechanism: Incoming URLs are passed through a Prioritizer which assigns a score. URLs are then distributed into multiple "Front Queues" based on their priority level.
The Selector: The Front Queue Selector cycles through these queues (typically using a weighted round-robin approach) to pick URLs, giving more frequent turns to higher-priority queues.

2. Back Queues (Politeness)
The Back Queues handle Politeness. You want to avoid downloading too many pages from the same host (e.g., wikipedia.org) at the same time to prevent crashing their server or getting your IP banned.
The Router: The Back Queue Router ensures that all URLs from the same host name always go into the same specific "Back Queue."
The Table: A mapping table keeps track of which host is associated with which queue.
The Selector: A separate selector pulls from these queues only when the previous task for that specific host is finished (often adding a small delay).

How they work together (The Flow)
Stage 1: The Front Queue (Priority) The Front Queue Selector picks a URL based on how important it is. You are right—it might pick 10 URLs in a row from apple.com because they are high priority.
Stage 2: The Back Queue Router (Sorting) Those 10 URLs are handed to the Back Queue Router. It doesnt download them yet! It simply puts all 10 into the specific "Back Queue" dedicated to apple.com.
Stage 3: The Back Queue Selector (The Gatekeeper) This is the "magic" part that solves your concern. The Back Queue Selector logic is: "I will only give a URL to a worker thread if the previous download from that same website finished a few seconds ago."

The Key Insight: Even if 1,000 apple.com URLs are waiting in the Back Queue because they are high priority, the Back Queue Selector will only release them one by one, with a "politeness delay" (e.g., 1 second) between each.



for the case where we will be needing to find out if we have seen a particular URL before or not, there are a couple of ways to do this
1. we can hash the content of the page and store that hash in our url table in the metafata DB
to do it even faster, we can index the table with respect to the hash
We can also store the hash inside a redis instance for fast lookups.

2. bloom filter- It is a space-efficient DS that is used to see set-inclusion. 
The main challenge with a Bloom filter is that it can give false positives. This means that it might tell us that we have crawled a page when we actually havent. 
We could argue that this is an acceptable trade-off for the performance benefits and can configure our bloom filter to reduce the probability of false positives by increasing the size 
of the filter and the number of hash functions used.
To be honest, I think the bloom filter here is a bit overkill.
Always bring up bloom filrer when you have space constraints.






-------------------DESIGN A NOTIFICATION SYSTEM-------------------
Scalable Notification System Design
Core Architecture: Event-Driven & Asynchronous
In high-scale systems (like Uber or Airbnb), notifications are decoupled from the main application logic to ensure speed and reliability.

Key Components

• Service Triggers ⚡: Apps drop a message into a queue rather than sending the notification directly.

• Message Queues 🗂️: Tools like Apache Kafka or RabbitMQ buffer incoming requests, preventing system crashes during traffic spikes.

• Notification Workers 👷: Independent services that pull messages from the queue, look up user preferences, and call external APIs (e.g., Twilio, Firebase).

• Analytical Engines 📊: Track metrics like delivery rates, bounces, and open rates.

Why this is the "Real World" Solution

• Scalability: You can spin up more workers instantly to handle millions of messages.

• Fault Tolerance: If an external provider goes down, the message stays safely in the queue to be processed later.




------------------DESIGN A NEWS FEED---------------------------

Functional requirements:-
	create post
	follow users
	view feed
	page through feed

	bonus:-
		like and comment
		privacy settings

C - consistency (good to have but not must)
A - Availibility (should have)
P - partition tolerance (must)


Non functional requirements
	eventual consistency
	500ms latency for posting and viewing
	2b DAU

core entities:-
	Posts
	Users
	Follow (A uni-directional link between users in our system.)

APIs:-


#todo: read about dynamoDB, SK (sort key), global seconday index, 



Using a simple pageNumber (like page=1, page=2) is known as Offset Pagination, and while it is very common for things like search results, it causes two major problems in a real-time system like a Facebook News Feed.

1. The "Skipped/Duplicate Content" Problem 🔄
Imagine you are looking at Page 1 of your feed. While you are reading, 5 of your friends post new photos. Those new posts get pushed to the very top of the database.

If you then click "Next Page" (Page 2):

The Shift: The posts that were at the bottom of Page 1 have now been pushed down into the Page 2 slot by those 5 new photos.
The Result: You will see the same posts again at the top of Page 2 that you just saw at the bottom of Page 1.

how does the cursor thing work?
in the first time, in the request, only the page size is sent.
it gives lets say 10 posts. it also sends a cursor (a timestamp).
the next time when the API is hit, it sends that cursor and it says "give me 10 more posts which is older than cursor timestamp".
it again gives back 10 new posts and another new cursor.



For the DB we can use dynamoDB as DynamoDB allows us to provision a nearly limitless amount of capacity provided we spread our load evenly across our partitions.


How following/followed table would work:-
Essentially, its explaining how to store the information that "User A follows User B" so that you can find it quickly later. 
Instead of a fancy "social graph" database, they are suggesting a Key-Value Store (like DynamoDB).
1. The "Follow" Table 📁
Think of this as a simple spreadsheet. Every time someone follows someone else, you add a row.

UserFollowing (Who is doing the following)  |   UserFollowed (Who is being followed)
	Alice												Bob
	Alice												Charlie
	Bob													Alice

Partition Key (UserFollowing): This is the "Main ID." If the database wants to find everything Alice is doing, it looks at this column first.

Sort Key (UserFollowed): This is used to organize the data under Alice.

2. Answering the Questions 🙋‍♂️
The paragraph mentions "Querying" and "Range Queries." Here is what that looks like in practice:

"Is Alice following Bob?": You look for the specific row where the Main ID is Alice and the Sort Key is Bob. If it exists, the answer is "Yes." (This is a Simple Lookup).

"Who does Alice follow?: You ask the database to give you every row where the Main ID is Alice. It will return Bob and Charlie. (This is a Range Query).

3. The GSI (Global Secondary Index) 🔄
Here is the tricky part. What if you want to know "Who follows Bob?"

In the table above, Bob is in the second column. Most databases cant "search backwards" efficiently. To fix this, we create a GSI, which is basically the database automatically making a duplicate, flipped version of the table:

UserFollowed (New Main ID)	|   UserFollowing (New Sort Key)
	Bob									Alice
	Alice								Bob
	Charlie								Alice

Now, to find Bobs followers, the database just looks at the first column of the flipped table!



How do we handle users with a large number of followers? (Uneven write problem)

-----Justin Bieber Problem-------->
To understand this, we have to look at the two ways a social media feed can be built:

1. Fan-out on Write (The "Pre-packaged" way) 📦
When Alice posts a photo, the system immediately "pushes" that photo into the "Feed Folders" of all her followers.

Benefit: When a follower opens their app, their feed is already built and waiting. It’s super fast to read. ⚡

The Bieber Problem: If Justin Bieber has 90 million followers, one single post from him triggers 90 million database writes at once. This would literally crash the system. 💥

2. Fan-out on Read (The "Cook-to-order" way) 🍳
The system does nothing when someone posts. Instead, when you open your app, the system looks at everyone you follow and "pulls" their latest posts together right then and there.

Benefit: No massive write spikes when celebrities post.

The Problem: If you follow 1,000 people, the system has to do a lot of work every single time you refresh your feed. It’s slow to read. 🐢
The "Hybrid" Approach (The clever part) 🧠
The paragraph is suggesting we use both methods based on how famous the user is:

For Regular Users (like us): Use Fan-out on Write. When you post, it only goes to a few hundred friends. The system can handle that easily, and your friends get a fast feed.

For Celebrities (Bieber/Modi): Use Fan-out on Read. The system ignores their posts during the "write" phase. 🛑

The Merge: When you open your feed, the system grabs your pre-built feed (full of your regular friends' posts) and merges it with any recent posts from the celebrities you follow.

Why the "Follow Table" needs a flag 🚩
To make this work, the system needs to know which type of user it's dealing with. In the "Follow Table" we discussed earlier, we add a little note (a flag) that says: "This person is a VIP. Don't try to precompute their posts for their followers."



How can we handle uneven reads of Posts?
1. The Strategy: The "Read-Aside" Cache 🛡️
Instead of every users app asking the main Post Table (the database) for the content of a post, they ask Redis (the cache) first.

	Long TTL (Time to Live): Since social media posts rarely change after they are published, we can let them sit in the cache for a long time (e.g., 24 hours).

	LRU (Least Recently Used): If the cache gets full, it automatically kicks out the "old/boring" posts to make room for new ones.

	Invalidation: If a user does edit their post, the system sends a command to Redis: "Delete the old version of Post #123." 
	The next time someone looks for it, the system will fetch the fresh version from the DB and put it back in the cache.

2. The "N * M" Math 🧮
This is just a way of saying the cache is distributed. 
If you have 10 servers (N) and each server has 64GB of RAM (M), your total "safety net" for posts is 640GB. 
By spreading posts across many servers, you can store way more than a single machine ever could.

3. The "Hot Key" Problem (The Real Challenge) 🔥
This is the most important part of the paragraph. It explains why a cache doesnt solve everything.

Imagine a post by a celebrity goes viral. That specific post has one unique Post ID. In a distributed cache like Redis, that specific Post ID is stored on exactly one physical server in your cluster (this is called "sharding").

The Problem: If 10 million people look at that viral post at the exact same time, all 10 million requests hit one single server in your Redis cluster.

The "Unequal Load": * Server A is catching fire because its handling the viral post.
	Server B, C, and D are sitting idle, doing almost nothing because they are holding "boring" posts that no one is looking at.

The Result: Your system is "underutilized" but also "failing" at the same time. You cant just add more servers to fix this, because no matter how many servers you add, that one viral post ID will still live on just one machine.

How to fix "Hot Keys" (Context for your next reading)
Usually, to solve this, engineers use Cache Replication. Instead of the viral post living on one machine, you copy it to all cache machines so the 10 million requests can be spread out across the entire cluster.


Remember- when ever we are going to read a lot from a table:- GSIs can also become hot, but they’re easier to scale, replicate, or shard than base tables. 
If the base table gets overloaded, it can cause catastrophic write failures, so its safer to offload this kind of read-heavy access to a GSI.