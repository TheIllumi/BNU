#include <iostream>
using namespace std;

// - - - H I S T O R Y   M A N A G E M E N T   S Y S T E M - - - //

struct Node {
	Node* next;
	Node* prev;
	string url;

	Node(string url) {
		this->url = url;
		prev = next = this;
	}
};

class HistorySite {
public:
	Node* current;

	// C O N S T R U C T O R
	HistorySite() : current(nullptr) {}

	// I N S E R T  A  N E W  N O D E
	void visit(string site) {
		Node* newNode = new Node(site);

		if (current == NULL) {
			current = newNode;
		}
		else {
			newNode->next = current->next;
			newNode->prev = current;
			current->next = newNode;
			current->next->prev = newNode;
			current = newNode;

			/*Node* nextNode = current->next;
			newNode->prev = current;
			newNode->next = nextNode;
			if (nextNode != nullptr) {
			nextNode->prev = newNode;
			}
			current->next = newNode;
			current = newNode;*/
		}
	};

	// M O V E  F O R W A R D
	void goForward() {
		if (current != NULL && current->next != NULL) {
			current = current->next;
		}
	};

	// M O V E  B A C K W A R D
	void goBack() {
		if (current != NULL && current->prev != NULL) {
			current = current->prev;
		}
	};

	// D I S P L A Y
	void display() {
		if (current == NULL) return;
		Node* temp = current;
		do {
			cout << temp->url << endl;
			temp = temp->next;
		} while (temp != current);
	};
};

int main() {
	HistorySite browser;

	// 1. V I S I T  5  W E B S I T E S

	browser.visit("google.com");
	browser.visit("stackoverflow.com");
	browser.visit("github.com");
	browser.visit("reddit.com");
	browser.visit("medium.com");

	cout << "Browsing history: (the most recently visited):" << endl;
	browser.display();
	cout << endl << endl;

	// 2. G O  B A C K  T W I C E
	browser.goBack();
	browser.goBack();
	cout << "After going back twice:" << endl;
	cout << "Current website: " << browser.current->url << endl;
	cout << endl << endl;

	// 3. V I S I T  A  N E W  W E B S I T E
	browser.visit("news.com");
	cout << "After visiting news:" << endl;
	cout << "Current website: " << browser.current->url << endl;
	cout << endl << endl;
	// 4. G O  F O R W A R D  O N C E  ( S H O U L D  N O T  M O V E  F O R W A R D  B E C A U S E  F O R W A R D  H I S T O R Y  I S  C L E A R E D )
	browser.goForward();
	cout << "After going forward once:" << endl;
	cout << "Current website: " << (browser.current ? browser.current->url : "None") << endl;
	cout << endl << endl;
	// 5. D I S P L A Y  C U R R E N T  B R O W S I N G  H I S T O R Y
	cout << "Browsing history: (the most recently visited):" << endl;
	browser.display();

	return 0;
}