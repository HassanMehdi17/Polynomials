# Polynomials
A program designed to apply simple functions ( addition, subtraction, division, multiplications) as well as differentiation and integration of polynomial equations

# Example Main() input
(copy paste into main)

PolyType poly1; //makes a null polynomial  
PolyType poly2(2,3); // makes the polynomial 2.00x^3  
PolyType poly3(3,4); // makes the polynomial 3.00x^4  
poly1 = poly2 + poly3; // makes poly1 = 3.00x^4 + 2.00x^3  
cout<<poly1<<endl;  // prints out 3.0x^4 + 2.00x^3  
poly3 = poly2*poly1; // sets poly3 to 6.0x^7+4.00x^6  
poly4 = poly3.differ(); // sets poly4 to 42.00x^6+24.00x^5  
poly5 = poly1.integr(); // sets poly5 to .60x^5+.50x^4  
