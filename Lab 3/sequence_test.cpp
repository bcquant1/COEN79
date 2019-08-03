#include <iostream>
#include "sequence1.h"

// Main Function Stuff

using namespace std;
using coen79_lab3::sequence;

void printSequence(sequence &s) {
	sequence seq = s;
	seq.start();

	// Loop to print the sequence.
	while(seq.is_item()) {
		cout << seq.current() << " ";
		seq.advance();
	}
	cout << endl;

	seq.end();
}

int main(int argc, const char * argv[])
{
	sequence seq1, seq2;

	// Testing attach
	seq1.attach(42);
	seq1.attach(25);
	seq1.attach(2);
	printSequence(seq1);
	// Testing insert
	seq1.insert(9);
	seq1.insert(17);
	seq1.attach(13);
	printSequence(seq1);

	// Test remove from end.
	cout << "End Removal Test" << endl;
	seq1.end();
	if (seq1.is_item()) seq1.remove_current();
	printSequence(seq1);
	// Test remove from front.
	cout << "Start Removal Test" << endl;
	seq1.start();
	if (seq1.is_item()) seq1.remove_current();
	printSequence(seq1);
	// Test remove from middle
	cout << "Start Removal Test" << endl;
	seq1.start();
	seq1.advance();
	seq1.remove_current();
	printSequence(seq1);

	cout << "Assignment Test" << endl;
	seq2 = seq1;
	seq1.attach(5);
	printSequence(seq1);
	printSequence(seq2);
	seq2.insert(18);
	seq2.attach(92);
	printSequence(seq2);

	cout << "Addition operator tests." << endl;
	sequence seq3;
	cout << (seq1 + seq2).current() << endl;
	cout << (seq1 + seq2)[0] << endl;
	seq3 += seq1;
	printSequence(seq3);
	seq3 += seq2;
	printSequence(seq1);
	printSequence(seq2);
	printSequence(seq3);

	cout << "Index operator tests." << endl;
	for (int i = 0; i < seq3.size(); i++) {
		cout << seq3[i];
		if (i < seq3.size()-1)
			cout << ", ";
	}
	cout << endl;

	// Example from lab. Can't do perfectly because printing moves the index.
	cout << "Lab Example" << endl;
	sequence labSequence;
	cout << "Size: " << labSequence.size() << endl;
	cout << "Is_Item: " << labSequence.is_item() << endl;
	labSequence.insert(12);
	printSequence(labSequence);
	labSequence.insert(17);
	printSequence(labSequence);
	labSequence.advance();
	cout << "Is_Item: " << labSequence.is_item() << endl;
	labSequence.insert(7);
	printSequence(labSequence);
	labSequence.attach(4);
	printSequence(labSequence);
	labSequence.advance();
	labSequence.advance();
	cout << "Size: " << labSequence.size() << endl;
	cout << "Is_Item: " << labSequence.is_item() << endl;
	labSequence.insert(3);
	printSequence(labSequence);
	labSequence.advance();
	labSequence.remove_current();
	printSequence(labSequence);
	labSequence.advance();
	labSequence.remove_current();
	printSequence(labSequence);
	labSequence.advance();
	labSequence.attach(11);
	printSequence(labSequence);
	labSequence.start();
	cout << "Start: " << labSequence.current() << endl;
	labSequence.end();
	cout << "End: " << labSequence.current() << endl;

}
