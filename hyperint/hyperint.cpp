#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <typeinfo>
#include "hyperint.h"

using namespace std;

// Implementation of hyperint.h
// Info:
// 234 would be stored in data vector as: [4,3,2]

/***********************************************************
* PUBLIC FUNCTIONS
***********************************************************/
bool hyperint::DEBUG = false;

/**
 * Constructor
 */
hyperint::hyperint(long num){	
	data = convertNumber(num);
}

/**
 * Destructor
 */
hyperint::~hyperint(){
	delete data;
}

/**
 * Operator +=
 */
const hyperint & hyperint::operator+=(const hyperint & right){
  int carry = 0;
  vector<int>::iterator thisIt = this->data->begin();
  for(vector<int>::const_iterator rit = right.data->begin(); rit != right.data->end(); ++rit, ++thisIt){
    if(thisIt == this->data->end()){
    	for(vector<int>::const_iterator rit2 = rit; rit2 != right.data->end(); ++rit2)
          this->data->push_back(*rit2);
      break;
    }
    if(DEBUG){
    	cout << "before addDigit: value for *thisIt = " << *thisIt;
		cout << endl;
    }
  	carry = addDigit(*thisIt, *rit, carry);
  	if(DEBUG){
		cout << "after addDigit: new value for *thisIt = " << *thisIt;
		cout << endl;
  	}
  }
  //there was a carry at the end
  while(carry != 0){
	const int x = 0;
	//if at the end of iterator
	if(thisIt == this->data->end()){
		this->data->push_back(carry);
		carry = 0;
	} else {
		carry = addDigit(*thisIt, x, carry);
		++thisIt;
	}
  }
  return *this;
}

/**
 * Operator*=
 */
const hyperint & hyperint::operator*=(const hyperint & right){
	if(DEBUG)
	  cout << "Inside operator*=:" << endl << *this << "   size: " << this->data->size() << endl
		<< right << "   size: " << right.data->size() << endl;

	hyperint zero(0);
	hyperint ctr(1);
	if(right == zero){
		data->clear();
		data->push_back(0);
	} else if(*this > ctr && right > ctr){
		hyperint oldVal(0);
		oldVal += *this;
		//if current hyperint is not 0
		//and right > 1
		while(ctr != right){
			assert(right > ctr && "Right should be greater than ctr");
			*this += oldVal;
			++ctr;
		}
	}

	return *this;
}

/**
 * Operator/=
 */
const hyperint & hyperint::operator/=(const hyperint & right){
	if(DEBUG)
		cout << "Inside operator/=:" << endl << *this << "   size: " << this->data->size() << endl
			<< right << "   size: " << right.data->size() << endl;

	//right >= left
	if(*this <= right){
		data->clear();
		data->push_back(0);
	} else {
		hyperint count(0);
		while(*this > right){
			*this -= right;
			++count;
		}
		(*this).data->clear();
		*this += count;
	}

	return *this;
}

/**
 * Operator-=
 */
const hyperint & hyperint::operator-=(const hyperint & right){
	//right >= left
	if(*this <= right){
		data->clear();
		data->push_back(0);
	}

	return *this;
}

// Prefix increment
const hyperint & hyperint::operator++(){
  hyperint hi = hyperint(1);
  *this += hi;
  return *this;
}

// Postfix increment
const hyperint hyperint::operator++(int num){
  	hyperint oldHi(0);
  	oldHi += *this;
  	++(*this);
  	return oldHi;
}

// Bool cast
hyperint::operator bool() const{
	if(this->data->size() > 0)
    {
      for(vector<int>::const_iterator it = this->data->begin(); it != this->data->end(); ++it){
      	if(*it != 0)
          return true;
      }
      // All int in data = 0
    	return false;
    }
  	else
      return false;
}

/***********************************************************
* PRIVATE FUNCTIONS
***********************************************************/
/**
* Converts a long number to vector<int> data.
*/
std::vector<int> * hyperint::convertNumber(long num){
  	vector<int> *newData = new vector<int>;
  	long value = num;
  	long remainder;
  	if(DEBUG)
  		cout << "Creating hyperint for " << num << endl;
	do{
      	remainder = value % 10;
  		value = value / 10;
      	newData->push_back(remainder);
		if(DEBUG)cout << "   adding " << remainder << " to hyperint" << endl;
    }while(value != 0);
	return newData;
}

