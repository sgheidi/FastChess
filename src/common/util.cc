#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "util.h"

void take_screenshot(const sf::RenderWindow& window, const std::string& filename) {
  sf::Texture texture;
  texture.create(window.getSize().x, window.getSize().y);
  texture.update(window);
  texture.copyToImage().saveToFile(filename) ? std::cout << "screenshot saved to " << filename << std::endl :
      std::cout << "Failed to capture screen" << std::endl;
}

void print_map(const std::map<std::string, std::vector<std::vector<int>>>& m) {
  for (const auto& [k, v] : m) {
    std::cout << k << std::endl;
    print_v2(v);
  }
}

std::string str(const int& n) {
  return std::to_string(n);
}

void print(const std::string& s) {
  std::cout << s << std::endl;
}

// This function removes any elements in v1 that are in v2.
// implemented as a reference, no need to return anything here
void filter2(std::vector<std::vector<int>>& v1, const std::vector<std::vector<int>>& v2) {
  for (int i=0;i<v1.size();i++) {
    if (in(v2, v1[i])) {
      v1.erase(v1.begin() + i);
      i--;
    }
  }
}

// This function removes any elements in v1 that are not in v2.
// implemented as a reference, no need to return anything here
void filter(std::vector<std::vector<int>>& v1, const std::vector<std::vector<int>>& v2) {
  for (int i=0;i<v1.size();i++) {
    if (!in(v2, v1[i])) {
      v1.erase(v1.begin() + i);
      i--;
    }
  }
}

void print_v3(std::vector<std::vector<std::vector<int>>> v) {
  printf("vec3d...\n");
  for (int i=0;i<v.size();i++) {
    for (int k=0;k<v[i].size();k++) {
      for (int j=0;j<v[i][k].size();j++) {
        printf("%d", v[i][k][j]);
      }
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void print_v2(std::vector<std::vector<int>> v) {
  printf("vec2d...\n");
  for (int i=0;i<v.size();i++) {
    for (int k=0;k<v[i].size();k++) {
      printf("%d", v[i][k]);
    }
    printf(" ");
  }
  printf("\n");
}

// return true if 1d vector in 2d vector
bool in(std::vector<std::vector<int>> v, const std::vector<int> item) {
  return std::find(v.begin(), v.end(), item) != v.end() ? true : false;
}
