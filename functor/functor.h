#pragma once

struct Sum {
    template <class T>
    T operator()(T x, T res) {
        return x + res;
    }
};

struct Prod {
    template <class T>
    T operator()(T x, T res) {
        return x * res;
    }
};

struct Concat {
    template <class T>
    T operator()(T x, T res) {
        for (size_t i = 0; i < x.size(); i++) {
            res.emplace_back(x[i]);
        }
        return res;
    }
};

template <class Iterator, class T, class BinaryOp>
T Fold(Iterator first, Iterator last, T init, BinaryOp func) {
    T res = init;
    while (first != last) {
        res = func(*first, res);
        first++;
    }
    return res;
}

class Length {
public:
    Length(int* cnt) {
        a_ = cnt;
    }
    template <class T>
    T operator()(T x, T res) {
        ++*a_;
        return res;
    }

private:
    int* a_;
};
