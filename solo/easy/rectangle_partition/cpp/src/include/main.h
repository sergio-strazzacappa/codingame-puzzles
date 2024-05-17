#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <string>

using namespace std;

int main();
void solve(string input_file, string output_file);
int logic(int width, int height, vector<int> x, vector<int> y);
int create_subrectangles(vector<int> x, vector<int> y);
void print_map(map<int, int> m);
void check_answer(int solution, int answer, string input_file);

#endif