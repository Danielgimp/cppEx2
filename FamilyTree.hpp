#include <iostream>
#include <string.h>
#include <exception>
using namespace std;
namespace family
{
	class Tree
	{
	public:
		string nodeName;
		string nodeRelation;
		string gender;
		Tree* father;
		Tree* mother;
		Tree* son;

		Tree(string name)
		{
			this->nodeName = name;
			this->nodeRelation = "me";
			this->father = nullptr;
			this->mother = nullptr;
		}
		Tree& addFather(string childName, string fatherName);
		Tree& addMother(string childName, string motherName);
		string relation(string name);
		string find(string con);
		void display();
		void remove(string name);
		Tree* findchild(Tree* root, string name);
		Tree* findNodeRelation(Tree* root, string name);
		void print(Tree* root, int space);

	};

	class err : public std::exception //?
	{
	public:
		const char* what() const noexcept { return "error"; }
	};

}



