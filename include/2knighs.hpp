#pragma once

#include <iterator>
#include <utility>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <vector>
#include <cassert>
#include <memory>
#include <Path.hpp>

namespace TwoKnights 
{

    bool findCombinations(const std::vector<int>& numbers, int target, std::vector<int>& currentCombination, int index);

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

        Path<int> path;
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

                auto [ones, twos] = this->path.stats();

                while (not this->canReachTarget(twos, ones, ydist)) {
                    
                    this->path.extend();
                    std::tie(ones, twos) = this->path.stats();
                }

                path_t _lc;

                std::vector<int> _l(this->path.rbegin(), this->path.rend());

                findCombinations(_l, ydist, _lc, 0); //сделать через итераторы
                
                this->setXAxiPath(std::make_shared<path_t>(this->path.begin(), this->path.end()));
                this->setYAxiPath(std::make_shared<path_t>(_lc.begin(), _lc.end()));
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

