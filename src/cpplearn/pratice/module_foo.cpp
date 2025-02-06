export module Module_foo;

namespace Bar{
    int private_func(){
        return 20;
    }

    export int ex_func(){
        return private_func();
    }
}
