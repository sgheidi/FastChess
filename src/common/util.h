#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

void take_screenshot(const sf::RenderWindow& window, const std::string& filename);
void init(std::string env);
std::string str(int n);
void print_map(std::map<std::string, std::vector<std::vector<int>>> map);
void print(std::string s);
std::vector<std::vector<int>> filter2(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2);
std::vector<std::vector<int>> filter(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2);
void print_v2(std::vector<std::vector<int>> v);
void print_v3(std::vector<std::vector<std::vector<int>>> v);
bool in(std::vector<std::vector<int>> v, std::vector<int> item);

template <typename T>
inline void print_v1(T v) {
  printf("vec1d...\n");
  for (int i=0;i<v.size();i++) {
    std::cout << v[i];
  }
  printf("\n");
}

#ifdef DEBUGAI
template <typename T>
inline void print_v1_Log(T v) {
  for (int i=0;i<v.size();i++) {
    Log << v[i];
  }
  Log << std::endl;
}
#endif

#endif // UTIL_H
