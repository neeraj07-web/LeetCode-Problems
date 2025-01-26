class Solution {
public:
    bool doesValidArrayExist(vector<int>& derived) {
         int n = derived.size();
        // XOR of all elements in `derived`
        int xorSum = 0;
        for (int num : derived) {
            xorSum ^= num;
        }
        // If XOR of all elements is 0, a valid `original` exists
        return xorSum == 0;
    }
};