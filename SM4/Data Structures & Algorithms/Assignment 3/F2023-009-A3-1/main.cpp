#include <iostream>
#include <fstream>
#include <filesystem>
#include <cctype> // For isalpha
using namespace std;
namespace fs = std::filesystem;

void traverse(const fs::path &path)
{
    if (!fs::exists(path))
        return;

    fs::path leftPath = path / "left";
    fs::path rightPath = path / "right";

    if (fs::exists(leftPath) || fs::exists(rightPath))
    {
        // Not a leaf folder
        if (fs::exists(leftPath))
            traverse(leftPath);
        if (fs::exists(rightPath))
            traverse(rightPath);
    }
    else
    {
        // This is a leaf folder, look for .txt file
        for (const auto &entry : fs::directory_iterator(path))
        {
            if (entry.path().extension() == ".txt")
            {
                cout << "📄 Found text file: " << entry.path() << endl;

                ifstream file(entry.path());
                char ch;
                cout << "🔠 Alphabets in file: ";
                while (file >> ch)
                {
                    if (isalpha(ch))
                        cout << ch;
                }
                cout << endl;
                file.close();
            }
        }
    }
}

int main()
{
    fs::path root = "charTree"; // This should be in your project folder
    traverse(root);
    return 0;
}