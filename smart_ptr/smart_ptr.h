#pragma once

#include <string>

class WeakPtr;

class SharedPtr {
public:
    SharedPtr(const WeakPtr& rhs);
    SharedPtr() : s_ptr(nullptr) {
        count = new int(0);
    }
    SharedPtr(const SharedPtr& other) {
        this->s_ptr = other.s_ptr;
        count = other.count;
        (*count)++;
    }
    SharedPtr(std::string* ptr) : s_ptr(ptr) {
        count = new int(1);
    }
    SharedPtr(std::string* str, int* ptr) {
        if (ptr == nullptr) {
            count = new int(0);
        } else {
            *ptr += 1;
            count = ptr;
            s_ptr = str;
        }
    }
    SharedPtr(SharedPtr&& ptr) {
        s_ptr = ptr.s_ptr;
        count = ptr.count;
    }
    SharedPtr& operator=(const SharedPtr& other) {
        if (s_ptr == other.s_ptr && count == other.count) {
            return *this;
        }
        if (*count == 1) {
            delete s_ptr;
            delete count;
        }
        s_ptr = other.s_ptr;
        count = other.count;
        if (*count != 0) {
            (*count)++;
        }
        return *this;
    }

    bool operator==(const SharedPtr& ptr) {
        if (*s_ptr == *(ptr.s_ptr)) {
            return true;
        }
        return false;
    }
    std::string& operator*() const {
        return *s_ptr;
    }
    ~SharedPtr() {
        if (*count == 1) {
            (*count)--;
            count = nullptr;
            delete s_ptr;
            delete count;
            s_ptr = nullptr;
            count = nullptr;
        }
        if (count != nullptr) {
            (*count)--;
        }
    }
    void Reset(std::string* ptr) {
        if (*count == 1) {
            delete s_ptr;
            delete count;
            count = nullptr;
        }
        if (count != nullptr) {
            (*count)--;
        }
        s_ptr = ptr;
        count = new int(1);
    }
    std::string* Get() {
        return s_ptr;
    }
    int* count = nullptr;
    std::string* s_ptr = nullptr;
};

class WeakPtr {
public:
    WeakPtr(const SharedPtr& ptr) {
        w_ptr = ptr.s_ptr;
        w_count = ptr.count;
    }
    WeakPtr() {
        w_ptr = nullptr;
    }
    WeakPtr(const WeakPtr& other) {
        this->w_ptr = other.w_ptr;
        this->w_count = other.w_count;
    }
    ~WeakPtr() {
        w_ptr = nullptr;
        w_count = nullptr;
    }

    WeakPtr& operator=(WeakPtr&& tmp) {
        w_ptr = tmp.w_ptr;
        w_count = tmp.w_count;
        delete tmp.w_ptr;
        delete tmp.w_count;
        tmp.w_ptr = nullptr;
        tmp.w_count = nullptr;
        return *this;
    }

    bool IsExpired() {
        if (w_ptr == nullptr) {
            w_ptr = nullptr;
            return true;
        }
        if (*w_count == 0) {
            w_ptr = nullptr;
            return true;
        }
        return false;
    }

    SharedPtr Lock() {
        SharedPtr new_ptr(w_ptr, w_count);
        return new_ptr;
    }
    WeakPtr& operator=(const WeakPtr& other) {
        this->w_ptr = other.w_ptr;
        this->w_count = other.w_count;
        return *this;
    }
    std::string* w_ptr = nullptr;
    int* w_count = nullptr;
};

SharedPtr::SharedPtr(const WeakPtr& rhs) {
    s_ptr = rhs.w_ptr;
    count = rhs.w_count;
}