#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <climits>
#include "poly.h"

//INVARIANT FOR POLYNOMIAL
// 1. current_degree is equal to the degree of the largest degree with a non-zero coeffecient.
// 2. coef_size is equal to the allocated size of coef.
// 3. coef stores the coeffecient of a certain degree at coef[degree].

using namespace std;

namespace coen70_lab6
{
    // HELPER FUNCTIONS
    void polynomial::update_current_degree() {
        current_degree = 0;

        for (int i = coef_size - 1; i > 0; i--) {
            if (coef[i] != 0.0)
            {
                current_degree = i;
                break;
            }
        }
    }
    
    void polynomial::reallocateForExponent(unsigned int exponent) {
        //incremented because array size has to be one larger than exponent
        ++exponent;
        
        //Return if smaller than current array
        if(exponent < coef_size)
            return;
        
        //Create new array and copy data
        double *newcoef;
        newcoef = new double[exponent];
        for(int i = 0; i < coef_size; i++) {
            newcoef[i] = coef[i];
        }
        
        //Fill new space with zeroes
        for(int i = coef_size; i < exponent; i++) {
            newcoef[i] = 0.0;
        }
        
        //Delete original array if allocated
        if(coef_size != 0)
            delete[] coef;
        
        //Set pointer to new array
        coef = newcoef;
        
        //update coef_size
        coef_size = exponent;
    }

    // CONSTRUCTOR
	polynomial::polynomial(double c, unsigned int exponent){
        coef_size = 0;
        
        reallocateForExponent(exponent);
        
        for (size_t i = 0; i < coef_size; i++) {
            if (i == exponent)
                coef[i] = c;
            else
                coef[i] = 0.0;
        }
        current_degree = exponent;
    }
    
    polynomial::~polynomial() {
        //delete all data in the heap
        delete[] coef;
        
    }
    
    polynomial::polynomial(const polynomial& other) {
        //Allocate memory
        reallocateForExponent(other.coef_size - 1);
        
        //Set variables equal
        current_degree = other.current_degree;
        
        //Copy data
        for(int i = 0; i <= current_degree; i++) {
            coef[i] = other.coef[i];
        }
    }

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        if(exponent >= coef_size)
            reallocateForExponent(exponent);
        coef[exponent] = coefficient;
        update_current_degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent){
        // Access, add, and assign.
        assign_coef(coefficient(exponent) + amount, exponent);
    }

	void polynomial::clear( ) {
        // Zero out all the coeficients.
        for (size_t i = 0; i <= current_degree; i++) {
            coef[i] = 0.0;
        }

        current_degree = 0;
    }
    
    polynomial& polynomial::operator=(const polynomial& other) {
        reallocateForExponent(other.coef_size - 1);
        
        current_degree = other.current_degree;
        
        for(int i = 0; i <= current_degree; i++) {
            coef[i] = other.coef[i];
        }
        
        return *this;
    }

	// // CONSTANT MEMBER FUNCTIONS
    polynomial polynomial::antiderivative( ) const {
        polynomial p;
        // Calculate anti-derivative.
        for (size_t i = 1; i <= this->degree()+1; i++) {
            p.assign_coef( this->coefficient(i-1) / i , i);
        }

        return p;
    }

	double polynomial::coefficient(unsigned int exponent) const {
        // Always return 0.0 if exponent is greater than maximum degree.
        if (exponent > current_degree)
            return 0.0;

        return coef[exponent];
    }

    double polynomial::definite_integral(double x0, double x1) const {
        polynomial anti = this->antiderivative();

        return anti.eval(x1) - anti.eval(x0);
    }

	polynomial polynomial::derivative( ) const {
        polynomial p;

        // Calculate derivative.
        for (size_t i = 0; i < this->degree(); i++) {
            p.assign_coef( this->coefficient(i+1) * (i+1) , i);
        }

        return p;
    }

	double polynomial::eval(double x) const {
        double sum = 0;
        // Evaluation loop.
        for (size_t i = 0; i <= current_degree; i++) {
            double cur_coef = coefficient(i);
            if (cur_coef != 0) {
                sum += cur_coef * pow(x, i);
            }
        }

        return sum;
    }

    bool polynomial::is_zero( ) const {
        if (current_degree == 0 && coef[0] == 0.0)
            return true;
        else
            return false;
    }

	unsigned int polynomial::next_term(unsigned int e) const {
        // Search for next term.
        for (size_t i = e+1; i <= current_degree; i++) {
            if (coef[i] != 0)
                return i;
        }
        return 0;
    }

    // Search for previous term.
	unsigned int polynomial::previous_term(unsigned int e) const {
        for (int i = e-1; i >= 0; i--) {
            if (coef[i] != 0)
                return i;
        }
        return UINT_MAX;
    }

    // // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2)
    {
        polynomial p3 = p1;
        for (size_t i = 0; i <= p2.degree(); i++) {
            p3.add_to_coef(p2.coefficient(i), i);
        }

        return p3;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial p3 = p1;
        for (size_t i = 0; i <= p2.degree(); i++) {
            p3.add_to_coef(-p2.coefficient(i), i);
        }

        return p3;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        polynomial p3;

        for (size_t i = 0; i <= p1.degree(); i++) {
            for (size_t j = 0; j <= p2.degree(); j++) {
                p3.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i+j);
            }
        }

        return p3;
    }

    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p)
    {
        // Save output settings.
        long savedFlags = out.ios::flags();
        int pres = out.precision();
        out << std::fixed;
        out << std::setprecision(1);

        if (p.is_zero())
            out << 0.00;
        else
        {
            bool firstPrint = true;
            //  Loop through array.
            for (int i = p.degree(); i >= 0; i--) {
                double theCoef = p.coefficient(i);
                if (theCoef != 0) {
                    // Don't print a plus for first coefficient.
                    if (!firstPrint) {
                        out << ((theCoef < 0) ? " - " : " + ");
                    }

                    out << ((firstPrint) ? theCoef : abs(theCoef));
                    // No need to print x^0
                    if (i > 0)
                    {
                        out << "x";
                        // No need to print ^1
                        if (i > 1)
                            out << "^" << i;
                    }

                    if (firstPrint)
                        firstPrint = false;
                }
            }
        }

        // Restore output settings.
        out << setprecision(pres);
        out.flags(savedFlags);
        return out;
    }
}
