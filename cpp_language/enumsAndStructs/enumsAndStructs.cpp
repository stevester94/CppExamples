/* Enums and Structs
Enums are used as a replacement in places you might use a #define
	- Note the type deffing only is required in C, in C++ it makes no difference

Structs are pretty straightforward
*/



#include <iostream>

using namespace std;

enum Color {
	red,
	blue,
	orange,
	violet
};

typedef enum YearInCollege {
	freshman,
	sophomore,
	junior,
	senior
};

typedef struct {
	YearInCollege currentYear;
	enum Color favoriteColor;
} Student;

int main() {
	// Assignments require this syntax if typedef isn't used
	enum Color favoriteColor = red;
	enum Color secondFavorite = violet;
	enum Color colorOfFire = red;

	cout << (favoriteColor == colorOfFire) << endl; // Returns true
	cout << (favoriteColor == secondFavorite) << endl; // Returns false


	// Works since we typedefed
	YearInCollege myYear = senior;
	YearInCollege briansYear = junior;

	cout << (myYear == briansYear) << endl; // Returns false

	Student brian;
	brian.favoriteColor = violet;
	brian.currentYear = junior;

	Student steven;
	steven.favoriteColor = red;
	steven.currentYear = senior;

	cout << "Do we both like color?" << (steven.favoriteColor == brian.favoriteColor) << endl;

}