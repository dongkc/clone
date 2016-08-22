#ifndef CLONE_FILE_FILEMANAGER_H
#define CLONE_FILE_FILEMANAGER_H

#include <fstream>
#include <vector>
#include <memory>

namespace Clone { namespace File
{
    class FileManager
    {
    public:
        FileManager(){}
        FileManager(const std::string& baseFileName_);
        void createFiles(int count_,
                         std::vector<std::shared_ptr<std::fstream> >& fileHandles_);

        void createFile(std::shared_ptr<std::fstream>& fileHandlePtr_);
        void mergeFiles(std::vector<std::shared_ptr<std::fstream> >& fileHandles_);
        void closeFiles(std::vector<std::shared_ptr<std::fstream> >& fileHandles_);
        void renameFile(const std::string& oldFileName, const std::string& newFileName);
        void deleteFiles(std::vector<std::shared_ptr<std::fstream> >& fileHandles_);

    protected:
        std::string                             _baseFileName;
    };
}}


#endif
