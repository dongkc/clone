#include "FileManager.h"

#include "Utils/NameGenerator.h"

#include <iostream>
#include <memory>


namespace Clone { namespace File
{

    FileManager::FileManager(const std::string& baseFileName_)
        :_baseFileName(baseFileName_)
    {
    }

    void FileManager::createFile(std::shared_ptr<std::fstream>& fileHandlePtr_)
    {
        fileHandlePtr_ = std::make_shared<std::fstream>(_baseFileName,
                                                        std::ios::out| 
                                                        std::ios::binary|
                                                        std::ios::trunc);
    }

    void FileManager::
    createFiles(int count_,
                std::vector<std::shared_ptr<std::fstream> >& fileHandles_)
    {
        Utils::NameGenerator nameGenerator;
        std::string newFileName;

        newFileName = 
            nameGenerator.createNameAppendedWithThreeDigitNumber(_baseFileName);

        //std::ofstream createFile(newFileName.c_str());
        //createFile.close();

        fileHandles_.push_back(
            std::make_shared<std::fstream>(
                newFileName.c_str(),
                std::fstream::out| 
                std::fstream::binary));

        if(!fileHandles_[0]->is_open())
        {
            std::cout << "Failed to open: <"
                      << newFileName
                      << ">\r\n";
        }

        for(int i = 1; i < count_; i++)
        {
            newFileName = 
                nameGenerator.createNameAppendedWithThreeDigitNumber(_baseFileName);
            std::cout << "New FileName: "
                      << newFileName
                      << "\r\n";

            std::ofstream createFile(newFileName.c_str());
            createFile.close();

            fileHandles_.push_back(
                std::make_shared<std::fstream>(
                    newFileName.c_str(),
                    std::fstream::out|
                    std::fstream::in|
                    std::fstream::binary));

            if(!fileHandles_[i]->is_open())
            {
                std::cout << "Failed to open "
                          << newFileName
                          << ".\r\n";
            }
        }
    }

    void FileManager::mergeFiles(std::vector<std::shared_ptr<std::fstream> >& fileHandles_)
    {
        fileHandles_[0]->seekp(0, std::ios_base::end);
        for(int i = 1; i < fileHandles_.size(); i++)
        {
            fileHandles_[i]->seekp(0, std::ios_base::beg);
            *fileHandles_[0] << fileHandles_[i]->rdbuf();
        }
    }

    void FileManager::closeFiles(std::vector<std::shared_ptr<std::fstream> >& fileHandles_)
    {
        for(int i = 0; i < fileHandles_.size(); i++)
        {
            fileHandles_[i]->close();
        }
    }

    void FileManager::renameFile(const std::string& oldFileName, const std::string& newFileName)
    {
        int ret;
        ret = rename(oldFileName.c_str() , newFileName.c_str());
        if ( ret == 0)
        {
            
        }
        else
        {
            std::cout << "Error renaming";
        }
    }

    void FileManager::deleteFiles(std::vector<std::shared_ptr<std::fstream> >& fileHandles_)
    {
        Utils::NameGenerator nameGenerator;
        std::string newFileName;
        int ret;

        //Leave first file ending in 000
        newFileName =  nameGenerator.createNameAppendedWithThreeDigitNumber(_baseFileName);

        for(int i=1; i< fileHandles_.size(); i++)
        {
            newFileName =  nameGenerator.createNameAppendedWithThreeDigitNumber(_baseFileName);
            ret = remove(newFileName.c_str());
            if ( ret == 0)
            {
            
            }
            else
            {
                std::cout << "Error removing file";
            }
        }
    }
}}
