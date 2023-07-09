#include <iostream>
#include <string>

int countWords(const std::string& str) {
    int wordCount = 0;
    bool isWord = false;

    for (char c : str) {
        if (std::isalpha(c)) {
            if (!isWord) { // 当当前字符是字母且上一个字符是空格时
                wordCount++;
                isWord = true;
            }
        } else {
            isWord = false;
        }
    }

    return wordCount;
}

int main() {
    std::string sentence = "Hello, world! I am learning C++.";
    int words = countWords(sentence);
    std::cout << "Word count: " << words << std::endl;

    return 0;
}
