#include <string>
#include "FamilyTree.hpp"
#include <exception>
using namespace family;

struct err1 : public std::exception {
    const char* what() const noexcept { return "The tree cannot handle this relation\n"; } //how this works?
};

string Tree::find(string name)
{
    Tree* child = findNodeRelation(this, name); //how this works?
    if (child != nullptr)return child->nodeName;
    throw runtime_error("The tree cannot handle '" +name +"' relation");
    return "";
}

Tree* Tree::findchild(Tree* root, string name) //how the recursion works?
{
    if (root->nodeName == name)
    {
        return root;
    }
    if (root->father != nullptr)
    {
        Tree* ans = findchild(root->father, name);
        if (ans != nullptr)
            return ans;
    }
    if (root->mother != nullptr) {
        Tree* ans = findchild(root->mother, name);
        if (ans != nullptr)
            return ans;
    }
    return nullptr;
}

Tree* Tree::findNodeRelation(Tree* root, string reg) //how the recursion works?
{
    if (root->nodeRelation == reg)
    {
        return root;
    }
    if (root->father != nullptr)
    {
        Tree* ans = findNodeRelation(root->father, reg);
        if (ans != nullptr)
            return ans;
    }
    if (root->mother != nullptr) {
        Tree* ans = findNodeRelation(root->mother, reg);
        if (ans != nullptr)
            return ans;
    }
    return nullptr;
}

Tree &Tree::addFather(string childName, string fatherName) //who is son really?
{														  // and how it work
    Tree* child = findchild(this, childName);
    if (child != nullptr)
    {
        if (child->father == nullptr)
        {
            child->father = new Tree(fatherName);
            child->father->son = child;
            child->father->gender = "male";
            if (child->nodeRelation == "me") child->father->nodeRelation = "father";
            else
                if (child->nodeRelation == "father") child->father->nodeRelation = "grandfather";
                else
                    if (child->nodeRelation == "grandfather") child->father->nodeRelation = "great-grandfather";
                    else
                        if (child->nodeRelation == "mother") child->father->nodeRelation = "grandfather";
                        else
                            if (child->nodeRelation == "grandmother") child->father->nodeRelation = "great-grandfather";
                            else
                            {
                                string temp = "great-" + child->nodeRelation;
                                for (int j = 0; j < 6; j++) temp.pop_back(); //what is that really? including for loop
                                temp += "father";
                                child->father->nodeRelation = temp;
                            }
            return *this;
        }
        else
        {
            throw runtime_error(childName + " already has a father !");
        }
    }
    else
    {
        throw runtime_error(childName + " is not in the tree");
    }

}

Tree &Tree::addMother(string childName, string motherName)
{
    Tree* child = findchild(this, childName);
    if (child != nullptr)
    {
        if (child->mother == nullptr)
        {
            child->mother = new Tree(motherName);
            child->mother->son = child;
            child->mother->gender = "famale";
            if (child->nodeRelation == "me") child->mother->nodeRelation = "mother";
            else
                if (child->nodeRelation == "father") child->mother->nodeRelation = "grandmother";
                else
                    if (child->nodeRelation == "grandfather") child->mother->nodeRelation = "great-grandmother";
                    else
                        if (child->nodeRelation == "mother") child->mother->nodeRelation = "grandmother";
                        else
                            if (child->nodeRelation == "grandmother") child->mother->nodeRelation = "great-grandmother";
                            else
                            {
                                string temp = "great-" + child->nodeRelation;
                                for (int j = 0; j < 6; j++) temp.pop_back();
                                temp += "mother";
                                child->mother->nodeRelation = temp;
                            }
            return *this;

        }
        else
        {
            throw runtime_error(childName + " already has a mother !");
        }
    }
    else
    {
        throw runtime_error(childName + " is not in the tree");
    }
}

string Tree::relation(string name)
{
    Tree* child = findchild(this, name);
    if (child == nullptr) return "unrelated";
    return child->nodeRelation;
}

void Tree::remove(string name)
{
Tree* ptr = findchild(this, name);
	if (ptr == this) { throw runtime_error("Can't remove the root of the tree (aka -> me"); }
	if(ptr!=nullptr){
            if (ptr->son->mother == ptr){ ptr->son->mother = nullptr; }
            if (ptr->son->father == ptr){ ptr->son->father = nullptr; }
            delete ptr;
      }
      else { throw runtime_error(name+" is not in the tree"); }


}

void Tree::print(Tree* root, int space) {
    if (root == NULL) return;
    space += 10;

    print(root->father, space);
    cout << endl;
    for (int i = 10; i < space; i++) { cout << " "; }
    cout << root->nodeName << "\n";
    print(root->mother, space);
}

void Tree::display()
{
    cout << "display tree:" << endl;
    print(this, 0);
}

