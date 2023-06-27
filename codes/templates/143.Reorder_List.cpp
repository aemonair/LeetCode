/*
 *******************************************************************
 * 143. Reorder List
 * Medium
 *******************************************************************
 * Given a singly linked list L: L0→L1→…→Ln-1→Ln,
 * reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
 *
 * You may not modify the values in the list's nodes, only nodes itself may be changed.
 *
 *******************************************************************
 * Example 1:
 *
 * Given 1->2->3->4, reorder it to 1->4->2->3.
 *******************************************************************
 * Example 2:
 *
 * Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
 *******************************************************************
 */
// 45 yy
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <climits>
#include <chrono>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define     RESET   "\033[0m"
#define     RED     "\033[31m"             /*      Red     */
#define     CYAN    "\033[36m"             /*      Cyan    */
#define     BLUE    "\033[34m"             /*      Blue    */
#define     GREEN   "\033[32m"             /*      Green   */
#define     WHITE   "\033[37m"             /*      White   */
#define     BLACK   "\033[30m"             /*      Black   */
#define     YELLOW  "\033[33m"             /*      Yellow  */
#define     MAGENTA "\033[35m"             /*      Magenta */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow  */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black   */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White   */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green   */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue    */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan    */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red     */

// Definition for singly-linked list.
typedef struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
}ListNode;

class Solution {
public:
    /////////////////////////////////////////////////////////////////
    void reorderList(ListNode* head)
    {
        return;
    }
    /////////////////////////////////////////////////////////////////
    ListNode * merge(ListNode * head, ListNode * halfhead)
    {
        if (head == halfhead){
            return head;
        }
        if(halfhead == nullptr && head == nullptr) {
            return nullptr;
        }
        if(halfhead==nullptr && head != nullptr && head ->next == nullptr) {
            return head;
        }
        if(head==nullptr && halfhead != nullptr && halfhead->next == nullptr) {
            return halfhead;
        }
        // head -> 1->2 ->3
        // half -> 4->5 ->6
        //            n2
        //        1->4->5->6
        //        1->4->
        //        head 5->6
        //        half 2->3
        //             n5
        //             5->2->3
        //             2->
        //           head 3
        //           half 6
        //                 next null
        //                 3-> 6
        //                 6->
        //                    null null
        //                 6->null
        //             2-> 6->null
        //          4-> 2->6  
            ListNode * next = head->next;
            head->next = halfhead;
            printList(head);
            //halfhead -> next; halfhead->next = head->next
            ListNode * newhead = merge(next, halfhead->next);
            halfhead ->next = newhead;
            // 1 2 3
            // 4 5 6
            //   n2
            // 1 4 5 6
            // 1 4 ?
            //     2 3
            // 1
            // 2
            // n null
            // 1->2
            //    2->?
            //       null , null      
            printList(head);
            return head;
    }
    void reorderList0(ListNode* head)
    {
        ListNode * slow = head;
        ListNode * fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            if (fast == nullptr) {
                ListNode * old = slow;
                slow = slow->next;
                old->next = nullptr;
            } else {
            slow = slow->next;
            }
        }
        ListNode *halfhead = reverse(slow);
        printList(head);
        printList(halfhead);
        ListNode * newhead = merge(head, halfhead);
        // 1 2 3
        // 4 5 6
        /*
        ListNode * p = head;
        ListNode * q = halfhead;
        while(p && q) {
            ListNode *  next = p ->next;
            p->next =q;
            p = next;

            next = q->next;
            q->next = p;
            q = next;
        }
        */
        printList(head);
        return;
    }
    /////////////////////////////////////////////////////////////////
    bool isSame(ListNode * head1, ListNode * head2)
    {
        if(head1==nullptr && head2== nullptr)
        {
            return true;
        }
        if(head1==nullptr || head2== nullptr)
        {
            return false;
        }
        if (head1->val == head2->val)
        {
            return isSame(head1->next , head2->next);
        }
        else
        {
            return false;
        }
    }
    ListNode * reverse(ListNode *head)
    {
        if(head == nullptr || head->next == nullptr)
        {
            return head;
        }
        ListNode * prev = nullptr;
        ListNode * next = head->next;
       
        while(head)
        {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;

    }
    std::vector<int> printList(ListNode* head)
    {
        std::vector<int> ret ; // = new ArrayList<>();
        std::unordered_set<int> set ; // = new ArrayList<>();
        ListNode *listNode = head;
        if (head)
        {
            std::cout << "head" << listNode->val << " : " ; //std::endl;
        }
        else
        {
            std::cout << "null" << std::endl;
        }
        while (listNode != nullptr) // && listNode->next != nullptr)
        {
            std::cout << listNode->val << " -> " ; // << std::endl;
            ret.push_back(listNode->val);
            if (set.count(listNode->val) > 0) {
                break;
            } else {
                set.insert(listNode->val);
            }
            listNode = listNode->next;
        }
        std::cout << "\b\b\b    " << std::endl;
        return ret;
    }
};

