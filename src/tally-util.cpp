#include "tally-util.h"
#include <stddef.h>         // for size_t
#include <__bit_reference>  // for __bit_iterator, operator-, operator==
#include <algorithm>        // for find
#include <iterator>         // for distance

namespace TallyUtil {

bool performTally(std::vector<bool>& arr) {
    // Find the first false value
    auto firstFalseIt = std::find(arr.begin(), arr.end(), false);
    
    // If no false value is found, return false
    if (firstFalseIt == arr.end()) {
        return false;
    }
    
    // Find the next true value after the first false value
    auto nextTrueIt = std::find(firstFalseIt + 1, arr.end(), true);
    
    // If no true value is found, return false
    if (nextTrueIt == arr.end()) {
        return false;
    }

    // Calculate the index of the first false value
    size_t firstFalseIndex = static_cast<size_t>(std::distance(arr.begin(), firstFalseIt));

    // Shift all elements after the first false one position to the left
    for (size_t i = firstFalseIndex; i < arr.size() - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    
    // Append a false value at the end of the array
    arr[arr.size() - 1] = false;

    return true;
}

} // namespace TallyUtil
