#include "../include/streamcc_test.h"
#define BOOST_TEST_MODULE ClassTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <random>
#include <map>
#include <iostream>




std::mt19937 gen;


BOOST_AUTO_TEST_CASE(CountSketch_Test) {
  Scc::CountSketch<int> cs(100, 20);
  std::discrete_distribution<int> dist {100, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  std::map<int, int> real; // to keep the actual frequencies

  for (int i = 0; i < 100000; ++i) {
    int p = dist(gen);
    cs.processItem(p);
    real[p] += 1;
  }
  
  // now check the frequencies
  for (int i = 0; i < 15 ; ++i) {
    BOOST_CHECK(cs.estTotWeight(i) == real[i]);
  }
}


BOOST_AUTO_TEST_CASE(CountMin_Test) {
  Scc::CountMin<int> cm(100, 20);
  std::discrete_distribution<int> dist {100, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  std::map<int, int> real; // to keep the actual frequencies

  for (int i = 0; i < 100000; ++i) {
    int p = dist(gen);
    cm.processItem(p);
    real[p] += 1;
  }
  
  // now check the frequencies
  for (int i = 0; i < 15 ; ++i) {
    BOOST_CHECK(cm.estTotWeight(i) == real[i]);
  }
}



BOOST_AUTO_TEST_CASE(DistinctCounter_Test) {
  Scc::DistinctCounter<int> f0(100);
  for (int i = 0; i < 10000; ++i) {
    for (int j = 0; j < 10; ++j)
      f0.processItem(i);
  }
  int estF0 = f0.getEstDistinct();
  BOOST_CHECK(estF0 < 10000 * 1.1);
  BOOST_CHECK(estF0 > 10000 * 0.9);  
}

BOOST_AUTO_TEST_CASE(Zeros_Test) {
  BOOST_CHECK(utils::zeros(1 << 30) == 1);
  BOOST_CHECK(utils::zeros(1 << 10) == 21);
  BOOST_CHECK(utils::zeros(101 << 29) == 0);
}


















