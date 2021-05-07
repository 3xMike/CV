#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
// ≈ƒ»Ќ—“¬≈ЌЌќ≈, „“ќ я ѕ–ќѕ”—“»Ћ
// 			!«јћ≈–я…“≈!
vector<string> SplitIntoWords(string line) {
  istringstream words_input(move(line));
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}//делит строку без \n на слова

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  for (string current_document; getline(document_input, current_document); ) {
    index.Add(move(current_document));
  }
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  vector<size_t> docid_count(index.Size()); // тут хранитьс€ число вхождений дл€ запроса документа [docid]
  for (string current_query; getline(query_input, current_query); ) { // считываем запросы
    const auto words = SplitIntoWords(current_query); // все слова в одном запросе

//    map<size_t, size_t> docid_count; // документ + число его вхождений
//    так как docid - подр€д идущие числа от 0 до index.docs.size()-1, вместо map<size_t,size_t> ебанЄм vector<size_t>

    for (auto& i : docid_count){
    	i = 0; //можно вынести за for, чтобы не выдел€ть пам€ть лишний раз
    }
    for (const auto& word : words) { // дл€ каждого слова в запросе
      for (const size_t docid : index.Lookup(word)) { // дл€ каждого дока дл€ этого слова
        docid_count[docid]++; // раньше map искал docid за log N, а теперь поиск в векторе за const
      }// теперь в словаре релевантность документов, отсортированна€ по докам
    }
    vector<pair<size_t, size_t>> search_results;
    for (size_t docid = 0; docid != docid_count.size(); ++docid){//заполнение
    	if (size_t count = docid_count[docid]; count != 0){
        	search_results.push_back(
        			make_pair(docid, count)
        	);
    	}

    }
    	//отсортировать по второму аргументу по убыванию, потом по первому по возрастанию
        // ну тут точно надо фиксить: нам не нужен полностью отсортированный список -- нам нужно только первые 5 запросов.
    	// поэтому пользуемс€ partial_sort:
    partial_sort(
      begin(search_results),
	  min(begin(search_results) + 5, end(search_results)),
      end(search_results),
      [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
//        int64_t lhs_docid = lhs.first;
//        auto lhs_hit_count = lhs.second;
//        int64_t rhs_docid = rhs.first;
//        auto rhs_hit_count = rhs.second;
        return make_pair(lhs.second, -static_cast<int64_t>(lhs.first)) > make_pair(rhs.second, -static_cast<int64_t>(rhs.first));
      }
    );


    search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(search_results, 5)) {
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;

  }
}

void InvertedIndex::Add(string document) {
  docs.push_back(move(document));

  const size_t docid = docs.size() - 1;
  for (const auto& word : SplitIntoWords(docs.back())) {
    index[word].push_back(docid);
  }
}

vector<size_t> InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}
