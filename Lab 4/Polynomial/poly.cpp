//
//  poly.cpp
//  lab4
//
//  Created by Braandon Quant on 1/31/19.
//  Copyright Â© 2019 SCU. All rights reserved.
//

#include "poly.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4{
    void polynomial::update_current_degree(){ // Update the degree to the highest exponent
        for ( int i=MAXIMUM_DEGREE; i>0; i--)
            if (data[i] != 0){
                current_degree=i;
                break;
            }
    }
    polynomial::polynomial(double c, unsigned int exponent){ // Constructor
        assert(exponent <= MAXIMUM_DEGREE);
        for (int i = 0; i < CAPACITY; i++){ // Initialize all data values to 0.
            data[i] = 0;
        }
        data[exponent] = c; // Add the input values to the appropriate index.
        current_degree=exponent; // Update current_degree.
    }
    void polynomial::assign_coef(double coefficient, unsigned int exponent){ // Insert a new value in the array.
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] = coefficient;
        update_current_degree(); // Update current_degree if needed.
    }
    void polynomial::add_to_coef(double amount, unsigned int exponent){ // Change the coefficient at 'exponent' by 'amount".
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] += amount;
        update_current_degree();
    }
    void polynomial::clear(){ // Set all values in the array and current_degree to 0.
        for(size_t i = 0; i <= current_degree; i++){
            data[i] = 0.0;
        }
        
        current_degree = 0;
    }
    polynomial polynomial::antiderivative()const{
        assert(degree()<MAXIMUM_DEGREE);
        polynomial a; // Create temporary polynomial object.
        for (int i= 1; i <= degree() + 1; i++){
            a.assign_coef(coefficient(i-1)/i, i); // Calculate the antiderivative and assign to temporary object.
        }
        
        return a;
        
    }
    
    double polynomial::coefficient(unsigned int exponent) const{ // Return the value of the coefficient at the given exponent.
        if (exponent > MAXIMUM_DEGREE){
            return 0;
        }
        else{
            return data[exponent];
        }
    }
    
    double polynomial::definite_integral (double x0, double x1) const{
        polynomial b = antiderivative(); // Calculate the antiderivative and assign it to a temp variable.
        double sum1 = b.eval(x1); // Evaluate the antiderivative at the given values.
        double sum2 = b.eval(x0);
        return sum1 - sum2; //Return the difference.
    }
    
    unsigned int polynomial::degree()const{ // Return the current degree of the polynomial.
        return current_degree;
    }
    polynomial polynomial::derivative()const{ // Calculate the derivative of the polynomial.
        polynomial a; // temp variable
        for (int i= 0; i < degree(); i++){
            a.assign_coef(coefficient(i+1)*(i+1), i); // Assign new coefficients to the temp data.
        }
        
        return a;
    }
    
    double polynomial::eval(double x) const{ // Evaluate the polynomial at x.
        int deg = degree();
        double sum1 = 0.0;
        for (int i = 0; i < deg+1 ;i++){
            sum1 += data[i]*pow(x,i);
        }
        return sum1;
    }
    
    bool polynomial::is_zero() const{ // Check if the polynomial is zero.
        for (int i = 0; i < MAXIMUM_DEGREE; i++){
            if (data[i] != 0){
                return false;
            }
        }
        return true;
    }
    unsigned int polynomial::next_term(unsigned int e) const{ // Report the next term of the function after exponent e.
        for (int i = e+1; i <= current_degree; i++){
            if (data[i] != 0){
                return i;
            }
        }
        return 0;
    }
    
    unsigned int polynomial::previous_term(unsigned int e) const{ // Report the previous term of the function before exponent e.
        for (int i = e-1; i >= 0; i--){
            if(data[i] != 0){
                return i;
            }
        }
        return UINT_MAX;
    }
    
    double polynomial::operator () (double x) const{ // Overload the () operator.
        return eval(x);
    }
    
    polynomial operator +(const polynomial& p1, const polynomial&p2){ // Overload the + operator.
        polynomial temp; // temporary variable
        int tempdeg;
        if (p1.degree()>=p2.degree()) // Set the loop condition to the highest degree needed to look through.
            tempdeg = p1.degree();
        else
            tempdeg = p2.degree();
        for (int i = 0; i<=tempdeg; i++) // Add the functions together.
            temp.add_to_coef(p1.coefficient(i) + p2.coefficient(i),i);
        return temp;
    }
    
    polynomial operator -(const polynomial& p1, const polynomial&p2){ // Overload the - operator.
        polynomial temp;
        int tempdeg;
        if (p1.degree()>=p2.degree()) // Set the loop condition to the highest degree needed to look through.
            tempdeg = p1.degree();
        else
            tempdeg = p2.degree();
        for (int i = 0; i<=tempdeg; i++) // Subtract the functions from each other.
            temp.assign_coef(p1.coefficient(i) - p2.coefficient(i),i);
        return temp;
    }
    
    polynomial operator *(const polynomial& p1, const polynomial&p2){ // Overloading the * operator.
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
        int i,j;
        int deg1 = p1.degree(), deg2 = p2.degree();
        polynomial result(0.0,0.0); // Create a temp variable w/ all values initialized to 0.
        for (i=0;i<deg1+1;i++)
            for(j=0;j<deg2+1;j++)
                result.add_to_coef(p1.coefficient(i)*p2.coefficient(j),i+j); // Add the product of the coefficients to the sum of the exponents.
        return result;
    }
    ostream& operator << (ostream& out, const polynomial&p){ // Overloading the << operator.
        int deg = p.degree();
        if (deg == 0 && p.coefficient(0)==0) //If it is empty, report "0.0".
            out<< "0.0";
        else if (deg==0 && p.coefficient(0)!=0) //If it is not empty, report the constant.
            out<< p.coefficient(0);
        else{
            out << p.coefficient(deg) << "x^" << deg; // Report the highest degree term.
            for (int i = p.degree()-1; i>=0; i--){ // Reporting the other terms.
                if (p.coefficient(i)!=0){
                    if (p.coefficient(i)<0) // If the term is negative.
                        out<< " - ";
                    else if (p.coefficient(i)>0) // If the term is positive.
                        out<< " + ";
                    out << abs(p.coefficient(i)); // Report the absolute value of the coefficient.
                    if (i>1)
                        out << "x^" << i; // If the exponent is >1, write the exponent.
                    else if (i==1)         // Otherwise don't write the exponent.
                        out << "x";
                }
            }
        }
        return out;
    }
}
