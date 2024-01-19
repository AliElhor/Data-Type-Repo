/*======================================================================
Test code for circular queue and dynamic stack
**======================================================================*/

#include <iostream>
#include <string>

#include "circular-queue.h"
#include "dynamic-stack.h"

using namespace std;

// Assert Macros for test cases.
#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;

string get_status_str(bool status)
{
    return status ? "PASSED" : "FAILED";
}

// Define the test suites (implementation below).
class DynamicStackTest
{
private:
    bool test_result[4] = {0, 0, 0, 0};
    string test_description[4] = {
        "Test1: new empty stack is valid",
        "Test2: push() an element on zero-element stacks",
        "Test3: peek() and pop() on one-element stack",
        "Test4: peek(), push(), and pop() work properly together",
    };

public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

    bool test1();
    bool test2();
    bool test3();
    bool test4();
};

class CircularQueueTest
{
private:
    bool test_result[4] = {0, 0, 0, 0};
    string test_description[4] = {
        "Test1: new empty queue is valid",
        "Test2: enqueue() an element on zero-element queues",
        "Test3: peek() and dequeue() on one-element queue",
        "Test4: peek(), enqueue(), and dequeue() work properly together",
    };

public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

    bool test1();
    bool test2();
    bool test3();
    bool test4();
};

//======================================================================
//================================ MAIN ================================
//======================================================================
int main()
{

    // The test suite has some tests implemented for you,
    // and place holders for where you can put your own.
    DynamicStackTest ds_test;

    // You can check the description for each test to see
    // what we will be testing for with the following method.
    // Alternatively, you can also navigate to the line above
    // where the test description is stored to read it.
    cout << ds_test.getTestDescription(1) << endl;

    // Tests can be run one at a time to get their result
    bool result = ds_test.test1();
    cout << "Test1: " << get_status_str(result) << endl
         << endl;

    // Or you can run all of the tests at once and generate a report.
    ds_test.runAllTests();
    ds_test.printReport();

    // Uncomment and use this for lab 2.2 when it is released.
     CircularQueueTest cq_test;
     cq_test.runAllTests();
     cq_test.printReport();

    return 0;
}

//======================================================================
//========================= Dynamic Stack Test =========================
//======================================================================
string DynamicStackTest::getTestDescription(int test_num)
{
    if (test_num < 1 || test_num > 4)
    { // check range.
        return "";
    }
    return test_description[test_num - 1];
}

void DynamicStackTest::runAllTests()
{
    test_result[0] = test1();
    test_result[1] = test2();
    test_result[2] = test3();
    test_result[3] = test4();
}

void DynamicStackTest::printReport()
{
    cout << "  DYNAMIC STACK TEST RESULTS  \n"
         << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n";
    for (int idx = 0; idx < 4; ++idx)
    {
        cout << test_description[idx] << "\n  " << get_status_str(test_result[idx]) << endl
             << endl;
    }
    cout << endl;
}

// Test 1: new empty stack is valid
bool DynamicStackTest::test1()
{

    // Test set up.
    unsigned int capacity = 5;
    DynamicStack stack(capacity);

    // Check that the internal state is set correctly.
    ASSERT_TRUE(stack.size() == 0)
    ASSERT_TRUE(stack.empty())
    ASSERT_TRUE(stack.capacity_ == capacity)
    ASSERT_TRUE(stack.init_capacity_ == capacity)
    ASSERT_FALSE(stack.items_ == nullptr)

    // Test the default constructor for the stack.
    DynamicStack default_stack;

    // Check that the internal state is set correctly.
    ASSERT_TRUE(default_stack.size() == 0)
    ASSERT_TRUE(default_stack.empty())
    ASSERT_TRUE(default_stack.capacity_ == 16)
    ASSERT_TRUE(default_stack.init_capacity_ == 16)
    ASSERT_FALSE(default_stack.items_ == nullptr)

    // Return true to signal all tests passed.
    return true;
}

// Test 2: push() an element on zero-element stacks
bool DynamicStackTest::test2()
{

    // Test set up.
    unsigned int capacity = 5;
    DynamicStack stack(capacity);

    // Try to add data to the stack (returns void so no assert check for success).
    stack.push(100);

    // Check that the internal state is correct.
    ASSERT_TRUE(stack.size() == 1)
    ASSERT_TRUE(stack.capacity_ == capacity)
    ASSERT_TRUE(stack.init_capacity_ == capacity)
    ASSERT_FALSE(stack.items_ == nullptr)
    ASSERT_TRUE(stack.items_[0] == 100)

    // Return true to signal all tests passed.
    return true;
}

