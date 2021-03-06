﻿#include "ssstring_uty.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#endif


//=========================================================================================
//! 文字列の切り分け
/*!
	検索キーを元に文字列を切り分け、文字列の配列を返します。
	@param[in] in_str 入力文字列
	@param[in] key 検索キー
	@param[out] out_array 出力文字列配列
	@retval なし

*/
//=========================================================================================
void	split_string( const std::string &in_str , 
						const char key, 
						std::vector<std::string>& out_array )
{
	std::istringstream in(in_str);
	char c;
	out_array.clear();
	while (in)
	{
		std::string index;
		while (in.get(c) && (c != key))	index.push_back(c);

		out_array.push_back( index );
	}	
		
}


std::string path2dir(const std::string &path) {
	const std::string::size_type pos = std::max<signed>(path.find_last_of('/'), path.find_last_of('\\'));
	return (pos == std::string::npos) ? std::string()
		: path.substr(0, pos + 1);
}

std::string path2file(const std::string &path) {
	return path.substr(std::max<signed>(path.find_last_of('/'), path.find_last_of('\\')) + 1);
}



bool	is_digit_string( std::string &in_str )
{
	std::istringstream in(in_str);
	 char c;
	while (in)
	{
		in.get(c);
		if ( c < 0 ) return false;
		if ( !(isdigit( c ) || c =='.' || c=='-' || c=='+' ) )
		{
			return false;
		}
	}
	return true;
}


std::string getFullPath( const std::string& basePath , const std::string &relPath )
{
#ifdef _WIN32
	static char	curPath[_MAX_PATH];

	_chdir( basePath.c_str() );
	_getcwd( curPath , _MAX_PATH ); 

	static char	buffer_[_MAX_PATH];
	_fullpath( buffer_ , relPath.c_str() , _MAX_PATH );

	_chdir( curPath );

	std::string temp = buffer_;
	temp+= "\\";

	return temp;
#else
	char	buffer_[2048];
	char	curPath[2048];
	char	curPath2[2048];
    getwd(curPath);
    
    if ( basePath[0]!='/')
    {
        std::string str = curPath;
        str+="/";
        str+= basePath;
        realpath( str.c_str() , curPath2 );
        chdir( curPath2 );
        std::string temp = relPath;
        realpath(temp.c_str(),buffer_ );
        //std::string ret_str = relPath + "/";
        return relPath;
    }else{
        chdir( basePath.c_str());
        std::string temp = basePath + relPath;
        realpath(temp.c_str(),buffer_ );
    }
        
    
    chdir(curPath);
    std::string ret_temp;
    ret_temp = buffer_;
    ret_temp+="/";
    return ret_temp;
#endif

}
