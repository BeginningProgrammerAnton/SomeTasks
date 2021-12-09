#pragma once
#include <unordered_map>
#include <functional>
#include <type_traits>
#include <vector>
#include <stack>
#include <queue>

template <typename Iterator, typename Predicat, typename Functor, class T>
void TransformIfNew(Iterator begin, Iterator end, Predicat p, Functor f, T value) {
    std::queue<T> qe;
    auto start = begin;
    while (begin != end) {
        try {
            qe.push(*begin);
            if (p(*begin)) {
                f(*begin);
            }
            ++begin;
        } catch (const std::runtime_error& ex) {
            size_t size = qe.size();
            for (size_t i = 0; i < size; i++) {
                *start = qe.front();
                qe.pop();
                ++start;
            }
            throw ex;
        } catch (const std::string& ex) {
            for (size_t i = 0; i < qe.size(); i++) {
                *start = qe.front();
                qe.pop();
                ++start;
            }
            throw ex;
        } catch (int ex) {

            size_t size = qe.size();
            for (size_t i = 0; i < size; i++) {
                *start = qe.front();
                qe.pop();
                ++start;
            }
            throw ex;
        } catch (const std::logic_error& ex) {
            std::cout << "NOT EXEPTION" << std::endl;
        }
    }
}

template <typename Iterator, typename Predicat, typename Functor>
void TransformIf(Iterator begin, Iterator end, Predicat p, Functor f) {
    TransformIfNew(begin, end, p, f, *begin);
}
