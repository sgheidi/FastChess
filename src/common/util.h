#ifndef COMMON_UTIL_H
#define COMMON_UTIL_H

#include <iostream>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

void take_screenshot(const sf::RenderWindow& window, const std::string& filename);
void init(const std::string& env);
std::string str(const int& n);
void print_map(std::map<std::string, std::vector<std::vector<int>>>& m);
void print(const std::string& s);
void filter2(std::vector<std::vector<int>>& v1, const std::vector<std::vector<int>>& v2);
void filter(std::vector<std::vector<int>>& v1, const std::vector<std::vector<int>>& v2);
void print_v2(std::vector<std::vector<int>> v);
void print_v3(std::vector<std::vector<std::vector<int>>> v);
bool in(std::vector<std::vector<int>> v, std::vector<int> item);

template <typename T>
inline void print_v1(T v) {
  printf("vec1d...\n");
  for (auto el : v)
    std::cout << el;
  printf("\n");
}

#ifdef DEBUGAI
template <typename T>
inline void print_v1_log(T v) {
  for (auto el : v)
    log << el;
  log << std::endl;
}
#endif

#endif // COMMON_UTIL_H