// Test 3: peek() and pop() on one-element stack
bool DynamicStackTest::test3()
{

    // Test set up.
    unsigned int capacity = 5;
    DynamicStack stack1(capacity);
    DynamicStack stack2(capacity);

    // Check peek on an empty stack.
    ASSERT_TRUE(stack1.peek() == DynamicStack::EMPTY_STACK)

    // Try to add data to the stacks (returns void so no assert check for success).
    stack1.push(100);
    stack2.push(200);

    // Check the state of the capacities before popping.
    ASSERT_TRUE(stack1.init_capacity_ == 5 && stack1.capacity_ == 5 && !stack1.empty() && stack1.size_ == 1)
    ASSERT_TRUE(stack2.init_capacity_ == 5 && stack2.capacity_ == 5 && !stack2.empty() && stack2.size_ == 1)

    // Peek at the top element, then remove it.
    ASSERT_TRUE(stack1.peek() == 100 && stack1.pop() == 100)
    ASSERT_TRUE(stack2.peek() == 200 && stack2.pop() == 200)

    // Check the state of the capacities after popping.
    ASSERT_TRUE(stack1.init_capacity_ == 5 && stack1.capacity_ == 5 && stack1.empty() && stack1.size_ == 0)
    ASSERT_TRUE(stack2.init_capacity_ == 5 && stack2.capacity_ == 5 && stack2.empty() && stack2.size_ == 0)

    // Check that the peek on an empty stack still gives expected value.
    ASSERT_TRUE(stack2.peek() == DynamicStack::EMPTY_STACK)

    // Return true to signal all tests passed.
    return true;
}

// Test 4: peek(), push(), and pop() work properly together
bool DynamicStackTest::test4()
{
    // Test set up
    unsigned int capacity = 5;
    DynamicStack stack1(capacity);
    DynamicStack stack2(capacity);

    for (int i = 0; i < 7; i++) {
        stack1.push(i);
    }

    ASSERT_TRUE(stack1.peek() == 6)
    ASSERT_TRUE(stack1.capacity_ == 10)

    for (int i = 0; i < 13; i++) {
        stack1.push(i);
    }

    ASSERT_TRUE(stack1.capacity_ == 20)

    for (int i = 0; i < 16; i++) {
        stack1.pop();
    }

    ASSERT_TRUE(stack1.capacity_ == 10)

    for (int i = 0; i < 3; i++) {
        stack1.pop();
    }

    ASSERT_TRUE(stack1.capacity_ == 5)
    ASSERT_TRUE(stack1.size_ == 1)

    stack1.pop();

    ASSERT_TRUE(stack1.capacity_ == 5)
    ASSERT_TRUE(stack1.size_ == 0)

    ASSERT_TRUE(stack1.pop() == -999)

    return true;
}

//======================================================================
//======================== Circular Queue Test =========================
//======================================================================
string CircularQueueTest::getTestDescription(int test_num)
{
    if (test_num < 1 || test_num > 4)
    { // check range.
        return "";
    }
    return test_description[test_num - 1];
}

void CircularQueueTest::runAllTests()
{
    test_result[0] = test1();
    test_result[1] = test2();
    test_result[2] = test3();
    test_result[3] = test4();
}

void CircularQueueTest::printReport()
{
    cout << "  CIRCULAR QUEUE TEST RESULTS  \n"
         << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n";
    for (int idx = 0; idx < 4; ++idx)
    {
        cout << test_description[idx] << "\n  " << get_status_str(test_result[idx]) << endl
             << endl;
    }
    cout << endl;
}

