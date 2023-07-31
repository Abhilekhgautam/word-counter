#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void print_count(std::unordered_map<std::string, int> word_counter){
   for (const auto& [word, count]: word_counter){
      std::cout << word << ":" << count << '\n';	   
   }	
}

static const std::vector<char> syms{' ', '#', '.', ',', ';', '&', '{', '}', ']', '[', '\n', '(', ')', '\t', '<', '>', '+', '-', '=', '"',':' };
bool contains_symbol(char temp_char){
 for (auto& elt: syms){
    if(temp_char == elt) return true;	 
 }
  return false;
}
int main(int argc, char **argv){
   char *program = argv[0];
   if(argc != 2){
     std::cerr << "Error: Invalid Argument List\n";
     std::cerr << "Usage: " << program << " <input_file>\n";
     std::exit(1);
   }	
   char *input_file_path = argv[1];

   if(!fs::exists(input_file_path)){
      std::cerr << "Error " << input_file_path << " : Not a file\n";
      std::exit(1);
   }

   std::ifstream input_file(input_file_path);

   if(input_file.is_open()){
      std::unordered_map<std::string, int> word_counter;
      char temp_byte;
      std::string word;
      while(input_file.good()){
	temp_byte = input_file.get();
	if(!contains_symbol(temp_byte))
	  word += temp_byte;
	else {
	if(word.length() == 0) continue;
	 auto found = word_counter.find(word);
	 if(found == word_counter.end()){
	   word_counter.emplace(word, 1); 	 
	   word.clear();
	 }
	 else{
	  //increase the count ..
	   word_counter[word] = word_counter[word] + 1;
	   // clear the word
	   word.clear();
	 }
	}
	
      }
      print_count(word_counter);

   } else {
     std::cerr << "Something Went Wrong: Couldn't open: " << input_file_path;	   
     std::exit(1);
   }
  return 0; //happy compiler :)
}
