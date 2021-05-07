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

class InvertedIndex { //хранилище доков. Список документов для каждого слова ускоряет асимптотику и искпользуется в реальных поисковиках
public:
  void Add(string document); //move документ и все его слова записать
  vector<size_t> Lookup(const string& word) const; // по слову выдаёт лист его доков

  const string& GetDocument(size_t id) const {//возвращает док
    return docs[id];
  }

  size_t Size() const{
	  return docs.size();
  }
private:
  // ВОПРОСЫ ЗДЕСЬ
  //вместо листа либо вектор, либо словарь, т к пихаем только в конец и надо итерироваться
  map<string, vector<size_t>> index; // каждому слову лист его документов, может быть по несколько раз (docid = docs[id]), поменял на вектор
  vector<string> docs; // документы внутри // СЮДА MOVE
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input); // копия UpdateDocumentBase
  void UpdateDocumentBase(istream& document_input); // заполняет index документами из потока
  void AddQueriesStream(istream& query_input, ostream& search_results_output); // ВОПРОСЫ ЗДЕСЬ

private:
  InvertedIndex index; // хранилище доков // ВОПРОСЫ ЗДЕСЬ
};
