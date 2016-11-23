/*
 * poly.cpp
 * Written by: Stephen Pacwa and Maggie Cai
 * 10/11/2016
 * Implementation file for the Polynomial class
 * See header file for information
 */

/*
 * Invariant for the poly class:
 * 1. The highest degree in the polynomial is stored in current_degree.
 * 2. When there is at least one coefficient, data is stored between coef[0] and coef[current_degree];
 * 3. A coefficient is stored according to its degree.
 */
#include "poly.h"
#include <cassert>
#include <cmath>
#include <climits>
#include <iostream>
#include <iomanip>

namespace coen70_lab4
{
    polynomial::polynomial(double c, unsigned int exponent)
    {
        assert(exponent <= MAXIMUM_DEGREE);                     //Constructor for polynomial class
        for(int i = 0; i < MAXIMUM_DEGREE + 1 ; i++)
        {
            if(exponent == i)
            {
                coef[i] = c;
            }
            else
            {
                coef[i] = 0;
            }
        }
    }
    
    void polynomial::update_current_degree()
    {
        for(int i = 0; i < MAXIMUM_DEGREE + 1 ; i++)
        {
            if(coef[i] != 0)
            {
                current_degree = i;                             //Sets highest degree through for loop
            }
        }
    }
    
    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
        assert(exponent <= MAXIMUM_DEGREE);
        
        coef[exponent] = coefficient;
        update_current_degree();
    }
    
    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
        assert(exponent <= MAXIMUM_DEGREE);
        
        coef[exponent] += amount;
        update_current_degree();
    }
    
    void polynomial::clear()
    {
        for(int i = 0; i < current_degree + 1; i++)
        {
            coef[i] = 0;                                    //Sets all degrees to zero
        }
        current_degree = 0;
    }
    
    polynomial polynomial::antiderivative() const
    {
        assert(degree() < MAXIMUM_DEGREE);
        
        polynomial p1;
        
        for(int i = current_degree + 1 ; i > 0 ; --i)
        {
            p1.coef[i] = coef[i - 1] / i;                   //Antiderivative formula for polynomials
        }
        
        p1.coef[0] = 0;
        p1.update_current_degree();                         //Keeps degree updated
        
        return p1;
    }
    
    double polynomial::coefficient(unsigned int exponent) const
    {
        return coef[exponent];
    }
    
    double polynomial::definite_integral(double x0, double x1) const
    {
        polynomial p = antiderivative();
        
        double left, right;
        
        for(int i = 1; i < p.current_degree + 1; i++)
        {
            left += p.coef[i] * pow(x0, i);                 //Calculates integral
            right += p.coef[i] * pow(x1, i);
        }
        
        return left - right;                                //Subtracts and returns
    }
    
    polynomial polynomial::derivative() const
    {
        polynomial p;
        
        for(int i = 0; i < current_degree; i++)
        {
            p.coef[i] = coef[i + 1] * (i + 1);              //Calculates derivative with polynomial formula
        }
        p.update_current_degree();                          //Updates current degree
        
        return p;
    }
    
    double polynomial::eval(double x) const
    {
        double val;
        
        for(int i = 0; i < current_degree + 1; i++)
        {
            val += coef[i] * pow(x, i);                     //Inserts x into polynomial and adds
        }
        
        return val;
    }
    
    bool polynomial::is_zero() const
    {
        return (current_degree == 0 && coef[0] == 0);
    }
    
    unsigned int polynomial::next_term(unsigned int e) const
    {
        if(e == current_degree)
        {
            return 0;
        }
        else
        {
            for(int i = e + 1; i < current_degree + 1; i++) //Looks for next term that has coefficient
            {
                if(coef[i] != 0)
                {
                    return i;
                }
            }
        }
    }
    
    unsigned int polynomial::previous_term(unsigned int e) const
    {
        for(int i = e - 1; i >= 0; i--)
        {
            if(coef[i] != 0)
            {
                return i;                                   //Looks for previous term
            }
        }
        
        return UINT_MAX;
    }
    
    polynomial operator +(const polynomial& p1, const polynomial& p2)
    {
        polynomial p3;
        
        for(int i = 0; i < polynomial::MAXIMUM_DEGREE + 1; i++)
        {
            p3.add_to_coef(p1.coefficient(i) + p2.coefficient(i), i);
        }
        
        return p3;
    }
    
    polynomial operator -(const polynomial& p1, const polynomial& p2)
    {
        polynomial p3;
        
        for(int i = 0; i < polynomial::MAXIMUM_DEGREE + 1; i++)
        {
            p3.add_to_coef(p1.coefficient(i) - p2.coefficient(i), i);
        }
        
        return p3;
    }
    
    polynomial operator *(const polynomial& p1, const polynomial& p2)
    {
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
        
        polynomial p3;
        
        for(int i = 0; i < p1.degree() + 1; i++)
        {
            for(int j = 0; j < p2.degree() + 1; j++)
            {
                p3.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
            }
        }
        
        return p3;
    }
    
    std::ostream& operator << (std::ostream& out, const polynomial& p)
    {
    	int coef = p.degree();
        double intpart;

    	if(coef > 1)                                            //Checks if the polynomial has more than one term
    	{ 
            if(modf(p.coefficient(coef), &intpart) == 0.0)
            {
                out << std::defaultfloat << p.coefficient(coef) << "x^" << coef;
            }
            else
            {
                out << std::fixed << std::setprecision(1) << p.coefficient(coef) << "x^" << coef;
            }
    	    coef = p.previous_term(coef);
    	    while (coef > 1)
    	    {
        		if(p.coefficient(coef) >= 0)
                {
        		    out << " + ";
                }
        		else
                {
        		    out << " - ";
                }
                if(modf(p.coefficient(coef), &intpart) == 0.0)
                {
                    out << std::defaultfloat << std::abs(p.coefficient(coef)) << "x^" << coef;
                }
                else
                {
                    out << std::fixed << std::setprecision(1) << std::abs(p.coefficient(coef)) << "x^" << coef;
                }
            		coef = p.previous_term(coef);
        	}
    	}
    	if(coef == 1)                                           //Runs if there is only one term left
    	{
    	    if(p.coefficient(coef) >= 0 && p.degree() != 1)
            {
                out << " + ";
            }
    	    else if (p.degree() != 1) 
            {
        		out << " - ";
            }

            if(modf(p.coefficient(coef), &intpart) == 0.0)
            {
                out << std::defaultfloat << std::abs(p.coefficient(coef)) << "x";
            }
            else
            {
                out << std::fixed << std::setprecision(1) << std::abs(p.coefficient(coef)) << "x";
            }

    	    if(p.coefficient(--coef) >= 0)
            {
                out << " + ";
            }
    	    else
            {
        		out << " - ";
            }

            if(modf(p.coefficient(coef), &intpart) == 0.0)
            {
                out << std::defaultfloat << std::abs(p.coefficient(coef));
            }
            else
            {
                out << std::fixed << std::setprecision(1) << std::abs(p.coefficient(coef));
            }
    	}
    	else                                                    //Runs for final coefficient
        {
            if(modf(p.coefficient(coef), &intpart) == 0.0)
            {
                out << std::defaultfloat << p.coefficient(coef);
            }
            else
            {
                out << std::fixed << std::setprecision(1) << p.coefficient(coef);
            }
        }
        out << std::defaultfloat;

    	return out; 
    }
}
