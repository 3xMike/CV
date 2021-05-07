#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>
using namespace std;

class InvertedIndex { //��������� �����. ������ ���������� ��� ������� ����� �������� ����������� � ������������� � �������� �����������
public:
  void Add(string document); //move �������� � ��� ��� ����� ��������
  vector<size_t> Lookup(const string& word) const; // �� ����� ����� ���� ��� �����

  const string& GetDocument(size_t id) const {//���������� ���
    return docs[id];
  }

  size_t Size() const{
	  return docs.size();
  }
private:
  // ������� �����
  //������ ����� ���� ������, ���� �������, � � ������ ������ � ����� � ���� �������������
  map<string, vector<size_t>> index; // ������� ����� ���� ��� ����������, ����� ���� �� ��������� ��� (docid = docs[id]), ������� �� ������
  vector<string> docs; // ��������� ������ // ���� MOVE
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input); // ����� UpdateDocumentBase
  void UpdateDocumentBase(istream& document_input); // ��������� index ����������� �� ������
  void AddQueriesStream(istream& query_input, ostream& search_results_output); // ������� �����

private:
  InvertedIndex index; // ��������� ����� // ������� �����
};
