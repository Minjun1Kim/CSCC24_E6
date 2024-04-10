#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <utility> //std::pair
#include <numeric> //std::accumulate
#include <functional>

using namespace std;

vector<int> numbers = {10, 20, 30, 40, 50};


void printNumbers(int num){
	cout << num << "\n";
}



void simpleLambdaExample(vector<int> nums){

	//pass an actual defined function as the function argument 
	// for_each(nums.begin(), nums.end(), printNumbers);

	//simplify using lambda 
	for_each(nums.begin(), nums.end(), [](int x) { cout << x << " "; });

}

void pbvLambdaExample(){
	
	vector<int> someNumbers = {1, 2, 3, 4, 5, 6, 7};
	
	//"The auto keyword directs the compiler to use the 
	//initialization expression of a declared variable, 
	//or lambda expression parameter, to deduce its type"
	//-https://learn.microsoft.com/en-us/cpp/cpp/auto-cpp?view=msvc-170

	auto pbv = [someNumbers] () mutable noexcept {
		for (size_t i = 0; i < someNumbers.size(); ++i) {
			someNumbers[i] = someNumbers[i] + 1;
			cout << someNumbers[i] << " ";
    	}
	};

	//this is the same thing as assigning the lambda expression to a function object
	//this is because lambda expressions are callable objects and the function class stores
	//a callable object 

	function<void(void)> func = [someNumbers] () mutable noexcept {
		for (size_t i = 0; i < someNumbers.size(); ++i) {
			someNumbers[i] = someNumbers[i] + 1;
			cout << someNumbers[i] << " ";
    	}
	};
	
	//func; reference to the fucntion
	// func(); calling the callable object func

	//pbv; a reference to the lamda expression, can pass it around
	pbv(); //calls the calling object pbv

	cout << "\n";
	simpleLambdaExample(someNumbers);
}

void pbrLambdaExample(){
	
	vector<string> someStrings = {"a", "ab", "abc", "abcd", "abcde"};
	
	auto pbr = [&someStrings] () {
		for (size_t i = 0; i < someStrings.size(); ++i) {
			someStrings[i] = someStrings[i] + "g";
			cout << someStrings[i] << " ";
    	}
	};

	pbr(); 

	cout << "\n";

	for(string s : someStrings){
		cout << s << " ";
	}
	

}

void complexLambdaExpression(){
	//a lambda expression that returns another lambda expresion
	auto subTwoNumsFunc = [](int y) -> function<int(int)> {
		//the below expression captures the above y by value when declared
		return [y](int x) -> int{ return y - x; };
	};

	auto subOneNumFunc = subTwoNumsFunc(10);

	int result = subOneNumFunc(5);
	
	cout << result << endl;


	//lambda expression that takes in another lambda expression
	auto passFunc = [](function<int(int)> f, int a) {
		return f(a) - 1;
	};


	auto passFuncCalled = passFunc([](int x){ return x * x; }, 2);

	cout << passFuncCalled << endl;
}


void simpleFilterExample(){
    auto largeNumbersFunc = [](int x) {return x > 30; };

    auto largeNumbers = views::filter(numbers, largeNumbersFunc);

	for (int num : largeNumbers) {
    	cout << num << " ";
	}                   
	cout << endl;
}

void complexFilterExample(){
    auto largeNumbersFunc = [](int x) {return x > 10; };
	auto multOf20 = [] (int y) { return y % 20 == 0; };

    auto niceLargeNumbers = numbers | views::filter(largeNumbersFunc)
									| views::filter(multOf20);

	for (int num : niceLargeNumbers) {
    	cout << num << " ";
	}   
	cout << endl;

}

// helper function to print elements of a vector
void printVector(const vector<int>& v) {
    for (int elem : v) {
        cout << elem << " ";
    }
    cout << endl;
}

// helper function to print elements of a vector of strings
void printVector(const vector<string>& v) {
    for (const string& elem : v) {
        cout << elem << endl; //print on new line
    }
}

void transformSquares() {
	vector<int> v = {1, 2, 3, 4, 5};
    vector<int> squares(v.size());
    transform(v.begin(), v.end(), squares.begin(), [](int x) { return x * x; });
    printVector(squares);
}

void transformWithLambda(){
	vector<int> list1 = {0, 5, 10};
    vector<int> list2 = {1, 10, 20};
    vector<int> result(list1.size());

    transform(list1.begin(), list1.end(), list2.begin(), result.begin(),
        [](int x, int y) {
            return 2 * (y - x);
        });
	
	printVector(result);

}

void transformConcat() {
	vector<string> names = {"Minjun", "Syed", "Anya", "Rawad"};
    vector<string> surnames = {"Kim", "Hussain", "Tafliovich", "Assi"};
    vector<string> fullNames(names.size());

    transform(names.begin(), names.end(), surnames.begin(), fullNames.begin(),
        [](const string& name, const string& surname) {
            return name + " " + surname;
        });

    printVector(fullNames);
}

void transformPairs() {
	vector<char> chars = {'a', 'b', 'c'};
    vector<pair<char, char>> pairs = {{'a', 'a'}, {'b', 'b'}, {'c', 'c'}};
    vector<pair<char, pair<char, char>>> result;

    transform(chars.begin(), chars.end(), pairs.begin(), back_inserter(result),
        [](char c, const pair<char, char>& p) {
            return make_pair(c, p);
        });

    for (const auto& elem : result) {
        cout << "(" << elem.first << ", (" << elem.second.first << ", " << elem.second.second << ")) ";
    }
    cout << endl;

}

void sumIntegers() {
    vector<int> nums = {1, 2, 3, 4, 5};
    int sum = accumulate(nums.begin(), nums.end(), 0);
    cout << "Sum: " << sum << endl; // Outputs: Sum: 15
}

void concatenateStrings() {
    vector<string> words = {"Hello", ", ", "world", "!"};
    string sentence = accumulate(words.begin(), words.end(), string(""));
    cout << sentence << endl; // Outputs: Hello, world!
	// (((( "" + "Hello") + ", ") + "world") + "!")
}

void productOfIntegers() {
    vector<int> nums = {1, 2, 3, 4, 5};
    int product = accumulate(nums.begin(), nums.end(), 1,
                                   [](int a, int b) { return a * b; });
    cout << "Product: " << product << endl; // Outputs: Product: 120
}

void concatenateStringsFoldR() {
    vector<string> words = {"Hello", ", ", "world", "!"};
    
    // Reverse the operation by using rbegin (reverse iterator points to last element) and rend (before first) for fold-right behavior
    string sentence = accumulate(words.rbegin(), words.rend(), string(""),
                                           plus<std::string>());

    cout << sentence << endl; // Outputs: "!world ,Hello"
	//(((( "" + "!") + "world") + ", ") + "Hello")
}


int main() {

	//=======Map Procedure examples=======//
	// transformSquares();
	// transformConcat();
	// transformPairs();
	// transformWithLambda();
	sumIntegers();
	concatenateStrings();
	productOfIntegers();
	concatenateStringsFoldR();


	//=======Lambda expression examples=======//

	//simple example using STL algorithm
	// simpleLambdaExample(numbers);

	//pass by value example
	// pbvLambdaExample();
	
	//pass by reference example
	// pbrLambdaExample();

	//HOF in C++ using lambda expressions and functions
	// complexLambdaExpression();


	//=======Filter examples=======//	
	//Will be going over filter examples using ranges and views
	// simpleFilterExample();

	// complexFilterExample();

	return 0;
}
