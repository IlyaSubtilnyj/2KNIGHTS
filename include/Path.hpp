#pragma once

#include <list>
#include <deque>
#include <cmath>
#include <utility>
#include <iterator>

namespace TwoKnights
{

    enum STEP: int {
        TINY = 0b0001,
        LONG = 0b0010,
    };

    STEP convert_step(STEP step);

    template<typename T>
    class Iterator {
    public:

        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;

        Iterator(pointer ptr) 
            : ptr(ptr) 
        {}

        reference operator*() { 
            return *ptr; 
        }

        Iterator& operator++() { 
            ptr++; 
            return *this; 
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ptr++;
            return temp;
        }

        bool operator==(const Iterator& other) const { 
            return ptr == other.ptr; 
        }

        bool operator!=(const Iterator& other) const { 
            return ptr != other.ptr; 
        }

    private:
        pointer ptr;
    };

    template<typename T>
    class Path {
    public:
        using path_t = std::deque<T>;
    private:
        int __border;
        path_t __path;
        path_t __rpath;
    protected:
        path_t& path() {
            return this->__path;
        }
        path_t& rpath() {
            return this->__rpath;
        }
    public:
        Path() = default;
        Path(int dist) {
            this->initNewPath(dist);
        }
        void to(int dist) {
            this->initNewPath(dist);
        }
        void extend() {
            
            this->__path.push_back(STEP::TINY);
            this->__path.push_back(STEP::TINY);
            this->__path.pop_front();
            this->__border--;
            this->reverse();
        }
        std::pair<int, int> stats() {

            return {
                this->__path.size() - this->__border,
                this->__border
            };
        }

        Iterator<T> begin() {
            return Iterator(&(*this->path().begin()));
        }
        Iterator<T> end() {
            return Iterator(&(*this->path().end())); //maybe back or something
        }
        Iterator<T> rbegin() {
            return Iterator<T>(&(*this->rpath().begin())); 
        }
        Iterator<T> rend() { 
            return Iterator<T>(&(*this->rpath().end())); 
        }
    private:
        void reverse() {

            this->rpath().clear();
            for(auto it = this->path().begin(); it != this->path().end(); ++it) {

                this->rpath().push_back(convert_step(static_cast<STEP>(*it)));
            }
        }
        void initNewPath(int dist) {

            auto& p = this->path();

            auto dummy = std::floor(dist / STEP::LONG);
            this->__border = dummy;
            for(int i = 0; i < dummy; i++) {

                p.push_back(STEP::LONG);
            }
            if(dist % STEP::LONG) {

                this->__border++;
                p.push_back(STEP::TINY);
            }
        }
    };
}
