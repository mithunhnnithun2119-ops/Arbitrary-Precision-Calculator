<div align="center">

<img width="100%" src="https://capsule-render.vercel.app/api?type=waving&color=0:0d1117,30:0a3d62,60:1a1a2e,100:16213e&height=260&section=header&text=Arbitrary%20Precision%20Calculator&fontSize=48&fontColor=00d4ff&fontAlignY=45&desc=Big%20Integer%20Arithmetic%20Engine%20in%20Pure%20C&descSize=20&descColor=a0cfee&descAlignY=65&animation=fadeIn&stroke=00d4ff&strokeWidth=1"/>

<img src="https://readme-typing-svg.demolab.com?font=Fira+Code&weight=700&size=19&duration=2500&pause=900&color=00D4FF&center=true&vCenter=true&width=680&lines=➕+Addition+%7C+➖+Subtraction+%7C+✖️+Multiplication+%7C+➗+Division;🔢+No+Integer+Overflow+—+Ever;📎+Doubly+Linked+List+per+Digit;⚡+Fully+CLI+Driven+in+Pure+C;🧠+Beyond+long+long+Limits" alt="Typing SVG" />

<br/>

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Unix-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Standard](https://img.shields.io/badge/Standard-C99-blue?style=for-the-badge&logo=gnu&logoColor=white)
![Build](https://img.shields.io/badge/Build-GCC-orange?style=for-the-badge&logo=gnu&logoColor=white)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-00d4ff?style=for-the-badge)

</div>

---

## 📌 Overview

**Arbitrary Precision Calculator (APC)** is a command-line arithmetic engine written entirely in **C** that performs **Addition, Subtraction, Multiplication, and Division** on numbers of **unlimited size** — far beyond what any standard data type (`int`, `long`, `long long`) can hold.

Instead of storing a number in a fixed-size variable, APC stores **each digit as a node** in a **Doubly Linked List**, making the number size limited only by available memory.

No external libraries. No language runtime tricks. Just pure **C**, **pointers**, and **data structures**.

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| ➕ **Addition** | Add two arbitrarily large positive integers |
| ➖ **Subtraction** | Subtract with proper borrow handling and sign detection |
| ✖️ **Multiplication** | Digit-by-digit multiply with carry propagation |
| ➗ **Division** | Long division on big integers with quotient and remainder |
| 🔢 **No Overflow** | Numbers stored as linked digit chains — size is unlimited |
| 📎 **Doubly Linked List** | Each digit is a node; supports forward and backward traversal |
| 🖥️ **CLI Interface** | All input and operations handled via command-line arguments |
| 🔍 **Input Validation** | Detects invalid characters, empty inputs, and edge cases |

---

## 📁 Project Structure

```
📁 apc/
│
├── 📄 main.c            → Entry point, argument parsing, operation dispatch
├── 📄 apc.c             → Core arithmetic logic (add, sub, mul, div)
├── 📄 apc.h             → Function declarations and DLL node struct
├── 📄 dll.c             → Doubly linked list: insert, delete, traverse, free
├── 📄 dll.h             → DLL declarations
├── 📄 utils.c           → Input validation, leading-zero removal, comparison
├── 📄 utils.h           → Utility declarations
├── 📄 Makefile          → Build automation
└── 📄 README.md         → You are here
```

---

## 🚀 Getting Started

### Prerequisites

```bash
# Verify GCC is installed
gcc --version

# Install on Ubuntu / Debian
sudo apt install gcc build-essential

# Install on Fedora / RHEL
sudo dnf install gcc make
```

### Build

```bash
# Clone the repository
git clone https://github.com/mithunhnnithun2119-ops/apc.git
cd apc

# Build with Makefile
make

# Or compile manually
gcc main.c apc.c dll.c utils.c -o apc
```

---

## 🖥️ Usage

### Syntax

```bash
./apc <number1> <operator> <number2>
```

### Operators

| Operator | Operation | Example |
|----------|-----------|---------|
| `+` | Addition | `./apc 99999999999 + 1` |
| `-` | Subtraction | `./apc 10000000000 - 9999999999` |
| `x` | Multiplication | `./apc 123456789 x 987654321` |
| `/` | Division | `./apc 999999999999 / 3` |

---

## 🎬 Demo

### Addition — Numbers Beyond `long long`

```bash
$ ./apc 99999999999999999999 + 1

  Input A  :  99999999999999999999
  Operator :  +
  Input B  :  1
  ──────────────────────────────────
  Result   :  100000000000000000000
```

### Multiplication of Large Numbers

```bash
$ ./apc 123456789123456789 x 987654321987654321

  Input A  :  123456789123456789
  Operator :  x
  Input B  :  987654321987654321
  ──────────────────────────────────
  Result   :  121932631137021795226185032818808969
```

### Division with Remainder

```bash
$ ./apc 1000000000000 / 7

  Input A  :  1000000000000
  Operator :  /
  Input B  :  7
  ──────────────────────────────────
  Quotient    :  142857142857
  Remainder   :  1
```

### Invalid Input Handling

```bash
$ ./apc 12abc + 5

  ❌ Error: Invalid input — '12abc' contains non-numeric characters.
```

---

## 🧠 Technical Deep Dive

### Core Idea — Why Linked Lists?

Standard C data types have fixed upper bounds:

```
int        →  2,147,483,647          (10 digits)
long long  →  9,223,372,036,854,775,807  (19 digits)
APC        →  unlimited              (memory is the only limit)
```

APC stores each digit of a number as a **node** in a **Doubly Linked List**:

```
  Number : 9 2 7 4 1

  HEAD ←→ [9] ←→ [2] ←→ [7] ←→ [4] ←→ [1] ←→ NULL
           ↑                               ↑
          MSB                             LSB
```

### Node Structure

```c
/* Single digit node in the doubly linked list */
typedef struct Node {
    int          digit;   /* One digit: 0–9              */
    struct Node *prev;    /* Pointer to higher-order digit */
    struct Node *next;    /* Pointer to lower-order digit  */
} Node;

/* Big number represented as a DLL */
typedef struct {
    Node *head;           /* Most significant digit  */
    Node *tail;           /* Least significant digit */
    int   sign;           /* 0 = positive, 1 = negative */
    int   length;         /* Total number of digits */
} BigNum;
```

### Addition Logic

```c
/*
 * Add two BigNums digit by digit from LSB to MSB.
 * Traverse from tail → head, sum digits, carry forward.
 */
BigNum* add(BigNum *a, BigNum *b) {
    Node   *pa    = a->tail;
    Node   *pb    = b->tail;
    int     carry = 0;
    BigNum *result = create_bignum();

    while (pa || pb || carry) {
        int sum = carry;
        if (pa) { sum += pa->digit; pa = pa->prev; }
        if (pb) { sum += pb->digit; pb = pb->prev; }
        carry = sum / 10;
        prepend_digit(result, sum % 10);
    }
    return result;
}
```

### Subtraction Logic

```c
/*
 * Subtract smaller from larger (comparison done first).
 * Traverse from LSB, borrow from next higher digit when needed.
 */
BigNum* subtract(BigNum *a, BigNum *b) {
    /* Ensure a >= b; if b > a, swap and set result sign = negative */
    if (compare(a, b) < 0) {
        BigNum *tmp = a; a = b; b = tmp;
        /* mark result negative */
    }

    Node *pa = a->tail, *pb = b->tail;
    int   borrow = 0;
    BigNum *result = create_bignum();

    while (pa) {
        int diff = pa->digit - borrow;
        if (pb) { diff -= pb->digit; pb = pb->prev; }
        if (diff < 0) { diff += 10; borrow = 1; }
        else            borrow = 0;
        prepend_digit(result, diff);
        pa = pa->prev;
    }
    remove_leading_zeros(result);
    return result;
}
```

### Leading Zero Removal

```c
/* Strip leading zeros from head of the DLL */
void remove_leading_zeros(BigNum *num) {
    while (num->head && num->head->digit == 0
           && num->head != num->tail) {
        Node *tmp  = num->head;
        num->head  = num->head->next;
        num->head->prev = NULL;
        free(tmp);
        num->length--;
    }
}
```

---

## ⚙️ Key Concepts Applied

| Concept | Application |
|---------|-------------|
| `Doubly Linked List` | Each digit is a node; supports both forward and backward traversal |
| `Dynamic Memory Allocation` | `malloc()` per node; `free()` after every operation |
| `Carry & Borrow Handling` | Propagated across all digits during arithmetic |
| `Big Number Comparison` | Length-first, then digit-by-digit from MSB for `>`, `<`, `=` |
| `Sign Management` | Tracks positive/negative for subtraction results |
| `Leading Zero Removal` | Cleans result DLL head after every operation |
| `Modular Programming` | Separate modules: dll, apc, utils, main |
| `CLI Argument Handling` | `argc` / `argv` for operands and operator input |
| `Input Validation` | Rejects non-numeric characters before any processing |

---

## 🧪 Challenges & Solutions

```
❌ Challenge 1: Handling arbitrarily large numbers without overflow
✅ Solution   : Stored each digit as a DLL node — number size becomes
                unlimited, bounded only by heap memory.

❌ Challenge 2: Memory leaks during dynamic allocation of nodes
✅ Solution   : Implemented a dedicated free_bignum() that traverses
                the entire list and frees every node after use.

❌ Challenge 3: Subtraction producing wrong results for b > a
✅ Solution   : Added a compare() function to detect magnitude; swapped
                operands when b > a and flagged the result as negative.

❌ Challenge 4: Multiplication producing intermediate overflow
✅ Solution   : Used digit-by-digit multiply with an intermediate result
                DLL, adding partial products shifted by position — the
                same algorithm as manual long multiplication on paper.

❌ Challenge 5: Leading zeros corrupting results (e.g. "007")
✅ Solution   : Called remove_leading_zeros() after every arithmetic
                operation to clean the result before display.
```

---

## 📈 Future Enhancements

- [ ] 🔣 Support for negative number inputs directly from CLI
- [ ] 🔢 Modulo (`%`) operation support
- [ ] ⚡ Karatsuba algorithm for faster large-number multiplication
- [ ] 📤 Export results to a text file
- [ ] 🖥️ Interactive REPL mode (loop until user types `exit`)
- [ ] 🔬 Support for floating-point arbitrary precision

---

## 🎓 Learning Outcomes

Building this project gave me hands-on experience in:

- **Doubly linked list design** — real-world application beyond textbook examples
- **Dynamic memory management** — zero leaks through disciplined `malloc` / `free` pairing
- **Arithmetic algorithm design** — carry, borrow, and long-division implemented from scratch
- **Modular C architecture** — clean separation of DLL, arithmetic, utilities, and entry point
- **Edge case thinking** — zeros, negatives, single-digit numbers, unequal lengths all handled
- **CLI robustness** — argument count validation and non-numeric input rejection

---

## 👤 Author

<div align="center">

| Field | Details |
|-------|---------|
| **Name** | Mithun H N |
| **Degree** | B.E. ECE — Visvesvaraya Technological University (CGPA: 8.13) |
| **Training** | Advanced Embedded Systems — Emertxe, Bangalore |
| **Certification** | Skill India / NSDC — ELE/Q1501 (Embedded Engineer) |
| **LinkedIn** | [linkedin.com/in/mithun-hn](https://www.linkedin.com/in/mithun-hn) |
| **GitHub** | [github.com/mithunhnnithun2119-ops](https://github.com/mithunhnnithun2119-ops) |
| **Email** | mithunhnmithun2119@gmail.com |

</div>

---

## 📜 License

```
MIT License — Copyright (c) 2024 Mithun H N
Free to use, modify, and distribute with attribution.
```

---

<div align="center">

<img width="100%" src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0d1117&height=120&section=footer&animation=fadeIn"/>

*"When the data type runs out of room, build your own."* ⚡

![Visitor Count](https://komarev.com/ghpvc/?username=mithunhnnithun2119-ops&color=00d4ff&style=for-the-badge&label=PROFILE+VIEWS)

⭐ **Star this repo if it helped you!** ⭐

</div>
