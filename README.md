<h1 align="center">
	Grover's search algorithm (GSA)
</h1>

<p align="center">
	Simple C++ implementation of Grover's search algorithm with Qubit class.
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/haimasker/Grover-search-algorithm?color=blue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/haimasker/Grover-search-algorithm?color=blue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/haimasker/Grover-search-algorithm?color=blue" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/haimasker/Grover-search-algorithm?color=blue" />
</p>

<h3 align="center">
	<a href="#preamble">Preamble</a>
	<span> · </span>
  <a href="#description">Description</a>
  <span> · </span>
  <a href="#functions">Functions</a>
</h3>

---

<a name="preamble"></a>
## Preamble

The purpose of this project is to create functions that implements Grover's quantum search algorithm. <br>
Qubit quantum register is presented via [Qubit class](https://github.com/Haimasker/Qubit). <br> <br>
GSA is the quantum algorithm that finds root $x$ of some function $f(x)$ among the values $1...N$. <br>
Usage of a quantum register allows not to perform a brute force to find root of the function. <br>
There are two types of this algorithm: $f(x)$ has only one root and $f(x)$ has at least one root (`singleGSA()` and `multipleGSA` respectively).

---

<a name="description"></a>
## Description

First of all, I recommend you to read some theoretical information about GSA and understand how it works [here](https://en.wikipedia.org/wiki/Grover%27s_algorithm) and [here](https://docs.microsoft.com/en-us/azure/quantum/concepts-grovers). <br>
Let's tale a closer look to phase Oracle and Grover's diffusion operators (`query` and `diffusion` matrices in programm respectively). <br> <br>
* Phase Oracle matrix has the following form:
```
        [ 1 0 ........ 0 ]
        [ 0 1 0 ...... 0 ]
query = [ .............. ]
        [ 0 ... -1 ... 0 ]
        [ 0 0 ........ 0 ]
```
  So, the phase Oracle matrix is the square diagonal matrix with ones, but there is -1 at the row the number of which is equal to the root of the function. <br>
  The phase Oracle applies a conditional phase shift of −1 for the solution item. <br> 
  Query matrix for the multiple roots case defines similarly. <br> <br>
  
* Diffusion matrix has the following form:
```
            [ 2/N-1 2/N ........ 2/N ]
            [ 2/N   2/N-1 ...... 2/N ]
diffusion = [ ...................... ]
            [ 2/N ........ 2/N-1 2/N ]
            [ 2/N ........ 2/N 2/N-1 ]
```
  The Grover's diffusion operator can be geometrically interpreted as a reflection in the vector space about the uniform superposition state.
  
---

<a name="functions"></a>
## Functions

* `singleGSA` - takes qubit register size and solution item index. <br>
If index is equal to 0 then it determines randomly.
```cpp
void singleGSA(unsigned, unsigned = 0);
```

* `multipleGSA` - takes qubit register size and vector of solution items indices. <br>
If vector is empty then it determines randomly.
```cpp
void multipleGSA(unsigned, std::set<unsigned> = {});
```

---
