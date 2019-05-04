// Muhammad Nebras Taleb
// 1306160206
// Date : 14.05.2017 
// Development Enviorement : Visual Studio 2017
#include <iostream>
#include <stdio.h>
#include <string>
#include <set>

using namespace std;
////////////global variables//////////////
int num_of_obj = 0;
char  numofrow[2] = {0,0};
char numofcol[2] = {0,0};
set<char>::iterator it;
/////////////my class/////////////////////
class Bacteria
{
public:
	Bacteria() { name = '\0'; }
	void multi();
	void set_food(char);
	char name;
	struct Loc { int R; int C; }loc;
	set<char> food;
};
Bacteria** Habitat;
void Bacteria::multi()
{
	int up = this->loc.R - 1;
	int down = this->loc.R + 1;
	int right = this->loc.C + 1;
	int left = this->loc.C - 1;
	int row = numofrow[0];
	int col = numofcol[0];
	if ((up != -1) && ((this->food.count(Habitat[up][this->loc.C].name))
		||   (Habitat[up][this->loc.C].name=='\0')))
	{
		Habitat[up][this->loc.C].name = this->name;
		Habitat[up][this->loc.C].food = this->food;
		Habitat[up][this->loc.C].loc.C = this->loc.C;
		Habitat[up][this->loc.C].loc.R = up;
		num_of_obj++;
	}
	
	if (down != row && ((this->food.count(Habitat[down][this->loc.C].name))
		|| (Habitat[down][this->loc.C].name == '\0')))
		{
		Habitat[down][this->loc.C].name = this->name;
		Habitat[down][this->loc.C].food = this->food;
		Habitat[down][this->loc.C].loc.C = this->loc.C;
		Habitat[down][this->loc.C].loc.R = down;
		num_of_obj++;
		
	}
	if ((right != col) && ((this->food.count(Habitat[this->loc.R][right].name) )
		|| (Habitat[this->loc.R][right].name == '\0')))
	{
		Habitat[this->loc.R][right].name = this->name;
		Habitat[this->loc.R][right].food = this->food;
		Habitat[this->loc.R][right].loc.C = right;
		Habitat[this->loc.R][right].loc.R = this->loc.R;
		num_of_obj++;
	}
	if ((left != -1) && ((this->food.count(Habitat[this->loc.R][left].name))
		|| (Habitat[this->loc.R][left].name == '\0')))
	{
		Habitat[this->loc.R][left].food = this->food;
		Habitat[this->loc.R][left].name = this->name;
		Habitat[this->loc.R][left].loc.C = left;
		Habitat[this->loc.R][left].loc.R = this->loc.R;
		num_of_obj++;
	}
};
void Bacteria::set_food(char C)
{
	food.insert(C);
};
//////////function prototypes//////////////
void print_file(FILE *);
inline void skip_line(FILE *);
void extract_bacte_names(FILE *);
void extract_rules(FILE *);
void extract_size(FILE *);
void extract_locations(FILE *);
void print_info();
void bulid_habitat();
void multiplication();
void print_result();
////////////global variables//////////////
Bacteria Bac_names[26];
Bacteria bacteria[576];
int num_of_bacteria = 0;
int N;
////////////The main///////////////////////
void main()
{
	
	FILE *in_file = fopen("data.txt", "r");
	print_file(in_file);
	extract_bacte_names(in_file);
	extract_rules(in_file);
	extract_size(in_file);
	extract_locations(in_file);
	print_info();
	bulid_habitat();
	multiplication();
	print_result();
	
	
	system("pause");
}

