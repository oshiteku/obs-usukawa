#pragma once

#include <algorithm>
#include <boost/process.hpp>

namespace bp = boost::process;
class UsukawaCore {
    public:
        UsukawaCore();
        ~UsukawaCore();
        void start(std::function<void(void)>);

    private:
        bp::child core_proc;
};
