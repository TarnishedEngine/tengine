#pragma once

#include <filesystem>
#include <vector>
#include <fstream>
#include <string>

#include <fmt/format.h>

#include <tengine/util/logger/logger.hpp>
#include <tengine/util/logger/logger_macros.hpp>

namespace tengine::util{

enum RecursiveFileByExtErr{

  ERR_OK,
  ERR_PATH_NOT_DIR,
  ERR_PATH_DOES_NOT_EXIST,

};

/**
 * @brief Gets all valid files of a particular extension in a directory recursively
 * @param dir Directory to scan for files
 * @param paths Vector onto which valid files' filepaths will be pushed
 * @param ext Extension to filter files by
 */
inline RecursiveFileByExtErr recursiveFileByExtension(const std::filesystem::path& dir, std::vector<std::filesystem::path>& paths, const std::string& ext){

  if(!std::filesystem::exists(dir)){
    TENGINE_LOG_ERROR("recursiveFileByExtension()", fmt::format("Path {} passed does not exist!", dir.string()));
    return RecursiveFileByExtErr::ERR_PATH_DOES_NOT_EXIST;
  }
  if(!std::filesystem::is_directory(dir)){
    TENGINE_LOG_ERROR("recursiveFileByExtension()", fmt::format("Path {} passed is not a directory!", dir.string()));
    return RecursiveFileByExtErr::ERR_PATH_NOT_DIR;
  }

  for(const auto& entry : std::filesystem::recursive_directory_iterator(dir)){

    if(entry.is_regular_file() && entry.path().extension() == ext){
      TENGINE_LOG_DEBUG("recursiveFileByExtension()", fmt::format("Found matching file at: {}", entry.path().string()));

      std::ifstream file(entry.path());
      if(!file){
        TENGINE_LOG_ERROR("recursiveFileByExtension()", fmt::format("Unable to open file at: {}", entry.path().string()));
        continue;
      }

      paths.push_back(entry);

    }

  }

  TENGINE_LOG_DEBUG("recursiveFileByExtension()", fmt::format("Finished scanning for files in {}", dir.string()));
  return RecursiveFileByExtErr::ERR_OK;

}

}