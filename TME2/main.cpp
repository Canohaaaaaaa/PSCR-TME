#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <iterator>
#include "HashMap.hh"
/*
Question 1.1
Il y a 566193 mots
Question 1.2
Il y a 20333 mots différents
Question 1.3
war : 298
peace : 114
Question 1.4
Trés mauvaise complexité, la recherche dans une liste (vector) est en O(n)
Pour un texte de n mots notre algorithme est en O(n²), la recherche des mots est trop couteuse
*/

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	//HashMap<string, int> unique;
	vector<pair<string, int>> unique;
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		bool trouve = false;
		for(pair<string, int>& paire : unique){
			if(paire.first == word){
				paire.second += 1;
				trouve = true;
			}
		}
		if(!trouve){
			pair<string, int> nouvelle_paire(word, 1);
			unique.push_back(nouvelle_paire);
		}

		/*
		int *valeur = unique.get(word);
		if(valeur){
			(*valeur)++;
		}
		else{
			unique.put(word, 1);
		}
		*/
		// word est maintenant "tout propre"
		/*
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		*/
	}
	input.close();
	/*
	for(const pair<string, int> paire : unique){
		if(paire.first == "war" || paire.first == "peace" || paire.first == "toto" ){
			cout << paire.first << " : " << paire.second << endl;
		}
	}
	*/
	cout << "Finished Parsing War and Peace" << endl;
	cout << "Taille :" << count(unique.begin(), unique.end()) << endl;
	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;

    return 0;
}