void Test(const std::string& testName,
        ListNode * head,
        ListNode * target
        )
{
    if(testName.length() > 0)
    {
        std::cout << BOLDMAGENTA << testName << " begins: "<< RESET << std::endl;       
    }

    Solution solution;

    auto start = std::chrono::system_clock::now();
    decltype(start) end ;
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    solution.printList(head);

const static int TEST_TIME = 1;
const static int TEST_0    = 1;
const static int TEST_1    = 0;
    // getpermutataion
    if (TEST_0)
    {
        std::cout << "Solution0 start.........." << std::endl;
        if (TEST_TIME)
        {
            start = std::chrono::system_clock::now();
        }

        solution.reorderList0(head);
        //solution.printList(head);
        if(solution.isSame( head ,target))
        {
            //10yy
            std::cout << GREEN << "Solution0 passed." << RESET <<  std::endl;
        }
        else
        {
            std::cout << RED << "Solution0 failed." <<  RESET << std::endl;
            std::cout << "expected:";  // << std::endl;
            solution.printList(target);
            std::cout << RESET ; //<< std::endl;
        }
        if (TEST_TIME)
        {
           end = std::chrono::system_clock::now();
           elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
           std::cout << "Solution0 costs " << elapsed.count() <<"micros" << std::endl;
        }
    }
    if (TEST_1)
    {
    }
}
void Test1()
{
    /*
     *         1 -> 2 -> 3 -> 4 -> 5
     *         1 -> 5 -> 2 -> 4 -> 3
     */
    struct ListNode * p1 = new ListNode(1);
    struct ListNode * p2 = new ListNode(2);
    struct ListNode * p3 = new ListNode(3);
    struct ListNode * p4 = new ListNode(4);
    struct ListNode * p5 = new ListNode(5);
   
    p1->next = p2;
    p2->next = p3;
    p3->next = p4;
    p4->next = p5;

    ListNode * q3 = new ListNode(3);
    ListNode * q4 = new ListNode(4, q3);
    ListNode * q2 = new ListNode(2, q4);
    ListNode * q5 = new ListNode(5, q2);
    ListNode * q1 = new ListNode(1, q5);

    Test("Test1", p1, q1);
}
void Test2()
{
    struct ListNode * r1 = new ListNode(1);
    struct ListNode * r2 = new ListNode(2);
    r1->next = r2;
    struct ListNode * p2 = new ListNode(2);
    struct ListNode * p1 = new ListNode(1,p2);
    Test("Test2", p1, r1);
}
void Test3()
{
    struct ListNode * p4 = new ListNode(4);
    struct ListNode * p3 = new ListNode(3,p4);
    struct ListNode * p2 = new ListNode(2,p3);
    struct ListNode * p1 = new ListNode(1,p2);

    struct ListNode * q3 = new ListNode(3);
    struct ListNode * q2 = new ListNode(2,q3);
    struct ListNode * q4 = new ListNode(4,q2);
    struct ListNode * q1 = new ListNode(1,q4);
    Test("Test3", p1, q1);
}
void Test4()
{
    struct ListNode * pc = new ListNode(12);
    struct ListNode * pa = new ListNode(10,pc);
    struct ListNode * p8 = new ListNode(8, pa);
    struct ListNode * p6 = new ListNode(6,p8);
    struct ListNode * p4 = new ListNode(4,p6);
    struct ListNode * p2 = new ListNode(2,p4);

    struct ListNode * q8 = new ListNode(8);
    struct ListNode * q6 = new ListNode(6 ,q8);
    struct ListNode * qa = new ListNode(10,q6);
    struct ListNode * q4 = new ListNode(4 ,qa);
    struct ListNode * qc = new ListNode(12,q4);
    struct ListNode * q2 = new ListNode(2 ,qc);
    // 2 4 6 8 10 12
    // 2 12 4 10 6 8
    Test("Test4", p2,q2);
}
void Test5()
{
    struct ListNode * pa = new ListNode(10);
    struct ListNode * p8 = new ListNode(8,pa);
    struct ListNode * p6 = new ListNode(6,p8);
    struct ListNode * p4 = new ListNode(4,p6);
    struct ListNode * p2 = new ListNode(2,p4);
    // 2 4 6 8 10
    // 2 10 4 8 6
    struct ListNode * q6 = new ListNode(6);
    struct ListNode * q8 = new ListNode(8 ,q6);
    struct ListNode * q4 = new ListNode(4 ,q8);
    struct ListNode * qa = new ListNode(10,q4);
    struct ListNode * q2 = new ListNode(2 ,qa);
    Test("Test5", p2,q2);
}
int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();

    return 0;
}
/*
 *
 *         1 -> 2 -> 3 -> 4 -> 5
 *              ↖            ↙ 
 *                ← ← ← ← ← ←
 *
 */

/*
 *  1->2->3->4
 *  1->2->4->3
 *  p pn  q   qn
 *  1->4<->2
 *     3
 *  1->4->2->3
 * */
