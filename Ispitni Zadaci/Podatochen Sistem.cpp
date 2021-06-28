#include<iostream>
#include<cstring>
enum Extension {txt, pdf, exe};

using namespace std;
class File {
    char *fileName;
    enum Extension ext;
    char *fileOwner;
    int fileSize;

public:
    File() {
        this->fileName=new char [0];
        ext=txt;
        this->fileOwner= new char[0];
        this->fileSize=0;
    }


    File(const char *fileName, const char *fileOwner, int fileSize, Extension ext ) {
        this-> fileSize=fileSize;
        this->ext=ext;
        this->fileName=new char[strlen(fileName)+1];
        strcpy(this->fileName,fileName);
        this->fileOwner=new char[strlen(fileOwner)+1];
        strcpy(this->fileOwner,fileOwner);
    }

    File(const File &f) {
        this-> fileSize=f.fileSize;
        this->ext=f.ext;
        this->fileName=new char[strlen(f.fileName)+1];
        strcpy(this->fileName,f.fileName);
        this->fileOwner=new char[strlen(f.fileOwner)+1];
        strcpy(this->fileOwner,f.fileOwner);

    }

    File& operator=(const File &f) {
        if(this!=&f) {
            this-> fileSize=f.fileSize;
            this->ext=f.ext;
            delete [] this->fileName;
            delete [] this->fileOwner;
            this->fileName=new char[strlen(f.fileName)+1];
            strcpy(this->fileName,f.fileName);
            this->fileOwner=new char[strlen(f.fileOwner)+1];
            strcpy(this->fileOwner,f.fileOwner);

        }

        return *this;
    }

    ~File () {
        delete [] this->fileOwner;
        delete [] this->fileName;

    }

    Extension getExt () {
        return ext;
    }

    void print() {
        cout<<"File name: "<<this->fileName<<".";
        if(ext==0)
            cout<<"pdf"<<endl;

        else if(ext==1) cout<<"txt"<<endl;
        else cout<<"exe"<<endl;

        cout<<"File owner: "<<this->fileOwner<<endl;
        cout<<"File size: "<<this->fileSize<<endl;
    }

    bool equals(const File &f) {
        return (strcmp(this->fileName,f.fileName)==0)&&(strcmp(this->fileOwner,f.fileOwner)==0)&&(this->ext==f.ext);
    }

    bool equalsType(const File & f) {
        return (strcmp(this->fileName,f.fileName)==0)&&(this->ext==f.ext);
    }


};

class Folder {
    char *name;
    int filenumber;
    File *niza;

public:
    Folder () {
        this->name= new char[0];
        this->filenumber=0;
        this->niza= new File[0];
    }

    Folder (const char *name) {

        this->filenumber=0;
        this->niza= new File[this->filenumber];
        for(int i=0; i<this->filenumber; i++) {
            this->niza[i]=niza[i];
        }


        this->name= new char[strlen(name)+1];
        strcpy(this->name,name);
    }

    Folder (const Folder &dir) {

        this->filenumber=dir.filenumber;
        this->niza= new File[this->filenumber];
        for(int i=0; i<this->filenumber; i++) {
            this->niza[i]=dir.niza[i];
        }


        this->name= new char[strlen(dir.name)+1];
        strcpy(this->name,dir.name);

    }

    Folder& operator=(const Folder &dir) {
        if(this!=&dir) {
            this->filenumber=dir.filenumber;
            this->niza= new File[this->filenumber];
            for(int i=0; i<this->filenumber; i++) {
                this->niza[i]=dir.niza[i];
            }

            this->name= new char[strlen(dir.name)+1];
            strcpy(this->name,dir.name);


        }
        return *this;

    }

    ~Folder() {
        delete [] this->niza;
        delete [] this->name;
    }


    void remove(const File & file){
    int counter=0;
    for(int i=0;i<this->filenumber;i++){
        if(!(this->niza[i].equals(file))){
          niza[counter] = niza[i];
            counter++;
        }
    }
    filenumber=counter;
    }
    void add(const File & file) {
        File *tmp= new File [this->filenumber+1];
        for(int i=0; i<this->filenumber; i++) {
            tmp[i]=this->niza[i];
        }
        tmp[this->filenumber++]=file;
        delete [] this->niza;
        niza=tmp;
    }

    void print() {
        cout<<"Folder name: "<<this->name<<endl;


        for(int i=0; i<this->filenumber; i++)
            this->niza[i].print();
    }



};


int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    } else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    } else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    } else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    } else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
