#pragma once

/*==============================================================================
nextgen file paths.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include <string>
#include <memory>

namespace Cmn
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constants. File identifiers.

// File codes.
static const int cFile_CommXRay = 101;
static const int cFile_CommStroke = 102;
static const int cFile_CatXRay = 103;
static const int cFile_CatStroke = 104;
static const int cFile_InputStroke = 105;
static const int cFile_KbdCalib = 201;
static const int cFile_KbdConsts = 202;
static const int cFile_KbdStenoTable = 203;
static const int cFile_CatScript_Test1 = 301;
static const int cFile_CatScript_Run2 = 302;
static const int cFile_Dictionary = 401;
static const int cFile_STestScript_Test1 = 501;
static const int cFile_STestScript_Test2 = 502;
static const int cFile_STestStroke = 503;
static const int cFile_CTestScript_Test1 = 601;
static const int cFile_CTestScript_Test2 = 602;

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Initialize. This must be called after the program directory is set.
void initialize_paths_cli();
void initialize_paths_gui();
void finalize_paths();

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Return a directory path.
const char* get_filesdir();
const char* get_datadir();
const char* get_logdir();

// Return a file path relative to a directory path.
const char* get_files_filepath(char* aBuffer, const char* aFileName);
const char* get_data_filepath(char* aBuffer, const char* aFileName);
const char* get_log_filepath(char* aBuffer, const char* aFileName);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

// Create a new string and fill it with a file path relative to a directory
// path.
std::unique_ptr<std::string> get_files_filepath(const char* aFileName);
std::unique_ptr<std::string> get_data_filepath(const char* aFileName);
std::unique_ptr<std::string> get_log_filepath(const char* aFileName);

// Create a new string and fill it with a file path that is determined
// by a file identifier.
std::unique_ptr<std::string> get_filepath_from_id(int aFileId);

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Methods.

void paths_test1();
void paths_show();

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace

