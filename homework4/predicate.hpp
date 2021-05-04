using namespace std;
#include <string>

template <typename TIterator, typename TPredicate>
bool anyOf(TIterator begin, TIterator end, TPredicate func) {
    for (;begin != end; ++begin) {
        if (func(*begin))
            return true;
    }
    return false;
}

template <typename TIterator, typename TPredicate>
bool allOf(TIterator begin, TIterator end, TPredicate func) {
    for (;begin != end; ++begin) {
        if (!func(*begin))
            return false;
    }
    return true;
}

template <typename TIterator, typename TPredicate>
bool noneOf(TIterator begin, TIterator end, TPredicate func) {
    for (;begin != end; ++begin) {
        if (func(*begin))
            return false;
    }
    return true;
}

template <typename TIterator, typename TPredicate>
bool oneOf(TIterator begin, TIterator end, TPredicate func) {
    unsigned count = 0;
    for (;begin != end; ++begin) {
        if (func(*begin))
            ++count;
    }
    return count == 1;
}

//fixed use default template argument std::less
template <typename TIterator, typename TCompare = std::less<>>
bool isSorted(TIterator begin, TIterator end, TCompare func = TCompare()) {
    for (;begin != end - 1; ++begin) {
        if (!func(*begin, *(begin+1)))
            return false;
    }
    return true;
}

//fixed N^2
template<class TIterator, typename TPredicate>
bool isPartitioned(TIterator begin, TIterator end, TPredicate func) {
    auto i = begin;
    for (; begin != end; begin++) {
        if (!func(*begin)) {
            i = begin;
            break;
        }
    }
    for (i; i != end; i++) {
        if (func(*i))
            return false;
    }
    return true;
}

template <typename TIterator, typename T>
TIterator findNot(TIterator begin, TIterator end, const T& value) {
    for (;begin != end; ++begin) {
        if (*begin != value)
            return begin;
    }
    return end;
}

template <typename TIterator, typename T>
TIterator findBackward(TIterator begin, TIterator end, const T& value) {
    TIterator tmp = end;
    for (;begin != end; ++begin) {
        if (*begin == value)
            tmp = begin;
    }
    return tmp;
}

template <typename TIterator, typename TPredicate>
bool isPalindrome(TIterator begin, TIterator end, TPredicate func) {
    --end;
    for (;distance(begin, end) > 0;) {
        if (!func(*begin, *end))
            return false;
        ++begin;
        --end;
    }

    return true;
}
