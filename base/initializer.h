#ifndef BASE_INITIALIZER_H_
#define BASE_INITIALIZER_H_

#include "base/basedefs.h"

#ifdef __cplusplus
#include <vector>
#include <memory>

namespace base {

class cc_constructor {
public:
    cc_constructor(int level) : order_(level) {}
    virtual ~cc_constructor() {}
    virtual int run() = 0;
    int order() const {
        return order_;
    }
protected:
    int order_;
};

class cc_initializer {
public:
    enum {
        kFirst = 10,
        kMiddle = 50,
        kLast = 99
    };
    ~cc_initializer();
    cc_initializer(const cc_initializer&) = delete;
    cc_initializer& operator=(const cc_initializer&) = delete;
    static cc_initializer* get_instance();
    cc_constructor* add_constructor(cc_constructor* c);
    int run();
    cc_initializer* sort();

private:
    cc_initializer() = default;
    void clear();

private:
    std::vector<cc_constructor*> container_;
};

inline int cc_initializer_run() {
    std::unique_ptr<cc_initializer> _initializer(
        cc_initializer::get_instance());
    return _initializer->sort()->run();
}

} //namespace base


#define CC_INIT(_name, _order) \
class _CONTACT(_cc_contructor_, _name) : public base::cc_constructor { \
public:                                                       \
    _CONTACT(_cc_contructor_, _name)(int order) : base::cc_constructor(order) {}           \
    ~_CONTACT(_cc_contructor_, _name)() = default;   \
    int run() override; \
private:                    \
    static base::cc_constructor* const construct_;  \
};  \
base::cc_constructor* const _CONTACT(_cc_contructor_, _name)::construct_ = \
    base::cc_initializer::get_instance()->add_constructor( \
    new _CONTACT(_cc_contructor_, _name)(_order)); \
int _CONTACT(_cc_contructor_, _name)::run()

#else
#define CC_INIT(name) 
#endif /* __cplusplus */


#endif /* BASE_INITIALIZER_H_ */