//New value goes in num, returns remainder
// Ex: num=9, toAdd=7
// Result: num=6, return value=1
int hyperint::addDigit(int & num, const int & toAdd, int carry){
	if(DEBUG)
		cout << "addDigit values: num = " << num << " , toAdd = " << toAdd << " carry = " << carry << endl;
	num = num + toAdd + carry;
  	int newcarry = num / 10;
  	num = num % 10;
  	assert(newcarry < 10 && "newcarry isn't less than 10");
	if(DEBUG)
		cout << "new values: num = " << num << " , carry = " << newcarry << endl;
  	return newcarry;
}

/***********************************************************
* FREE FRIEND FUNCTIONS
***********************************************************/

const bool operator==(const hyperint & left, const hyperint & right){
	if(left.data->size() != right.data->size())
      return false;
  	else{
      vector<int>::const_iterator rit = right.data->begin();
      
      for(vector<int>::const_iterator lit = left.data->begin(); lit != left.data->end(); ++lit, ++rit){
      	if(*lit != *rit)
          return false;
      }
      // If it gets here they are equal.
      return true;
    }
}

const bool operator!=(const hyperint & left, const hyperint & right){
	return(!(left==right));
}

const bool operator>=(const hyperint & left, const hyperint & right){
	return((left>right)||(left==right));
}

const bool operator<=(const hyperint & left, const hyperint & right){
	return((left<right)||(left==right));
}

const bool operator>(const hyperint & left, const hyperint & right){
	if(left.data->size() > right.data->size())
      return true;
  	else if(right.data->size() > left.data->size())
      return false;
    else{ // They have the same size of data
      	vector<int>::const_reverse_iterator rit = right.data->rbegin();
      for(vector<int>::const_reverse_iterator lit = left.data->rbegin(); lit != left.data->rend(); ++lit, ++rit){
      	if(*lit < *rit)
          return false;
        else if(*lit > *rit)
          return true;
      }
      // They are equal
      return false;
    }
}

const bool operator<(const hyperint & left, const hyperint & right){
	if(left.data->size() > right.data->size())
      return false;
  	else if(right.data->size() > left.data->size())
      return true;
    else{ // They have the same size of data
      	vector<int>::const_reverse_iterator rit = right.data->rbegin();
		for(vector<int>::const_reverse_iterator lit = left.data->rbegin(); lit != left.data->rend(); ++lit, ++rit){
			for(vector<int>::const_reverse_iterator lit = left.data->rbegin(); lit != left.data->rend(); ++lit, ++rit){
				if(*lit < *rit)
					return true;
				else if(*lit > *rit)
					return false;
			}
		}
	// They are equal
	return false;
	}
}
  		
std::istream & operator>>(std::istream & is, const hyperint & hyp){
	return is;
}

std::ostream & operator<<(std::ostream & os, const hyperint & hyp){
	for(vector<int>::const_reverse_iterator it = hyp.data->rbegin(); it != hyp.data->rend(); ++it)
		os << *it;
	return os;
}

/***********************************************************
* FREE FUNCTIONS
***********************************************************/

/**
* The addition operator with 2 hyperints
*/
const hyperint operator+(const hyperint & left, const hyperint & right){
	hyperint result = left;
	result += right;
	return result;
}

/**
* The substraction operator with 2 hyperints
*/
const hyperint operator-(const hyperint & left, const hyperint & right){
	hyperint result = left;
	result -= right;
	return result;
}

/**
* The multiplication operator with 2 hyperints
*/
const hyperint operator*(const hyperint & left, const hyperint & right){
	hyperint result = left;
	result *= right;
	return result;
}

/**
* The division operator with 2 hyperints
*/
const hyperint operator/(const hyperint & left, const hyperint & right){
	hyperint result = left;
	result /= right;
	return result;
}


/**
 * Operator^
 */
const hyperint operator^(const hyperint & left, const hyperint & right){
	if(hyperint::DEBUG)
	  cout << "Inside operator^=:" << endl << left << "   size: " << left.data->size() << endl
		<< right << "   size: " << right.data->size() << endl;

	hyperint zero(0);
	hyperint ctr(1);
	hyperint result(0);

	if((right == zero && left != zero) || left == ctr){
		// x^0
		++result;
	} else if((right > ctr) && (left > ctr)){
		result += left;

		//x^y y > 1, x > 1
		while(ctr != right){
			assert(right > ctr && "Right should be greater than ctr");
			result *= left;
			++ctr;
		}
	}

	return result;
}

