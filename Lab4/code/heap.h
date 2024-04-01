
/**#include <vector>
#include <cassert>

template <class Comparable>
class Heap {
    
public:
    
    explicit Heap() : P(i) {
        
    }
    
    explicit Heap(std::vector)
    
    //Member functions
    
    
    void makeEMpty() {
        pq.clear();
        pq.push_back(Comparable{});
        
    }
    
    bool isEmpty() {
        return P.size() == 1;  // slot zero is not used
        
    }
    
    void insert();
    
    
    
private:
    std::vector<Comparable> P;
    
    void heapify();
    
    void percolateDown(size_t i);
    
    bool isMinHeap() const {
        int n = A.size();
        for (int i = 1; i < n; i++) {
            int parent = (i - 1) / 2;
            if (A[parent] > A[i]) {
                return false;
            }
        }
        return true;
    }
    
}
*/