// Test 1: new empty queue is valid
bool CircularQueueTest::test1()
{

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue(capacity);

    // Check that the internal state is set correctly.
    ASSERT_TRUE(queue.size() == 0)
    ASSERT_TRUE(queue.empty())
    ASSERT_FALSE(queue.full())
    ASSERT_TRUE(queue.capacity_ == capacity)
    ASSERT_FALSE(queue.items_ == nullptr)
    ASSERT_TRUE(queue.head_ == 0 && queue.tail_ == 0)

    // Test the default constructor for the queue.
    CircularQueue default_queue;

    // Check that the internal state is set correctly.
    ASSERT_TRUE(default_queue.size() == 0)
    ASSERT_TRUE(default_queue.empty())
    ASSERT_FALSE(default_queue.full())
    ASSERT_TRUE(default_queue.capacity_ == 16)
    ASSERT_FALSE(default_queue.items_ == nullptr)
    ASSERT_TRUE(default_queue.head_ == 0 && default_queue.tail_ == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 2: enqueue() an element on zero-element queues
bool CircularQueueTest::test2()
{

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue1(capacity);
    CircularQueue queue2(capacity);

    // Try to enqueue data to the queues.
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue2.enqueue(100))

    // Check that the internal state is correct.
    ASSERT_TRUE(queue1.size() == queue2.size() && queue1.size() == 1)
    ASSERT_FALSE(queue1.items_ == nullptr)
    ASSERT_FALSE(queue2.items_ == nullptr)
    ASSERT_TRUE(queue1.items_[queue1.head_] == 100)
    ASSERT_TRUE(queue2.items_[queue2.head_] == 100)
    ASSERT_TRUE(queue1.head_ == 0 && queue1.tail_ == 1)
    ASSERT_TRUE(queue2.head_ == 0 && queue2.tail_ == 1)

    // Return true to signal all tests passed.
    return true;
}

// Test 3: peek() and dequeue() on one-element queue
bool CircularQueueTest::test3()
{

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue1(capacity);
    CircularQueue queue2(capacity);

    // Check peek on an empty queue.
    ASSERT_TRUE(queue1.peek() == CircularQueue::EMPTY_QUEUE)

    // Add data to the queues.
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue2.enqueue(200))

    // Peek at the top element, then remove it.
    ASSERT_TRUE(queue1.peek() == 100 && queue1.dequeue() == 100)
    ASSERT_TRUE(queue2.peek() == 200 && queue2.dequeue() == 200)

    // Check the resulting sizes of the queues.
    ASSERT_TRUE(queue1.size_ == queue2.size_ && queue1.size_ == 0)
    ASSERT_TRUE(queue1.empty() && queue2.empty())

    // Check that the peek on an empty queue still gives expected value.
    ASSERT_TRUE(queue2.peek() == CircularQueue::EMPTY_QUEUE)

    // Return true to signal all tests passed.
    return true;
}

// Test 4: peek(), enqueue(), and dequeue() work properly together
bool CircularQueueTest::test4()
{
    unsigned int capacity = 5;
    CircularQueue queue1(capacity);
    CircularQueue queue2(capacity);

    ASSERT_TRUE(queue1.peek() == CircularQueue::EMPTY_QUEUE)

    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue1.enqueue(200))
    ASSERT_TRUE(queue1.enqueue(300))
    ASSERT_TRUE(queue1.peek() == 100 && queue1.dequeue() == 100)
    ASSERT_TRUE(queue1.enqueue(400))
    ASSERT_TRUE(queue1.enqueue(500))
    ASSERT_TRUE(queue1.enqueue(600))
    ASSERT_FALSE(queue1.enqueue(700))
    ASSERT_TRUE(queue1.peek() == 200 && queue1.dequeue() == 200)
    ASSERT_TRUE(queue1.size() == 4 )
    ASSERT_TRUE(queue1.enqueue(800))
    ASSERT_TRUE(queue1.peek() == 300 && queue1.dequeue() == 300)
    ASSERT_TRUE(queue1.enqueue(900))
    ASSERT_TRUE(queue1.peek() == 400 && queue1.dequeue() == 400)
    ASSERT_TRUE(queue1.enqueue(110))
    ASSERT_TRUE(queue1.peek() == 500 && queue1.dequeue() == 500)
    ASSERT_TRUE(queue1.enqueue(120))
    ASSERT_TRUE(queue1.peek() == 600 && queue1.dequeue() == 600)
    ASSERT_TRUE(queue1.enqueue(130))
    ASSERT_FALSE(queue1.enqueue(140))
    ASSERT_FALSE(queue1.enqueue(150))
    ASSERT_TRUE(queue1.peek() == 800 && queue1.dequeue() == 800)
    ASSERT_TRUE(queue1.peek() == 900 && queue1.dequeue() == 900)
    ASSERT_TRUE(queue1.peek() == 110 && queue1.dequeue() == 110)
    ASSERT_TRUE(queue1.peek() == 120 && queue1.dequeue() == 120)
    ASSERT_TRUE(queue1.peek() == 130 && queue1.dequeue() == 130)
    ASSERT_TRUE(queue1.dequeue() == -999 && queue1.size() == 0 && queue1.empty())
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue1.enqueue(200))
    ASSERT_TRUE(queue1.enqueue(300))
    ASSERT_TRUE(queue1.enqueue(400))
    ASSERT_TRUE(queue1.enqueue(500))
    ASSERT_FALSE(queue1.enqueue(600))

    queue1.~CircularQueue();

    ASSERT_TRUE(queue1.items_ == nullptr)
    ASSERT_FALSE(queue1.enqueue(500))

    return true;
}
