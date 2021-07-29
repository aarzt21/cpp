
// This is my informatics homework. The task was to answer how many ways there are to own a certain amount of money using a recursive approach. 




#include<iostream>
#include<vector>
// How many ways can you own 1 CHF?


// PRE: 0 <= end <= denominations.size(), and
//      0 < denominations.at(0) < denominations.at(1) < .. denominators.at(end-1)
//      describes a (potentially empty)
//      sequence of denominations
// POST: return value is the number of ways to partition amount
//       using denominations from denominations.at(0), ..., denominations.at(end-1)
unsigned int partitions(unsigned int amount,
                        const std::vector<unsigned int>& denominations,
                        unsigned int end) {

            if (amount == 0) return 1;
            if (amount < 0) return 0;

            unsigned int nCombos = 0;

            for(unsigned int i = 0; i < end ; ++i){
              if(amount < denominations[i]) break;
              nCombos = nCombos + partitions(amount - denominations[i], denominations, i+1);
            }

            return nCombos;
}








int main() {
  // the 13 denominations of CHF
  std::vector<unsigned int> chf = {5,10,20,50,100,200,500,1000,2000,5000,10000,20000,100000};

  // input
  std::cout << "in how many ways can I own x CHF-centimes for x =?\n";
  unsigned int x;
  std::cin >> x;

  // computation and output
  std::cout << partitions(x, chf, chf.size()) << "\n";

  return 0;
}
