#include "pch.h" 
#include <fstream> 
#include"C:\Users\Даниил Михайлович\source\repos\AISD_lab3_sem4\AISD_lab3_sem4\AISD_lab3_sem4.cpp"
#include "CppUnitTest.h" 
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

std::ifstream file(R"(C:\Users\Даниил Михайлович\source\repos\AISD_lab3_sem4\AISD_lab3_sem4\data.txt)"); adjacency_matrix adj_matrix;

	TEST_CLASS(lab_3)
	{
	public:
		TEST_METHOD(find_city_1)
		{
			string s = read(file);
			string city = "Moscow";
			gleipnir<std::string> cities = get_cities(s);
			Assert::IsTrue(cities.find(&city));
		}
		TEST_METHOD(find_city_2)
		{
			file.close();
			file.open(R"(C:\Users\Даниил Михайлович\source\repos\AISD_lab3_sem4\AISD_lab3_sem4\data.txt)"); std::string s = read(file);
			string city = "Samara";
			gleipnir<string> cities = get_cities(s);
			Assert::IsTrue(cities.find(&city));
		}
		TEST_METHOD(not_find_city_1)
		{
			string s = read(file);
			string city = "Ryazan";
			gleipnir<std::string> cities = get_cities(s);
			Assert::IsFalse(cities.find(&city));
		}
		TEST_METHOD(not_find_city_2)
		{
			string s = read(file);
			string city = "Ryazan";
			gleipnir<std::string> cities = get_cities(s);
			Assert::IsFalse(cities.find(&city));
		}
		TEST_METHOD(min_road_1)
		{
			file.close();
			file.open(R"(C:\Users\Даниил Михайлович\source\repos\AISD_lab3_sem4\AISD_lab3_sem4\data.txt)"); make_adjacency_matrix(file, adj_matrix);
			Assert::IsTrue(adj_matrix.matrix[0][1] == 7000);
		}
		TEST_METHOD(min_road_2)
		{
			file.close();
			file.open(R"(C:\Users\Даниил Михайлович\source\repos\AISD_lab3_sem4\AISD_lab3_sem4\data.txt)"); make_adjacency_matrix(file, adj_matrix);
			Assert::IsTrue(adj_matrix.matrix[3][3] == INF);
		}
	};
