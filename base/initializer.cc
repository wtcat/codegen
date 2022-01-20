#include <algorithm>

#include "base/initializer.h"


namespace base {

cc_initializer::~cc_initializer() {
    clear();
}

cc_initializer* cc_initializer::get_instance() {
    static cc_initializer* initializer_ptr;
    if (initializer_ptr == nullptr)
        initializer_ptr = new cc_initializer();
    return initializer_ptr;
}

int cc_initializer::run() {
    int ret = 0;
    for (auto iter : container_) {
        ret = iter->run();
        if (ret)
            break;
    }
    return ret;
}

cc_constructor* cc_initializer::add_constructor(cc_constructor* c) {
    container_.push_back(c);
    return c;
}

void cc_initializer::clear() {
    for (auto iter : container_)
        delete iter;
}

cc_initializer *cc_initializer::sort() {
    std::sort(container_.begin(), container_.end(),
        [](cc_constructor* a, cc_constructor* b) {
            return a->order() < b->order();
        }
    );
    return this;
}


} //namespace