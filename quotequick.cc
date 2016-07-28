#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>  /* for srand, rand */
#include <string.h>


using namespace std;


string get_random_vector_elem(vector<string> & vect) {
  int vect_length = vect.size();

  if (vect_length == 0) {
    throw "vector is empty";
  } else if (vect_length == 1) {
    return vect.at(0);
  } else {
    srand( time(nullptr) ); // make the number random actually random
    return vect.at(rand() % vect_length);
  }
}


int main() {
  string filename, quote, line, line_seperator;
  vector<string> quotes;

  bool quote_exists = false;

  quote = "";
  line_seperator = "===";
  filename = "quotes.txt";

  ifstream quotefile (filename);

  if (quotefile.is_open()) {
    while (!quotefile.eof()){
      getline (quotefile, line);

      if (quote == "" && line == line_seperator) {
        // start of a new quote
        quote_exists = false;
      } else if (line != line_seperator && !line.empty()) {
        quote_exists = true;
      }

      // end of quote
      if (line == line_seperator) {
        if (quote != "") {
          quotes.push_back(quote);
        }
        quote = "";
        continue;
      } else if (!line.empty()) {
        // add line to the quote
        if (quote != "") {
          quote += " " + line;
        } else {
          quote = line;
        }
      }
    }
    if (quote_exists) {
      quotes.push_back(quote);
    }
  } else {
    cout << "There was an error opening file: " << filename << endl;
    exit(1);
  }

  if (quotes.empty()) {
    cout << "Looks like there are no valid quotes in file: " << filename << endl;
    exit(1);
  } else {
    cout << get_random_vector_elem(quotes) << endl;
  }
  return 0;
}
