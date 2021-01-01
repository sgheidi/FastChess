#include "util.h"

void take_screenshot(const sf::RenderWindow& window, const std::string& filename) {
  sf::Texture texture;
  texture.create(window.getSize().x, window.getSize().y);
  texture.update(window);
  if (texture.copyToImage().saveToFile(filename))
    std::cout << "screenshot saved to " << filename << std::endl;
  else
    std::cout << "Failed to capture screen" << std::endl;
}

void print_map(std::map<std::string, std::vector<std::vector<int>>> map) {
  for (std::map<std::string, std::vector<std::vector<int>>>::iterator itr=map.begin();itr!=map.end();itr++) {
    std::cout << itr->first << std::endl;
    print_v2(itr->second);
  }
}

std::string str(int n) {
  return std::to_string(n);
}

void print(std::string s) {
  std::cout << s << std::endl;
}

// This function removes any elements in v1 that are in v2
std::vector<std::vector<int>>
filter2(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2) {
  for (int i=0;i<v1.size();i++) {
    if (in(v2, v1[i])) {
      v1.erase(v1.begin() + i);
      i--;
    }
  }
  return v1;
}

// This function removes any elements in v1 that are not in v2
std::vector<std::vector<int>>
filter(std::vector<std::vector<int>> v1, std::vector<std::vector<int>> v2) {
  for (int i=0;i<v1.size();i++) {
    if (!in(v2, v1[i])) {
      v1.erase(v1.begin() + i);
      i--;
    }
  }
  return v1;
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
bool in(std::vector<std::vector<int>> v, std::vector<int> item) {
  if (std::find(v.begin(), v.end(), item) != v.end())
    return true;
  return false;
}
