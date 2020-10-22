// EvrakCantam.cpp : Defines the entry point for the application.
//

#include "EvrakCantam.h"
#include <filesystem>
#include <ctime>
#include <chrono>
#include <vector>

namespace fs = std::filesystem;

using namespace std;

// Settings
const string AYARDOSYA = "";

//string yerelYol = "C:\\Users\\Caner\\Desktop\\testDir1\\";
//string seyyarYol = "C:\\Users\\Caner\\Desktop\\testDir2\\";

string yerelYol = "/home/caner/test/testdir1";
string seyyarYol = "/home/caner/test/testdir2";

const string settingsPath="EvrakCantam.settings";

struct dosya {
	string yol;
	uintmax_t boyut;
	time_t tarih;
};

vector<dosya> yerelDosyalar;

template <typename TP>
std::time_t to_time_t(TP tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
		+ system_clock::now());
	return system_clock::to_time_t(sctp);
}

int main()
{
	ayarlariYukle();
	cout << yerelYol << endl;
	cout << seyyarYol << endl << endl;

	yerelKlasorOku();

	return 0;
}

//Load settings from settings file.
bool ayarlariYukle()
{
	return true;
}

//Scan local files
void yerelKlasorOku()
{
	int i = 0;
	for (const auto& rawYerelDosyalar : fs::recursive_directory_iterator(yerelYol))
	{
		if(fs::is_directory(rawYerelDosyalar.path())) continue;
		yerelDosyalar.push_back(dosya());
		yerelDosyalar[i].yol = rawYerelDosyalar.path().string();
		yerelDosyalar[i].boyut = fs::file_size(rawYerelDosyalar.path());
		yerelDosyalar[i].tarih = to_time_t(fs::last_write_time(rawYerelDosyalar.path()));

		char buff[40];
		strftime(buff, 40, "%d.%m.%Y", localtime(&yerelDosyalar[i].tarih));
		std::cout << yerelDosyalar[i].yol << "\t" << yerelDosyalar[i].boyut << "\t" << buff << std::endl;
	}

}