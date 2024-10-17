/*==============================================================================
==============================================================================*/
#include "stdafx.h"

#pragma warning(disable:6387)

#include "cmnPaths.h"

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants.

static const int cMaxPath = 512;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Regional variables.

static bool rPathsInitFlag = false;
static char* rFilesDir = 0;
static char* rLogDir = 0;
static char* rDataDir = 0;

void guard_paths_init();
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize. This must be called first.

void initialize_paths_cli()
{
   rFilesDir = (char*)malloc(cMaxPath);
   Ris::portableFullPath(rFilesDir, "../files");
   strcat(rFilesDir, "/");

   rLogDir = (char*)malloc(cMaxPath);
   Ris::portableFullPath(rLogDir, "../log");
   strcat(rLogDir, "/");

   rDataDir = (char*)malloc(cMaxPath);
   Ris::portableFullPath(rDataDir, "../data");
   strcat(rDataDir, "/");

   rPathsInitFlag = true;
}

void initialize_paths_gui()
{
   rFilesDir = (char*)malloc(cMaxPath);
   Ris::portableFullPath(rFilesDir, "..\\files");
   strcat(rFilesDir, "\\");

   rLogDir = (char*)malloc(cMaxPath);
   strcpy(rLogDir, getenv("USERPROFILE"));
   strcat(rLogDir, "\\AppData\\Roaming\\Stenograph\\StenographBluetooth\\log\\");

   rDataDir = (char*)malloc(cMaxPath);
   strcpy(rDataDir, getenv("USERPROFILE"));
   strcat(rDataDir, "\\AppData\\Roaming\\Stenograph\\StenographBluetooth\\data\\");

   rPathsInitFlag = true;
}

void finalize_paths()
{
   guard_paths_init();
   free(rFilesDir);
   free(rLogDir);
   free(rDataDir);
   rPathsInitFlag = false;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return directory paths.

void guard_paths_init()
{
   if (!rPathsInitFlag)
   {
      printf("NG::Paths NOT INITIALIZED exiting program\n");
      exit(-1);
   }
}

const char* get_filesdir()
{
   guard_paths_init();
   return rFilesDir;
}

const char* get_datadir()
{
   guard_paths_init();
   return rDataDir;
}

const char* get_logdir()
{
   guard_paths_init();
   return rLogDir;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Return file paths relative to directory paths.

const char* get_files_filepath(char* aBuffer, const char* aFileName)
{
   guard_paths_init();
   strcpy(aBuffer, get_filesdir());
   strcat(aBuffer, aFileName);
   return aBuffer;
}

const char* get_data_filepath(char* aBuffer, const char* aFileName)
{
   guard_paths_init();
   strcpy(aBuffer, get_datadir());
   strcat(aBuffer, aFileName);
   return aBuffer;
}

const char* get_log_filepath(char* aBuffer, const char* aFileName)
{
   guard_paths_init();
   strcpy(aBuffer, get_logdir());
   strcat(aBuffer, aFileName);
   return aBuffer;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create a new string and fill it with a file path relative to a directory
// path. The string must be deleted by the caller when done.

std::unique_ptr<std::string> get_files_filepath(const char* aFileName)
{
   guard_paths_init();
   auto tString = std::make_unique<std::string>(get_filesdir());
   *tString += aFileName;
   return tString;
}

std::unique_ptr<std::string> get_data_filepath(const char* aFileName)
{
   guard_paths_init();
   auto tString = std::make_unique<std::string>(get_datadir());
   *tString += aFileName;
   return tString;
}

std::unique_ptr<std::string> get_log_filepath(const char* aFileName)
{
   guard_paths_init();
   auto tString = std::make_unique<std::string>(get_logdir());
   *tString += aFileName;
   return tString;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Create a new string and fill it with a file path that is determined
// by a file identifier. The string must be deleted by the caller when done.

std::unique_ptr<std::string> get_filepath_from_id(int aFileId)
{
   guard_paths_init();
   switch (aFileId)
   {
   case cFile_CommXRay: return get_log_filepath("aaa_comm.sgxr2");
   case cFile_CommStroke: return get_log_filepath("aaa_comm.sgstn");
   case cFile_CatXRay: return get_log_filepath("aaa_catem.sgxr2");
   case cFile_CatStroke: return get_log_filepath("aaa_catem.sgstn");
   case cFile_InputStroke: return get_data_filepath("current_strokes.sgstn");
   case cFile_KbdCalib: return get_files_filepath("kbdcalib.bin");
   case cFile_KbdConsts: return get_files_filepath("kbdconsts.bin");
   case cFile_KbdStenoTable: return get_files_filepath("kbdstenotable.bin");
   case cFile_CatScript_Test1: return get_files_filepath("script_cat_test1.txt");
   case cFile_CatScript_Run2: return get_files_filepath("script_cat_run2.txt");
   case cFile_Dictionary: return get_log_filepath("dictionary.ngdct");
   case cFile_STestScript_Test1: return get_files_filepath("script_stest_test1.txt");
   case cFile_STestScript_Test2: return get_files_filepath("script_stest_test2.txt");
   case cFile_STestStroke: return get_log_filepath("aaa_stest.sgstn");
   case cFile_CTestScript_Test1: return get_files_filepath("script_ctest_test1.txt");
   case cFile_CTestScript_Test2: return get_files_filepath("script_ctest_test2.txt");
   default:
      auto tString = std::make_unique<std::string>("BAD FILEID");
      return tString;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

void paths_test1()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

void paths_show()
{
   Prn::print(0, "paths*********************BEGIN");

   Prn::print(0, "files    %s", get_filesdir());
   Prn::print(0, "log      %s", get_logdir());
   Prn::print(0, "data     %s", get_datadir());

   Prn::print(0, "paths*********************END");
   return;

   auto tString1 = get_filepath_from_id(cFile_KbdCalib);
   Prn::print(0, "KbdCalib %s", tString1->c_str());

   std::unique_ptr<std::string> tString2 = get_log_filepath("mylog.txt");
   Prn::print(0, "LogFile  %s", tString2->c_str());

   Prn::print(0, "paths*********************END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
#if 0
void initialize_paths()
{
   rFilesDir = (char*)malloc(cMaxPath);
   Ris::portableFullPath(rFilesDir, "..\\files");
   strcat(rFilesDir, "\\");
   if (!Ris::portableFilePathExists(rFilesDir))
   {
      strcpy(rFilesDir, "C:\\Program Files\\Stenograph\\BthProxy\\files\\");
   }

   rLogDir = (char*)malloc(cMaxPath);
   Ris::portableFullPath(rLogDir, "..\\log");
   strcat(rLogDir, "\\");
   if (!Ris::portableFilePathExists(rLogDir))
   {
      strcpy(rLogDir, getenv("userprofile"));
      strcat(rLogDir, "\\AppData\\Roaming\\Stenograph\\BthProxy\\log\\");
   }

   rDataDir = (char*)malloc(cMaxPath);
   Ris::portableFullPath(rDataDir, "..\\data");
   strcat(rDataDir, "\\");
   if (!Ris::portableFilePathExists(rDataDir))
   {
      strcpy(rDataDir, getenv("userprofile"));
      strcat(rDataDir, "\\AppData\\Roaming\\Stenograph\\BthProxy\\data\\");
   }

   rPathsInitFlag = true;
}
#endif