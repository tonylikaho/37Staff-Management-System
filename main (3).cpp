#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
struct employee{
  string id, name, lastName, address, role, wage;
};
struct dataBase{
  vector < employee > v;
} db;
void createEmpDoc (int, string, string, string, string);
void createNewEmployee ();
void deleteEmployee ();
void getIdOfEmployee ();
void printEmployees ();
void editAnEmployee ();
int main (){
  cout << "---Terminal---\n\n";
  string choice;

  while (choice != "7")                                         //meun
    {
      cout <<
	"1. Add a new employee\n2. Get ID of an employee\n3. List all the employees\n4. Delete an employee\n5. Edit an employee\n6. Print all employees to text documents\n7. Exit\n";
      cout << endl << ">";
      cin >> choice;
      getchar ();
      if (choice == "1")
	{
	  srand (time (NULL));
	  createNewEmployee ();
	}
      else if (choice == "2")
	{
	  getIdOfEmployee ();
	}
      else if (choice == "3")
	{
	  printEmployees ();
	}
      else if (choice == "4")
	{
	  deleteEmployee ();
	}
      else if (choice == "5")
	{
	  editAnEmployee ();
	}
      else if (choice == "6")
	{
	  if (db.v.size () <= 0)
	    {
	      printf ("\nDB is null\n\n");
	    }
	  else
	    {
	      int x = 0;
	      for (int i = 0; i < db.v.size (); i++)
		{
		  auto a = stoi (db.v[i].id);
		  createEmpDoc (a, db.v[i].role, db.v[i].wage, db.v[i].name,
				db.v[i].lastName);
		  x++;
		}
	      printf ("\nSuccessfully created %i documents!\n\n", x);
	    }
	}
      else if (choice == "7")
	{
	  return EXIT_SUCCESS;
	}
      else
	cout << "\nThat is not an option!\nplease choose 1-7\n";

    }



  return 0;
}
void createEmpDoc (int id, string role, string wage, string firstname,string lastname){
  auto s = to_string (id) + ".txt";
  ofstream file (s);

  if (file.is_open ())
    {
      file << firstname << endl << lastname << endl << role << endl << wage <<
	endl << id << endl;
      cout <<
	"\nSucessfully created a new file with the employees information.\n\n";
      return;
    }
}
void createNewEmployee (){
  srand (time (NULL));
  struct employee *emp = new employee;
  int x;

  //enter the employees information
  cout << "--New employee---" << endl << endl << "Enter the firstname: >";
  getline (cin, emp->name);
  cout << endl;
  cout << "Enter the lastname: >";
  getline (cin, emp->lastName);
  cout << endl;
  cout << "Enter the role: >";
  getline (cin, emp->role);
  cout << endl;
  cout << "Enter the address: >";
  getline (cin, emp->address);
  cout << endl;
  cout << "Enter the wage: >";
  getline (cin, emp->wage);
  cout << endl;
  cout << "Assigning ID to the new employee...\n\n";
  x = (1 + rand () % 99999);
  auto s = to_string (x);	//convert id to string
  emp->id = s;

  for (int i = 0; i < db.v.size (); i++)
    {
      if (db.v.size () <= 0)
	{
	  break;
	}
      //if we by any unlucky chanse we would get a duplication in Id's
      if (emp->id == db.v[i].id)
	{
	  printf ("This ID already exist, assigning new id...\n");
	redo:
	  emp->id = (1 + rand () % 99999);
	  if (emp->id == db.v[i].id)
	    goto redo;
	}
    }

  //save the new employee in the database
  db.v.push_back (*emp);

  delete emp;
  emp = nullptr;
}
void deleteEmployee (){
  string FN, LN, IDD, b;
  bool a = 0;

  cout<<"\n\nEnter the employees firstname that you'd like to delete: >";
  cin >> FN;
  cout << "\n\nEnter the employees lastname that you'd like to delete: >";
  cin >> LN;
  cout << "\n\nEnter the employees ID that you'd like to delete: >";
  cin >> IDD;
  for (int i = 0; i < db.v.size (); i++)
    {
      if (IDD == db.v[i].id && LN == db.v[i].lastName && FN == db.v[i].name)
	{
	  cout << "Are you sure you want to delete" << db.v[i].name.
	    c_str () << db.v[i].lastName.
	    c_str () << "?\n(plese input Y for yes or N for No)";
	  cin >> b;
	  if (b == "Y")
	    {
	      printf ("Employee %s has been deleted\n", db.v[i].id.c_str ());
	      db.v.erase (db.v.begin () + i);
	      a = 1;
	    }
	}
    }
  if (a == 0 && b != "N")
    cout << "Employee not found" << endl;
}
void getIdOfEmployee () {
  string name;
  cout << "\nEnter the firstnamename you'd like to find the ID for: >";
  cin >> name;

  for (int i = 0; i < db.v.size (); i++)
    {
      if (name != db.v[i].name)
	continue;
      else
	printf ("\nName: %s\nID: %s\n\n", db.v[i].name.c_str (),
		db.v[i].id.c_str ());
    }
}
void printEmployees (){
  if (db.v.size () < 0 || db.v.size () == 0)
    {
      cout << "The database is NULL" << endl << endl << endl;
    }
  if (db.v.size () > 0)
    {
      for (int i = 0; i < db.v.size (); i++)
	{
	  printf
	    ("\nEmploye %i\n{\n\tFirstname: \t%s\n\tLastname: %s\n\tRole: \t%s\n\tAddress: \t%s\n\tWage: \t%s\n\tId: \t%s\n}\n\n",
	     i + 1, db.v[i].name.c_str (), db.v[i].lastName.c_str (),
	     db.v[i].role.c_str (), db.v[i].address.c_str (),
	     db.v[i].wage.c_str (), db.v[i].id.c_str ());
	}
    }
}
void editAnEmployee (){
  string FN, LN, IDD;
  int check=0;
  string wage, id, newName, lastName, newAddress, newRole;
  char d;
  bool running = true;
  if (db.v.size () < 0||db.v.size () == 0){
      cout<<"The database is NULL\n\n";
      return;
    }
  cout<<"\n\nEnter the employees firstname that you'd like to delete: >";
  cin >> FN;
  cout << "\n\nEnter the employees lastname that you'd like to delete: >";
  cin >> LN;
  cout << "\n\nEnter the employees ID that you'd like to delete: >";
  cin >> IDD;
  while (running){
      for (int i = 0; i < db.v.size (); i++){
	  if (IDD == db.v[i].id && LN == db.v[i].lastName && FN == db.v[i].name)
	    {check=1;
	      printf ("To exit edit mode, press 6\n\n");
	      printf("\nPress 1 to edit firstname, 2 to edit lastname, 3 for address, 4 for role and 5 for wage, 6 to go back\n>");
          cin >> d;
        switch (d)
		{
		case '1':
		  cout << endl << "Enter the new employees new firstname: >";
		  cin >> newName;
		  db.v[i].name = newName;
		  break;
		case '2':
		  cout << endl << "Enter the new lastname: >";
		  cin >> lastName;
		  db.v[i].lastName = lastName;
		  break;
		case '3':
		  cout << endl << "Enter the new address: >";
		  cin >> newAddress;
		  db.v[i].address = newAddress;
		  break;
		case '4':
		  cout << endl << "Enter the new role for the employee: >";
		  cin >> newRole;
		  db.v[i].role = newRole;
		  break;
		case '5':
		  cout << endl << "Enter thew new wage for the employee: >";
		  cin >> wage;
		  db.v[i].wage = wage;
		  break;
		case '6':
		  running = false;
		  break;
		default:
		  cout << "Not a valid option!\nchoose again"<<endl;
	      cin>>d;
	       break;// flush stream
	    }

	}
	if(check==0){
	    cout<<"employee Not Found"<<endl;
	    running = false;
	}
    }
}
    
}