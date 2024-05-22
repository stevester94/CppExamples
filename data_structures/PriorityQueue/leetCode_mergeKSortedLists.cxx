/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <queue>
#include <algorithm>
#include <iostream>


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if( lists.size() == 0 ) {
            return nullptr;
        }

        priority_queue<ListNode*, vector<ListNode*>, compare> q;

        // Sanitize input of empty lists. We do this once on init, it will be fast
        for( ListNode* n : lists ) {
            cout << n << endl;
            if( n != nullptr ) {
                q.push( n );
            }
        }

        if( q.size() == 0 ) {
            return nullptr;
        }

        ListNode* head = q.top();
        q.pop();

        if( head == nullptr ) {
            return nullptr;
        }

        if( head->next != nullptr ) {
            q.push( head->next );
        }
        ListNode* cur = head;

        while( ! q.empty() ) {
            ListNode* now = q.top();
            q.pop();
            cur->next = now;
            cur = now;

            if( now->next != nullptr ) {
                q.push(now->next);
            }
        }

        return head;
    }

private:
    // Returns true if left comes before right (Debateable)
    struct compare {
        bool operator()(const ListNode* l, const ListNode* r) const { return l->val > r->val; }
    };
};