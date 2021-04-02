#include <bits/stdc++.h>
using namespace std;
#define f1(n) for (int i = 0; i < n; i++)
#define f2(n) for (int j = 0; j < n; j++)
vector<char> small = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
vector<char> capital = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int solve(set<string> s, map<char, int> assign)
{
  int count = 0;
  set<string>::iterator itr1;
  for (itr1 = s.begin(); itr1 != s.end(); itr1++)
  {
    string t = *itr1;
    for (int i = 0; i < t.length(); i++)
    {
      int value = assign[t[i]];
      if (value == 1)
      {
        count++;
        break;
      }
    }
  }
  return count;
}

bool is_present(vector<int> v, int x)
{
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i] == x)
    {
      return true;
    }
  }
  return false;
}

void beam_search(vector<map<char, int>> &bAssigns, vector<string> &beam_penetration, set<string> problem, map<char, int> assign, int b, int stepsize)
{
  map<char, int> bestAssign = assign;
  map<char, int> editAssign = assign;
  int c;
  vector<int> assignValues;
  vector<char> assignkeys;
  map<char, int>::iterator itr;
  for (itr = assign.begin(); itr != assign.end(); itr++)
  {
    assignValues.push_back(itr->second);
    assignkeys.push_back(itr->first);
  }
  vector<int> steps;
  vector<map<char, int>> possibleAssigns;
  vector<int> possibleScores;
  int initial = solve(problem, assign);
  string p;
  if (initial == problem.size())
  {
    p = to_string(stepsize) + "/" + to_string(stepsize);
    bAssigns.push_back(assign);
    beam_penetration.push_back(p);
  }
  for (int i = 0; i < assignValues.size(); i++)
  {
    stepsize++;
    editAssign[assignkeys[i]] = abs(assignValues[i] - 1);
    c = solve(problem, editAssign);
    possibleAssigns.push_back(editAssign);
    possibleScores.push_back(c);
    steps.push_back(stepsize);
  }
  sort(possibleScores.begin(), possibleScores.end());
  vector<int> selected;
  int i = possibleScores.size() - b;
  while (i < possibleScores.size())
  {
    selected.push_back(possibleScores[i]);
    i++;
  }
  vector<int> index;
  map<char, int> selectedAssign;
  if (is_present(possibleScores, problem.size()))
  {
    for (int i = 0; i < possibleScores.size(); i++)
    {
      if (possibleScores[i] == problem.size())
      {
        index.push_back(i);
      }
    }
    p = to_string(steps[index[0]]) + "/" + to_string(steps[index[0]]);
    bAssigns.push_back(possibleAssigns[index[0]]);
    beam_penetration.push_back(p);
  }
  else
  {
    for (int i = 0; i < selected.size(); i++)
    {
      selectedAssign = possibleAssigns[i];
      beam_search(bAssigns, beam_penetration, problem, selectedAssign, b + 1, stepsize);
    }
  }
}
void variable_Neighbour(vector<map<char, int>> &vAssigns, vector<string> &var_penetration, vector<int> &bvar, set<string> problem, map<char, int> assign, int b, int step)
{
  map<char, int> bestAssign = assign;
  map<char, int> editAssign = assign;
  int c;
  vector<int> assignValues;
  vector<char> assignkeys;
  map<char, int>::iterator itr;
  for (itr = assign.begin(); itr != assign.end(); itr++)
  {
    assignValues.push_back(itr->second);
    assignkeys.push_back(itr->first);
  }
  vector<int> steps;
  vector<map<char, int>> possibleAssigns;
  vector<int> possibleScores;
  int initial = solve(problem, assign);
  string p;
  if (initial == problem.size())
  {
    p = to_string(step) + "/" + to_string(step);
    vAssigns.push_back(assign);
    var_penetration.push_back(p);
    bvar.push_back(b);
  }
  for (int i = 0; i < assignValues.size(); i++)
  {
    step++;
    editAssign[assignkeys[i]] = abs(assignValues[i] - 1);
    c = solve(problem, editAssign);
    possibleAssigns.push_back(editAssign);
    possibleScores.push_back(c);
    steps.push_back(step);
  }
  sort(possibleScores.begin(), possibleScores.end());
  vector<int> selected;
  int i = possibleScores.size() - b;
  while (i < possibleScores.size())
  {
    selected.push_back(possibleScores[i]);
    i++;
  }
  vector<int> index;
  map<char, int> selectedAssign;
  if (is_present(possibleScores, problem.size()))
  {
    for (int i = 0; i < possibleScores.size(); i++)
    {
      if (possibleScores[i] == problem.size())
      {
        index.push_back(i);
      }
    }
    p = to_string(steps[index[0]]) + "/" + to_string(steps[index[0]]);
    vAssigns.push_back(possibleAssigns[index[0]]);
    var_penetration.push_back(p);
    bvar.push_back(b);
  }
  else
  {
    for (int i = 0; i < selected.size(); i++)
    {
      selectedAssign = possibleAssigns[i];
      variable_Neighbour(vAssigns, var_penetration, bvar, problem, selectedAssign, b + 1, step);
    }
  }
}
void hill_climbing(vector<map<char, int>> &hAssigns, vector<int> &h_n, vector<string> &hill_penetration, set<string> problem, map<char, int> assign, int parentNum, int rec, int step)
{
  map<char, int> bestAssign = assign;
  vector<char> assignkeys;
  vector<int> assignvalues;
  for (auto i : assign)
  {
    assignkeys.push_back(i.first);
    assignvalues.push_back(i.second);
  }
  map<char, int> maxAssign;
  map<char, int> editAssign;
  int maxnum = parentNum;
  maxAssign = assign;
  map<char, int>::iterator ir;
  editAssign = assign;
  for (int i = 0; i < assignvalues.size(); i++)
  {
    step += 1;
    editAssign[assign[i]] = abs(assignvalues[i] - 1);
    int c = solve(problem, editAssign);
    if (maxnum < c)
    {
      rec = step;
      maxnum = c;
      maxAssign = editAssign;
    }
  }
  if (maxnum == parentNum)
  {
    string s = to_string(rec) + "/" + to_string(step - assignvalues.size());
    hAssigns.push_back(bestAssign);
    h_n.push_back(maxnum);
    hill_penetration.push_back(s);
    return;
  }
  else
  {
    parentNum = maxnum;
    bestAssign = maxAssign;
    return hill_climbing(hAssigns, h_n, hill_penetration, problem, bestAssign, parentNum, rec, step);
  }
}
map<char, int> assignment(vector<char> problem, int n)
{
  vector<char> positive, negative;
  map<char, int> assign;
  map<char, int>::iterator itra;
  vector<char> variable;
  f1(n)
  {
    positive.push_back(small[i]);
    negative.push_back(capital[i]);
  }
  f1(n)
  {
    variable.push_back(positive[i]);
  }
  f1(n)
  {
    variable.push_back(negative[i]);
  }
  f1(n)
  {
    int a = rand() % 2;
    assign[positive[i]] = a;
  }
  int index = 0;
  for (itra = assign.begin(); itra != assign.end(); itra++)
  {
    int a = itra->second;
    assign[negative[index]] = abs(1 - a);
    index++;
  }
  return assign;
}
void printKLengthString(vector<string> &problem, vector<char> set, string sequence, int n, int k)
{
  vector<string> res;
  if (k == 0)
  {
    problem.push_back(sequence);

    return;
  }
  for (int i = 0; i < n; i++)
  {
    string newSequence;
    newSequence = sequence + set[i];
    printKLengthString(problem, set, newSequence, n, k - 1);
  }
}
int main()
{
  cout << "Enter the number of clauses: ";
  int m;
  cin >> m;
  cout << "Enter the number of variables in a clause: ";
  int k;
  cin >> k;
  cout << "Enter number of variables: ";
  int n;
  cin >> n;
  vector<char> positive, negative;
  set<string> s;
  map<char, int> assign;
  f1(n)
  {
    positive.push_back(small[i]);
    negative.push_back(capital[i]);
  }
  vector<char> variable;
  f1(n)
  {
    variable.push_back(positive[i]);
  }
  f1(n)
  {
    variable.push_back(negative[i]);
  }
  //**create problem**//
  vector<string> problem;
  printKLengthString(problem, variable, "", 2 * n, k);
  int threshold = 20;
  set<set<string>> c;
  set<int> index2;
  set<int>::iterator itr;
  srand(time(0));
  while (threshold--)
  {
    while (index2.size() != k)
    {
      int v = rand() % problem.size();
      index2.insert(v);
    }
    itr = index2.begin();
    set<string> temp;

    while (!index2.empty())
    {
      temp.insert(problem[*itr]);
      index2.erase(*itr);
      itr = index2.begin();
    }
    c.insert(temp);

    index2.clear();
  }
  set<set<string>>::iterator itr3;
  set<string>::iterator itr4;
  vector<map<char, int>> hAssigns;
  vector<map<char, int>> assigns;
  vector<int> h_n;
  vector<int> initials;
  vector<string> hill_penetration;
  vector<map<char, int>> vAssigns;
  vector<string> var_penetration;
  vector<int> bvar;
  vector<map<char, int>> bAssigns;
  vector<string> beam_penetration;
  vector<map<char, int>> bAssigns2;
  vector<string> beam_penetration2;
  int i = 0;
  for (itr3 = c.begin(); itr3 != c.end(); itr3++)
  {
    map<char, int> map2;
    map2 = assignment(variable, n);
    map<char, int>::iterator ir;
    int initial = solve(*itr3, map2);
    hill_climbing(hAssigns, h_n, hill_penetration, *itr3, map2, initial, 1, 1);
    cout << "Problem " << i << "= (";
    for (itr4 = itr3->begin(); itr4 != itr3->end(); itr4++)
    {
      cout << "(" << *(itr4) << ")";
    }
    cout << ")";
    cout << "\nHill Climbing:";
    map<char, int>::iterator itr;
    for (itr = hAssigns[i].begin(); itr != hAssigns[i].end(); itr++)
    {
      cout << itr->first << "->" << itr->second << " ";
    }
    cout << "\nPenetrance" << hill_penetration[i] << endl;
    variable_Neighbour(vAssigns, var_penetration, bvar, *itr3, map2, 1, 1);
    cout << "Variable-neighbourhood:";
    for (itr = vAssigns[i].begin(); itr != vAssigns[i].end(); itr++)
    {

      cout << itr->first << "->" << itr->second << " ";
    }
    cout << endl;
    cout << "Penetrance" << var_penetration[i] << endl;
    beam_search(bAssigns, beam_penetration, *itr3, map2, 3, 1);
    beam_search(bAssigns2, beam_penetration2, *itr3, map2, 4, 1);
    cout << "Beam Search for b=" << 3 << ": ";
    for (itr = bAssigns[i].begin(); itr != bAssigns[i].end(); itr++)
    {
      cout << itr->first << "->" << itr->second << " ";
    }
    cout << "\nPenetrance" << beam_penetration[i] << endl;
    cout << "Beam Search for b=" << 4 << ": ";
    for (itr = bAssigns2[i].begin(); itr != bAssigns2[i].end(); itr++)
    {

      cout << itr->first << "->" << itr->second << " ";
    }
    cout << "\nPenetrance" << beam_penetration2[i] << endl;
    cout << endl;
    i += 1;
  }
}