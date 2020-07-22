#include <string>
#include "FamilyTree.hpp"
#include <exception>
using namespace family;

struct err1 : public std::exception {
    const char* what() const noexcept { return "The tree cannot handle this relation\n"; } //how this works?
};

string Tree::find(string name)
{
    Tree* child = findreg(this, name); //how this works?
    if (child != nullptr)return child->child;
    throw runtime_error("The tree cannot handle '" +name +"' relation");
    return "";
}

Tree* Tree::findchild(Tree* root, string name) //how the recursion works?
{
    if (root->child == name)
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

Tree* Tree::findreg(Tree* root, string reg) //how the recursion works?
{
    if (root->reg == reg)
    {
        return root;
    }
    if (root->father != nullptr)
    {
        Tree* ans = findreg(root->father, reg);
        if (ans != nullptr)
            return ans;
    }
    if (root->mother != nullptr) {
        Tree* ans = findreg(root->mother, reg);
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
            if (child->reg == "me") child->father->reg = "father";
            else
                if (child->reg == "father") child->father->reg = "grandfather";
                else
                    if (child->reg == "grandfather") child->father->reg = "great-grandfather";
                    else
                        if (child->reg == "mother") child->father->reg = "grandfather";
                        else
                            if (child->reg == "grandmother") child->father->reg = "great-grandfather";
                            else
                            {
                                string temp = "great-" + child->reg;
                                for (int j = 0; j < 6; j++) temp.pop_back(); //what is that really? including for loop
                                temp += "father";
                                child->father->reg = temp;
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
            if (child->reg == "me") child->mother->reg = "mother";
            else
                if (child->reg == "father") child->mother->reg = "grandmother";
                else
                    if (child->reg == "grandfather") child->mother->reg = "great-grandmother";
                    else
                        if (child->reg == "mother") child->mother->reg = "grandmother";
                        else
                            if (child->reg == "grandmother") child->mother->reg = "great-grandmother";
                            else
                            {
                                string temp = "great-" + child->reg;
                                for (int j = 0; j < 6; j++) temp.pop_back();
                                temp += "mother";
                                child->mother->reg = temp;
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
    return child->reg;
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
    cout << root->child << "\n";
    print(root->mother, space);
}

void Tree::display()
{
    cout << "display tree:" << endl;
    print(this, 0);
}

