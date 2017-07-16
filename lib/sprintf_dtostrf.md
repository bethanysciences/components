<link rel="stylesheet" href="modest.css">
# sprintf and dtostrf

### dtostrf function
convert floats to fixed string
```
char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
    char fmt[20];
    sprintf(fmt, "%%%d.%df", width, prec);
    sprintf(sout, fmt, val);
    return sout;
}
```
`val` float variable  
`width` returned string length INCLUDING decimal point  
`prec` precision    
`sout` returned string  

### basic sprintf function
```  
int temp;  
char tempSTR[6];  
sprintf(temp, "%s F", tempSTR)
```  
`temp` number to format  
`tempSTR` target character array  

### Flags
`.` decimal  
`%` 0 padding  
`s` string  
`d` signed decimal  
`b` binary  

`c` character ASCII value  
`e` scientific notation (1.2e+2)  
`E` uppercase sci notation (1.2e+2)   
`o` octal number  
`u` unsigned decimal  
`x` lowercase hexadecimal  
`X` uppercase hexadecimal  

# sprintf
```string sprintf ( string $format [, mixed $args [, mixed $... ]] )```  

## format
The format string is composed of zero or more directives: ordinary characters (excluding %) that are copied directly to the result, and conversion specifications, each of which results in fetching its own parameter. This applies to both sprintf() and printf().  

Each conversion specification consists of a percent sign (%), followed by one or more of these elements, in order:  
* An optional sign specifier that forces a sign (- or +) to be used on a number. By default, only the - sign is used on a number if it's negative. This specifier forces positive numbers to have the + sign attached as well.  
* An optional padding specifier that says what character will be used for padding the results to the right string size. This may be a space character or a 0 (zero character). The default is to pad with spaces. An alternate padding character can be specified by prefixing it with a single quote ('). See the examples below.  
* An optional alignment specifier that says if the result should be left-justified or right-justified. The default is right-justified; a - character here will make it left-justified.  
* An optional number, a width specifier that says how many characters (minimum) this conversion should result in.
* An optional precision specifier in the form of a period (.) followed by an optional decimal digit string that says how many decimal digits should be displayed for floating-point numbers. When using this specifier on a string, it acts as a cutoff point, setting a maximum character limit to the string. Additionally, the character to use when padding a number may optionally be specified between the period and the digit.
* A type specifier that says what type the argument data should be treated as.

Possible types:

`%` literal percent character. No argument is required  
`b` argument is treated as an integer, and presented as a binary number  
`c` argument is treated as an integer, and presented as the character with that ASCII value  
`d` argument is treated as an integer, and presented as a (signed) decimal number  
`e` argument is treated as scientific notation (e.g. 1.2e+2). The precision specifier stands for the number of digits after the decimal point since PHP 5.2.1. In earlier versions, it was taken as number of significant digits (one less)  
`E` like %e but uses uppercase letter (e.g. 1.2E+2)
`f` argument is treated as a float, and presented as a floating-point number (locale aware)  
`F` argument is treated as a float, and presented as a floating-point number (non-locale aware)   Available since PHP 5.0.3  
`g` shorter of %e and %f  
`G` shorter of %E and %f
`o` argument is treated as an integer, and presented as an octal number  
`s` argument is treated as and presented as a string  
`u` argument is treated as an integer, and presented as an unsigned decimal number  
`x` argument is treated as an integer and presented as a hexadecimal number (with lowercase letters)  
`X` argument is treated as an integer and presented as a hexadecimal number (with uppercase letters)   

Variables will be co-erced to a suitable type for the specifier:

### Type Handling  

| Type    | Specifiers  |
|:------- |:-----------:|
| string  | s  |
| integer | d, u, c, o, x, X, b |
| double  | g, G, e, E, f, F |
