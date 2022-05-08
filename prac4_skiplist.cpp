#include<bits/stdc++.h>
using namespace std;

class LinkedList
{
    public:
        int val;
        LinkedList *next,*up,*down;
        LinkedList(int value)
        {
            val=value;
            next=up=down=NULL;
        }
};
LinkedList *root;
void create(LinkedList *curr)
{
    for(int i=1;i<=3;i++)
    {
        LinkedList *temp = curr,*prev=NULL;
        while(temp!=NULL)
        {
            LinkedList *extra = new LinkedList(temp->val);
            extra->down=temp;
            temp->up=extra;
            if(prev!=NULL) prev->next=extra;
            int skip = 2;
            prev=extra;
            while(temp!=NULL && skip--) temp=temp->next;
        }
        curr = curr->up;
        root = curr;
    }
}

bool search(LinkedList *curr,int find)
{
    if(curr == NULL) return false;
    if(curr->val == find) return true;
    if(curr->next==NULL || curr->next->val>find) return search(curr->down,find);
    else return search(curr->next,find);
    return false;
}

void display(LinkedList *curr)
{
    cout<<"Level Wise List :- \n";
    while(curr!=NULL)
    {
        LinkedList *temp = curr;
        while(temp!=NULL) cout<<temp->val<<" ",temp=temp->next;
        cout<<endl;
        curr=curr->down;
    }
}

void insert(LinkedList *curr,int ele)
{
    stack<LinkedList*> path;
    while(curr!=NULL)
    {
        LinkedList *temp = curr;
        while(temp!=NULL && temp->next!=NULL && temp->next->val<ele) temp=temp->next;
        path.push(temp);
        curr=curr->down;
    }
    srand(time(0));
    LinkedList *temp = path.top();
    path.pop();
    LinkedList *extra = new LinkedList(ele);
    extra->next = temp->next;
    temp->next = extra;
    LinkedList *curr1 = extra;
    while(path.size())
    {
        temp = path.top();
        path.pop(); 
        int random = rand();
        if(random%2)
        {
            extra = new LinkedList(ele);
            curr1->up = extra;
            extra->down = curr1;
            extra->next = temp->next;
            temp->next = extra;
            curr1 = extra;
        }
    }
    cout<<"Element successfully Inserted!\n";
}

void del(LinkedList *curr,int ele)
{
    if(!search(curr,ele))
    {
        cout<<"Element Not Found\n";
        return;
    }
    stack<LinkedList*> path;
    while(curr!=NULL)
    {
        LinkedList *temp = curr;
        while(temp!=NULL && temp->next!=NULL && temp->next->val<ele) temp=temp->next;
        path.push(temp);
        curr=curr->down;
    }

    while(path.size())
    {
        LinkedList *temp = path.top();
        path.pop();
        LinkedList *temp1 = temp->next;
        if(temp1!=NULL && temp1->val==ele) temp->next=temp1->next;
    }
    cout<<"Element Successfully Deleted!\n";
}

int main(){
    int ele = 1;
    LinkedList *start = new LinkedList(ele);
    LinkedList *curr = start;
    ifstream datafile("data4.txt");
    string line="";
    while (getline (datafile, line)) {
        vector <string> tokens;
        stringstream check1(line);
        string intermediate;
        while(getline(check1, intermediate, ' ')){
            tokens.push_back(intermediate);
        }
        ele = stoi(tokens[0]);
        //cout<<ele<<" - ";
        LinkedList *temp = new LinkedList(ele);
        curr->next = temp;
        curr = curr->next;
    }
    datafile.close();

    create(start);
    display(root);
    while(1)
    {
        int choice,x;
        
        cout<<"Enter You Choice :-\n";
        cout<<"1 to Search\n";
        cout<<"2 to Insert\n";
        cout<<"3 to Delete\n";
        cout<<"4 to Display\n";
        cout<<"5 to Exit\n";
        
        cin>>choice;
        if(choice==1)
        {
            cout<<"Enter The Element :- ";
            cin>>x;
            if(search(root,x)) cout<<"Present\n";
            else cout<<"Not Present\n";
        }

        if(choice==2)
        {
            cout<<"Enter The Element :- ";
            cin>>x;
            insert(root,x);
        }

        if(choice==3)
        {
            cout<<"Enter The Element :- ";
            cin>>x;
            del(root,x);
        }

        if(choice==4)
        {
            display(root);
        }

        if(choice==5)
        {
            cout<<"Program Executed Successfully!\n";
            break;
        }
    }
    return 0;
}