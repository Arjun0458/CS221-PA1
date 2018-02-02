#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "grill.h"
#include "linkedlist.h"
#include "kebab.h"

Grill::Grill () {}


bool Grill::swap(unsigned int pos1, unsigned int pos2) {

	unsigned int lower_pos;
	unsigned int higher_pos;

	if( pos1 > pos2 ) {
		higher_pos = pos1;
		lower_pos = pos2;
	} else {
		higher_pos = pos2;
		lower_pos = pos1;
	}

	// remove the kebabs from higher_pos and lower_pos. Note: pos1 and
	// pos2 are 1 based index, so a subtraction by 1 is required
	Kebab *higher_pos_kebab = rack.removeAt(higher_pos - 1);
	Kebab *lower_pos_kebab = rack.removeAt(lower_pos - 1);

	// if either of the removals failed, return false
	if( (higher_pos_kebab == NULL) || (lower_pos_kebab == NULL) ) {
		return false;
	}

	// insert the two kebabs in the other position to complete
	// the swap
	bool swap1 = rack.insertAt(higher_pos_kebab, lower_pos - 1); 
	bool swap2 = rack.insertAt(lower_pos_kebab, higher_pos - 1);

	// if the insertions failed, return false, else return true
	if( (swap1 == false) || (swap2 == false) ) {
		return false;
	} else {
		return true;
	}
}

Kebab* Grill::request(unsigned int pos) {
	// return a pointer to the kebab at pos if the removal was
	// successful or return NULL if it wasn't. Need to use 
	// pos - 1 because pos is 1 based
	return rack.removeAt(pos - 1);
}

Kebab* Grill::request(Kebab& r) {
	// iterate through the rack and check each kebab to see if it 
	// matches the ingredients of r. If theres a match remove and
	// return the kebab at that position. Since the loop starts at
	// 0 and goes to max position, the leftmost matching kebab will
	// be chosen
	for( unsigned int i = 0; i < rack.size(); i++ ) {
		if( r.hasSameIngredients( *rack.elementAt(i) ) )
			return rack.removeAt(i);
	}
	// if no matches were found, return NULL
	return NULL;
}

void Grill::addKebab(Kebab& n) {
	// add the kebab to the back (rightmost) of the rack
	rack.insertBack(&n);
}

void Grill::sortByMeat(){
	// this is an insertion sort algorithm. I have adapted the example found at:
	// http://www.geeksforgeeks.org/insertion-sort/ 

	int j;
	Kebab *key;

	for( int i = 1; i < (int) rack.size(); i++ ) {
		key = rack.elementAt( (unsigned int) i );
		j = i - 1;

		// move kebabs in rack of positions 0 to i-1 that have more meat than key
		// one position ahead of where they currently are
		while( (j >= 0) && (rack.elementAt( (unsigned int) j )->numMeats() < key->numMeats() ) ) {
			
			// put kebab at j into j+1
			rack.removeAt( (unsigned int)(j+1) );
			rack.insertAt( rack.elementAt( (unsigned int)j ), (unsigned int)(j+1) );
			j--;
		}
		// put key kebab into the rack at position j+1
		rack.removeAt( (unsigned int)(j+1) );
		rack.insertAt( key, (unsigned int)(j+1) );
	}
	
}

 std::vector<std::string> Grill::showKebabs() const {

	 // create the string vector
	 std::vector<std::string> kebabsOnGrill;

	 // iterate through the rack and put each kebab into the vector in
	 // its string form representing its ingredients
	 for( unsigned int i = 0; i < rack.size(); i++ ) {
		 kebabsOnGrill.push_back( rack.elementAt(i)->listIngredients() );
	 }
	 return kebabsOnGrill;
 }


		
		



