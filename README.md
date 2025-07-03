# 🧾 Deriv – C++ Symbolic Derivative Calculator

This project implements a symbolic derivative engine in C++, capable of parsing and differentiating algebraic expressions. It showcases expression trees, recursive descent parsing, and output simplification — all written without external libraries.

---

## 🎯 Goal

The purpose of this tool is to read mathematical expressions (e.g., `x^2 + 3*x + 5`) and compute their symbolic derivative with respect to `x`. This makes it useful for learning symbolic differentiation, expression trees, and recursive algorithms.

---

## 💡 Features

- Parses fully parenthesized algebraic expressions
- Builds an abstract syntax tree (AST)
- Recursively computes derivatives using symbolic rules
- Outputs simplified results

---

## 🧠 Concepts Practiced

### ✔️ C++ Theory and Techniques

- Custom string tokenization and expression parsing
- Tree construction using `Node` structures
- Recursive descent parsing and evaluation
- Polymorphism and encapsulation in the `Node` hierarchy
- Recursive derivative computation based on type of operation (`+`, `*`, `^`, etc.)

### ✔️ Mathematics

- Differentiation of:
  - Constants and variables
  - Sums and products
  - Exponentials (e.g., `x^n`)
  - Chain and product rules

---

## 📁 Structure

```
deriv-master/
├── main.cpp         # CLI wrapper and tests
├── Node.cpp/h       # Base class for expression tree nodes
├── Const.cpp/h      # Constant node
├── Var.cpp/h        # Variable node (e.g., 'x')
├── Sum.cpp/h        # Sum node (a + b)
├── Mul.cpp/h        # Multiplication node (a * b)
├── Pow.cpp/h        # Power node (a ^ b)
├── Parser.cpp/h     # Expression parsing logic
├── utils.cpp/h      # Simplification, memory cleanup
└── test.txt         # Sample input expressions
```

---

## 🧪 How to Use

### 🛠️ Build

```bash
g++ -std=c++17 *.cpp -o deriv
```

### ▶️ Run

```bash
./deriv
```

The program will prompt for an input expression, compute its derivative, and print both the original and derived expressions.

---

## 📘 Example

**Input:**
```
(x^2 + 3*x + 5)
```

**Output:**
```
Original: (x^2 + 3*x + 5)
Derivative: ((2*x) + 3)
```

---

Symbolic Derivation Engine – C++ Coursework  
Faculty of Computer Science (FII)