////////function defenitions//////////
void print_file(FILE *f)
{
	cout << "\nThe Input File :\n";
	cout << "================\n\n";
	char c;
	while ((c = fgetc(f)) != EOF)
	{
		cout << c;
	}
	cout << endl;
	rewind(f);
}
inline void skip_line(FILE *f)
{
	char c[11];
	fgets(c, 11, f);
	int x = ftell(f);
	fseek(f, x, SEEK_SET);
}
void extract_bacte_names(FILE *f)
{
	 char c;
	skip_line(f);
	//now we'll read the bacteria's names
	while ((c = fgetc(f)) != '\n')
	{
		if (c != ' ')
		{
			Bac_names[num_of_bacteria].name = c;
			num_of_bacteria++;
		}
	}
}
void extract_rules(FILE* f)
{
	char c;
	skip_line(f);
	/*char y;
	y = fgetc(f);if(y!='A')skip_line(f);*/
	 int i = 0; char arrow[5]; char t;
	while ((c = getc(f)) != 's')
	{
		if (Bac_names[i].name == c)
		{
			fgets(arrow, 4, f); t = getc(f);
			t = getc(f);
			Bac_names[i].set_food(t);t=getc(f);
		}
		else
		{
				i++;
			if (Bac_names[i].name == c)
			{
				fgets(arrow, 4, f); t = getc(f);
				t = getc(f);
				Bac_names[i].set_food(t); t=getc(f);
			}
		}
	}
}
void extract_size(FILE * f)
{
	char n1, n2; char x[5];
	skip_line(f);
	n1 = getc(f); 	n2 = getc(f);
	if (n2 == ' ')
	{
		fgets(x, 3, f);
		numofrow[0] = (n1-48);
	}
	else
	{
		fseek(f, -2, SEEK_CUR);
		fgets(numofrow, 3, f);
		fgets(x, 4, f);
	}
	n1 = getc(f); 	n2 = getc(f);
	if (n2 != '\n')
	{
		fseek(f, -2, SEEK_CUR);
		fgets(numofcol, 3, f);
	}
	else
		numofcol[0] = (n1-48);


	if (numofrow[1] != 0)
	{
		int x = (numofrow[0] - 48) * 10 + (numofrow[1] - 48);
		numofrow[0] = x;
	}
	if (numofcol[1] != 0)
	{
		int x = (numofcol[0] - 48) * 10 + (numofcol[1] - 48);
		numofcol[0] = x;

	}
}
void extract_locations(FILE *f)
{
	char c = getc(f);
	/*skip_line(f);*/ skip_line(f);
	char  space; int i = 0; int j = 0;
	while ((c = getc(f)) != EOF)
	{
		num_of_obj++;
		if (Bac_names[i].name == c)
		{
			bacteria[j] = Bac_names[i];
			space = fgetc(f);
			bacteria[j].loc.R = fgetc(f) - 48;
			space = fgetc(f);
			bacteria[j].loc.C = fgetc(f) - 48;
			space = fgetc(f); j++;
		}
		else
		{
			i++;
			bacteria[j] = Bac_names[i];
			space = fgetc(f);
			bacteria[j].loc.R = fgetc(f) - 48;
			space = fgetc(f);
			bacteria[j].loc.C = fgetc(f) - 48;
			space = fgetc(f); j++;
		}
	}
}
void print_info()
{
	cout << endl << "The Information That We Can Extract From The Input File Is The Following :" << endl;
	cout << "==========================================================================" << endl;
	for (int o = 0; o<num_of_obj; o++)
	{

		cout << bacteria[o].name << " Can eat :";
		for (it = bacteria[o].food.begin(); it != bacteria[o].food.end(); it++)
			cout << " " << *it;
		cout << "\t  Its location : " << bacteria[o].loc.R << "x" << bacteria[o].loc.C << endl;
	}
	cout << endl << "==========================================================================" << endl ;
}
void bulid_habitat()
{
	 Habitat = new Bacteria*[numofrow[0]];
	for (int a = 0; a < numofrow[0]; a++)
		Habitat[a] = new Bacteria[numofcol[0]];
	for (int t = 0; t < num_of_obj; t++)
	{
		Habitat[bacteria[t].loc.R][bacteria[t].loc.C] = bacteria[t];
	}
	cout << "The Habitat That We Have Before Any Turn Is :\n \n";
	int row, col;
	row = numofrow[0];
	col = numofcol[0];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (Habitat[i][j].name !='\0' )
				cout << " " << Habitat[i][j].name <<" ";
			else
				cout << " * ";

		}
		cout << endl;

	}
}
void multiplication()
{
	cout << endl << "==========================================================================";
	cout << endl << "Enter The Number Of Turns You Want Please : \n ";
	cin >> N;
	int name_counter = 0;
	int obj_counter = 0;
	int f;
	int itr;
	for (int counter = 0; counter < N; counter++)
	{
		name_counter = 0;
		obj_counter = 0;
		for (int n = 0; n < num_of_obj; n++)
		{

			if (Bac_names[name_counter].name == bacteria[obj_counter].name)
			{
				if (Habitat[bacteria[obj_counter].loc.R][bacteria[obj_counter].loc.C].name == bacteria[obj_counter].name)
				{
					bacteria[obj_counter].multi();
				}
				obj_counter++;
			}
			else
			{
				name_counter++;
				if (Bac_names[name_counter].name == bacteria[obj_counter].name)
				{
					if (Habitat[bacteria[obj_counter].loc.R][bacteria[obj_counter].loc.C].name == bacteria[obj_counter].name)
					{
						bacteria[obj_counter].multi();
					}
					obj_counter++;
				}
			}
		}

		itr = 0;
		f = 0;
		while (f != num_of_bacteria)
		{
			for (int i = 0; i < numofrow[0]; i++)
			{
				for (int j = 0; j < numofcol[0]; j++)
				{
					if ((Habitat[i][j].name != '\0') && (Habitat[i][j].name == Bac_names[f].name))
					{
						bacteria[itr] = Habitat[i][j];
						itr++;
					}
				}
			}
			f++;
		}
		

	}
}
void print_result()
{
	cout<<"---\n";
	cout << endl;
	cout << "Tha Habitat Status After " << N << " Turn(s) is :\n\n";
	for (int i = 0; i < numofrow[0]; i++)
	{
		for (int j = 0; j < numofcol[0]; j++)
		{
			if (Habitat[i][j].name != '\0')
				cout << " " << Habitat[i][j].name << " ";
			else
				cout << " * ";

		}
		cout << endl;
	}
	cout << endl;
}