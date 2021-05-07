#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(string line) {
  istringstream words_input(move(line));
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}//äåëèò ñòðîêó áåç \n íà ñëîâà

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
  vector<size_t> docid_count(index.Size()); 
  for (string current_query; getline(query_input, current_query); ) { 
    const auto words = SplitIntoWords(current_query); 


    for (auto& i : docid_count){
    	i = 0; 
    }
    for (const auto& word : words) { 
      for (const size_t docid : index.Lookup(word)) { 
        docid_count[docid]++;
      }
    }
    vector<pair<size_t, size_t>> search_results;
    for (size_t docid = 0; docid != docid_count.size(); ++docid){
    	if (size_t count = docid_count[docid]; count != 0){
        	search_results.push_back(
        			make_pair(docid, count)
        	);
    	}

    }

    partial_sort(
      begin(search_results),
	  min(begin(search_results) + 5, end(search_results)),
      end(search_results),
      [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
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
