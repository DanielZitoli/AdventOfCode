#include "helpers.h"
#include <memory>

// struct Tree {
//   virtual string toStr() = 0;
//   virtual ~Tree() {}
// };

// struct Op : public Tree {
//   string op;
//   unique_ptr<Tree> left, right;

//   Op(unique_ptr<Tree> left, string op, unique_ptr<Tree> right): op{op}, left{move(left)}, right{move(right)} {}

//   string toStr() override {
//     return "(" + left->toStr() + op + right->toStr() + ")";
//   }
// };

// struct Leaf : public Tree {
//   string val;
//   Leaf(int n): val{to_string(n)} {}
//   Leaf(string val): val{val} {}

//   string toStr() override { return val; }
// };

long long getCombo(long long operand, long long a, long long b, long long c) {
  if (operand < 4) return operand;
  if (operand == 4) return a;
  if (operand == 5) return b;
  if (operand == 6) return c;
  cout << "HERE\n";
  return -100;
}

string getComboLeaf(long long operand, long long a, long long b, long long c) {
  if (operand < 4) return to_string(operand);
  if (operand == 4) return "a";
  if (operand == 5) return "b";
  if (operand == 6) return "c";
  cout << "ERROR\n";
  return "-9999";
}

bool runSimulation(long long a, const vector<int>& nums) {
  long long i = 0, printCount = 0, b = 0, c = 0;

  // unique_ptr<Tree> aTree = make_unique<Leaf>("a"), bTree = make_unique<Leaf>("b"), cTree = make_unique<Leaf>("c");

  string aTree("a"), bTree("b"), cTree("c");

  while (i < nums.size()) {
    // cout << i << endl;
    int opcode = nums[i], operand = nums[i+1];

    if (opcode == 0) {
      a = a / (1 << getCombo(operand, a, b, c));
      // aTree = make_unique<Op>(
      //   move(aTree), 
      //   "/", 
      //   make_unique<Op>(
      //     make_unique<Leaf>(2), 
      //     "^", 
      //     make_unique<Leaf>(getComboLeaf(operand, a, b, c))
      //   )
      // );
      aTree = "(" + aTree + " / 2^" + getComboLeaf(operand, a, b, c) + ")";
    }
    if (opcode == 1) {
      b ^= operand;
      // bTree = make_unique<Op>(
      //   move(bTree), 
      //   "xor", 
      //   make_unique<Leaf>(operand)
      // );
      bTree = "(" + bTree + " xor " + to_string(operand) + ")";
    }
    if (opcode == 2) {
      b = getCombo(operand, a, b, c) % 8;
      // bTree = make_unique<Op>(
      //   make_unique<Leaf>(getComboLeaf(operand, a, b, c)), 
      //   "%", 
      //   make_unique<Leaf>(8)
      // );
      bTree = "(" + getComboLeaf(operand, a, b, c) + " % " + "8)";
    }
    if (opcode == 3) {
      if (a!=0) i = operand-2;
    }
    if (opcode == 4) {
      b = b ^ c;
      // bTree = make_unique<Op>(
      //   move(bTree), 
      //   "xor", 
      //   move(cTree)
      // );
      bTree = "(" + bTree + " xor " + cTree + ")";
    }
    if (opcode == 5) {
      // if (printCount > nums.size()) return false; // too many printed
      int output = getCombo(operand, a, b, c)%8;
      
      // if (output != nums[printCount++]) return false;

      // cout << (getCombo(operand, a, b, c)%8) << ",";

      cout << "printing output of: " << output << " - ";
      if (operand < 4) cout << output;
      if (operand == 4) cout << aTree;  //->toStr();
      if (operand == 5) cout << bTree;  //->toStr();
      if (operand == 6) cout << cTree;  //->toStr();
      cout << endl;
    }
    if (opcode == 6) {
      b = a / (1 << getCombo(operand, a, b, c));
      // bTree = make_unique<Op>(
      //   move(aTree), 
      //   "/", 
      //   make_unique<Op>(
      //     make_unique<Leaf>(2), 
      //     "^", 
      //     make_unique<Leaf>(getComboLeaf(operand, a, b, c))
      //   )
      // );
      bTree = "(" + aTree + " / " + "(2 ^ " + getComboLeaf(operand, a, b, c) + "))"; 
    }
    if (opcode == 7) {
      c = a / (1 << getCombo(operand, a, b, c));
      // cTree = make_unique<Op>(
      //   move(aTree), 
      //   "/", 
      //   make_unique<Op>(
      //     make_unique<Leaf>(2), 
      //     "^", 
      //     make_unique<Leaf>(getComboLeaf(operand, a, b, c))
      //   )
      // );
      cTree = "(" + aTree + " / (2" + " ^ " + getComboLeaf(operand, a, b, c) + "))";
    }
    i+=2;
  }

  cout << aTree << endl;   // ->toStr() << endl;
  cout << bTree << endl;   // ->toStr() << endl;
  cout << cTree << endl;   // ->toStr() << endl;



  return (printCount == nums.size());
}

int main() {

  int a, b, c, num;
  string line1, line2, line3;
  getline(cin, line1), getline(cin, line2), getline(cin, line3);
  istringstream stream1(line1.substr(11)), stream2(line2.substr(11)), stream3(line3.substr(11));
  stream1 >> a; stream2 >> b; stream3 >> c;
  getline(cin, line1); getline(cin, line1);
  vector<int> nums = extractIntegers(line1);

  cout << a << " " << b << " " << c << endl << nums << endl;
  
  // unique_ptr<Tree> aTree = make_unique<Op>(make_unique<Leaf>("a"), "/", make_unique<Op>(make_unique<Leaf>(2), "^", make_unique<Leaf>(getComboLeaf(5, a, b, c))));
  // cout << aTree->toStr() << endl;

  runSimulation(a, nums);
  cout << endl;
  runSimulation(a+100000000, nums);
  // from running this simulation we find that when printing the ith (i=0,1,2,...) value, we are printing:
  // ((((a % 8) xor 3) xor (a / (2 ^ 3)^i)) xor 5) == ((((a % 8) xor 3) xor (a / 8^i)) xor 5) = nums[i]
  // using the properties of XOR we find that this is equivalent to:
  // a[0:2]^a[3i:3i+2] = nums[i] ^ 011 ^ 101
  // -> a[3i:3i+2] = nums[i] ^ 110 ^ nums[0:2]
  // we can try all values of nums[0:2] from 0-7

  for (int first3Bits = 0; first3Bits < 8; ++first3Bits) {
    long long power = 1, A=0;
    for (int i = 0; i < nums.size(); ++i) {
      A += (nums[i]^6^first3Bits)*power;
      power *= 8;
    }
    cout << endl << A << endl;
    runSimulation(A, nums);
  }



  return 0;
}