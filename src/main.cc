#include <iostream>
#include <string>
#include "glob.h"

bool GlobMatch(const std::string& pattern, const std::string& str) {
  size_t px = 0;
  size_t nx = 0;
  size_t next_px = 0;
  size_t next_nx = 0;

  while (px < pattern.length() || nx < str.length()) {
    if (px < pattern.length()) {
      char c = pattern[px];
      switch (c) {
        case '?': {
          if (nx < str.length()) {
            ++nx;
            ++px;
            continue;
          }
          break;
        }

        case '*': {
          next_px = px;
          next_nx = nx + 1;
          ++px;
          continue;
          break;
        }

        default: {
          if (nx < str.length() && str[nx] == c) {
            ++px;
            ++nx;
            continue;
          }
          break;
        }
      }
    }

    if (0 < next_nx && next_nx <= str.length()) {
			px = next_px;
			nx = next_nx;
			continue;
		}
    return false;
  }

  return true;
}

bool TestGlob(const std::string& pattern, const std::string& str) {
  Glob glob;
  glob.Parser(pattern);
  return glob.GetAutomato().Exec(str);
}

void PrintTokens(const std::string& str) {
  Lexer l(str);
  std::vector<Token> tokens = l.Scanner();
  for (auto& token : tokens) {
    std::cout << token << " ";
  }
  std::cout << "\n";
}

int main(int argc, char **argv) {
  // std::cout << "'te*', 'teste' -> " << GlobMatch("te*", "teste") << std::endl;
  // std::cout << "'tea*', 'teste' -> " << GlobMatch("tea*", "teste") << std::endl;
  // std::cout << "'test?', 'teste' -> " << GlobMatch("test?", "teste") << std::endl;
  // std::cout << "'te?te', 'texte' -> " << GlobMatch("te?te", "texte") << std::endl;
  // std::cout << "'te?*', 'te' -> " << GlobMatch("te?*", "te") << std::endl;
  // std::cout << "'te?*', 'tesa' -> " << GlobMatch("te?*", "tesa") << std::endl;
  // std::cout << "'teste*', 'teste1' -> " << GlobMatch("te?*", "tesa") << std::endl;
  // std::cout << "'teste*', 'teste' -> " << GlobMatch("te?*", "tesa") << std::endl;
  // std::cout << "'tes*a*c*', 'teste_xfdsr_crdsd' -> " << GlobMatch("tes*a*c*", "teste_xfdsr_crdsd") << std::endl;
  // std::cout << "'tes*a*c*', 'teste_afdsr_crdsd' -> " << GlobMatch("tes*a*c*", "teste_afdsr_crdsd") << std::endl;
  // std::cout << "'te**te', 'tete' -> " << GlobMatch("te**te", "tete") << std::endl;
  // std::cout << "-----------------------------------\n";
  // std::cout << "'te*', 'teste' -> " << TestGlob("te*", "teste") << std::endl;
  // std::cout << "'tea*', 'teste' -> " << TestGlob("tea*", "teste") << std::endl;
  // std::cout << "'test?', 'teste' -> " << TestGlob("test?", "teste") << std::endl;
  // std::cout << "'te?te', 'texte' -> " << TestGlob("te?te", "texte") << std::endl;
  // std::cout << "'te?*', 'te' -> " << TestGlob("te?*", "te") << std::endl;
  // std::cout << "'te?*', 'tesa' -> " << TestGlob("te?*", "tesa") << std::endl;
  // std::cout << "'teste*', 'teste1' -> " << TestGlob("te?*", "tesa") << std::endl;
  // std::cout << "'teste*', 'teste' -> " << TestGlob("te?*", "tesa") << std::endl;
  // std::cout << "'tes*a*c*', 'teste_xfdsr_crdsd' -> " << TestGlob("tes*a*c*", "teste_xfdsr_crdsd") << std::endl;
  // std::cout << "'tes*a*c*', 'teste_afdsr_crdsd' -> " << TestGlob("tes*a*c*", "teste_afdsr_crdsd") << std::endl;
  // std::cout << "'te**te', 'tete' -> " << TestGlob("te**te", "tete") << std::endl;

  PrintTokens("te*e");
  PrintTokens("te+[a-z]?sd");
  PrintTokens("te+[^a-z]");
  PrintTokens("te*(as|sd[jpg])");
  return 0;
}
