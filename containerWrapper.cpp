#include <iostream>
#include <algorithm> // std::sort, std::find, std::copy
#include <iterator> // std::distance, std::advance, std::back_inserter
#include <limits>   // std::numeric_limits<size_t>::max()
#include <numeric>  // std::accumulate()
#include <vector>
using namespace std;

#include "containerWrapper.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif

IContainerWrapper::~IContainerWrapper() = default;


VectorWrapper::VectorWrapper(const IContainerWrapper::value_type *elements, size_t N) {
    vector<value_type> vect(elements,elements + N);
    impl_ = vect;
}

void VectorWrapper::erase(size_t position) {
    auto it = std::next(impl_.begin(),position);
    impl_.erase(impl_.begin() + position);
}
