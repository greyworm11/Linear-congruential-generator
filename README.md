# Linear-congruential-generator

The Linear Congruent Generator (LCG) is an algorithm that gives a sequence of pseudorandom numbers calculated using a recursive formula. The method is one of the oldest and best known algorithms for generating pseudorandom numbers.

</br>

The generator is defined by the recurrence relation:

![recurrence relation](https://github.com/greyworm11/Linear-congruential-generator/blob/main/Recurrence%20relation.gif?raw=true)

Where X is the sequence of pseudo-random values;
</br>
m , 0 < m, - the "modulus";
</br>
a, 0 < a < m, - the "multiplier";
</br>
c, 0 <= c < m, - the "increment";
</br>
X*0*, 0 <= X*0* < m, - the "seed" or "start value";

___
## Parameters
To achieve a good LCG, it is necessary to choose the right parameters.

</br>

### Main theorems

+ m is 2 to the power of the machine word length;
+ the numbers c and m must be mutually prime;
+ b = a - 1 multiple of p, for every prime p that is a divisor of m;
+ b = a - 1 is a multiple of 4 if m is a multiple of 4;
+ the number X0 is random;

_it may be strange that we use a random number to generate "random" numbers, but due to this the LCG parameters will show a higher performance. The implementation uses a fixed value: 189231, but in practice you can use the built-in C rand() function._

___

## Generator parameters used in the program

+ m = 2^32, because we take the machine word to be 32 bits long;
+ X0 = 189231;
+ c = 1;
+ a = 214013;

___
## Testing

![Start window example image](https://github.com/greyworm11/Linear-congruential-generator/blob/main/start_window_example.PNG?raw=true)

Here you can choose what do you want to do.

All of the parameters may be changed, the most popular and usable [here](https://en.wikipedia.org/wiki/Linear_congruential_generator).

![Time delay param](https://github.com/greyworm11/Linear-congruential-generator/blob/main/time_delay_option.PNG?raw=true)

*Here you can change time between generating new element, **line 365***.

___

## Contacts

</br>

*This program was written by Sergey Poshekhonov and Konstantin Tsibulskas. For any feedback, please write to telegram: [link](https://t.me/sergejgwssd).*

*I will be glad to hear your questions, criticism and suggestions.*
