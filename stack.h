class Stack { 
	public:
		Stack();
		//lege functie, we gebruiken de constructor
		void create(){};
		//bepaalt of de stapel leeg is
		bool isEmpty();
		//maakt de stapel leeg
		void clear();
		//voegt eennewItemtoe op de top van de stapel en
		//geeft terug of de opdracht gelukt is
		bool push(char newItem);
		//verwijdert het bovenste element van de stapel en 
		//geeft terug of de opdracht gelukt is
		bool pop();
		//geef het bovenste stapelelement
		//en geeft terug of de opdracht gelukt is
		bool top(char topItem);
	private:
		char arr[1000];
		char topElement;
};//Stack

Stack::Stack(){
	topElement = -1;
}//constructor

bool Stack::isEmpty(){
	return (topElement == -1);
}//isEmpty 
	
void Stack::clear(){
	topElement = -1;
}//clear
		
bool Stack::push(char newItem){
	topElement++;
	arr[topElement] = newItem;
	return true;	
}//push

bool Stack::pop(){
	if (topElement == -1)
		return false;
	topElement--;
	return true;
}//pop

char Stack::top(){
	topItem = arr[topElement];
	return topItem;
}//top




