#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

//Класс конечного автомата
class FiniteStateMachine
{
	std::vector<std::vector<int>> sigma;
	std::map<char, int> alphabet;

	size_t cmp_count;

public:
	//Конструктор
	FiniteStateMachine(const std::string & P, std::map<char, int> & alphabet) : alphabet(alphabet), cmp_count(0)
	{
		//Создание функции переходов
		sigma.resize(alphabet.size());

		//Создание автомата
		int m = P.length();
		for (int q = 0; q <= m; ++q)
			for (auto a = begin(alphabet); a != end(alphabet); ++a)
			{
				int k = std::min(m + 1, q + 2);
				do
				{
					--k;
				} while (!is_suffix(P, k, q, a->first));
				
				sigma[a->second].push_back(k);
			}
	}
	
//Возвращает значение для пары (q, a)
	int get(int q, char a) const
	{
		return sigma[alphabet.at(a)][q];
	}

	//Печать конечного автомата
	friend std::ostream & operator<<(std::ostream & os, const FiniteStateMachine & m ) 
	{
		const int os_width = 3;
		os.width(os_width);
		os << ' ';
		os << ' ';
		for (size_t i = 0; i < m.sigma[0].size(); ++i)
		{
			os.width(os_width);
			os << i;
			os << ' ';
		}
		os << "\n\n";
		for (auto i = begin(m.alphabet); i != end(m.alphabet); ++i)
		{
			os.width(os_width);
			os << i->first;
			os << ' ';
			for (size_t j = 0; j < m.sigma[0].size(); ++j)
			{
				os.width(os_width);
				os << m.sigma[i->second][j];
				os << ' ';
			}
			os << '\n';
		}
		return os;
	}

	//Возвращает количество сравнений, выполненых при построении автомата
	size_t get_cmp_count() const
	{
		return cmp_count;
	}

private:
	//True, если P_k является суффиксом P_q+a
	bool is_suffix(const std::string & P, int k, int q, char a)
	{
		if (k == 0)
			return true;
		if (k > q + 1 || P[k - 1] != a)
			return false;
		cmp_count++;
		for (int i1 = k - 2, i2 = q - 1; i1 >= 0 && i2 >= 0; --i1, --i2, ++cmp_count)
			if (P[i1] != P[i2])
				return false;
		return true;
	}
};

//Возвращает алфавит состоящий из символов двух строк
std::map<char, int> make_alphabet(const std::string & s1, const std::string & s2)
{
	std::map<char, int> alphabet;
	for (auto it = begin(s1); it != end(s1); ++it)
		alphabet[*it] = 0;
	for (auto it = begin(s2); it != end(s2); ++it)
		alphabet[*it] = 0;
	int index = 0;
	for (auto it = begin(alphabet); it != end(alphabet); ++it, ++index)
		it->second = index;
	return alphabet;
}

//Выполняет поиск образца P в тексте T
std::vector<int> finiteAutomatonMatcher(const std::string & P, const std::string & T, bool debug_write = false)
{
	FiniteStateMachine f(P, make_alphabet(P, T)); //построение автомата
	//std::cout << f << std::endl;
	int n = T.length();
	int m = P.length();
	int q = 0;

	size_t cmp = 0;

	std::vector<int> res;
	for (int i = 0; i < n; ++i) 
	{
		q = f.get(q, T[i]); 
		++cmp;
		if (q == m)
		{
			res.push_back((i + 1) - m);
			//break;
		}
	}

	//вывод количества сравнений
	if (debug_write)
		std::cout << "cmp_count = " << cmp << " + " << f.get_cmp_count() << '\n';

	return res;
}