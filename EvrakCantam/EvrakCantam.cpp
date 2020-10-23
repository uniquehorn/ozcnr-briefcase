// EvrakCantam.cpp : Defines the entry point for the application.
//

#include "EvrakCantam.h"
#include <filesystem>
#include <ctime>
#include <vector>
#include <fstream>

namespace fs = std::filesystem;

using namespace std;

// Settings
#ifdef _WIN32
	const string HOME_DIR =getenv("USER");
	const string SETTING_SUB_DIR ="\\EvrakCantam";
#else 
	const string HOME_DIR=getenv("HOME");
	const string SETTING_SUB_DIR ="/.EvrakCantam";
#endif
const string SETTING_FILE = "/EvrakCantam.settings";
const string SETTING_DIR = HOME_DIR + SETTING_SUB_DIR;
const string SETTING_FULL = SETTING_DIR + SETTING_FILE;

string yerelYol = "/home/caner/test/testdir1";
string seyyarYol = "/home/caner/test/testdir2";

struct dosya {
	string yol;
	uintmax_t boyut;
	time_t tarih;
};

vector<dosya> yerelDosyalar, seyyarDosyalar;

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
	yerelKlasorOku();
	portDirScan();

	return 0;
}

//Load settings from settings file.
bool ayarlariYukle()
{
	fs::path settingsDir=fs::path(SETTING_DIR);
	if(!fs::exists(settingsDir))
		fs::create_directory(settingsDir);

	if(fs::exists(fs::path(SETTING_FULL)))
	{
		std::ifstream setStr(SETTING_FULL);
		string satir;
		while(setStr >> satir)
		{
			int delimeter=satir.find_first_of('=');
			string setName = satir.substr(0,delimeter);
			string setVal = satir.substr(delimeter+1, satir.npos);

			if		(setName=="localDir") 	{ yerelYol=setVal; }
			else if (setName=="portDir") 	{ seyyarYol = setVal; }
		}

	} else 
	{
		std::ofstream settingStream(SETTING_FULL);
		settingStream.close();

		//TO-DO: Write default settings. Ask for directories.
	}

	return true;
}

//Scan local files
void yerelKlasorOku()
{
	cout << "YEREL DOSYALAR" << endl;
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

//Scan portable files
void portDirScan()
{
	cout << "SEYYAR DOSYALAR" << endl;
	int i = 0;
	for (const auto& rawPortFiles : fs::recursive_directory_iterator(seyyarYol))
	{
		if(fs::is_directory(rawPortFiles.path())) continue;
		seyyarDosyalar.push_back(dosya());
		seyyarDosyalar[i].yol = rawPortFiles.path().string();
		seyyarDosyalar[i].boyut = fs::file_size(rawPortFiles.path());
		seyyarDosyalar[i].tarih = to_time_t(fs::last_write_time(rawPortFiles.path()));

		char buff[40];
		strftime(buff, 40, "%d.%m.%Y", localtime(&seyyarDosyalar[i].tarih));
		std::cout << seyyarDosyalar[i].yol << "\t" << seyyarDosyalar[i].boyut << "\t" << buff << std::endl;
	}

}

void scanMove()
{
	for(auto &file : yerelDosyalar)
	{
		
	}
}