#include <iostream>

class String
{
private:
	int m_size;
	char* m_string;

public:
	String()
		: m_size(0), m_string(0) {}

	String(const char* string)
		: m_size(strlen(string)), m_string(new char[m_size + 1])
	{
		for (int i = 0; i < m_size; i++)
		{
			m_string[i] = string[i];
		}

		m_string[m_size] = '\0';
	}

	String(const String& string)
		: m_size(string.m_size), m_string(new char[m_size + 1])
	{
		for (int i = 0; i < m_size; i++)
		{
			m_string[i] = string.m_string[i];
		}

		m_string[m_size] = '\0';
	}

	const char& operator[](const int index) const
	{
		return m_string[index];
	}

	friend bool operator==(const String& s1, const String& s2);
	friend bool operator!=(const String& s1, const String& s2);
	friend bool operator>(const String& s1, const String s2);
	friend bool operator<(const String& s1, const String s2);
	friend std::istream& operator>>(std::istream& is, const String s1);
	friend std::ostream& operator<<(std::ostream& os, const String s1);

	String operator+(const String& s1)
	{
		String temp;
		temp.m_size = this->m_size + s1.m_size;
		delete[] temp.m_string;
		temp.m_string = new char[temp.m_size + 1];

		for (int i = 0; i < this->m_size; i++)
		{
			temp.m_string[i] = this->m_string[i];
		}

		for (int i = this->m_size; i < temp.m_size; i++)
		{
			temp.m_string[i] = s1.m_string[i - s1.m_size];
		}

		temp.m_string[temp.m_size] = '\0';

		return temp;
	}

	int find(const char* string)
	{
		int result_index = 0;
		int index = 0;
		int i_string = 0;

		for (int i = 0; i < this->m_size; i++)
		{
			if (this->m_string[i] == string[i_string])
			{
				index++;
				i_string++;
				result_index = i;
			}
			else
			{
				if (index == strlen(string))
				{
					break;
				}
				else
				{
					index = 0;
					i_string = 0;
					result_index = 0;
				}
			}
		}

		result_index -= strlen(string) - 1;

		return result_index;
	}

	void replace(const char* string, const char* replace_string)
	{
		int begin_index = find(string);

		if (begin_index >= 0)
		{
			char* t_string = new char[this->m_size - strlen(string)];

			for (int i = 0; i < begin_index; i++)
			{
				t_string[i] = this->m_string[i];
			}

			for (int i = begin_index + strlen(string); i < this->m_size; i++)
			{
				t_string[i - strlen(string)] = this->m_string[i];
			}

			delete[] this->m_string;

			this->m_size = this->m_size + (strlen(replace_string) - strlen(string));
			this->m_string = new char[m_size + 1];

			for (int i = 0; i < begin_index; i++)
			{
				this->m_string[i] = t_string[i];
			}

			for (int i = begin_index; i < (begin_index + (strlen(replace_string))); i++)
			{
				this->m_string[i] = replace_string[i - begin_index];   
			}

			for (int i = begin_index + (strlen(replace_string)); i < this->m_size; i++)
			{
				this->m_string[i] = t_string[i - strlen(replace_string)];
			}

			this->m_string[this->m_size] = '\0';

			delete[] t_string;
		}
	}

	void removalEnd(int number_removal)
	{
		char* t_string = new char[this->m_size - number_removal];

		for (int i = 0; i < this->m_size - number_removal; i++)
		{
			t_string[i] = this->m_string[i];
		}

		delete[] this->m_string;
		this->m_size -= number_removal;
		this->m_string = new char[m_size + 1];

		for (int i = 0; i < this->m_size; i++)
		{
			this->m_string[i] = t_string[i];
		}

		delete[] t_string;

		this->m_string[this->m_size] = '\0';
	}

	void insert(const char* string, int insert_index)
	{
		if (insert_index >= 0 && insert_index < this->m_size)
		{
			char* t_string = new char[this->m_size];

			for (int i = 0; i < this->m_size; i++)
			{
				t_string[i] = this->m_string[i];
			}

			delete[] this->m_string;
			this->m_size += strlen(string);
			this->m_string = new char[this->m_size + 1];

			for (int i = 0; i < insert_index; i++)
			{
				this->m_string[i] = t_string[i];
			}

			for (int i = insert_index; i < insert_index + strlen(string); i++)
			{
				this->m_string[i] = string[i - insert_index];
			}

			for (int i = insert_index + strlen(string); i < this->m_size; i++)
			{
				this->m_string[i] = t_string[i - strlen(string)];
			}

			delete[] t_string;

			this->m_string[this->m_size] = '\0';
		}
	}

	~String()
	{
		delete[] this->m_string;
		this->m_string = 0;
	}
};

bool operator==(const String& s1, const String& s2)
{
	if (s1.m_size != s2.m_size)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < s1.m_size; i++)
		{
			if (s1[i] == s2[i])
			{
				continue;
			}
			else
			{
				return false;
			}
		}

		return true;
	}
}

bool operator!=(const String& s1, const String& s2)
{
	if (s1.m_size != s2.m_size)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < s1.m_size; i++)
		{
			if (s1[i] != s2[i])
			{
				return true;
			}
		}

		return false;
	}
}

bool operator>(const String& s1, const String s2)
{
	int size;
	s1.m_size < s2.m_size ? size = s1.m_size : size = s2.m_size;

	for (int i = 0; i < size; i++)
	{
		if (s1[i] > s2[i])
		{
			return true;
		}
	}
	if (s1.m_size > s2.m_size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator<(const String& s1, const String s2)
{
	int size;
	s1.m_size < s2.m_size ? size = s1.m_size : size = s2.m_size;

	for (int i = 0; i < size; i++)
	{
		if (s1[i] < s2[i])
		{
			return true;
		}
	}
	if (s1.m_size < s2.m_size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::istream& operator>>(std::istream& is, const String s1) // Доробити
{
	return is;
}

std::ostream& operator<<(std::ostream& os, const String s1)
{
	os << s1.m_string;
	return os;
}

int main()
{
	String s1 = "Hello, world!";
	String s2 = s1;
	std::cout << s1 << '\n';

	std::cout << s1.find("Hello") << '\n';

	s1.replace("ll", "wwo");
	std::cout << s1 << '\n';

	s1.removalEnd(3);
	std::cout << s1 << '\n';

	s1.insert("qqq", 8);
	std::cout << s1 << '\n';


	return 0;
}