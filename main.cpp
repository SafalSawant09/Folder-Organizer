// Header Files
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;
using namespace fs;

// Function Declarations
string* fillArray(string, int);
void makeFolders(string*, int);
void moveFiles(string, int);

int main()
{
    string pth;
    int nOfFiles;

    // Inputting from user
    {
        // Input path
        cout << "Enter path for your folder:" << endl;
        cin >> pth;
    
        // Input number of files in the folder
        cout << "No. of files in the folder: ";
        cin >> nOfFiles;
    }

    // Visiblity changes
    {
        // Extra line for better visibility
        cout << endl;
        // Text for the user to know the process is in progress
        cout << "Working...." << endl;
    }

    // Main Logic
    {
        // Fill array with file extensions
        string* extensions = fillArray(pth, nOfFiles);

        // Function to make folders
        makeFolders(extensions, nOfFiles);
        
        // Function to move all files to respective folders
        moveFiles(pth, nOfFiles);
    }
    
    // Text to mark completion
    cout << "Files Moved";
    
    return 0;
}

// Function Code
string* fillArray(string pth, int size)
{
    string* extensions;
    int i = 0;
    for (auto currentFile : directory_iterator(pth))
    {
        path filePath = currentFile;
        cout << filePath.extension().string() << endl;
        
        if (i <= size)
        {
            extensions[i] = filePath.extension().string();
            i++;
        }
        else
            break;
    }

    return extensions;
}

void makeFolders(string* arr, int length)
{
    for (int i = 0; i < length; i++)
    {   
        path folderPath = "Test\\" + arr[i];
        if (filesystem::create_directory(folderPath))
            continue;            
        else
            continue;
    }
}

void moveFiles(string pth, int n)
{
    for (const auto& fileEntry : directory_iterator(pth))
    {
        if (is_regular_file(fileEntry))
        {
            string ext = fileEntry.path().extension().string(); // e.g. ".txt"

            path targetFolder = pth + "\\" + ext;
            path targetPath = targetFolder / fileEntry.path().filename();

            try {
                rename(fileEntry.path(), targetPath);
            } catch (filesystem_error& e) {
                cerr << "Error moving file: " << e.what() << endl;
            }
        }
    }
}