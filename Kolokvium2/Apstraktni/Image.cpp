#include <iostream>
#include <cstring>
using namespace std;

class Image {
protected:
    char *name;
    char owner[50];
    int width;
    int height;

    void copy(const Image &other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        strcpy(owner, other.owner);
        width = other.width;
        height = other.height;
    }

public:
    Image(const char *name = "untitled", const char *owner = "unknown", int width = 800, int height = 800) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->owner, owner);
        this->width = width;
        this->height = height;
    }

    Image(const Image &other) {
        copy(other);
    }

    Image& operator=(const Image &other) {
        if (this != &other) {
            delete[] name;
            copy(other);
        }
        return *this;
    }

    virtual ~Image() {
        delete[] name;
    }

    virtual int fileSize() const {
        return width * height * 3;
    }

    friend ostream& operator<<(ostream &out, const Image &image) {
        out << image.name << " " << image.owner << " " << image.fileSize() << endl;
        return out;
    }

    bool operator>(const Image &other) const {
        return this->fileSize() > other.fileSize();
    }
};

class TransparentImage : public Image {
private:
    bool supportsTransparency;

public:
    TransparentImage(const char *name = "untitled", const char *owner = "unknown", int width = 800, int height = 800, bool supportsTransparency = false)
    : Image(name, owner, width, height) {
        this->supportsTransparency = supportsTransparency;
    }

    int fileSize() const override {
        if (supportsTransparency) {
            return width * height * 4;
        } else {
            return width * height + (width * height) / 8;
        }
    }

    friend ostream& operator<<(ostream &out, const TransparentImage &image) {
        out << image.name << " " << image.owner << " " << image.fileSize() << endl;
        return out;
    }
};

class Folder {
protected:
    char folderName[255];
    char owner[50];
    Image *images[100];
    int numImages;

    void copy(const Folder &other) {
        strcpy(folderName, other.folderName);
        strcpy(owner, other.owner);
        numImages = other.numImages;
        for (int i = 0; i < numImages; ++i) {
            images[i] = other.images[i];
        }
    }

public:
    Folder(const char *folderName = "", const char *owner = "unknown") {
        strcpy(this->folderName, folderName);
        strcpy(this->owner, owner);
        numImages = 0;
    }

    Folder(const Folder &other) {
        copy(other);
    }

    Folder& operator=(const Folder &other) {
        if (this != &other) {
            copy(other);
        }
        return *this;
    }

    int folderSize() const {
        int size = 0;
        for (int i = 0; i < numImages; ++i) {
            size += images[i]->fileSize();
        }
        return size;
    }

    Image* getMaxFile() const {
        if (numImages == 0) {
            return nullptr;
        }

        Image *maxFile = images[0];
        for (int i = 1; i < numImages; ++i) {
            if (*images[i] > *maxFile) {
                maxFile = images[i];
            }
        }
        return maxFile;
    }

    Folder& operator+=(Image *image) {
        if (numImages < 100) {
            images[numImages++] = image;
        }
        return *this;
    }

    Image* operator[](int index) const {
        if (index < 0 || index >= numImages) {
            return nullptr;
        }
        return images[index];
    }

    friend ostream& operator<<(ostream &out, const Folder &folder) {
        out << folder.folderName << " " << folder.owner << " \n--\n";
        for (int i = 0; i < folder.numImages; ++i) {
            out << *folder.images[i];
        }
        out << "--\nFolder size: " << folder.folderSize() << endl;
        return out;
    }
};

Folder max_folder_size(Folder folders[], int numFolders) {
    Folder maxFolder = folders[0];
    for (int i = 1; i < numFolders; ++i) {
        if (folders[i].folderSize() > maxFolder.folderSize()) {
            maxFolder = folders[i];
        }
    }
    return maxFolder;
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class Image

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;

        Image f1;
        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TransparentImage
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
}