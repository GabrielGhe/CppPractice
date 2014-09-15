#ifndef HYPERINT_H
#define HYPERINT_H

#include <string>
#include <vector>
#include <iostream>

class hyperint{
	public:
		static bool DEBUG;
		hyperint(long num);
		const hyperint & operator+=(const hyperint & right);
		const hyperint & operator *=(const hyperint & right);
		const hyperint & operator /=(const hyperint & right);
		const hyperint & operator -=(const hyperint & right);
 		const hyperint & operator++(); // Prefix increment
  		const hyperint operator++(int num); // Postfix increment

        // Operators
  		friend const bool operator==(const hyperint & left, const hyperint & right);
  		friend const bool operator!=(const hyperint & left, const hyperint & right);
  		friend const bool operator>=(const hyperint & left, const hyperint & right);
  		friend const bool operator<=(const hyperint & left, const hyperint & right);
  		friend const bool operator>(const hyperint & left, const hyperint & right);
  		friend const bool operator<(const hyperint & left, const hyperint & right);
  		friend const hyperint operator^(const hyperint & left, const hyperint & right);
  		
  		// Friend
  		friend std::istream & operator>>(std::istream & is, const hyperint & hyp);
   		friend std::ostream & operator<<(std::ostream & os, const hyperint & hyp);
  	
  		// Conversions
  		operator bool() const;
		~hyperint();
  	private:
  		std::vector<int> *data;
		std::vector<int> * convertNumber(long num);
		int addDigit(int & num, const int & toAdd, int carry);
};

// Free function declarations

const hyperint operator+(const hyperint & left, const hyperint & right);
const hyperint operator-(const hyperint & left, const hyperint & right);
const hyperint operator*(const hyperint & left, const hyperint & right);
const hyperint operator/(const hyperint & left, const hyperint & right);


#endif
