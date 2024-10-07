#pragma once

#include <iterator>
#include <utility>
#include <list>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <vector>
#include <cassert>
#include <memory>

namespace TwoKnights 
{

    //заимплементить итератор
    class Path {
        public:
        using path_t = std::list<int>;
        enum STEP: int {
            TINY = 0b0001,
            LONG = 0b0010,
        };
        private:
        int __stepsCount;
        int __firstshortStep;
        path_t __shortestXAxisPath;
        protected:
        path_t& path() {
            return this->__shortestXAxisPath;
        }

        public:

        Path() = default;

        Path(int dist)
        {
            this->initNewPath(dist);
        }

        void to(int dist) {
            this->initNewPath(dist);
        }

        private:

        void initNewPath(int dist) {

            auto& p = this->path();
            
            auto dummy = std::floor(dist / STEP::LONG);

            this->__stepsCount      = dummy;
            this->__firstshortStep  = dummy + 1;

            p.assign(dummy, STEP::LONG);

            if(dist % STEP::LONG) {

                this->__stepsCount++;
                this->__firstshortStep++;
                p.push_back(STEP::TINY);
            }
        }

        public:
        void extend() {

            auto& p = this->path();

            auto it = p.begin();
            std::advance(it, __firstshortStep - 1 - 1);
            
            p.insert(it, 1);
            p.insert(it, 1);
            p.erase(it);

            this->__stepsCount++;
            this->__firstshortStep--;
        }

        std::pair<int, int> stats(bool reverse = false) {

            std::pair<int, int> result{
                this->__stepsCount - (this->__firstshortStep - 1),
                this->__firstshortStep - 1
            };

            if(reverse) {

                std::swap(result.first, result.second);
            }
            
            return result;
        }

        std::vector<int> get() {

            auto& p = this->path();
            return {p.begin(), p.end()};
        }

        std::vector<int> reverse() {

            std::vector<int> res(this->__stepsCount);
            auto& p = this->path();
            std::transform(p.begin(), p.end(), res.begin(), [this](int value) -> int {
                return this->reverseStep(static_cast<STEP>(value));
            });

            return res;
        }

        STEP reverseStep(STEP step) {

            return static_cast<STEP>(step xor 0b0011);
        }
    };

    class Solution {
        
        /**
         * Aliases
         */
        public:

        using coor_t = int32_t;
        using path_t = std::vector<int>;
        using path_ptr_t = std::shared_ptr<path_t>;

        /**
         * Results, its setters and getters
         */
        private: //results

        path_ptr_t __xAliasPath;
        path_ptr_t __yAliasPath;

        public: //results getters

        path_ptr_t getXAxiPath() const {
            return this->__xAliasPath;
        }

        path_ptr_t getYAxiPath() const {
            return this->__yAliasPath;
        }

        protected: //result setters

        void setXAxiPath(path_ptr_t path) {
            this->__xAliasPath = path;
        }

        void setYAxiPath(path_ptr_t&& path) {
            this->__yAliasPath = path;
        }

        /**
         * Constructors and assignments
         */
        public:

        Solution(coor_t x1, coor_t y1, coor_t x2, coor_t y2)
            :
            _kx(x1, x2),
            _ky(y1, y2),
            path()
        {}

        Solution(const Solution &src) = delete;

        Solution(Solution &&src) = delete;

        Solution& operator=(const Solution &rhs) = delete;

        Solution& operator=(Solution &&rhs) = delete;

        /**
         * Implementation
         */
        private:

        Path path;
        std::pair<coor_t, coor_t> _kx;
        std::pair<coor_t, coor_t> _ky;
        
        coor_t _M;
        coor_t _N;
        
        std::list<int> _g;
        
        private:
        
        std::pair<coor_t, coor_t> _getModelCoor() {
        
            return std::make_pair(
                std::abs(this->_kx.second - this->_kx.first), 
                std::abs(this->_ky.second - this->_ky.first)
            );
        }
        
        public:
        
        void Get() {
            
            auto modelCoor = this->_getModelCoor();
            return this->fill(modelCoor.first, modelCoor.second);
        }
        
        void fill(coor_t xdist, coor_t ydist) {

            this->path.to(xdist);

            std::pair<int, int> stats = this->path.stats(true);

            while (not this->canReachTarget(stats.first, stats.second, ydist)) {
                
                this->path.extend();
                stats = this->path.stats(true);
            }

            path_t _lc;

            this->findCombinations(this->path.reverse(), ydist, _lc, 0); //сделать через итераторы
            
            this->setXAxiPath(std::make_shared<path_t>(this->path.get())); //сделать через итераторы
            this->setYAxiPath(std::make_shared<path_t>(_lc.begin(), _lc.end()));
        }
        
        bool findCombinations(const path_t& numbers, int target, path_t& currentCombination, int index) const {
            
            if (index == numbers.size()) {
                int total = 0;
                for (int num : currentCombination) {
                    total += num;
                }
                return total == target;
            }
        
            // Рассмотрим текущий элемент с плюсом
            currentCombination.push_back(numbers[index]);
            if (findCombinations(numbers, target, currentCombination, index + 1)) {
                return true;
            }
            currentCombination.pop_back();
        
            // Рассмотрим текущий элемент с минусом
            currentCombination.push_back(-numbers[index]);
            if (findCombinations(numbers, target, currentCombination, index + 1)) {
                return true;
            }
            currentCombination.pop_back();
        
            return false; // Если ни один из вариантов не подошел
        }

        private:

        bool canReachTarget(int countOf1, int countOf2, int target) const {
            
            auto maxSum = countOf1 + 2 * countOf2;
        
            if (target > maxSum) {
                return false;
            }
        
            if ((target % 2) != (maxSum % 2)) {
                return false;
            }
            
            return true;
        }
    };
}

