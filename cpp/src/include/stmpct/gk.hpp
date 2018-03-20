#pragma once

// The Greenwald-Khanna algorithm as defined in the paper
// Space-Efficient Online Computation of Quantile Summaries
#include <iosfwd>
#include <list>
#include <vector>
#include "stmpct.hpp"

namespace stmpct {

class gk : public stmpctalg
{
public:
    gk(double epsilon);
    virtual void insert(double v) final;
    virtual double quantile(double phi) final;

private:
    static const int MAX_BAND = 999999;

    struct tuple {
        double v;
        int g;
        int delta;

        tuple(double v, int g, int delta) : v(v), g(g), delta(delta) {}

        bool operator==(const tuple& rhs) const {
            return v == rhs.v && g == rhs.g && delta == rhs.delta;
        }
    };

#ifdef UNIT_TESTING
    friend class ::gk_unit_tests;
#endif
    friend std::ostream& operator<<(std::ostream&, const gk&);
    friend std::ostream& operator<<(std::ostream&, const gk::tuple&);

    // Even though list<tuple> has better insert/delete O(x),
    // empirical measurements show that vector<tuple> is faster.
    // In any case, we can change the data structure for tuples
    // simply by modifying the below line.  TODO: Explore using
    // multiset<tuple> instead.
    typedef std::vector<tuple> tuples_t;

    static std::vector<int> construct_band_lookup(int two_epsilon_n);
    void do_insert(double v);
    tuples_t::iterator find_insertion_index(double v);
    int determine_delta(tuples_t::iterator it);
    void compress();

    double m_epsilon;
    int m_one_over_2e;
    tuples_t m_S;
    int m_n;
};

std::ostream& operator<<(std::ostream& os, const gk& g);
std::ostream& operator<<(std::ostream& os, const gk::tuple& t);

}