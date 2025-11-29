#include <iostream>
#include <string>
using namespace std;
class Stack
{
private:
    static const int MAX_SIZE = 10000;
    string data[MAX_SIZE];
    int top;
public:
    Stack() : top(-1) {}
    bool isEmpty()
    {
        return top == -1;
    }
    bool isFull()
    {
        return top == MAX_SIZE - 1;
    }
    void push(const string& item)
    {
        if(isFull())
        {
            cout<<"Stack overflow!"<<endl;
            return;
        }
        top++;
        data[top] = item;
    }
    string pop()
    {
        if(isEmpty())
        {
            cout<<"Stack underflow!"<<endl;
            return "";
        }
        string item = data[top];
        top--;
        return item;
    }
    string peek()
    {
        if(isEmpty())
        {
            cout<<"Stack is empty!"<<endl;
            return "";
        }
        return data[top];
    }
};
class TextEditor
{
private:
    string text;
    int cursor;
    Stack undoStack;
    Stack redoStack;
public:
    TextEditor() : text(""), cursor(0) {}
    void insert(const string& newText)
    {
        undoStack.push(text);
        text.insert(cursor, newText);
        cursor += newText.length();
        redoStack = Stack();
    }
   void erase(int numChars)
   {
    if(numChars > cursor)
        numChars = cursor;
    if(numChars > 0)
    {
        undoStack.push(text);
        text.erase(cursor - numChars, numChars);
        cursor -= numChars;
        redoStack = Stack();
    }
}
    void moveCursor(int position)
    {
        if(position < 0 || position > text.length())
        {
            cout<<"Invalid cursor position!"<<endl;
            return;
        }
        cursor = position;
    }
    void undo()
    {
        if(undoStack.isEmpty())
        {
            cout<<"Nothing to undo!"<<endl;
            return;
        }
        redoStack.push(text);
        text = undoStack.pop();
        cursor = text.length();
    }
    void redo()
    {
        if(redoStack.isEmpty())
        {
            cout<<"Nothing to redo!"<<endl;
            return;
        }
        undoStack.push(text);
        text = redoStack.pop();
        cursor = text.length();
    }
    void display()
    {
        for(int i = 0; i < text.length(); i++)
        {
            if(i == cursor)
            {
                cout<<"|";
            }
            cout<<text[i];
        }
        if(cursor == text.length())
        {
            cout<<"|";
        }
        cout<<endl;
    }
};
int main()
{
    TextEditor editor;
    int choice;
    string newText;
    int numChars;
    int newPosition;
    do
    {
        cout<<"Text Editor Menu"<<endl;
        cout<<"1. Insert Text"<<endl;
        cout<<"2. Erase Text"<<endl;
        cout<<"3. Move Cursor"<<endl;
        cout<<"4. Undo"<<endl;
        cout<<"5. Redo"<<endl;
        cout<<"6. Display Text"<<endl;
        cout<<"7. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch (choice)
        {
            case 1:
                cout<<"Enter the text to insert: ";
                cin.ignore();
                getline(cin, newText);
                editor.insert(newText);
                break;
            case 2:
                cout<<"Enter the number of characters to erase: ";
                cin>>numChars;
                editor.erase(numChars);
                break;
            case 3:
                cout<<"Enter the new cursor position: ";
                cin>>newPosition;
                editor.moveCursor(newPosition);
                break;
            case 4:
                editor.undo();
                break;
            case 5:
                editor.redo();
                break;
            case 6:
                editor.display();
                break;
            case 7:
                cout<<"Exiting..."<<endl;
                break;
            default:
                cout<<"Invalid choice!"<<endl;
                break;
        }
        cout<<endl;
    }while(choice != 7);
    return 0;
}